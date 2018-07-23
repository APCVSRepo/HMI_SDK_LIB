
set(PHONE_DIR ${SDL_QT_HMI_DIR}/Phone)

include_directories (
    ${PHONE_DIR}
    ${PHONE_DIR}/app
    ${PHONE_DIR}/Factory
    ${PHONE_DIR}/Source
    ${PHONE_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          PHONE_SOURCES)
aux_source_directory(./app      PHONE_SOURCES)
aux_source_directory(./data     PHONE_SOURCES)
aux_source_directory(./Factory  PHONE_SOURCES)
aux_source_directory(./UI       PHONE_SOURCES)

find_package(Qt5Widgets)

add_library (Phone ${PHONE_SOURCES})

target_link_libraries(Phone Qt5::Widgets)
target_link_libraries(Phone HMIFrameWork)
target_link_libraries(Phone HMIWidgets)
