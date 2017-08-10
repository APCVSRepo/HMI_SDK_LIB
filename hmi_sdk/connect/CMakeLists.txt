
set(CONNECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CONNECT_INCLUDE_DIR ${CONNECT_INCLUDE_DIR} PARENT_SCOPE)


#link_directories()

set(LIBRARIES
)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include
  ${JSON_INCLUDE_DIR}
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
include_directories (
  ${PTHREAD_INCLUDE_DIR}
)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
include_directories (
  ${CMAKE_SOURCE_DIR}/include/wince
)
endif()

set (SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/basic_communication.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hmi_button.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hmi_channel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hmi_navigation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hmi_tts.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hmi_ui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hmi_vehicle_info.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hmi_video_stream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hmi_vr.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sdl_connector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sockets_to_sdl.cpp
)


add_library(SdlConnector ${SOURCES})

#target_link_libraries(${PROJECT} ${LIBRARIES})











