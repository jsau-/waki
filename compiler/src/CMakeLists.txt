set (waki_SOURCES)

include(${CMAKE_CURRENT_LIST_DIR}/emitter/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/modules/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/parser/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/tokenizer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/typechecker/CMakeLists.txt)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

add_executable(waki ${waki_SOURCES} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
