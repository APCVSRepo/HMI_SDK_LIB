
set(QUICKLANUCH_DIR ${SDL_QT_HMI_DIR}/QuickLanuch)

include_directories (
    ${QUICKLANUCH_DIR}
    ${QUICKLANUCH_DIR}/app
    ${QUICKLANUCH_DIR}/Factory
    ${QUICKLANUCH_DIR}/Source
    ${QUICKLANUCH_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          QUICKLANUCH_SOURCES)
aux_source_directory(./app      QUICKLANUCH_SOURCES)
aux_source_directory(./Factory  QUICKLANUCH_SOURCES)
aux_source_directory(./UI       QUICKLANUCH_SOURCES)

find_package(Qt5Widgets)

add_library (QuickLanuch ${QUICKLANUCH_SOURCES})

target_link_libraries(QuickLanuch HMIFrameWork)
target_link_libraries(QuickLanuch HMIWidgets)
target_link_libraries(QuickLanuch Qt5::Widgets)
