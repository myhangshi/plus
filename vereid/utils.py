"""Miscellaneous utility functions."""
#same as: 2018AICity_TeamUW/Keras/yolo3/utils.py

from functools import reduce
import cv2
from PIL import Image
import numpy as np
from matplotlib.colors import rgb_to_hsv, hsv_to_rgb

def compose(*funcs):
    """Compose arbitrarily many functions, evaluated left to right.

    Reference: https://mathieularose.com/function-composition-in-python/
    """
    # return lambda x: reduce(lambda v, f: f(v), funcs, x)
    if funcs:
        return reduce(lambda f, g: lambda *a, **kw: g(f(*a, **kw)), funcs)
    else:
        raise ValueError('Composition of empty sequence not supported.')

def resize(image, width=None, height=None, inter=cv2.INTER_AREA):
    '''
    image: cv2.imread format
    '''
    # initialize the dimensions of the image to be resized and grab the image size
    dim = None
    (h, w) = image.shape[:2]
    # if both the width and height are None, then return the
    # original image
    if width is None and height is None:
        return image

    # check to see if the width is None
    if width is None:
        # calculate the ratio of the height and construct the dimensions
        r = height / float(h)
        dim = (int(w * r), height)
    # otherwise, the height is None
    else:
        # calculate the ratio of the width and construct the dimensions
        r = width / float(w)
        dim = (width, int(h * r))
        
    # resize the image
    resized = cv2.resize(image, dim, interpolation=inter)
    # return the resized image and scale
    return resized, r

