set(prog_name remove_stop_word)

add_executable(${prog_name}_test ${prog_name}_test.cpp) 
target_link_libraries(${prog_name}_test ${GTEST_BOTH_LIBRARIES})
