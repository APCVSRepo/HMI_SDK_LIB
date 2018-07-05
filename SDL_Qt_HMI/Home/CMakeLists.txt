
set(HOME_DIR ${SDL_QT_HMI_DIR}/Home)

include_directories (
    ${HOME_DIR}
    ${HOME_DIR}/app
    ${HOME_DIR}/data
    ${HOME_DIR}/data/Settings
    ${HOME_DIR}/Factory
    ${HOME_DIR}/Source
    ${HOME_DIR}/UI
    ${HOME_DIR}/UI/PlayVedio
    ${HOME_DIR}/UI/Settings
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.                  HOME_SOURCES)
aux_source_directory(./app              HOME_SOURCES)
aux_source_directory(./data             HOME_SOURCES)
aux_source_directory(./data/Settings    HOME_SOURCES)
aux_source_directory(./Factory          HOME_SOURCES)
aux_source_directory(./UI               HOME_SOURCES)
aux_source_directory(./UI/Settings      HOME_SOURCES)
aux_source_directory(./UI/PlayVedio     HOME_SOURCES)

find_package(Qt5Widgets)

add_library (Home ${HOME_SOURCES})

target_link_libraries(Home Qt5::Widgets)
target_link_libraries(Home HMIFrameWork)
target_link_libraries(Home HMIWidgets)
