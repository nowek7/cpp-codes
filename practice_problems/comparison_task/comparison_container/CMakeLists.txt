cmake_minimum_required(VERSION 3.16)
project(comparison_container)

set(HEADERS
    inc/vector_comparison_tool.hpp
    inc/list_comparison_tool.hpp
    inc/deque_comparison_tool.hpp)

set(SOURCES
    src/vector_comparison_tool.cpp
    src/list_comparison_tool.cpp
    src/deque_comparison_tool.cpp
    src/main.cpp)

include_directories(inc)
include_directories(../externals)

add_executable(comparison_container ${SOURCES})

set_target_properties (comparison_container PROPERTIES FOLDER "comparison_container")
