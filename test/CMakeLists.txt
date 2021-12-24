cmake_minimum_required(VERSION 3.18)
project(eventpp2)

find_package(Catch2 REQUIRED)

file(GLOB sources "*.cpp")
add_executable(eventpp2-test ${sources})
add_dependencies(eventpp2-test eventpp2)
target_link_libraries(eventpp2-test eventpp2 Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(eventpp2-test)
