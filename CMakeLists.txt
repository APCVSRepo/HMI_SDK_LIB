
cmake_minimum_required(VERSION 2.8.0)


set (PROJECT hmi_sdk)

#compiler set
#message(STATUS ${CMAKE_SYSTEM_NAME})
if(SYSTEM_NAME STREQUAL "Android")
SET(CMAKE_SYSTEM_NAME Android)
endif()

#when build on android plat,you should set -DCOMPILER_PATH=your compiler root path
if(CMAKE_SYSTEM_NAME STREQUAL "Android")
if(NOT COMPILER_PATH)
SET(COMPILER_PATH "/opt/android-9-toolchain")
endif()
message(STATUS "Current cross compiler path is ${COMPILER_PATH}")
SET(CMAKE_CXX_COMPILER "${COMPILER_PATH}/bin/arm-linux-androideabi-g++")
SET(CMAKE_C_COMPILER "${COMPILER_PATH}/bin/arm-linux-androideabi-gcc")
endif()


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_definitions(-DOS_WIN32)
elseif(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
  add_definitions(-DOS_WINCE)
  add_definitions(-DUNICODE)
  add_definitions(-D_WIN32_WCE=0x600)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
endif()

project (${PROJECT})
# ---
add_subdirectory(./tools)

add_subdirectory(./hmi_sdk)

add_subdirectory(./app)









