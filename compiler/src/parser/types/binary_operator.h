#ifndef waki_parser_types_binary_operator
#define waki_parser_types_binary_operator

#include "../../tokenizer/lexeme_type.h"

enum class BinaryOperator {
  EQUALS = (int)LexemeType::EQUALS,
  NOT_EQUALS = (int)LexemeType::NOT_EQUALS,
  LOGICAL_AND = (int)LexemeType::LOGICAL_AND,
  LOGICAL_OR = (int)LexemeType::LOGICAL_OR,
  BITWISE_AND = (int)LexemeType::BITWISE_AND,
  BITWISE_OR = (int)LexemeType::BITWISE_OR,
  BITWISE_XOR = (int)LexemeType::BITWISE_XOR,
  BITWISE_NOT = (int)LexemeType::BITWISE_NOT,
  BITWISE_SHIFT_LEFT = (int)LexemeType::BITWISE_SHIFT_LEFT,
  BITWISE_SHIFT_RIGHT = (int)LexemeType::BITWISE_SHIFT_RIGHT,
  LESS_THAN_OR_EQUAL = (int)LexemeType::LESS_THAN_OR_EQUAL,
  GREATER_THAN_OR_EQUAL = (int)LexemeType::GREATER_THAN_OR_EQUAL,
  MULTIPLY_ASSIGN = (int)LexemeType::MULTIPLY_ASSIGN,
  DIVIDE_ASSIGN = (int)LexemeType::DIVIDE_ASSIGN,
  ADD_ASSIGN = (int)LexemeType::ADD_ASSIGN,
  SUBTRACT_ASSIGN = (int)LexemeType::SUBTRACT_ASSIGN,
  LESS_THAN = (int)LexemeType::LESS_THAN,
  GREATER_THAN = (int)LexemeType::GREATER_THAN,
  MULTIPLY = (int)LexemeType::MULTIPLY,
  DIVIDE = (int)LexemeType::DIVIDE,
  ADD = (int)LexemeType::ADD,
  SUBTRACT = (int)LexemeType::SUBTRACT,
};

#endif
