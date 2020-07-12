find_package(PythonInterp 3)
find_package(PythonLibs 3)

if(PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
  exec_program(${PYTHON_EXECUTABLE}
    ARGS "-c \"from distutils import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))\""
    OUTPUT_VARIABLE PYTHON_SUFFIX
    RETURN_VALUE PYTHON_SUFFIX_NOT_FOUND)

  exec_program(${PYTHON_EXECUTABLE}
    ARGS "-c \"from distutils import sysconfig; print(sysconfig.get_python_lib(plat_specific=True))\""
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    RETURN_VALUE PYTHON_SITE_PACKAGES_NOT_FOUND)


  include_directories(${PYTHON_INCLUDE_DIR})

  add_library(pyrdg SHARED pyrdg.c)
  set_target_properties(pyrdg PROPERTIES SUFFIX "${PYTHON_SUFFIX}")
  set_target_properties(pyrdg PROPERTIES PREFIX "")
  set_target_properties(pyrdg PROPERTIES OUTPUT_NAME "rdg")
  target_link_libraries(pyrdg rdg ${PYTHON_LIBRARIES})

  install(TARGETS pyrdg LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES})

  add_test(NAME test_pyrdg COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_pyrdg.py)
  set_property(TEST test_pyrdg PROPERTY ENVIRONMENT PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR})
endif(PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
