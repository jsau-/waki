include(${CMAKE_CURRENT_LIST_DIR}/expressions/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/statements/CMakeLists.txt)

list(APPEND waki_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/ast_node.h
  ${CMAKE_CURRENT_LIST_DIR}/ast_visitor.h
  ${CMAKE_CURRENT_LIST_DIR}/parser_error.h
  ${CMAKE_CURRENT_LIST_DIR}/parser.cpp
  ${CMAKE_CURRENT_LIST_DIR}/parser.h
)
