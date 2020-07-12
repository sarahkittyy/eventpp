cmake_minimum_required(VERSION 3.13)
project(eventpp)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources "src/*.cpp")

if(DEFINED BUILD_TESTS)
	add_subdirectory("test/")
endif()

add_library(eventpp ${sources})
target_include_directories(eventpp PUBLIC "include/")
target_compile_options(eventpp PUBLIC -Wall)