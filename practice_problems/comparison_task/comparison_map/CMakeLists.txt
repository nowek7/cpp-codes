cmake_minimum_required(VERSION 3.16)
project(comparison_map)

include_directories(../externals)

add_executable(comparison_map main.cpp map_comparison_tool.cpp)

set_target_properties (comparison_map PROPERTIES FOLDER "comparison_map")