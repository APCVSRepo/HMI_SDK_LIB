# Sample QT HMI

This is the QT HMI project using HMI_SDK_LIB to interact with sdl_core. It is currently able to run under Linux, and support for other platforms is also planned.<br>
This project has been verified in the environment `Ubuntu 16.04 LTS 64bit`.

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
$cmake <SampleQTHMI_dir>
$make
```
Then you can get the executable `SampleQTHMI`

##### Dependency
In order to be able to build successfully, you need to install the qt library. There are two ways to do that:
  1. Use the `apt` command to directly install the qt related dependencies, as follows:
```shell
$apt install qtbase5-dev
```
  Notice: you may got `SIGSEGV` error when do [`make test`](#test), if so, please use the next method.

  2. Install `Qt Creator`(Qt Creator >= VERSION 5.3.2) and specify the environment variable of QT before you run `cmake`, as follows(just change the version number of QT to what you had installed):
```shell
$export PATH=/home/<user_name>/Qt5.3.2/5.3/gcc_64/bin:$PATH
$export QTDIR=/home/<user_name>/Qt5.3.2/5.3/gcc_64
$cmake <SampleQTHMI_dir>
$make
```


### USE Qt Creator
#### Linux
##### Environment
* Qt Creator >= VERSION 5.3.2
##### BUILD
Install and open your Qt Creator, make sure you can run the sample qt project, then open `SampleQTHMI.pro`, and build your project.<br>
After this, you can get the executable `SampleQTHMI` in your build directory.


## Start QT HMI
Create a folder for your executable as `<execute_dir>` and do:
  1. Build [sdl_core](https://github.com/smartdevicelink/sdl_core), after `make install`, copy all the files in the `bin` folder to `<execute_dir>`
  2. Build `HMI_SDK_LIB`, which is just in the upper directory, after `make`, copy `libhmi_sdk.so` in `app` folder to `<execute_dir>`
  3. Copy the generated `SampleQTHMI` to `<execute_dir>`, see chapter [Generate QT HMI](#generate-qt-hmi)
  4. Create a folder named `Config` in your `<execute_dir>`, and copy all the files in `<current_path>/res/hmi` to `<execute_dir>/Config`
  5. Copy opening movie `Main_build_3.mov` in `<current_path>/res` to `<execute_dir>`
  6. Open `smartDeviceLink.ini` in the `<execute_dir>`, modify `VideoStreamConsumer` and `AudioStreamConsumer` to `pipe`, as follows:
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
$./SampleQTHMI 
```

Notice: 
  1. In order for the program to work properly, you may need to complete [SDL Core Video Stream Setup](https://www.smartdevicelink.com/en/guides/core/video-streaming-setup/). For a quick look(there may be other dependencies， just install them):
```shell
$sudo apt-get install git cmake build-essential libavahi-client-dev libsqlite3-dev chromium-browser libssl-dev libudev-dev libgtest-dev libbluetooth3 libbluetooth-dev bluez-tools gstreamer1.0* libpulse-dev

$sudo apt-get update
$sudo apt-get upgrade
$sudo ldconfig
```
  2. If you want to use USB connect with sdl, you should run step7/8 in root authority.
  3. If you want to add a new class to QT HMI, make sure the class name is not the same as the class defined in `hmi_sdk`, such as `VR`, `BasicCommunication`, `Buttons`, `Navigation`, `TTS`, `VehicleInfo`, `UI`, etc. Otherwise, when compiling the project with `cmake`, the resulting executable will behave unexpectedly at runtime because the wrong constructor was called. `Please don't do it unless you understand the impact`.
  4. If you want to connect some Mobile Apps(QQ Music, 网易云音乐, etc.) to sdl_core via BT connection, make sure your host BT device's name contains words `Ford`/`Sync`, such as `Ford-Sync-XXX` or other similar names, otherwise, the apps will not be recognized.


# Test & Coverage
  We have added unit tests for `SDL RPCs` in the `SDLApps/Templates` folder, and the other modules(Home, HVAC, Phone, etc) are not included. It is also possible to generate a test coverage report when run `make test`.

## Used technologies
### Test framework:
  * [Google Test](https://github.com/google/googletest) - Google's C++ test framework.
### Coverage:
  * GCOV - test coverage program.
  * LCOV - graphical front-end for GCC's coverage testing tool for gcov.

## How to run Test

  1. Build project with enabled flag `-DBUILD_TESTS=on`
  2. Execute command `make test`

## How to generate test coverage report

  1. Build project with enabled flag `-DBUILD_TESTS_COVERAGE=on`, this will automatically set `-DBUILD_TESTS=on`
  2. Execute command `make test` and wait for the end of the execution
  3. Go to `<build_directory>/TestResult`, and open `index.html` to view the test coverage report


# Known issues

  1. If error occurred when start run `SampleQTHMI`, please try to move your excute folder to a short path; If the path is too long, there may be some problem.
  2. When run `make test`, you may get `SIGSEGV` error, if so, please reference to the second method of [Dependency](#dependency).

