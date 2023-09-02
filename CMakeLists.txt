cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project("Cache")

file(GLOB SRC "src/*")
add_executable(main ${SRC})
target_include_directories(main PRIVATE "include")
# add_executable(test main.cpp)
target_link_libraries(main gtest gmock pthread)