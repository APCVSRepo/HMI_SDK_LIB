set(PTHREAD_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(PTHREAD_INCLUDE_DIRECTORY ${PTHREAD_INCLUDE_DIRECTORY} PARENT_SCOPE)

# Set target name.
set(TARGET pthread)

# Add include directories.
include_directories(
  .
  ${SQLITE3_INCLUDE_DIRECTORY}/include
)

if(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
include_directories(
  ${WCECOMPAT_INCLUDE_DIRECTORY}
)
endif()

# Add source code files.
set (SOURCES
  pthread.c
)

# Add the difinitions.
if (NOT BUILD_SHARED_LIBS)
add_definitions(-DPTW32_STATIC_LIB)
endif()

add_definitions(-DHAVE_PTW32_CONFIG_H)
add_definitions(-DUNICODE)
add_definitions(-DHAVE_CONFIG_H)
if(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
add_definitions(-DWINCE)
endif()

# Set output target and type.
if (BUILD_SHARED_LIBS)
  add_library(${TARGET} SHARED ${SOURCES})
else()
  add_library(${TARGET} ${SOURCES})
endif()
