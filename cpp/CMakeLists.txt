cmake_minimum_required (VERSION 2.6)
project (zero-example-cpp)
add_executable(example example.cpp)
target_link_libraries(example zmq)
