
Run the getModels.sh file from command line to download the needed model files

	sudo chmod a+x getModels.sh
	./getModels.sh


C++:
a single image:
    ./object_detection_yolo.out --image=bird.jpg
a video file:
    ./object_detection_yolo.out --video=run.mp4

Compilation examples:
mkdir build
cd build
cmake .. 
make 

