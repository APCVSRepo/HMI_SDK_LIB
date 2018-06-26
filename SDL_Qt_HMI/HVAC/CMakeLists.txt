
set(HVAC_DIR ${SDL_QT_HMI_DIR}/HVAC)

include_directories (
    ${HVAC_DIR}
    ${HVAC_DIR}/app
    ${HVAC_DIR}/data
    ${HVAC_DIR}/Factory
    ${HVAC_DIR}/Source
    ${HVAC_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          HVAC_SOURCES)
aux_source_directory(./app      HVAC_SOURCES)
aux_source_directory(./data     HVAC_SOURCES)
aux_source_directory(./Factory  HVAC_SOURCES)
aux_source_directory(./UI       HVAC_SOURCES)

find_package(Qt5Widgets)

add_library (HVAC ${HVAC_SOURCES})

target_link_libraries(HVAC Qt5::Widgets)
target_link_libraries(HVAC HMIFrameWork)
target_link_libraries(HVAC HMIWidgets)
