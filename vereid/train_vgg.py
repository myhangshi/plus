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
import tensorflow as tf
from PIL import Image, ImageFont, ImageDraw

from yolo3 import preprocess_true_boxes, yolo_body, tiny_yolo_body, yolo_loss
from utils import get_random_data,letterbox_image,rotate,resize
from lxml import etree
#from imutils import paths

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import argparse, pickle, csv, cv2
import os, time

# =============================================================================
# global path definitions
root_dir = os.path.expanduser('~/2019AICity_carson/Track2/')
#root_dir = os.getcwd() + '/' #/media/f/2019AICity_carson/Track2/
train_xml = root_dir + 'aic19-track2-reid/train_label.xml'
train_img_path = root_dir + 'aic19-track2-reid/image_train/'
train_csv = root_dir + "aic19-track2-reid/train_label.csv"
train_feat = root_dir + "aic19-track2-reid/train_feat.csv"
train_feat_pkl = root_dir + "aic19-track2-reid/train_feat.pkl"
train_track = root_dir + "aic19-track2-reid/train_track.txt"
log_dir = root_dir + "log/000/"
label_bin = root_dir + "output/smallvggnet_lb.pickle"
#The following will be replaced by args
model_path = root_dir + "output/" + "smallvggnet.model"  
plot_path = root_dir + "output/" + time.strftime("%H_%M_%S") + "_smallvggnet_plot.png"  

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-d", "--dataset", default = train_img_path,
	help="path to training image set")
ap.add_argument("-m", "--model", default = model_path,
	help="path to output trained model")
ap.add_argument("-l", "--label-bin", default = label_bin,
	help="path to output label binarizer")
ap.add_argument("-p", "--plot", default = plot_path,
	help="path to output accuracy/loss plot")
ap.add_argument("-g", "--gpus", type=int, default=1,
	help="# of GPUs to use for training")
args = vars(ap.parse_args())

# =============================================================================

# =============================================================================

try:
    os.stat(log_dir)
except:
    os.makedirs(log_dir)
    
INIT_LR = 0.001
EPOCHS = 15
NUM_EPOCHS = 100
BS = 32
SIZE = (64,64) #64*64 for smallVGGNet

# =============================================================================

# =============================================================================
# partition the data into training and testing splits using 75% of
# the data for training and the remaining 10% for testing
#(trainX, testX, trainY, testY) = train_test_split(data, labels, test_size=0.1, random_state=44000)

# convert the labels from integers to vectors (for 2-class, binary
# classification you should use Keras' to_categorical function
# instead as the scikit-learn's LabelBinarizer will not return a vector)
val_split = 0.1
with open(train_csv) as f:
    lines = f.readlines()
np.random.seed(10101)
np.random.shuffle(lines)
np.random.seed(None)
num_val = int(len(lines)*val_split)
num_train = len(lines) - num_val
# load lb binarizer
lb = pickle.loads(open(label_bin, "rb").read())
#lb = pickle.loads(open(args["label_bin"], "rb").read())
# =============================================================================
def poly_decay(epoch):
	# initialize the maximum number of epochs, base learning rate,
	# and power of the polynomial
	maxEpochs = NUM_EPOCHS
	baseLR = INIT_LR
	power = 1.0
	# compute the new learning rate based on polynomial decay
	alpha = baseLR * (1 - (epoch / float(maxEpochs))) ** power
	# return the new learning rate
	return alpha
# =============================================================================
    
# =============================================================================
logging = TensorBoard(log_dir=log_dir)
checkpoint = ModelCheckpoint(log_dir + 'ep{epoch:03d}-loss{loss:.3f}-val_loss{val_loss:.3f}.h5',
        monitor='val_loss', save_weights_only=True, save_best_only=True, period=3)
#reduce_lr = ReduceLROnPlateau(monitor='val_loss', factor=0.1, patience=3, verbose=1)#using poly_decay
early_stopping = EarlyStopping(monitor='val_loss', min_delta=0, patience=10, verbose=1)
callbacks = [logging, checkpoint, LearningRateScheduler(poly_decay)]
# =============================================================================

# initialize our VGG-like Convolutional Neural Network
# grab the number of GPUs and store it in a conveience variable
G = args["gpus"]
# check to see if we are compiling using just a single GPU
if G <= 1:
	print("[INFO] training with 1 GPU...")
	model = SmallVGGNet.build(width=64, height=64, depth=3, classes=len(lb.classes_))
# otherwise, we are compiling using multiple GPUs
else:
	print("[INFO] training with {} GPUs...".format(G))
	# we'll store a copy of the model on *every* GPU and then combine
	# the results from the gradient updates on the CPU
	with tf.device("/cpu:0"):
		# initialize the model
		model = SmallVGGNet.build(width=64, height=64, depth=3,	classes=len(lb.classes_))
	
	# make the model parallel
	model = multi_gpu_model(model, gpus=G)

