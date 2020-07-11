cmake_minimum_required(VERSION 2.8)
enable_testing()

project(rdg C)

if (APPLE)
  set(CMAKE_MACOSX_RPATH FALSE)
endif()

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)
