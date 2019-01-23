# -*- coding: utf-8 -*-
"""
Created on Sat Jan 12 23:29:39 2019

@author: Huawei
"""

# =============================================================================
# import libs
# =============================================================================


# python train_vgg.py --dataset animals --model output/smallvggnet.model --label-bin output/smallvggnet_lb.pickle --plot output/smallvggnet_plot.png

import matplotlib
# set the matplotlib backend so figures can be saved in the background
matplotlib.use("Agg")

# import the necessary packages
from smallvggnet import SmallVGGNet
from sklearn.preprocessing import LabelBinarizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from keras.preprocessing.image import ImageDataGenerator
from keras.optimizers import SGD,Adam
from keras.utils.training_utils import multi_gpu_model

import keras.backend as K
from keras.layers import Input, Lambda
from keras.models import Model
from keras.callbacks import TensorBoard, ModelCheckpoint, ReduceLROnPlateau, EarlyStopping, LearningRateScheduler
from PIL import Image, ImageFont, ImageDraw

from yolo3 import preprocess_true_boxes, yolo_body, tiny_yolo_body, yolo_loss
from utils import get_random_data,letterbox_image,rotate,resize
from lxml import etree
from imutils import paths
from debugger import Debugger

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import argparse, pickle, csv, cv2
import os, time

# construct the argument parser and parse the arguments
#ap = argparse.ArgumentParser()
#ap.add_argument("-d", "--dataset", required=True,
#	help="path to input dataset of images")
#ap.add_argument("-m", "--model", required=True,
#	help="path to output trained model")
#ap.add_argument("-l", "--label-bin", required=True,
#	help="path to output label binarizer")
#ap.add_argument("-p", "--plot", required=True,
#	help="path to output accuracy/loss plot")
#ap.add_argument("-g", "--gpus", type=int, default=1,
#	help="# of GPUs to use for training")
#args = vars(ap.parse_args())

# =============================================================================
# global path definitions
#root_dir = os.path.expanduser('~/2019AICity_carson/Track2/')
#root_dir = os.getcwd() + '/' #/media/f/2019AICity_carson/Track2/
#train_xml = root_dir + 'aic19-track2-reid/train_label.xml'
#train_img_path = root_dir + 'aic19-track2-reid/image_train'
#train_csv = root_dir + "aic19-track2-reid/train_label.csv"
#train_feat = root_dir + "aic19-track2-reid/train_feat.txt"
#train_feat_pkl = root_dir + "aic19-track2-reid/train_feat.pkl"
#train_track = root_dir + "aic19-track2-reid/train_track.txt"
#log_dir = root_dir + "log/000"
##The following will be replaced by args
#model_path = root_dir + "output/" + time.strftime("%H_%M_%S") + "_smallvggnet.model"  
#plot_path = root_dir + "output/" + time.strftime("%H_%M_%S") + "_smallvggnet_plot.png"  
#label_bin = root_dir + "output/smallvggnet_lb.pickle"

# =============================================================================

def convert_xml(train_xml):
    '''
    Parse input_xml and return a dataframe
    '''

    tree = etree.parse(train_xml)
    root = tree.getroot()
    train_items = [] 
    for obj in root.findall('./Items/Item'):
        #order img, vid, cami
        train_items.append(obj.values())
    train_items = sorted(train_items, key = lambda x:(x[2],x[1]))
    df = pd.DataFrame(columns=obj.keys(),data = train_items)
    return df

def convert_trainlabel(train_csv):
    '''
    Parse train_label.csv and return the dataframe of vid, imageName combo
    @return: total 478 vehicles, 1 to 323 have cameraID assigned, 324 to 478 does not have cameraID
    '''
    df_csv = pd.read_csv(train_csv, header = None, names = ['vehicleID', 'imageName'])
    df_csv.sort_values(by=['vehicleID'], inplace=True)
    df_csv['vehicleID'] = df_csv['vehicleID'].apply(lambda x: format(x,'04d'))
    return df_csv

