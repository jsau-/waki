cmake_minimum_required(VERSION 3.5)

project(waki VERSION 0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

add_compile_options(-pedantic-errors -Wall -Wextra -Werror)

include_directories(include)

set (waki_SOURCES)

include(src/CMakeLists.txt)

add_executable(waki ${waki_SOURCES})
