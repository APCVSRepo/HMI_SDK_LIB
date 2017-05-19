
#link_directories()


set(LIBRARIES
)

include_directories (
  ${CONNECT_INCLUDE_DIR}
  ${JSON_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include
)

set (SOURCES
  main.cpp
)


add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT} ${LIBRARIES})

install(TARGETS ${PROJECT} DESTINATION ${CMAKE_BINARY_DIR}/bin)
