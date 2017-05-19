
#link_directories()

set(LIBRARIES
)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CONNECT_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${JSON_INCLUDE_DIR}
)


set (SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/AppData.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/AppList.cpp
)


add_library(AppData ${SOURCES})

#target_link_libraries(${PROJECT} ${LIBRARIES})

