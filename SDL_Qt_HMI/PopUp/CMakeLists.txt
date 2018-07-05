
set(POPUP_DIR ${SDL_QT_HMI_DIR}/PopUp)

include_directories (
    ${POPUP_DIR}
    ${POPUP_DIR}/app
    ${POPUP_DIR}/Factory
    ${POPUP_DIR}/Source
    ${POPUP_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          POPUP_SOURCES)
aux_source_directory(./app      POPUP_SOURCES)
aux_source_directory(./Factory  POPUP_SOURCES)
aux_source_directory(./UI       POPUP_SOURCES)

find_package(Qt5Widgets)

add_library (PopUp ${POPUP_SOURCES})

target_link_libraries(PopUp Qt5::Widgets)
target_link_libraries(PopUp HMIFrameWork)
target_link_libraries(PopUp HMIWidgets)
