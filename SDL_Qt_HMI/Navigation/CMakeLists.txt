
set(NAVIGATION_DIR ${SDL_QT_HMI_DIR}/Navigation)

include_directories (
    ${NAVIGATION_DIR}
    ${NAVIGATION_DIR}/app
    ${NAVIGATION_DIR}/Factory
    ${NAVIGATION_DIR}/Source
    ${NAVIGATION_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          NAVIGATION_SOURCES)
aux_source_directory(./app      NAVIGATION_SOURCES)
aux_source_directory(./Factory  NAVIGATION_SOURCES)
aux_source_directory(./UI       NAVIGATION_SOURCES)

find_package(Qt5Widgets)

add_library (Navigation ${NAVIGATION_SOURCES})

target_link_libraries(Navigation HMIFrameWork)
target_link_libraries(Navigation HMIWidgets)
target_link_libraries(Navigation Qt5::Widgets)
