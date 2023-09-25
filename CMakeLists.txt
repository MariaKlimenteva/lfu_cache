cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project("Cache")

file(GLOB SRC "src/*")
add_executable(DEBUG ${SRC})
target_include_directories(DEBUG PRIVATE "include")

file(GLOB SRC "src/*")
add_executable(RELEASE ${SRC})
target_include_directories(RELEASE PRIVATE "include")

file(GLOB SRC "src/*")
add_executable(TEST ${SRC})
target_include_directories(TEST PRIVATE "include")

target_compile_definitions(TEST PRIVATE TEST_PARAM)

add_custom_target(RUN_TEST DEPENDS TEST
        WORKING_DIRECTORY ../
        COMMAND ./test.sh)