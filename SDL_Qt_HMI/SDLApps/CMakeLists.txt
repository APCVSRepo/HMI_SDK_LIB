
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
aux_source_directory(./Templates                    SDLAPPS_SOURCES)
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

add_library (SDLApps ${SDLAPPS_SOURCES})

target_link_libraries(SDLApps Qt5::Widgets)
target_link_libraries(SDLApps HMIFrameWork)
target_link_libraries(SDLApps HMIWidgets)
