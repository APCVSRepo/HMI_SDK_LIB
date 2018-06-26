
set(MEDIA_DIR ${SDL_QT_HMI_DIR}/Media)

include_directories (
    ${MEDIA_DIR}
    ${MEDIA_DIR}/app
    ${MEDIA_DIR}/Factory
    ${MEDIA_DIR}/Source
    ${MEDIA_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          MEDIA_SOURCES)
aux_source_directory(./app      MEDIA_SOURCES)
aux_source_directory(./Factory  MEDIA_SOURCES)
aux_source_directory(./UI       MEDIA_SOURCES)

find_package(Qt5Widgets)

add_library (Media ${MEDIA_SOURCES})

target_link_libraries(Media Qt5::Widgets)
target_link_libraries(Media HMIFrameWork)
target_link_libraries(Media HMIWidgets)
