# find source files in current path
aux_source_directory(. HMI_FRAMEWORK_SOURCES)

find_package(Qt5Widgets)

add_library (HMIFrameWork ${HMI_FRAMEWORK_SOURCES})

target_link_libraries(HMIFrameWork Qt5::Widgets)
target_link_libraries(HMIFrameWork /usr/lib/x86_64-linux-gnu/libgstreamer-1.0.so)
target_link_libraries(HMIFrameWork /usr/lib/x86_64-linux-gnu/libgobject-2.0.so)
target_link_libraries(HMIFrameWork /usr/lib/x86_64-linux-gnu/libgstvideo-1.0.so)