def convert_traintrack(train_track, cam2img):
    '''
    @train_track.txt, each row shows vehicles from the same camera
    @cam2img_df: the output from convert_xml
    @vid2img_df: the output from train_lable.csv for vehicleID assignment
    @output: generate the validataion data for predicting cameraID
    '''
    test_camera = []
    visited = set()
    with open(train_track, 'r') as f:
        lines = f.readlines()
    for line in lines:
        list_imgs = line.split()#same vid and same cameraID
        if all([imgName in cam2img for imgName in list_imgs]):
            for imgName in list_imgs:
                visited.add(imgName)
            continue
        else:
            test_camera.append(list_imgs)
    return test_camera, visited

# =============================================================================
#Do some cross check between train_label.csv and train_label.xml
#cam2img_df = convert_xml(train_xml)
#vid2img_df = convert_trainlabel(train_csv)
#img2vid = sorted(vid2img_df.vehicleID.unique())
#img2cam = sorted(cam2img_df.vehicleID.unique())
#vid2img = sorted(vid2img_df.imageName.unique())
#cam2img = sorted(cam2img_df.imageName.unique())
#expand the imageName to full path:
#cam2img_df['imageName'] = cam2img_df['imageName'].apply(lambda x:train_img_path+x)
#vid2img_df['imageName'] = vid2img_df['imageName'].apply(lambda x:train_img_path+x)

#label binarizer
#lb = LabelBinarizer()
#vid_bin = lb.fit_transform(img2cam)
##f = open(args["label_bin"], "wb")
#f = open(label_bin, "wb")
#f.write(pickle.dumps(lb))
#
#test_camera, visited = convert_traintrack(train_track, cam2img)
#assert img2vid == img2cam and vid2img == cam2img and not test_camera, 'Warning: train_label.xml and train_lable.csv mismatch'
# =============================================================================  

def get_train(train_img_path, train_df, size, pickle_path):
    '''
    loop over the image list from the dataframe and resize the image
    '''
#    debug = Debugger(train_feat_json)
    with open(pickle_path, "wb") as f:
#        field_names = list(train_df.columns) + ['train_feat']
#        odict = csv.DictWriter(ofile, field_names)
        
        #save the intermediate to json
        labels = []
        norm_feat = []        
        for i, (img_name, vid, cid) in enumerate(train_df.values):
            single_img = train_img_path + '/' + img_name
            # ########cv2 imread and utils.resize
            image, scale = get_random_data(single_img, size, random=True)
            assert image.shape == (size[0],size[1], 3), 'image not in uniform shape'
            image = image.flatten()
            image = image.reshape((1,image.shape[0]))
            norm_feat.append(image)
            labels.append(vid)
#            row = {'imageName': img_name, 'vehicleID': vid, 'cameraID': cid, 'train_feat': image}
#            pickle.dump(row,f)
#            #detections are stored per frame slicing
#            odict.writerow(row)
            #generate a random 
    f.close()
    return norm_feat,labels

# =============================================================================
##################Some testings##############################
# open(train_feat, 'w').close()#empty the file
# open(train_feat_pkl, 'w').close()#empty the file
# data = []
# labels = []
# norm_feat, labels= get_train(train_img_path, cam2img_df, SIZE, train_feat_pkl)
# norm_feat = np.squeeze(norm_feat, axis = 1)
# # =============================================================================
# data = np.array(norm_feat, dtype="float")
# cam2img_df['train_feat'] = pd.DataFrame(data)
# cam2img_df.to_pickle()
# #data = data / 255.0 #aready normalized in get_random_data func
# labels = np.array(labels)
# 
# #show random image
# n = len(data)
# np.random.seed(10101)  # Fixed seed for consistent colors across runs.
# rand_image = data[np.random.randint(low=1, high = n)]
# rand_image = np.array(rand_image*255, dtype = np.uint8)
# img = Image.fromarray(rand_image, 'RGB')
# img.save(root_dir + 'output/' + 'rand.png')
# img.show()
# =============================================================================
