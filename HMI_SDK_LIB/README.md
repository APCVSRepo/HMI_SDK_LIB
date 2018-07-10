# Getting Started
## Linux
### Environment
* CMake >= VERSION 2.8.0
### BUILD
Create a folder for your build and run:
```shell
$cmake -DCMAKE_SYSTEM_NAME="Linux" -DCMAKE_BUILD_TYPE="Release" <hmi_sdk_lib_dir>
$make
```

## WIN32
### Environment
* Visual Studio 2008+
* CMake >= VERSION 2.8.0
### BUILD     
Create a folder for your build and run
```shell
$cmake -DCMAKE_SYSTEM_NAME="Windows" -DCMAKE_BUILD_TYPE="Release" <hmi_sdk_lib_dir>
```
 Open project with VS to build

## WINCE
### Environment
* Visual Studio 2008 or Visual Studio 2005
* CMake >= VERSION 2.8.0
### BUILD
Create a folder for your build and run
```shell
$cmake -G "Visual Studio 9 2008 CHSINT SDK For WinCE 6.0 (ARMV4I)" -DCMAKE_SYSTEM_NAME="WindowsCE" -DCMAKE_BUILD_TYPE="Release" <hmi_sdk_lib_dir>
```
Open project with VS to build

## ANDROID
### Environment
* NDK(ndk_r14b)
* CMake >= VERSION 2.8.0
### CREATE NDK TOOLCHAIN
run
```shell
<ndk_dir>/build/tools/make_standalone_toolchain.py --arch arm --api 19 --install-dir <ndk_toolchain_dir>
```
### BUILD
Create a folder for your build and run
```shell
$cmake -DSYSTEM_NAME="Android" -DCOMPILER_PATH=<ndk_toolchain_dir> <hmi_sdk_lib_dir>
$make
```
