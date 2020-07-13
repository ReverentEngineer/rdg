cmake_minimum_required(VERSION 2.8)
enable_testing()

project(rdg C)
set(PROJECT_VERSION 1.0.0)

if (APPLE)
  set(CMAKE_MACOSX_RPATH FALSE)
endif()

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(doc)
add_subdirectory(python)
