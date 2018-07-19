
set(VR_DIR ${SDL_QT_HMI_DIR}/VR)

include_directories (
    ${VR_DIR}
    ${VR_DIR}/app
    ${VR_DIR}/Factory
    ${VR_DIR}/Source
    ${VR_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          VR_SOURCES)
aux_source_directory(./app      VR_SOURCES)
aux_source_directory(./Factory  VR_SOURCES)
aux_source_directory(./UI       VR_SOURCES)

find_package(Qt5Widgets)

add_library (VoiceRecognition ${VR_SOURCES})

target_link_libraries(VoiceRecognition Qt5::Widgets)
target_link_libraries(VoiceRecognition HMIFrameWork)
target_link_libraries(VoiceRecognition HMIWidgets)