def rotate(image, angle, center=None, scale=1.0):
    '''
    image: cv2.imread format
    '''
    # grab the dimensions of the image
    (h, w) = image.shape[:2]
    # if the center is None, initialize it as the center of
    # the image
    if center is None:
        center = (w // 2, h // 2)
    # perform the rotation
    M = cv2.getRotationMatrix2D(center, angle, scale)
    rotated = cv2.warpAffine(image, M, (w, h))
    # return the rotated image
    return rotated

def letterbox_image(image, size):
    '''resize image with unchanged aspect ratio using padding'''
    '''image format: PIL.Image format'''
    iw, ih = image.size
    w, h = size
    scale = min(w/iw, h/ih)
    nw = int(iw*scale)
    nh = int(ih*scale)

    image = image.resize((nw,nh), Image.BICUBIC)
    new_image = Image.new('RGB', size, (128,128,128))
    new_image.paste(image, ((w-nw)//2, (h-nh)//2))
    return new_image
	
def rand(a=0, b=1):
    return np.random.rand()*(b-a) + a

def get_random_data(img_path, input_shape, random=True, jitter=.3, hue=.1, sat=1.5, val=1.5, proc_img=True):
    '''random preprocessing for real-time data augmentation'''
    image = Image.open(img_path)
    iw, ih = image.size
    h, w = input_shape

    if not random:
        # resize image
        scale = min(w/iw, h/ih)
        nw = int(iw*scale)
        nh = int(ih*scale)
        dx = (w-nw)//2
        dy = (h-nh)//2
        image_data=0
        if proc_img:
            image = image.resize((nw,nh), Image.BICUBIC)
            new_image = Image.new('RGB', (w,h), (128,128,128))
            new_image.paste(image, (dx, dy))
            image_data = np.array(new_image)/255.
        return image_data, scale

    # resize image
    new_ar = w/h * rand(1-jitter,1+jitter)/rand(1-jitter,1+jitter)
    scale = rand(.25, 2)
    if new_ar < 1:
        nh = int(scale*h)
        nw = int(nh*new_ar)
    else:
        nw = int(scale*w)
        nh = int(nw/new_ar)
    image = image.resize((nw,nh), Image.BICUBIC)

    # place image
    dx = int(rand(0, w-nw))
    dy = int(rand(0, h-nh))
    new_image = Image.new('RGB', (w,h), (128,128,128))
    new_image.paste(image, (dx, dy))
    image = new_image

    # flip image or not
    flip = rand()<.5
    if flip: image = image.transpose(Image.FLIP_LEFT_RIGHT)

    # distort image
    hue = rand(-hue, hue)
    sat = rand(1, sat) if rand()<.5 else 1/rand(1, sat)
    val = rand(1, val) if rand()<.5 else 1/rand(1, val)
    x = rgb_to_hsv(np.array(image)/255.)
    x[..., 0] += hue
    x[..., 0][x[..., 0]>1] -= 1
    x[..., 0][x[..., 0]<0] += 1
    x[..., 1] *= sat
    x[..., 2] *= val
    x[x>1] = 1
    x[x<0] = 0
    image_data = hsv_to_rgb(x) # numpy array, 0 to 1

    return image_data, scale

import numpy as np
import csv
from progressbar import ProgressBar
import pandas as pd

def load_mot(detections):
    """
    Loads detections stored in a mot-challenge like formatted CSV or numpy array (fieldNames = ['frame', 'id', 'x', 'y',
    'w', 'h', 'score', -1,-1,-1,'class']).

    Args:
        detections

    Returns:
        list: list containing the detections for each frame.
    """
    
    data = []
    if type(detections) is str:
        raw = pd.read_table(detections, sep=',', header=None, names = ['frame',
                            'id', 'x', 'y','w', 'h', 'score', 'color_1', 'color_2', 'color_3','class'])
    else:
        # assume it is an array
        assert isinstance(detections, np.ndarray), "only numpy arrays or *.csv paths are supported as detections."
        raw = detections.astype(np.float32)
    raw['x_right'] = raw['x'] +raw['w']
    raw['y_bot'] = raw['y'] + raw['h']
    frames = np.split(raw, np.where(np.diff(raw['frame']))[0]+1, axis=0)#same frame as the same object

    end_frame = len(frames)
    ptr = 0
    pbar = ProgressBar(maxval=end_frame)
    pbar.start()
    for i in range(end_frame):
        dets = []
        if ptr < len(frames) and frames[ptr]['frame'].iloc[0] == i:
            select_cols = ['x','y','x_right','y_bot', 'score', 'class']
            for j in range(len(frames[ptr][select_cols])):
                x1,y1,x2,y2,s,cls = frames[ptr][select_cols].iloc[j]
#                print("frame", ptr, "bbox spec", x1,y1,x2,y2,s)
                dets.append({'bbox': (x1,y1,x2,y2), 'score': s, 'class': cls})
            ptr += 1
        data.append(dets)
        pbar.update(i)
    pbar.finish()
    return data


def save_to_csv(out_path, tracks):
    """
    Saves tracks to a CSV file.

    Args:
        out_path (str): path to output csv file.
        tracks (list): list of tracks to store.
    """

    with open(out_path, "w") as ofile:
        field_names = ['frame', 'id', 'x', 'y', 'w', 'h', 'score', 'wx', 'wy', 'wz', 'class']

        odict = csv.DictWriter(ofile, field_names)
        id_ = 1
        for track in tracks:
            for i, bbox in enumerate(track['bboxes']):
                row = {'id': id_,
                       'frame': track['start_frame'] + i,
                       'x': np.int(bbox[0]),
                       'y': np.int(bbox[1]),
                       'w': np.int(bbox[2] - bbox[0]),
                       'h': np.int(bbox[3] - bbox[1]),
                       'score': np.round(track['max_score'],2),
                       'wx': -1,
                       'wy': -1,
                       'wz': -1,
                       'class': track['class']}

                odict.writerow(row)
            id_ += 1

def iou(bbox1, bbox2):
    """
    Calculates the intersection-over-union of two bounding boxes.

    Args:
        bbox1 (numpy.array, list of floats): bounding box in format x1,y1,x2,y2.
        bbox2 (numpy.array, list of floats): bounding box in format x1,y1,x2,y2.

    Returns:
        int: intersection-over-onion of bbox1, bbox2
    """

    bbox1 = [float(x) for x in bbox1]
    bbox2 = [float(x) for x in bbox2]

    (x0_1, y0_1, x1_1, y1_1) = bbox1
    (x0_2, y0_2, x1_2, y1_2) = bbox2

    # get the overlap rectangle
    overlap_x0 = max(x0_1, x0_2)
    overlap_y0 = max(y0_1, y0_2)
    overlap_x1 = min(x1_1, x1_2)
    overlap_y1 = min(y1_1, y1_2)

    # check if there is an overlap
    if overlap_x1 - overlap_x0 <= 0 or overlap_y1 - overlap_y0 <= 0:
        return 0

    # if yes, calculate the ratio of the overlap to each ROI size and the unified size
    size_1 = (x1_1 - x0_1) * (y1_1 - y0_1)
    size_2 = (x1_2 - x0_2) * (y1_2 - y0_2)
    size_intersection = (overlap_x1 - overlap_x0) * (overlap_y1 - overlap_y0)
    size_union = size_1 + size_2 - size_intersection

    return size_intersection / size_union
