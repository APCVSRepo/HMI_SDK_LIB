
set(STATUSBAR_DIR ${SDL_QT_HMI_DIR}/StatusBar)

include_directories (
    ${STATUSBAR_DIR}
    ${STATUSBAR_DIR}/app
    ${STATUSBAR_DIR}/Factory
    ${STATUSBAR_DIR}/Source
    ${STATUSBAR_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          STATUSBAR_SOURCES)
aux_source_directory(./app      STATUSBAR_SOURCES)
aux_source_directory(./Factory  STATUSBAR_SOURCES)
aux_source_directory(./UI       STATUSBAR_SOURCES)

find_package(Qt5Widgets)

add_library (StatusBar ${STATUSBAR_SOURCES})

target_link_libraries(StatusBar Qt5::Widgets)
target_link_libraries(StatusBar HMIFrameWork)
target_link_libraries(StatusBar HMIWidgets)
