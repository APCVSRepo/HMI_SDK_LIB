
#link_directories()


set(LIBRARIES
AppData
SdlConnector
jsoncpp_lib_static
)

if(SDL_SUPPORT_LIB)
	link_directories(${CMAKE_SOURCE_DIR}/lib)
	list(APPEND LIBRARIES smartDeviceLinkCore)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
  list(APPEND LIBRARIES pthreadVC2)
endif()

include_directories (
  ${CONNECT_INCLUDE_DIR}
  ${APPDATA_INCLUDE_DIR}
  ${JSON_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${PTHREAD_INCLUDE_DIR}
)

if(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
include_directories (
  ${CMAKE_SOURCE_DIR}/include/wince
)
endif()
set (SOURCES
  main.cpp
)

add_library(${PROJECT} SHARED ${SOURCES})

target_link_libraries(${PROJECT} ${LIBRARIES})

install(TARGETS ${PROJECT} DESTINATION ${CMAKE_BINARY_DIR}/bin)
