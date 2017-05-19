
cmake_minimum_required(VERSION 2.8.0)


set (PROJECT hmi_sdk)


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_definitions(-DOS_WIN32)
elseif(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
  add_definitions(-DOS_WINCE)
  add_definitions(-DUNICODE)
  add_definitions(-D_WIN32_WCE=0x600)
endif()

project (${PROJECT})
# ---
add_subdirectory(./tools)

add_subdirectory(./hmi_sdk)

add_subdirectory(./app)









