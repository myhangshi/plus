# -*- coding: utf-8 -*-
"""
Created on Fri Jan  4 09:34:32 2019

@author: rein9
"""
import numpy as np
import json
class NumpyEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, (np.int_, np.intc, np.intp, np.int8, np.int16, np.int32, np.int64,
                            np.uint8, np.uint16, np.uint32, np.uint64)):
            return int(obj)
        elif isinstance(obj, (np.float_, np.float16, np.float32, np.float64)):
            return float(obj)
        elif isinstance(obj, (np.ndarray,)):
            return obj.tolist()
        return json.JSONEncoder.default(self, obj)

class Debugger(object):

    def __init__(self, filename):
        self.detections = []
        self.filename = filename

    def store_detected_bounding_boxes(self,img_name,vid,cid,image):
        self.detections.append({'imageName': img_name, 'vehicleID': vid, 'cameraID': cid, 'train_feat': image})

    def write_detection(self):
        with open(self.filename, 'w') as f:
            json.dump(self.detections, f, cls=NumpyEncoder)

    def read_detected_bounding_boxes(self):
        with open(self.filename, 'r') as g:
            mydic_restored = json.loads(g.read())
        return mydic_restored
