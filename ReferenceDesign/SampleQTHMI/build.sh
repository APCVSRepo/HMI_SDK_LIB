#!/bin/bash

if [ ! -d "./build/" ];then
  	echo "create build dir ..."
    mkdir build
else
  	echo "clean build dir ..."
# 	rm -rf ./build/*
fi

cd ./build

echo "load env path..."
#export PATH=/home/<user_name>/Qt5.3.2/5.3/gcc_64/bin:$PATH
export PATH=/home/linux/E/Qt5.3.2/5.3/gcc_64/bin:$PATH
echo "${PATH}"

echo "load qt path ..."
#export QTDIR=/home/<user_name>/Qt5.3.2/5.3/gcc_64
export QTDIR=/home/linux/E/Qt5.3.2/5.3/gcc_64
echo "${QTDIR}"

echo "load libhmi_sdk.so ..."
#hmisdk_lib=/home/<user_path>/HMI_SDK_LIB/<build_dir>/app
hmisdk_dir=../../../build/app
hmisdk_lib=${hmisdk_dir}/libhmi_sdk.so

echo "${hmisdk_dir}"
if [ ! -f "${hmisdk_lib}" ];then
    
	echo "error: libhmi_sdk.so does not exist." 
	echo "Please check whether the libhmi_sdk.so path is correct."
	echo "exit build ..."
else
	cp ${hmisdk_lib} ../lib/linux
	echo "Start build ..."
  	cmake ../ -DBUILD_TESTS_COVERAGE=on
  	make
	echo "run test ..."
  	cd SDLApps/Templates
	sh HMITest.sh
	
	cd ../../../
	if [ ! -d "./buildOut" ];then
		mkdir buildOut
		cd buildOut
		mkdir bin
	else
		rm -rf buildOut/*
		cd buildOut
		mkdir bin
	fi

	cd ..
	
	if [ -f "build/SampleQTHMI" ];then

		echo "cp build/SampleQTHMI to buildOut/bin/"
		cp ./build/SampleQTHMI ./buildOut/bin
	
	else
		echo "Failed to build SampleQTHMI."
	fi

	if [ -f "build/TestResult/index.html" ];then

		echo "cp build/TestResult/ to buildOut/"
		cp -rf ./build/TestResult ./buildOut/
  	    echo "Test coverage is viewed through buildOut/TestResult/index.html file."
	
	else
  	    echo "Failure of test coverage generation."
	fi

  	echo "build finish."
fi
