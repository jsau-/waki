list(APPEND waki_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/identifier_already_defined_error.h
  ${CMAKE_CURRENT_LIST_DIR}/identifier_table.cpp
  ${CMAKE_CURRENT_LIST_DIR}/identifier_table.h
  ${CMAKE_CURRENT_LIST_DIR}/identifier_undefined_error.h
  ${CMAKE_CURRENT_LIST_DIR}/identifier.cpp
  ${CMAKE_CURRENT_LIST_DIR}/identifier.h
  ${CMAKE_CURRENT_LIST_DIR}/mutability_violation_error.h
  ${CMAKE_CURRENT_LIST_DIR}/type_error.h
  ${CMAKE_CURRENT_LIST_DIR}/typechecker_error.h
  ${CMAKE_CURRENT_LIST_DIR}/typechecker.cpp
  ${CMAKE_CURRENT_LIST_DIR}/typechecker.h
  ${CMAKE_CURRENT_LIST_DIR}/uninferrable_type_error.h
)
