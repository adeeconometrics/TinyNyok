cmake_minimum_required(VERSION 3.16)

set(This TinyNyok)
project(${This} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -std=c++17")

enable_testing()

add_subdirectory(googletest)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES include/*.cpp)

set(Headers ${INC_FILES})
set(Source ${SRC_FILES})

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
