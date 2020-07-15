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

    foreach (MANALIAS rdg_new.3 rdg_permutations.3 rdg_free.3)
      install(CODE "execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink 
      rdg_generate.3 \${CMAKE_INSTALL_PREFIX}/share/man/man3/${MANALIAS})")
        install(CODE "message(STATUS \"Created man alias: rdg_generate.3 -> ${MANALIAS}}\")")
    endforeach()

    add_custom_target(man ALL DEPENDS rdg.1 rdg_generate.3)
  endif(POD2MAN_EXECUTABLE)
endif(UNIX)

find_program(SPHINX_EXECUTABLE sphinx-build)
if(SPHINX_EXECUTABLE)
  message(STATUS "Found sphinx-build. Documentation enabled.")

  add_custom_target(docs COMMAND ${SPHINX_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/sphinx html)
endif(SPHINX_EXECUTABLE)
