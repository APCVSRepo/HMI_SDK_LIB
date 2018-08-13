
include("./set_3rd_party_paths.cmake")

set(CONNECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CONNECT_INCLUDE_DIR ${CONNECT_INCLUDE_DIR} PARENT_SCOPE)


#link_directories()

set(LIBRARIES
)

# add boost lib

  find_package(Boost 1.66.0 COMPONENTS system)
  set(BOOST_LIB_SOURCE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/boost_src)
  set(BOOST_LIBS_DIRECTORY ${3RD_PARTY_INSTALL_PREFIX}/lib)
  SET_PROPERTY(GLOBAL PROPERTY GLOBAL_BOOST_LIBS ${BOOST_LIBS_DIRECTORY})
  set(BOOST_INCLUDE_DIRECTORY ${3RD_PARTY_INSTALL_PREFIX}/include )
  if (NOT ${Boost_FOUND})
    message(STATUS "Did not find boost. Downloading and installing boost 1.66")
    set(BOOST_INSTALL_COMMAND ./b2 install)
    if (${3RD_PARTY_INSTALL_PREFIX} MATCHES "/usr/local")
      set(BOOST_INSTALL_COMMAND sudo ./b2 install)
    endif()
    include(ExternalProject)
    ExternalProject_Add(
      Boost
      URL https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.gz
      DOWNLOAD_DIR ${BOOST_LIB_SOURCE_DIRECTORY}
      SOURCE_DIR ${BOOST_LIB_SOURCE_DIRECTORY}
      CONFIGURE_COMMAND ./bootstrap.sh --with-libraries=system --prefix=${3RD_PARTY_INSTALL_PREFIX}
      BUILD_COMMAND ./b2
      INSTALL_COMMAND ${BOOST_INSTALL_COMMAND} --with-system --prefix=${3RD_PARTY_INSTALL_PREFIX}
      INSTALL_DIR ${3RD_PARTY_INSTALL_PREFIX}
      BUILD_IN_SOURCE true
    )

    set(BOOST_INCLUDE_DIR ${BOOST_ROOT_DIR}/Boost-prefix/src/Boost)
    set(BOOST_LIB_DIR ${BOOST_ROOT_DIR}/Boost-prefix/src/Boost/stage/lib/)
  endif()
#message(STATUS "BOOST_INCLUDE_DIR:${BOOST_INCLUDE_DIR}")


include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include
  ${JSON_INCLUDE_DIR}
  ${BOOST_INCLUDE_DIR}
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
  ${CMAKE_CURRENT_SOURCE_DIR}/src/WS_Session.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/websocket_to_sdl.cpp
)


add_library(SdlConnector ${SOURCES})

target_link_libraries(SdlConnector ${Boost_LIBRARIES})











