bison_target(PARSER parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c)
flex_target(LEXER lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.c
 COMPILE_FLAGS "-R --header-file=${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.h")
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(rdg_version.c.in rdg_version.c @ONLY)

add_library(rdg 
  rdg_atom.c
  rdg_branch.c
  rdg_group.c
  rdg_buffer.c
  rdg_range.c 
  rdg.c
  ${CMAKE_CURRENT_BINARY_DIR}/rdg_version.c
  ${BISON_PARSER_OUTPUTS}
  ${FLEX_LEXER_OUTPUTS})

add_executable(rdg-bin main.c)
set_target_properties(rdg-bin PROPERTIES OUTPUT_NAME rdg)
target_link_libraries(rdg-bin rdg)
if(NOT WIN32)
    target_link_libraries(rdg  m)
endif()

install(TARGETS rdg rdg-bin 
  EXPORT
  RDG
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES rdg.h DESTINATION include)
