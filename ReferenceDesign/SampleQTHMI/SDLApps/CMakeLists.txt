
set(SDLAPPS_DIR ${SDL_QT_HMI_DIR}/SDLApps)

# Instruct CMake not to run uic(for ui_interface.h).
SET(CMAKE_AUTOUIC OFF)

include_directories (
    ${SDLAPPS_DIR}
    ${SDLAPPS_DIR}/app
    ${SDLAPPS_DIR}/Factory
    ${SDLAPPS_DIR}/Source
    ${SDLAPPS_DIR}/Data
    ${SDLAPPS_DIR}/Templates
    ${SDLAPPS_DIR}/Templates/Alert
    ${SDLAPPS_DIR}/Templates/AppListView
    ${SDLAPPS_DIR}/Templates/ChoiceSet
    ${SDLAPPS_DIR}/Templates/CommandView
    ${SDLAPPS_DIR}/Templates/Common
    ${SDLAPPS_DIR}/Templates/Config
    ${SDLAPPS_DIR}/Templates/ScrollableMessage
    ${SDLAPPS_DIR}/Templates/Show
    ${SDLAPPS_DIR}/Templates/SliderView
    ${SDLAPPS_DIR}/Templates/Template
    ${SDLAPPS_DIR}/Templates/utils/VideoStream
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
    ${HMI_SDK_DIR}
)

aux_source_directory(.                              SDLAPPS_SOURCES)
aux_source_directory(./app                          SDLAPPS_SOURCES)
aux_source_directory(./Data                         SDLAPPS_SOURCES)
aux_source_directory(./Factory                      SDLAPPS_SOURCES)
aux_source_directory(./Templates/Alert              SDLAPPS_SOURCES)
aux_source_directory(./Templates/AppListView        SDLAPPS_SOURCES)
aux_source_directory(./Templates/ChoiceSet          SDLAPPS_SOURCES)
aux_source_directory(./Templates/CommandView        SDLAPPS_SOURCES)
aux_source_directory(./Templates/Common             SDLAPPS_SOURCES)
aux_source_directory(./Templates/Config             SDLAPPS_SOURCES)
aux_source_directory(./Templates/ScrollableMessage  SDLAPPS_SOURCES)
aux_source_directory(./Templates/Show               SDLAPPS_SOURCES)
aux_source_directory(./Templates/SliderView         SDLAPPS_SOURCES)
aux_source_directory(./Templates/Template           SDLAPPS_SOURCES)
aux_source_directory(./Templates/utils              SDLAPPS_SOURCES)
aux_source_directory(./Templates/utils/VideoStream  SDLAPPS_SOURCES)
aux_source_directory(./UI                           SDLAPPS_SOURCES)

find_package(Qt5Widgets)

add_library (SDLApps ${SDLAPPS_SOURCES} ${SDLAPPS_DIR}/Templates/UIManager.cpp)

target_link_libraries(SDLApps Qt5::Widgets)
target_link_libraries(SDLApps HMIFrameWork)
target_link_libraries(SDLApps HMIWidgets)

# for test
if(BUILD_TESTS)

find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

add_subdirectory(Templates)

endif()
