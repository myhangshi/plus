import numpy as np
import cv2 
cap = cv2.VideoCapture(0) 
while True : 
    ret, frame = cap.read() 
    cv2.imshow('frame',cv2.resize(frame, (500,500))) 
    if cv2.waitKey(25) & 0xFF == ord('q'): 
        break 
cap.release() 
cv2.destroyAllWindows()

