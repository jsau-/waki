#ifndef waki_parser_types_binary_operator
#define waki_parser_types_binary_operator

#include "../../tokenizer/token_type.h"

enum class BinaryOperator {
  EQUALS = (int)TokenType::EQUALS,
  NOT_EQUALS = (int)TokenType::NOT_EQUALS,
  LOGICAL_AND = (int)TokenType::LOGICAL_AND,
  LOGICAL_OR = (int)TokenType::LOGICAL_OR,
  BITWISE_AND = (int)TokenType::BITWISE_AND,
  BITWISE_OR = (int)TokenType::BITWISE_OR,
  BITWISE_XOR = (int)TokenType::BITWISE_XOR,
  BITWISE_NOT = (int)TokenType::BITWISE_NOT,
  BITWISE_SHIFT_LEFT = (int)TokenType::BITWISE_SHIFT_LEFT,
  BITWISE_SHIFT_RIGHT = (int)TokenType::BITWISE_SHIFT_RIGHT,
  LESS_THAN_OR_EQUAL = (int)TokenType::LESS_THAN_OR_EQUAL,
  GREATER_THAN_OR_EQUAL = (int)TokenType::GREATER_THAN_OR_EQUAL,
  MULTIPLY_ASSIGN = (int)TokenType::MULTIPLY_ASSIGN,
  DIVIDE_ASSIGN = (int)TokenType::DIVIDE_ASSIGN,
  ADD_ASSIGN = (int)TokenType::ADD_ASSIGN,
  SUBTRACT_ASSIGN = (int)TokenType::SUBTRACT_ASSIGN,
  LESS_THAN = (int)TokenType::LESS_THAN,
  GREATER_THAN = (int)TokenType::GREATER_THAN,
  MULTIPLY = (int)TokenType::MULTIPLY,
  DIVIDE = (int)TokenType::DIVIDE,
  ADD = (int)TokenType::ADD,
  SUBTRACT = (int)TokenType::SUBTRACT,
};

#endif
