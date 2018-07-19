# find source files in current path
aux_source_directory(. HMI_WIDGETS_SOURCES)

find_package(Qt5Widgets)

add_library (HMIWidgets ${HMI_WIDGETS_SOURCES})

target_link_libraries(HMIWidgets Qt5::Widgets)
