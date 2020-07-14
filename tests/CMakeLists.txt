function(add_rdg_test NAME)
  add_executable(test_${NAME} src/test_${NAME}.c)
  target_link_libraries(test_${NAME} rdg)
  add_test(test_${NAME} test_${NAME})
endfunction(add_rdg_test)

add_rdg_test(rdg)
add_rdg_test(rdg_atom)
add_rdg_test(rdg_branch)
add_rdg_test(rdg_buffer)
add_rdg_test(rdg_group)
add_rdg_test(rdg_range)

add_test(test_cli ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_cli
  ${PROJECT_BINARY_DIR}/src/rdg ${CMAKE_CURRENT_SOURCE_DIR}/data)
