#ifndef waki_parser_types_assignment_operator
#define waki_parser_types_assignment_operator

#include <stdexcept>
#include <string>
#include "../../tokenizer/token_names.h"
#include "../../tokenizer/token_type.h"

enum class AssignmentOperator {
  MULTIPLY_ASSIGN = (int)TokenType::MULTIPLY_ASSIGN,
  DIVIDE_ASSIGN = (int)TokenType::DIVIDE_ASSIGN,
  ADD_ASSIGN = (int)TokenType::ADD_ASSIGN,
  SUBTRACT_ASSIGN = (int)TokenType::SUBTRACT_ASSIGN,
  ASSIGN_EQUALS = (int)TokenType::ASSIGN_EQUALS,
};

#endif
