cmake_minimum_required(VERSION 2.8.11)

project(SDL_Qt_HMI)

# QT Tools
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
SET(CMAKE_AUTOUIC ON) 
# Instruct CMake to run uic automatically when needed.
SET(CMAKE_AUTORCC ON) 

set(SDL_QT_HMI_DIR ${CMAKE_SOURCE_DIR})
set(HMIFRAMEWORK_DIR ${CMAKE_SOURCE_DIR}/HMIFRAMEWORK)
set(HMIWIDGETS_DIR ${CMAKE_SOURCE_DIR}/HMIWidgets)

include_directories (
    ${SDL_QT_HMI_DIR}
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
    ${SDL_QT_HMI_DIR}/../include
    ${SDL_QT_HMI_DIR}/../hmi_sdk/gstplayer/include
    ${SDL_QT_HMI_DIR}/../tools/jsoncpp/include
    ${SDL_QT_HMI_DIR}/../hmi_sdk/connect/include
    ${SDL_QT_HMI_DIR}/../hmi_sdk/app_data/include
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

# Tell CMake to create the SDL_Qt_HMI executable
add_executable(SDL_Qt_HMI ${DIR_SRCS} ${RCC_SOURCE})

# Use the Widgets module from Qt 5.
target_link_libraries(SDL_Qt_HMI Qt5::Widgets)
# link other libraries
target_link_libraries(SDL_Qt_HMI HMIFrameWork)
target_link_libraries(SDL_Qt_HMI HMIWidgets)
target_link_libraries(SDL_Qt_HMI Home)
target_link_libraries(SDL_Qt_HMI HVAC)
target_link_libraries(SDL_Qt_HMI Media)
target_link_libraries(SDL_Qt_HMI Message)
target_link_libraries(SDL_Qt_HMI Navigation)
target_link_libraries(SDL_Qt_HMI Phone)
target_link_libraries(SDL_Qt_HMI PopUp)
target_link_libraries(SDL_Qt_HMI Prompt)
target_link_libraries(SDL_Qt_HMI QuickLanuch)
target_link_libraries(SDL_Qt_HMI SDLApps)
target_link_libraries(SDL_Qt_HMI StatusBar)
target_link_libraries(SDL_Qt_HMI VR)
