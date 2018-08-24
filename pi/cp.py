from picamera import PiCamera 
from time import sleep 

camera = PiCamera() 
camera.resolution = (2592, 1944) 
camera.framerate = 30
camera.annotate_text = "Hello World!" 
 
camera.start_preview()
sleep(5)
camera.capture('/home/pi/Desktop/max1.jpg') 


camera.stop_preview() 

