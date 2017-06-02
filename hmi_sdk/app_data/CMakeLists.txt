set(APPDATA_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(APPDATA_INCLUDE_DIR ${APPDATA_INCLUDE_DIR} PARENT_SCOPE)

#link_directories()

set(LIBRARIES
)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CONNECT_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${JSON_INCLUDE_DIR}
)

if(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
include_directories (
  ${CMAKE_SOURCE_DIR}/include/wince
)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
include_directories (
  ${PTHREAD_INCLUDE_DIR}
)
endif()

set (SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/AppData.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/AppList.cpp
)


add_library(AppData ${SOURCES})

#target_link_libraries(${PROJECT} ${LIBRARIES})

