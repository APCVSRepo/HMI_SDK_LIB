
set(MESSAGE_DIR ${SDL_QT_HMI_DIR}/Message)

include_directories (
    ${MESSAGE_DIR}
    ${MESSAGE_DIR}/app
    ${MESSAGE_DIR}/Factory
    ${MESSAGE_DIR}/Source
    ${MESSAGE_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          MESSAGE_SOURCES)
aux_source_directory(./app      MESSAGE_SOURCES)
aux_source_directory(./data     MESSAGE_SOURCES)
aux_source_directory(./Factory  MESSAGE_SOURCES)
aux_source_directory(./UI       MESSAGE_SOURCES)

find_package(Qt5Widgets)
add_library (Message ${MESSAGE_SOURCES})

target_link_libraries(Message Qt5::Widgets)
target_link_libraries(Message HMIFrameWork)
target_link_libraries(Message HMIWidgets)
