cmake_minimum_required(VERSION 3.5)

project(waki VERSION 0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

add_compile_options(-pedantic-errors -Wall -Wextra -Werror)

add_subdirectory(src)
add_subdirectory(test)
