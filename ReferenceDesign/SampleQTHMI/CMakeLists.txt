cmake_minimum_required(VERSION 2.8.11)

project(SampleQTHMI)

option(BUILD_TESTS "Possibility to build and run tests" OFF)
option(BUILD_TESTS_COVERAGE "Possibility to generate test coverage report when run tests" OFF)

# for test
if(BUILD_TESTS_COVERAGE)
    #auto enable BUILD_TESTS when BUILD_TESTS_COVERAGE is enabled
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    enable_testing()

    add_definitions(-DBUILD_TESTS)
    message(STATUS "Tests enabled")
endif()

if(BUILD_TESTS_COVERAGE)
    add_definitions(-DBUILD_TESTS_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    message(STATUS "Tests coverage enabled")
endif()


set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# QT Tools
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTORCC ON)


set(SDL_QT_HMI_DIR ${CMAKE_SOURCE_DIR})
set(HMIFRAMEWORK_DIR ${CMAKE_SOURCE_DIR}/HMIFrameWork)
set(HMIWIDGETS_DIR ${CMAKE_SOURCE_DIR}/HMIWidgets)


include_directories(
    ${SDL_QT_HMI_DIR}
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
    ${SDL_QT_HMI_DIR}/../../HMI_SDK_LIB/include
    /usr/include/glib-2.0
    /usr/include/gstreamer-1.0
    /usr/lib/x86_64-linux-gnu
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
    /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include
    ${SDL_QT_HMI_DIR}/Home/app
    ${SDL_QT_HMI_DIR}/QuickLanuch/app
    ${SDL_QT_HMI_DIR}/StatusBar/app
    ${SDL_QT_HMI_DIR}/PopUp/app
    ${SDL_QT_HMI_DIR}/Prompt/app
    ${SDL_QT_HMI_DIR}/SDLApps/app
    ${SDL_QT_HMI_DIR}/HVAC/app
    ${SDL_QT_HMI_DIR}/Phone/app
    ${SDL_QT_HMI_DIR}/Message/app
    ${SDL_QT_HMI_DIR}/Navigation/app
    ${SDL_QT_HMI_DIR}/Media/app
    ${SDL_QT_HMI_DIR}/VR/app
)

# find source files in current path
aux_source_directory(. DIR_SRCS)

# add subdirectories
add_subdirectory(HMIFrameWork)
add_subdirectory(HMIWidgets)
add_subdirectory(Home)
add_subdirectory(HVAC)
add_subdirectory(Media)
add_subdirectory(Message)
add_subdirectory(Navigation)
add_subdirectory(Phone)
add_subdirectory(PopUp)
add_subdirectory(Prompt)
add_subdirectory(QuickLanuch)
add_subdirectory(SDLApps)
add_subdirectory(StatusBar)
add_subdirectory(VR)

# rcc files
set (RCC_SOURCE
    ${SDL_QT_HMI_DIR}/Home/Source/HomeImages.qrc
    ${SDL_QT_HMI_DIR}/QuickLanuch/Source/QuickLanuchImages.qrc
    ${SDL_QT_HMI_DIR}/Home/Source/images/Settings/SettingsSource.qrc
    ${SDL_QT_HMI_DIR}/StatusBar/Source/StatusBarImages.qrc
    ${SDL_QT_HMI_DIR}/PopUp/Source/PopUpImages.qrc
    ${SDL_QT_HMI_DIR}/HVAC/Source/HVACImages.qrc
    ${SDL_QT_HMI_DIR}/Phone/Source/PhoneImages.qrc
    ${SDL_QT_HMI_DIR}/Prompt/Source/PromptImages.qrc
    ${SDL_QT_HMI_DIR}/Message/Source/MessageImages.qrc
    ${SDL_QT_HMI_DIR}/SDLApps/Source/SDLAppsImages.qrc
    ${SDL_QT_HMI_DIR}/Navigation/Source/NavigationImages.qrc
    ${SDL_QT_HMI_DIR}/Media/Source/MediaImages.qrc
    ${SDL_QT_HMI_DIR}/VR/Source/VRImages.qrc
)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the SampleQTHMI executable
add_executable(SampleQTHMI ${DIR_SRCS} ${RCC_SOURCE})

# Use the Widgets module from Qt 5.
target_link_libraries(SampleQTHMI Qt5::Widgets)
# link other libraries
target_link_libraries(SampleQTHMI HMIFrameWork)
target_link_libraries(SampleQTHMI HMIWidgets)
target_link_libraries(SampleQTHMI Home)
target_link_libraries(SampleQTHMI HVAC)
target_link_libraries(SampleQTHMI Media)
target_link_libraries(SampleQTHMI Message)
target_link_libraries(SampleQTHMI Navi)
target_link_libraries(SampleQTHMI Phone)
target_link_libraries(SampleQTHMI PopUp)
target_link_libraries(SampleQTHMI Prompt)
target_link_libraries(SampleQTHMI QuickLanuch)
target_link_libraries(SampleQTHMI SDLApps)
target_link_libraries(SampleQTHMI StatusBar)
target_link_libraries(SampleQTHMI VoiceRecognition)




