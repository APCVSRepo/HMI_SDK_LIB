

add_subdirectory(./jsoncpp)
set(JSON_INCLUDE_DIR ${JSON_INCLUDE_DIR} PARENT_SCOPE)

add_subdirectory(./googletest-release-1.8.0)
set(GOOGLETEST_INCLUDE_DIR ${GOOGLETEST_INCLUDE_DIR} PARENT_SCOPE)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
add_subdirectory(./pthread4w)
set(PTHREAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pthread4w PARENT_SCOPE)
endif()









