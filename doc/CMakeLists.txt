if (BUILD_DOCS)
  if (UNIX)
    find_program(POD2MAN_EXECUTABLE pod2man)

    if (POD2MAN_EXECUTABLE)
      message(STATUS "Found pod2man. Manpages enabled.")
    
      add_custom_command(OUTPUT rdg.1 COMMAND ${POD2MAN_EXECUTABLE} --center="User Commands"
        --release=${PROJECT_VERSION} ${CMAKE_CURRENT_SOURCE_DIR}/man1/rdg.pod ./rdg.1)

      install(FILES ${CMAKE_CURRENT_BINARY_DIR}/rdg.1 DESTINATION share/man/man1)
    
      add_custom_command(OUTPUT rdg_generate.3 COMMAND ${POD2MAN_EXECUTABLE} --center="Library Functions"
      --release=${PROJECT_VERSION} --name=RDG ${CMAKE_CURRENT_SOURCE_DIR}/man3/rdg_generate.pod ./rdg_generate.3)
  
      install(FILES ${CMAKE_CURRENT_BINARY_DIR}/rdg_generate.3 DESTINATION share/man/man3)

      macro(install_symlink path link)
        install(CODE "execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink ${path} \${CMAKE_INSTALL_PREFIX}/${link})")
        install(CODE "message(STATUS \"Created symlink: ${link} -> ${path}\")")
      endmacro(install_symlink)

      foreach (LINK rdg_new.3 rdg_permutations.3 rdg_free.3)
          install_symlink(rdg_generate.3 share/man/man3/${LINK})
      endforeach()

      add_custom_target(man ALL DEPENDS rdg.1 rdg_generate.3)
    endif(POD2MAN_EXECUTABLE)
  endif(UNIX)

  if (DOXYGEN_FOUND)
    message(STATUS "Found doxygen. API documentation enabled.")
    configure_file(Doxyfile.in Doxyfile @ONLY)

    add_custom_target(doxygen ALL
      COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen"
      VERBATIM)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share)
  endif()
endif()
