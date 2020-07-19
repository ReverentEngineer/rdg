find_package(PythonInterp 3)
find_package(PythonLibs 3)

if(PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
  set(BUILD_PYTHON ON CACHE BOOL "Enables Python bindings.")
  message(STATUS "Python libraries found. Python bindings are ${BUILD_PYTHON}.")
  if (BUILD_PYTHON)
    add_custom_target(pyrdg ALL 
      ${CMAKE_COMMAND} -E env LD_LIBRARY_PATH=${PROJECT_BINARY_DIR}/src
      ${CMAKE_COMMAND} -E env CFLAGS=\"${CMAKE_C_FLAGS} -I${PROJECT_SOURCE_DIR}/src\"
      ${PYTHON_EXECUTABLE} setup.py build WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      DEPENDS rdg)

    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/build)

    install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE}  setup.py install
      --prefix=\${CMAKE_INSTALL_PREFIX}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})")

    add_test(NAME test_pyrdg COMMAND ${PYTHON_EXECUTABLE} -m unittest discover 
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  endif(BUILD_PYTHON)
endif(PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
