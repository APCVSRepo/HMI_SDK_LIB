# hmi_sdk_lib

# Getting Started
## Linux
### Environment
* CMake
### BUILD
Create a folder for your build and run `cmake <hmi_sdk_lib_dir>`


## WIN32
### Environment
* Visual Studio 2008+
* CMake
### BUILD
Create a folder for your build and run `cmake -DCMAKE_SYSTEM_NAME="Windows" <hmi_sdk_lib_dir>`

## WINCE
### Environment
* Visual Studio 2008 or Visual Studio 2005
* CMake
### BUILD
Create a folder for your build and run `cmake -DCMAKE_SYSTEM_NAME="WindowsCE" <hmi_sdk_lib_dir>`

## ANDROID
### Environment
* NDK
* CMake
### CREATE NDK TOOLCHAIN
run `<ndk_dir>/build/tools/make_standalone_toolchain.py --arch arm --api <api> --install-dir <target_dir>`
### BUILD
Create a folder for your build and run `cmake -DSYSTEM_NAME="Android" -DCOMPILER_PATH=<ndk_toolchain_dir> <hmi_sdk_lib_dir>`
