#ifndef waki_parser_types_assignment_operator
#define waki_parser_types_assignment_operator

#include "../../tokenizer/lexeme_type.h"

enum class AssignmentOperator {
  MULTIPLY_ASSIGN = (int)LexemeType::MULTIPLY_ASSIGN,
  DIVIDE_ASSIGN = (int)LexemeType::DIVIDE_ASSIGN,
  ADD_ASSIGN = (int)LexemeType::ADD_ASSIGN,
  SUBTRACT_ASSIGN = (int)LexemeType::SUBTRACT_ASSIGN,
  ASSIGN_EQUALS = (int)LexemeType::ASSIGN_EQUALS,
};

#endif
