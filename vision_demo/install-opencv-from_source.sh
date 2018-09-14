#! /bin/bash


echo ""
echo "************************ Please confirm *******************************"
echo " Installing OpenCV from source may take a long time. "
echo " Select n to skip OpenCV installation or y to install it." 

read -p " Continue installing OpenCV (y/n) ? " CONTINUE
if [[ "$CONTINUE" == "y" || "$CONTINUE" == "Y" ]]; then
	echo ""; 
	echo "Uninstalling pip installation";
	sudo pip3 uninstall opencv-contrib-python
	sudo pip3 uninstall opencv-python  
	echo "";
	echo "Installing OpenCV"; 
	echo "";
	sudo apt-get update -y && sudo apt-get upgrade -y
	sudo apt-get install -y build-essential cmake pkg-config
	sudo apt-get install -y libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev
	sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
	sudo apt-get install -y libxvidcore-dev libx264-dev
	sudo apt-get install -y libgtk2.0-dev libgtk-3-dev
	sudo apt-get install -y libatlas-base-dev gfortran
	sudo apt-get install -y python2.7-dev python3-dev

	#wget -O opencv.zip https://github.com/Itseez/opencv/archive/3.3.0.zip
	#unzip opencv.zip
	git clone https://github.com/opencv/opencv.git 
	git clone https://github.com/opencv/opencv_contrib.git
	cd opencv 
	git checkout 3.4.2 
	cd .. 
	cd opencv_contrib 
	git checkout 3.4.2 
	cd .. 


	#wget -O opencv_contrib.zip https://github.com/Itseez/opencv_contrib/archive/3.3.0.zip
	#unzip opencv_contrib.zip
	#cd ~/opencv-3.3.0/
	cd opencv 
	mkdir build
	cd build
	
	cmake -D CMAKE_BUILD_TYPE=RELEASE \
	      -D CMAKE_INSTALL_PREFIX=/usr/local \
	      -D INSTALL_PYTHON_EXAMPLES=OFF \
	      -D BUILD_opencv_python3=ON  \
	      -D BUILD_opencv_python2=ON  \
	      -D BUILD_opencv_java=OFF   \
	      -D OPENCV_EXTRA_MODULES_PATH=/home/aurora/workspace/opencv_contrib/modules \
	      -D BUILD_EXAMPLES=ON ..
	
	make -j`nproc`
	sudo make install
	sudo ldconfig
else
	echo "";
	echo "Skipping OpenCV installation";
	echo "";
fi


