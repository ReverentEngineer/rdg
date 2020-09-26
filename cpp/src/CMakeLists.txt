add_library(rdg++ rdg.cpp)
target_link_libraries(rdg++ rdg)
install(TARGETS rdg++ DESTINATION lib)
install(FILES rdg.hh DESTINATION include)
