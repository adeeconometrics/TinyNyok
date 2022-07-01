cmake_minimum_required(VERSION 3.16)

set(This NyokTest)

file(GLOB_RECURSE TEST_FILES *.cpp)
set(Source ${TEST_FILES})

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC 
	gtest_main
	TinyNyok
)

add_test(
	NAME ${This}
	COMMAND ${This}
)