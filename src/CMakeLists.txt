bison_target(PARSER parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c)
flex_target(LEXER lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.c
 COMPILE_FLAGS "-R --header-file=${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.h")
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_library(rdg 
  rdg_atom.c
  rdg_branch.c
  rdg_group.c
  rdg_buffer.c
  rdg_range.c 
  rdg.c
  ${BISON_PARSER_OUTPUTS}
  ${FLEX_LEXER_OUTPUTS})

add_executable(rdg-bin main.c)
set_target_properties(rdg-bin PROPERTIES OUTPUT_NAME rdg)
target_link_libraries(rdg-bin rdg)

install(TARGETS rdg rdg-bin RUNTIME DESTINATION bin LIBRARY DESTINATION lib)
install(FILES rdg.h DESTINATION include)
