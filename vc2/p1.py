import numpy as np 

import cv2 
img = cv2.imread('test.jpg', 0) 

cv2.imshow('image', img) 
cv2.waitKey(0) & 0xFF 
cv2.destroyAllWindows()

