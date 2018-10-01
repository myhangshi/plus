**Models**

`wget http://download.tensorflow.org/models/object_detection/mask_rcnn_inception_v2_coco_2018_01_28.tar.gz`
`tar zxvf mask_rcnn_inception_v2_coco_2018_01_28.tar.gz`

Download and extract the needed model files.

**Usage Examples :**


Compile using:
`mkdir build`
'cd build`
'cmake ..`
`make`


Run using:
`./mask_rcnn.out --image=cars.jpg`
`./mask_rcnn.out --video=cars.mp4`
