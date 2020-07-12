project(eventpp)

file(GLOB_RECURSE sources "${CMAKE_SOURCE_DIR}/test/*.cpp")


add_executable(eventpp-test ${sources})
add_dependencies(eventpp-test eventpp)

target_include_directories(
	eventpp-test
	PUBLIC
	"${CMAKE_SOURCE_DIR}/test/"
	"${CMAKE_SOURCE_DIR}/lib/catch2"
)
target_compile_options(eventpp-test PUBLIC -Wall)

target_link_libraries(eventpp-test eventpp)