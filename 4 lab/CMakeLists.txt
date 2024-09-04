cmake_minimum_required(VERSION 3.26)

project(CountSpanningTrees)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(CountSpanningTrees main.cpp)

target_link_libraries(CountSpanningTrees PRIVATE source1)

add_subdirectory(test)

add_dependencies(CountSpanningTrees run_tests)