
include_directories(
  .
)

set (SOURCES
  pthread.c
)

add_definitions(-DPTW32_STATIC_LIB)

if(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
  add_definitions(-DHAVE_PTW32_CONFIG_H)
  add_definitions(-DWINCE)
  add_definitions(-D_UWIN_)
endif()

add_library(pthreadVC2 ${HEADERS} ${SOURCES})
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(pthreadVC2 ws2_32)
endif()
