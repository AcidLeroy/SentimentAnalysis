set(prog_name preprocessing)

add_executable(${prog_name}_test ${prog_name}_test.cpp) 
target_link_libraries(${prog_name}_test gtest gtest_main)
add_test( NAME ${prog_name}_test  COMMAND ${prog_name}_test)