# =============================================================================    
# construct the image generator for data augmentation
from preprocess import convert_xml
from sklearn.utils import shuffle
cam2img_df = convert_xml(train_xml)
#cam2img_df['zip_target'] = cam2img_df.vehicleID + cam2img_df.cameraID
cam2img_df = shuffle(cam2img_df, random_state = 10086)
trainimg_lst = cam2img_df['imageName'].values[:num_train]
valimg_lst = cam2img_df['imageName'].values[num_train:]
trainvid_lst = cam2img_df['vehicleID'].values[:num_train]
valvid_lst = cam2img_df['vehicleID'].values[num_train:]
train_df = pd.DataFrame({'imageName': trainimg_lst, 'vehicleID': trainvid_lst}, dtype=str)
val_df = pd.DataFrame({'imageName': valimg_lst, 'vehicleID': valvid_lst}, dtype=str)

#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
train_datagen = ImageDataGenerator(
                 featurewise_center=True,
                 samplewise_center=False,
                 featurewise_std_normalization=True,
                 samplewise_std_normalization=False,
                 zca_whitening=False,
                 zca_epsilon=1e-6,
                 rotation_range=30,
                 width_shift_range=0.1,
                 height_shift_range=0.1,
                 brightness_range=None,
                 shear_range=0.2,
                 zoom_range=0.2,
                 channel_shift_range=0.,
                 fill_mode='nearest',
                 cval=0.,
                 horizontal_flip=True,
                 vertical_flip=False,
                 rescale=1/255.,
                 preprocessing_function=None,
                 data_format=None,
                 validation_split=0.,
                 dtype=None)

train_generator = train_datagen.flow_from_dataframe(dataframe=train_df, directory=train_img_path,
                        x_col='imageName', y_col ='vehicleID',
                        has_ext=True,
                        target_size=(64, 64), color_mode='rgb',
                        classes=list(lb.classes_), class_mode='categorical',
                        batch_size=BS, shuffle=True, seed=10086,
                        save_to_dir='output/aug_train',
                        save_prefix='',
                        save_format='jpg',
                        subset=None,
                        interpolation='nearest') 

val_generator = train_datagen.flow_from_dataframe(val_df, train_img_path,
                        x_col='imageName', y_col ='vehicleID',
                        has_ext=True,
                        target_size=(64, 64), color_mode='rgb',
                        classes=list(lb.classes_), class_mode='categorical',
                        batch_size=BS, shuffle=True, seed=10086,
                        save_to_dir='output/aug_val',
                        save_prefix='',
                        save_format='jpg',
                        subset=None,
                        interpolation='nearest') 
# =============================================================================
# Train with frozen layers first, to get a stable loss.
# Adjust num epochs to your dataset. This step is enough to obtain a not bad model.
if True:
    model.compile(optimizer=Adam(lr=INIT_LR), loss="categorical_crossentropy",
	metrics=["accuracy"])

    print("[INFO] compile the network...")
    H = model.fit_generator(train_generator,
            steps_per_epoch=max(1, num_train//BS),
            epochs=EPOCHS,
            initial_epoch=0,
            validation_data=val_generator,
            validation_steps=max(1, num_val//BS),
            callbacks=[logging, checkpoint])
    model.save_weights(log_dir + 'trained_weights_stage_1.h5')

# Unfreeze and continue training, to fine-tune.
# Train longer if the result is not good.
if True:
    for i in range(len(model.layers)):
        model.layers[i].trainable = True
    model.compile(optimizer=Adam(lr=1e-4), loss="categorical_crossentropy",
	metrics=["accuracy"]) # recompile to apply the change
    print('Unfreeze all of the layers.')

    # note that more GPU memory is required after unfreezing the body
    print("[INFO] training network...")
    print('Train on {} samples, val on {} samples, with batch size {}.'.format(num_train, num_val, BS))
    H = model.fit_generator(train_generator,
            steps_per_epoch=max(1, num_train//BS),
            epochs=NUM_EPOCHS,
            initial_epoch=EPOCHS,
            validation_data=val_generator,
            validation_steps=max(1, num_val//BS),
            callbacks=callbacks)
    model.save_weights(log_dir + 'trained_weights_final.h5')
    
# =============================================================================
# grab the history object dictionary
H = H.history

# plot the training loss and accuracy
N = np.arange(0, NUM_EPOCHS)
plt.style.use("ggplot")
plt.figure()
plt.plot(N, H["loss"], label="train_loss")
plt.plot(N, H["val_loss"], label="val_loss")
plt.plot(N, H["acc"], label="train_acc")
plt.plot(N, H["val_acc"], label="val_acc")
plt.title("Training Loss and Accuracy (SmallVGGNet)")
plt.xlabel("Epoch #")
plt.ylabel("Loss/Accuracy")
plt.legend()
#plt.savefig(args["plot"])
plt.savefig(plot_path)

# save the model and label binarizer to disk
print("[INFO] serializing network and label binarizer...")
#model.save(args["model"])
model.save(model_path)
f.close()
