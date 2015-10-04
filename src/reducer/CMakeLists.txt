set(prog_name reducer)

file(COPY ${prog_name}.py DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_executable(${prog_name} ${prog_name}.cpp)
