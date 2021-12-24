cmake_minimum_required(VERSION 3.18)
project(eventpp2)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "Build the tests." ON)

file(GLOB_RECURSE sources "src/*.cpp")

add_library(eventpp ${sources})

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(test/)
endif()

target_compile_options(eventpp PUBLIC -Wall)
target_include_directories(eventpp PUBLIC
	"include/"
	PRIVATE
	"src/"
)
target_link_libraries(eventpp
	
)
