
set(PROMPT_DIR ${SDL_QT_HMI_DIR}/Prompt)

include_directories (
    ${PROMPT_DIR}
    ${PROMPT_DIR}/app
    ${PROMPT_DIR}/Factory
    ${PROMPT_DIR}/Source
    ${PROMPT_DIR}/UI
    ${HMIFRAMEWORK_DIR}
    ${HMIWIDGETS_DIR}
)

aux_source_directory(.          PROMPT_SOURCES)
aux_source_directory(./app      PROMPT_SOURCES)
aux_source_directory(./Factory  PROMPT_SOURCES)
aux_source_directory(./UI       PROMPT_SOURCES)

find_package(Qt5Widgets)

add_library (Prompt ${PROMPT_SOURCES})

target_link_libraries(Prompt Qt5::Widgets)
target_link_libraries(Prompt HMIFrameWork)
target_link_libraries(Prompt HMIWidgets)
