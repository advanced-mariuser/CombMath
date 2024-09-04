FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(source1 ${SRC})
target_include_directories(source1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})