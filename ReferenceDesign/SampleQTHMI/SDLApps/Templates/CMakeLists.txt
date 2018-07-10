
# for test
if(BUILD_TESTS)

set(SDLAPPS_TEMPLATES_DIR ${SDL_QT_HMI_DIR}/SDLApps/Templates)

include_directories(
    ${SDL_QT_HMI_DIR}/../../HMI_SDK_LIB/include
    ${SDL_QT_HMI_DIR}/3rd_party/include/jsoncpp/include
    ${SDL_QT_HMI_DIR}/../../HMI_SDK_LIB/hmi_sdk/connect/include
    ${SDL_QT_HMI_DIR}/../../HMI_SDK_LIB/hmi_sdk/app_data/include
    ${SDL_QT_HMI_DIR}/HMIFrameWork
    ${SDL_QT_HMI_DIR}/HMIWidgets
    ${SDLAPPS_TEMPLATES_DIR}
    ${SDLAPPS_TEMPLATES_DIR}/test
    ${SDLAPPS_TEMPLATES_DIR}/Alert
    ${SDLAPPS_TEMPLATES_DIR}/Alert/test
    ${SDLAPPS_TEMPLATES_DIR}/AppListView
    ${SDLAPPS_TEMPLATES_DIR}/AppListView/test
    ${SDLAPPS_TEMPLATES_DIR}/ChoiceSet
    ${SDLAPPS_TEMPLATES_DIR}/ChoiceSet/test
    ${SDLAPPS_TEMPLATES_DIR}/CommandView
    ${SDLAPPS_TEMPLATES_DIR}/CommandView/test
    ${SDLAPPS_TEMPLATES_DIR}/Common
    ${SDLAPPS_TEMPLATES_DIR}/Common/test
    ${SDLAPPS_TEMPLATES_DIR}/Config
    ${SDLAPPS_TEMPLATES_DIR}/Config/test
    ${SDLAPPS_TEMPLATES_DIR}/ScrollableMessage
    ${SDLAPPS_TEMPLATES_DIR}/ScrollableMessage/test
    ${SDLAPPS_TEMPLATES_DIR}/Show
    ${SDLAPPS_TEMPLATES_DIR}/Show/test
    ${SDLAPPS_TEMPLATES_DIR}/SliderView
    ${SDLAPPS_TEMPLATES_DIR}/SliderView/test
    ${SDLAPPS_TEMPLATES_DIR}/Template
    ${SDLAPPS_TEMPLATES_DIR}/Template/test
    ${SDLAPPS_TEMPLATES_DIR}/utils/VideoStream
    ${SDLAPPS_TEMPLATES_DIR}/utils/VideoStream/test
)

set (SDLAPPS_SOURCES_TEST test_main.cc)
aux_source_directory(./test                    SDLAPPS_SOURCES_TEST)
aux_source_directory(./Alert/test              SDLAPPS_SOURCES_TEST)
aux_source_directory(./AppListView/test        SDLAPPS_SOURCES_TEST)
aux_source_directory(./ChoiceSet/test          SDLAPPS_SOURCES_TEST)
aux_source_directory(./CommandView/test        SDLAPPS_SOURCES_TEST)
aux_source_directory(./Common/test             SDLAPPS_SOURCES_TEST)
aux_source_directory(./Config/test             SDLAPPS_SOURCES_TEST)
aux_source_directory(./ScrollableMessage/test  SDLAPPS_SOURCES_TEST)
aux_source_directory(./Show/test               SDLAPPS_SOURCES_TEST)
aux_source_directory(./SliderView/test         SDLAPPS_SOURCES_TEST)
aux_source_directory(./Template/test           SDLAPPS_SOURCES_TEST)
aux_source_directory(./utils/VideoStream/test  SDLAPPS_SOURCES_TEST)

find_package(Qt5Widgets)

add_executable(HMI_TEST ${SDLAPPS_SOURCES_TEST})

target_link_libraries(HMI_TEST Qt5::Widgets)
target_link_libraries(HMI_TEST HMIFrameWork)
target_link_libraries(HMI_TEST HMIWidgets)
target_link_libraries(HMI_TEST libgtest libgmock)
target_link_libraries(HMI_TEST SDLApps)
target_link_libraries(HMI_TEST ${SDL_QT_HMI_DIR}/3rd_party/lib/libjsoncpp.a)
target_link_libraries(HMI_TEST ${SDL_QT_HMI_DIR}/lib/linux/libhmi_sdk.so)


#copy lib file to test directory
configure_file(${SDL_QT_HMI_DIR}/lib/linux/libhmi_sdk.so . COPYONLY)

configure_file(${SDLAPPS_TEMPLATES_DIR}/test/HMITest.sh . COPYONLY)

add_test(NAME HMI_TEST
         COMMAND HMITest.sh)
#add_test(NAME HMI_TEST
#         COMMAND HMI_TEST)

endif()

