cmake_minimum_required(VERSION 3.16)
project(comparison-task)

if (UNIX)
  message(status "** Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions -Wall -Wextra")
elseif(WIN32)
  message(status "** Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /std:c++latest")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(comparison_container)
add_subdirectory(comparison_map)