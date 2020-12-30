#ifndef waki_tokenizer_token_patterns
#define waki_tokenizer_token_patterns

#include <map>
#include <regex>

#include "./lexeme_type.h"

/**
 * Non-exhaustive set of patterns that can be used to identify tokens. Note that
 * certain tokens will be omitted from the list if no relevant pattern could be
 * used to match them (eg. END_OF_FILE)
 */
const std::map<LexemeType, std::regex> TOKEN_PATTERNS = {
  {LexemeType::WHITESPACE, std::regex("\\s+")},
  {LexemeType::SINGLE_LINE_COMMENT, std::regex("//.*")},

  /*
   * TODO: This is pretty dumb, and will trigger identifier declarations
   * containing these tokens, eg. `doubleInterval`. This is obviously not
   * something we want.
   */
  {LexemeType::SIGNED_INTEGER_32, std::regex("int")},
  {LexemeType::FLOAT, std::regex("float")},
  {LexemeType::DOUBLE, std::regex("double")},
  {LexemeType::BOOLEAN, std::regex("bool")},
  {LexemeType::STRING, std::regex("string")},
  {LexemeType::FUNCTION, std::regex("function")},
  {LexemeType::FUNCTION_RETURNS, std::regex("returns")},
  {LexemeType::RETURN, std::regex("return")},
  {LexemeType::MUTABLE, std::regex("mutable")},
  {LexemeType::NULLABLE, std::regex("nullable")},
  {LexemeType::NAMESPACE, std::regex("namespace")},
  {LexemeType::IMPORT, std::regex("#import")},

  {LexemeType::NULL_LITERAL, std::regex("null")},
  {LexemeType::FLOAT_LITERAL, std::regex("[+-]?([0-9]*[.])?[0-9]+f")},
  {LexemeType::DOUBLE_LITERAL, std::regex("[+-]?([0-9]*[.])?[0-9]+d")},
  {LexemeType::SIGNED_INTEGER_32_LITERAL, std::regex("[+-]?\\d+")},
  {LexemeType::BOOLEAN_LITERAL, std::regex("true|false")},
  {LexemeType::STRING_LITERAL, std::regex("'([^'\\\\]|\\\\.)*'")},

  {LexemeType::EQUALS, std::regex("==")},
  {LexemeType::NOT_EQUALS, std::regex("!=")},
  {LexemeType::LOGICAL_AND, std::regex("&&")},
  {LexemeType::LOGICAL_OR, std::regex("\\|\\|")},
  {LexemeType::BITWISE_AND, std::regex("&")},
  {LexemeType::BITWISE_OR, std::regex("\\|")},
  {LexemeType::BITWISE_XOR, std::regex("\\^")},
  {LexemeType::BITWISE_NOT, std::regex("~")},
  {LexemeType::BITWISE_SHIFT_LEFT, std::regex("<<")},
  {LexemeType::BITWISE_SHIFT_RIGHT, std::regex(">>")},
  {LexemeType::LESS_THAN_OR_EQUAL, std::regex("<=")},
  {LexemeType::GREATER_THAN_OR_EQUAL, std::regex(">=")},
  {LexemeType::NOT, std::regex("!")},
  {LexemeType::LESS_THAN, std::regex("<")},
  {LexemeType::GREATER_THAN, std::regex(">")},
  {LexemeType::NULL_COALESCE, std::regex("\\?\\?")},
  {LexemeType::TERNARY, std::regex("\\?")},
  {LexemeType::TERNARY_FALLBACK, std::regex(":")},
  {LexemeType::MULTIPLY_ASSIGN, std::regex("\\*=")},
  {LexemeType::DIVIDE_ASSIGN, std::regex("\\/=")},
  {LexemeType::ADD_ASSIGN, std::regex("\\+=")},
  {LexemeType::SUBTRACT_ASSIGN, std::regex("-=")},
  {LexemeType::ASSIGN_EQUALS, std::regex("=")},
  {LexemeType::MULTIPLY, std::regex("\\*")},
  {LexemeType::DIVIDE, std::regex("\\/")},
  {LexemeType::ADD, std::regex("\\+")},
  {LexemeType::SUBTRACT, std::regex("-")},

  {LexemeType::OPEN_BRACE, std::regex("\\{")},
  {LexemeType::CLOSE_BRACE, std::regex("\\}")},
  {LexemeType::OPEN_PARENTHESIS, std::regex("\\(")},
  {LexemeType::CLOSE_PARENTHESIS, std::regex("\\)")},

  {LexemeType::END_OF_STATEMENT, std::regex(";")},

  {LexemeType::IDENTIFIER, std::regex("[A-Za-z_]+")},
};

#endif
