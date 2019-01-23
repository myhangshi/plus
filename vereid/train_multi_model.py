#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jan 16 17:56:08 2019

@author: rwzhang
"""# USAGE
# python train_multi_model.py  --net resnet --gpu 1

import matplotlib
# set the matplotlib backend so figures can be saved in the background
matplotlib.use("Agg")
# import the necessary packages
import matplotlib.pyplot as plt
from keras.applications import ResNet50
from keras.applications import InceptionV3
from keras.applications import Xception # TensorFlow ONLY
from keras.applications import VGG16
from keras.applications import VGG19
from keras.applications import imagenet_utils
from keras.applications.inception_v3 import preprocess_input
from keras.preprocessing.image import img_to_array
from keras.preprocessing.image import load_img
from keras.layers import Input, Flatten, Dense
from keras.models import Model, load_model, clone_model
from keras.preprocessing.image import ImageDataGenerator
from keras.optimizers import SGD, Adam
from keras.utils.training_utils import multi_gpu_model
from keras.callbacks import TensorBoard, ModelCheckpoint, ReduceLROnPlateau, EarlyStopping, LearningRateScheduler
import tensorflow as tf
import numpy as np
import pandas as pd
import argparse, pickle, os, re

# =============================================================================
# global path definitions
#root_dir = os.path.expanduser('~/2019AICity_carson/Track2/')
root_dir = os.getcwd() + '/' #/media/f/2019AICity_carson/Track2/
train_xml = root_dir + 'aic19-track2-reid/train_label.xml'
train_img_path = root_dir + 'aic19-track2-reid/image_train/'
train_csv = root_dir + "aic19-track2-reid/train_label.csv"
train_feat = root_dir + "aic19-track2-reid/train_feat.csv"
train_feat_pkl = root_dir + "aic19-track2-reid/train_feat.pkl"
train_track = root_dir + "aic19-track2-reid/train_track.txt"
label_bin = root_dir + "output/smallvggnet_lb.pickle"

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-d", "--dataset", default = train_img_path,
    help="path to training image set")
ap.add_argument("-l", "--label-bin", default = label_bin,
    help="path to output label binarizer")
ap.add_argument("-g", "--gpus", type=int, default=1,
    help="# of GPUs to use for training")
ap.add_argument("-n", "--net", type=str, default="resnet",
    help="name of pre-trained network to use")
ap.add_argument("-m", "--model", type=str, required=False,default = "",
	help="path to pre-trained model")
args = vars(ap.parse_args())

# define a dictionary that maps model names to their classes
# inside Keras
MODELS = {
    "vgg16": VGG16,
    "vgg19": VGG19,
    "inception": InceptionV3,
    "xception": Xception, # TensorFlow ONLY
    "resnet": ResNet50
}

# =============================================================================
INIT_LR = 0.001
INTER_EPOCHS = 10
NUM_EPOCHS = 200 
BS = 32
SIZE = (224,224) #64*64 for smallVGGNet
val_split = 0.1
with open(train_csv) as f:
    lines = f.readlines()

np.random.seed(10101)
np.random.shuffle(lines)
np.random.seed(None)
num_val = int(len(lines)*val_split)
num_train = len(lines) - num_val

# =============================================================================
# convert the labels from integers to vectors (for 2-class, binary
# classification you should use Keras' to_categorical function
# instead as the scikit-learn's LabelBinarizer will not return a vector)
# load lb binarizer
lb = pickle.loads(open(label_bin, "rb").read())
#lb = pickle.loads(open(args["label_bin"], "rb").read())

# =============================================================================
# esnure a valid model name was supplied via command line argument
if args["net"] not in MODELS.keys():
    raise AssertionError("The --net command line argument should "
        "be a key in the `MODELS` dictionary")
#The following will be replaced by args
log_dir = root_dir + "log/" + args["net"] + "/"

try:
    os.stat(log_dir)
except:
    os.makedirs(log_dir)
#model_path = log_dir + args["net"] + ".model"
plot_path = log_dir + args["net"] + "_smallvggnet_plot.png"

# =============================================================================

# load our the network weights from disk (NOTE: if this is the
# first time you are running this script for a given network, the
# weights will need to be downloaded first -- depending on which
# network you are using, the weights can be 90-575MB, so be
# patient; the weights will be cached and subsequent runs of this
# script will be *much* faster)
def create_model(net_type):
    Network = MODELS[net_type]
    inp = Input(shape=(SIZE[0],SIZE[1],3))
    ld_model = Network(include_top=False, weights='imagenet', input_tensor=inp)
    
    x = ld_model.output #Loaded with no-top model
    #Really depends on whether you want pre-trained values to be fixed or not
    for layer in ld_model.layers:
        layer.trainable = False
    
    #Add here whatever dense layers you need
    x = Flatten()(x)
    predictions = Dense(len(lb.classes_), activation='softmax', name='fc1000')(x)
    model = Model(inputs=ld_model.inputs, outputs=predictions)
    return model

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
#checkpoint = ModelCheckpoint(log_dir + 'ep{epoch:03d}-loss{loss:.3f}-val_loss{val_loss:.3f}.model', monitor='val_loss', save_weights_only=False, period=1)
checkpoint = ModelCheckpoint(log_dir + 'ep{epoch:03d}-loss{loss:.3f}-val_loss{val_loss:.3f}.h5', monitor='val_loss', save_weights_only=True, save_best_only=True, period=10)
#reduce_lr = ReduceLROnPlateau(monitor='val_loss', factor=0.1, patience=3, verbose=1)#using poly_decay
early_stopping = EarlyStopping(monitor='val_loss', min_delta=0, patience=10, verbose=1)
callbacks = [logging, checkpoint, LearningRateScheduler(poly_decay)]
# =============================================================================

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
                        target_size=SIZE, color_mode='rgb',
                        classes=list(lb.classes_), class_mode='categorical',
                        batch_size=BS, shuffle=True, seed=10086,
                        save_to_dir=None,
                        save_prefix='',
                        save_format='jpg',
                        subset=None,
                        interpolation='nearest')

val_generator = train_datagen.flow_from_dataframe(val_df, train_img_path,
                        x_col='imageName', y_col ='vehicleID',
                        has_ext=True,
                        target_size=SIZE, color_mode='rgb',
                        classes=list(lb.classes_), class_mode='categorical',
                        batch_size=BS, shuffle=True, seed=10086,
                        save_to_dir=None,
                        save_prefix='',
                        save_format='jpg',
                        subset=None,
                        interpolation='nearest')
# =============================================================================

# =============================================================================
# Load previous saved weight before training
if re.search(r".*\_stage\_1.*", args['model']):
    inter_weight = log_dir + args['net'] +  '_trained_weights_stage_1.h5'
 #   inter_model = log_dir + args['net'] +  '_trained_model_stage_1.model'
    cur_epoch = INTER_EPOCHS
else: 
    m = re.match(r"ep(?P<epoch>\d+)\-loss(?P<loss>\d+\.\d+)\-val_loss(?P<val_loss>\d+\.\d+)", args["model"])
    if m:
        cur_epoch = int(m.groupdict()['epoch'])
        cur_loss = float(m.groupdict()['loss'])
        cur_valloss = float(m.groupdict()['val_loss'])
        inter_weight = log_dir + args["model"]
    else:
        cur_epoch = 0
    
# =============================================================================

print("[INFO] compile the network for initial training ...")
# initialize our VGG-like Convolutional Neural Network
# grab the number of GPUs and store it in a conveience variable
# check to see if we are compiling using just a single GPU
G = args["gpus"]
#if True:
if cur_epoch < INTER_EPOCHS:
    # Train with frozen layers first, to get a stable loss.
    # Adjust num epochs to your dataset. This step is enough to obtain a not bad model.
    print("[INFO] compile the network from fresh, ignoring the --weight argument")
    #only rebuild the model when the cur_epoch smaller than intermediate point
    if G <= 1:
        print("[INFO] training with 1 GPU from fresh")
        model = create_model(args["net"])
    # otherwise, we are compiling using multiple GPUs
    else:
        print("[INFO] training with {} GPUs from fresh".format(G))
        # we'll store a copy of the model on *every* GPU and then combine
        # the results from the gradient updates on the CPU
        with tf.device("/cpu:0"):
            # initialize the model
            model = create_model(args["net"])
        # make the model parallel
        model = multi_gpu_model(model, gpus=G)
    model.compile(optimizer=Adam(lr=INIT_LR), loss="categorical_crossentropy",	metrics=["accuracy"])        
    H = model.fit_generator(train_generator,
            steps_per_epoch=max(1, num_train//BS),
            epochs=INTER_EPOCHS,
            initial_epoch=0,
            validation_data=val_generator,
            validation_steps=max(1, num_val//BS),
            callbacks=[logging, checkpoint])
    #save the intermediate weight file
    print("[INOF] Finished initial training, saving the model and weight")
    inter_weight = log_dir + args['net'] +  '_trained_weights_stage_1.h5'
#    inter_model = log_dir + args['net'] +  '_trained_model_stage_1.model'
    model.save_weights(inter_weight)
    model.save(inter_model)
# =============================================================================

# =============================================================================
# Unfreeze and continue training, to fine-tune.
# del model
try:
    model
    print("[INFO] Continue fine training")
    model.summary()
except:
    print("[INFO] Creating new model for loading existing weight")
    if G <= 1:
        print("[INFO] training with 1 GPU from existing weight")
        model = create_model(args["net"])
    # otherwise, we are compiling using multiple GPUs
    else:
        print("[INFO] training with {} GPUs from fresh".format(G))
        # we'll store a copy of the model on *every* GPU and then combine
        # the results from the gradient updates on the CPU
        with tf.device("/cpu:0"):
            # initialize the model
            model = create_model(args["net"])
        # make the model parallel
        model = multi_gpu_model(model, gpus=G)

if True:   
    # note that more GPU memory is required after unfreezing the body
    print("[INFO] Continue training network from {} Epochs".format(cur_epoch))
    print('Train on {} samples, val on {} samples, with batch size {}.'.format(num_train, num_val, BS))
    for i in range(len(model.layers)):
        model.layers[i].trainable = True
    model.compile(optimizer=Adam(lr=1e-4), loss="categorical_crossentropy",metrics=["accuracy"]) # recompile to apply the change
    model.load_weights(inter_weight, by_name=True, skip_mismatch=True)            
    H = model.fit_generator(train_generator,
            steps_per_epoch=max(1, num_train//BS),
            epochs=NUM_EPOCHS,
            initial_epoch=cur_epoch,
            validation_data=val_generator,
            validation_steps=max(1, num_val//BS),
            callbacks=callbacks)
    model.save_weights(log_dir + args['net'] + '_trained_weights_final.h5')
    # save the model and label binarizer to disk
    print("[INFO] serializing network and label binarizer...")
    model.save(log_dir + args['net'] + '_trained_weights_final.model')

# =============================================================================
# grab the history object dictionary
H = H.history
