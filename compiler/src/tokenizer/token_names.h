#ifndef waki_tokenizer_token_names
#define waki_tokenizer_token_names

#include <map>
#include <string>
#include "token_type.h"

const std::map<TokenType, std::string> TOKEN_NAMES = {
  { TokenType::WHITESPACE, "Whitespace" },
  { TokenType::SINGLE_LINE_COMMENT, "Single-line comment" },
  { TokenType::MULTI_LINE_COMMENT, "Multi-line comment" },

  { TokenType::SIGNED_INTEGER_32, "Signed 32-bit integer" },
  { TokenType::FLOAT, "Float" },
  { TokenType::DOUBLE, "Double" },
  { TokenType::BOOLEAN, "Boolean" },
  { TokenType::STRING, "String" },
  { TokenType::FUNCTION, "Function" },
  { TokenType::FUNCTION_RETURNS, "Function return" },
  { TokenType::RETURN, "Return" },
  { TokenType::MUTABLE, "Mutable" },
  { TokenType::NULLABLE, "Nullable" },
  { TokenType::NAMESPACE, "Namespace" },
  { TokenType::IMPORT, "Import" },

  { TokenType::NULL_LITERAL, "Null literal" },
  { TokenType::FLOAT_LITERAL, "Float literal" },
  { TokenType::DOUBLE_LITERAL, "Double literal" },
  { TokenType::SIGNED_INTEGER_32_LITERAL, "Signed 32-bit integer literal" },
  { TokenType::BOOLEAN_LITERAL, "Boolean literal" },
  { TokenType::STRING_LITERAL, "String literal" },

  { TokenType::EQUALS, "Equals" },
  { TokenType::MULTIPLY, "Multiply" },
  { TokenType::DIVIDE, "Divide" },
  { TokenType::ADD, "Add" },
  { TokenType::SUBTRACT, "Subtract" },
  { TokenType::LOGICAL_AND, "Logical and" },
  { TokenType::LOGICAL_OR, "Logical or" },
  { TokenType::BITWISE_AND, "Bitwise and" },
  { TokenType::BITWISE_OR, "Bitwise or" },
  { TokenType::BITWISE_XOR, "Bitwise xor" },
  { TokenType::BITWISE_NOT, "Bitwise ot" },
  { TokenType::BITWISE_SHIFT_LEFT, "Bitwise shift left" },
  { TokenType::BITWISE_SHIFT_RIGHT, "Bitwise shift right" },
  { TokenType::LESS_THAN_OR_EQUAL, "Less than or equal" },
  { TokenType::GREATER_THAN_OR_EQUAL, "Greater than or equal" },
  { TokenType::LESS_THAN, "Less than" },
  { TokenType::GREATER_THAN, "Greater than" },
  { TokenType::NULL_COALESCE, "Null coalesce" },
  { TokenType::TERNARY, "Ternary" },
  { TokenType::TERNARY_FALLBACK, "Ternary fallback" },

  { TokenType::OPEN_BRACE, "Open brace" },
  { TokenType::CLOSE_BRACE, "Close brace" },
  { TokenType::OPEN_PARENTHESIS, "Open parenthesis" },
  { TokenType::CLOSE_PARENTHESIS, "Close parenthesis" },

  { TokenType::END_OF_STATEMENT, "End of statement" },

  { TokenType::IDENTIFIER, "Identifier" },
};

#endif
