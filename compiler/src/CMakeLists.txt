include(${CMAKE_CURRENT_LIST_DIR}/emitter/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/modules/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/parser/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/tokenizer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/typechecker/CMakeLists.txt)

list(APPEND waki_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)
