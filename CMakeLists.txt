cmake_minimum_required(VERSION 2.8)
enable_testing()

project(rdg C)
set(PROJECT_VERSION 1.0.0)

include(CTest)

if (APPLE)
  set(CMAKE_MACOSX_RPATH FALSE)
endif()

find_package(BISON 2.6.0 REQUIRED)
find_package(FLEX REQUIRED)

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(doc)
add_subdirectory(python)

set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION "A regex data generation library")
set(CPACK_PACKAGE_RELEASE 1)
include(CPack)

install(EXPORT RDG DESTINATION cmake)
configure_file(RDGConfig.cmake.in RDGConfig.cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/RDGConfig.cmake DESTINATION cmake)
configure_file(rdg.pc.in rdg.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/rdg.pc DESTINATION lib/pkgconfig)
