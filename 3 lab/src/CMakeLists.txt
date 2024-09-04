FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(gamma ${SRC})
target_include_directories(gamma PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})