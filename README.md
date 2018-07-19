
# HMI_SDK_LIB

HMI_SDK_LIB is a sample Qt HMI sdk to use with sdl_core, which encapsulated json parser.<br>
At the same time, we also provide a reference design for QT HMI using HMI_SDK_LIB.<br>
This repository consists of two parts: 
  * HMI_SDK_LIB: Qt HMI sdk to use with sdl_core
  * ReferenceDesign: QT HMI project using HMI_SDK_LIB to interact with sdl_core

## Subdirectory

### HMI_SDK_LIB
HMI_SDK_LIB mainly generates HMI SDK library. It supports the LINUX, WIN32, WINCE, and ANDROID platforms as a middleware for connecting HMI and SDL Core.
Please refer to "HMI_SDK_LIB/README.md" for compilation and build.

### ReferenceDesign
ReferenceDesign contains examples of how the HMI SDK works.
There is currently a sample SampleQTHMI project. For how to run the example, please refer to the "README.md" of the sample project.


