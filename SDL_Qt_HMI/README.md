# SDL QT HMI

This is the QT HMI project for the sdl core. It is currently able to run under Linux, and support for other platforms is also planned.<br>
This project has been verified in the environment Ubuntu 16.04 LTS 64bit.

# Getting Started

## Generate QT HMI

Currently, we have two ways to generate QT HMI:
  * Use CMake
  * Use Qt Creator

### USE CMake
#### Linux
##### Environment
* CMake >= VERSION 2.8.11
##### BUILD
Create a folder for your build and run:
```shell
$cmake <SDL_QT_HMI_dir>
$make
```
Then you can get the executable `SDL_Qt_HMI`

##### Dependency
When run cmake, you may need install package qtbase5-dev:
```shell
$apt install qtbase5-dev
```

### USE Qt Creator
#### Linux
##### Environment
* Qt Creator >= VERSION 5.3.2
##### BUILD
Install and open your Qt Creator, make sure you can run the sample qt project, then open `SDL_Qt_HMI.pro`, and build your project.<br>
After this, you can get the executable `SDL_Qt_HMI` in your build directory.


## Start QT HMI
Create a folder for your executable as <excute_dir> and do:
  1. Build [sdl_core](https://github.com/smartdevicelink/sdl_core), after `make install`, copy all the files in the bin folder to <excute_dir>
  2. Build HMI_SDK_LIB, which is just in the upper directory, after `make`, copy `libhmi_sdk.so` in app folder to <excute_dir>
  3. Copy the generated `SDL_Qt_HMI` to <excute_dir>, see chapter [Generate QT HMI](#generate-qt-hmi)
  4. Create a folder named Config in your <excute_dir>, and copy all the files in `<current_path>/res/hmi` to `<excute_dir>/Config`
  5. Copy opening movie `Main_build_3.mov` in `<current_path>/res` to <excute_dir>
  6. Open `smartDeviceLink.ini` in the <excute_dir>, modify `VideoStreamConsumer` and `AudioStreamConsumer` to `pipe`, as follows:
>;VideoStreamConsumer = socket<br>
>;AudioStreamConsumer = socket<br>
>;VideoStreamConsumer = file<br>
>;AudioStreamConsumer = file<br>
>VideoStreamConsumer = pipe<br>
>AudioStreamConsumer = pipe<br>
  7. Start sdl core
```shell
$./start.sh
```
  8. Start QT HMI
```shell
$./SDL_Qt_HMI 
```

Notice: If you want to use USB connect with sdl, you should run step7/8 in root authority.


# Known issues

  1. If error occurred when start run SDL_Qt_HMI, please try to move your excute folder to a short path; If the path is too long, there may be some problem.







