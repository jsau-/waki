#ifndef waki_tokenizer_token_names
#define waki_tokenizer_token_names

#include <map>
#include <string>

#include "lexeme_type.h"

const std::map<LexemeType, std::string> TOKEN_NAMES = {
  {LexemeType::WHITESPACE, "whitespace"},
  {LexemeType::SINGLE_LINE_COMMENT, "single-line comment"},

  {LexemeType::SIGNED_INTEGER_32, "signed 32-bit integer"},
  {LexemeType::FLOAT, "float"},
  {LexemeType::DOUBLE, "double"},
  {LexemeType::BOOLEAN, "boolean"},
  {LexemeType::STRING, "string"},
  {LexemeType::FUNCTION, "function"},
  {LexemeType::FUNCTION_RETURNS, "function return"},
  {LexemeType::RETURN, "return"},
  {LexemeType::MUTABLE, "mutable variable modifier"},
  {LexemeType::NULLABLE, "nullable variable modifier"},
  {LexemeType::NAMESPACE, "namespace"},
  {LexemeType::IMPORT, "import"},

  {LexemeType::NULL_LITERAL, "null literal"},
  {LexemeType::FLOAT_LITERAL, "float literal"},
  {LexemeType::DOUBLE_LITERAL, "double literal"},
  {LexemeType::SIGNED_INTEGER_32_LITERAL, "signed 32-bit integer literal"},
  {LexemeType::BOOLEAN_LITERAL, "boolean literal"},
  {LexemeType::STRING_LITERAL, "string literal"},

  {LexemeType::EQUALS, "=="},
  {LexemeType::NOT_EQUALS, "!="},
  {LexemeType::LOGICAL_AND, "&&"},
  {LexemeType::LOGICAL_OR, "||"},
  {LexemeType::BITWISE_AND, "&"},
  {LexemeType::BITWISE_OR, "|"},
  {LexemeType::BITWISE_XOR, "^"},
  {LexemeType::BITWISE_NOT, "~"},
  {LexemeType::BITWISE_SHIFT_LEFT, "<<"},
  {LexemeType::BITWISE_SHIFT_RIGHT, ">>"},
  {LexemeType::LESS_THAN_OR_EQUAL, "<="},
  {LexemeType::GREATER_THAN_OR_EQUAL, ">="},
  {LexemeType::NOT, "!"},
  {LexemeType::LESS_THAN, "<"},
  {LexemeType::GREATER_THAN, ">"},
  {LexemeType::NULL_COALESCE, "??"},
  {LexemeType::TERNARY, "?"},
  {LexemeType::TERNARY_FALLBACK, ":"},
  {LexemeType::MULTIPLY_ASSIGN, "*="},
  {LexemeType::DIVIDE_ASSIGN, "/="},
  {LexemeType::ADD_ASSIGN, "+="},
  {LexemeType::SUBTRACT_ASSIGN, "-="},
  {LexemeType::ASSIGN_EQUALS, "="},
  {LexemeType::MULTIPLY, "*"},
  {LexemeType::DIVIDE, "/"},
  {LexemeType::ADD, "+"},
  {LexemeType::SUBTRACT, "-"},

  {LexemeType::OPEN_BRACE, "{"},
  {LexemeType::CLOSE_BRACE, "}"},
  {LexemeType::OPEN_PARENTHESIS, "("},
  {LexemeType::CLOSE_PARENTHESIS, ")"},

  {LexemeType::END_OF_STATEMENT, ";"},

  {LexemeType::IDENTIFIER, "identifier"},
};

#endif
