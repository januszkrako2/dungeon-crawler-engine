cmake_minimum_required(VERSION 3.25.1...4.0)
project(dungeon-crawler
	VERSION 1.0
	DESCRIPTION "A simple dungeon crawler game designed for the terminal"
	LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
add_executable(${CMAKE_PROJECT_NAME})
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
	-O3
	-Wall -Wextra -Wpedantic -Werror
)
add_subdirectory(src)
add_subdirectory(lib)
