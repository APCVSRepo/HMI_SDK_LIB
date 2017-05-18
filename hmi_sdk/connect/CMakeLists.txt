
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

set (SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/BasicCommunication.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Buttons.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Channel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CVideoStream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Navigation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SDLConnector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SocketsToSDL.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/TTS.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/UI.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VehicleInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VR.cpp
)


add_library(SdlConnector ${SOURCES})

#target_link_libraries(${PROJECT} ${LIBRARIES})

