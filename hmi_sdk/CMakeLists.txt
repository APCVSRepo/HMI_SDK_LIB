
include_directories (
  ./
)

add_subdirectory(./connect)
set(CONNECT_INCLUDE_DIR ${CONNECT_INCLUDE_DIR} PARENT_SCOPE)

add_subdirectory(./app_data)
