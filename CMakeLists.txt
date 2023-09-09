cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project("Cache")

file(GLOB SRC "src/*")
add_executable(DEBUG ${SRC})
target_include_directories(DEBUG PRIVATE "include")
target_link_libraries(DEBUG gtest gmock pthread)

file(GLOB SRC "src/*")
add_executable(RELEASE ${SRC})
target_include_directories(RELEASE PRIVATE "include")
target_link_libraries(RELEASE gtest gmock pthread)

file(GLOB SRC "src/*")
add_executable(TEST ${SRC})
target_include_directories(TEST PRIVATE "include")
target_link_libraries(TEST gtest gmock pthread)
target_compile_definitions(TEST PRIVATE TEST_PARAM)