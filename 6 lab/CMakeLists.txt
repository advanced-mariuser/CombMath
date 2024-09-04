cmake_minimum_required(VERSION 3.26)

project(HungarianAlgorithm)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(HungarianAlgorithm main.cpp)

target_link_libraries(HungarianAlgorithm PRIVATE source1)

#add_subdirectory(test)
#
#add_dependencies(HungarianAlgorithm run_tests)