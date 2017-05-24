
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
  add_definitions(-D_WIN32_WCE=$(CEVER))
  add_definitions(-D_CONSOLE)
  add_definitions(-DUNDER_CE)
  add_definitions(-D$(ARCHFAM))
  add_definitions(-D$(_ARCHFAM_))
  add_definitions(-DOS_WINCE)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  add_definitions(-DHAVE_PTW32_CONFIG_H)
  add_definitions(-D_UNICODE)
  add_definitions(-DUNICODE)
  add_definitions(-DWINCE)
  add_definitions(-D_WIN32)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
  set (CMAKE_CXX_FLAGS "/wd\"4819\" /wd\"4244\" /wd\"4390\" /wd\"4996\"  /EHsc /bigobj /Z7 /GF")
  set (CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG") #It will be appended to CMAKE_CXX_FLAGS in release
  set (CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})  
  set (CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:CONSOLE /ENTRY:")  
endif()

project (${PROJECT})
# ---
add_subdirectory(./tools)

add_subdirectory(./hmi_sdk)

add_subdirectory(./app)









