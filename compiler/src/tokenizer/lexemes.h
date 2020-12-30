#ifndef waki_tokenizer_lexemes
#define waki_tokenizer_lexemes

#include <regex>
#include <string>
#include <vector>

#include "lexeme_flags.h"
#include "lexeme_metadata.h"
#include "token_type.h"

std::map<TokenType, LexemeMetadata> LEXEMES = {
  /*
   * Syntactically unimportant values
   */

  {TokenType::UNKNOWN, LexemeMetadata("unknown")},
  {TokenType::WHITESPACE, LexemeMetadata("whitespace", std::regex("\\s+"))},
  {TokenType::SINGLE_LINE_COMMENT, LexemeMetadata("single line comment", std::regex("//.*"))},

  /*
   * Data types
   */

  {TokenType::SIGNED_INTEGER_32,
   LexemeMetadata("signed 32-bit integer variable", std::regex("int"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                    LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::FLOAT, LexemeMetadata("floating point variable", std::regex("float"), tl::nullopt,
                                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                      LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::DOUBLE, LexemeMetadata("double-precision variable", std::regex("double"), tl::nullopt,
                                     LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                       LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::BOOLEAN, LexemeMetadata("boolean variable", std::regex("bool"), tl::nullopt,
                                      LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                        LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::STRING, LexemeMetadata("string variable", std::regex("string"), tl::nullopt,
                                     LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                       LEXEMEFLAG_RESERVED_KEYWORD)},

  /*
   * Data type modifiers
   */

  {TokenType::MUTABLE,
   LexemeMetadata("mutable modifier", std::regex("mutable"), "mutable",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_VARIABLE_MODIFIER |
                    LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::NULLABLE,
   LexemeMetadata("nullable modifier", std::regex("nullable"), "nullable",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_VARIABLE_MODIFIER |
                    LEXEMEFLAG_RESERVED_KEYWORD)},

  /*
   * Data type literal values
   */

  {TokenType::NULL_LITERAL,
   LexemeMetadata("null literal", std::regex("null"), "null",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::FLOAT_LITERAL,
   LexemeMetadata("floating point literal", std::regex("[+-]?([0-9]*[.])?[0-9]+f"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::DOUBLE_LITERAL,
   LexemeMetadata("double-precision literal", std::regex("[+-]?([0-9]*[.])?[0-9]+d"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::SIGNED_INTEGER_32_LITERAL,
   LexemeMetadata("signed 32-bit integer literal", std::regex("[+-]?\\d+"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::BOOLEAN_LITERAL, LexemeMetadata("boolean literal", std::regex("true|false"),
                                              tl::nullopt, LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::STRING_LITERAL, LexemeMetadata("string literal", std::regex("'([^'\\\\]|\\\\.)*'"),
                                             tl::nullopt, LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},

  /*
   * Keywords
   */

  {TokenType::FUNCTION,
   LexemeMetadata("function", std::regex("function"), "function",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::FUNCTION_RETURNS,
   LexemeMetadata("returns", std::regex("returns"), "returns",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::RETURN,
   LexemeMetadata("return", std::regex("return"), "return",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::NAMESPACE,
   LexemeMetadata("namespace", std::regex("namespace"), "namespace",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {TokenType::IMPORT,
   LexemeMetadata("import", std::regex("import"), "import",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},

  /*
   * Operators
   */

  {TokenType::EQUALS,
   LexemeMetadata("equality", std::regex("=="),
                  "==", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::NOT_EQUALS,
   LexemeMetadata("inequality", std::regex("!="),
                  "!=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::LOGICAL_AND,
   LexemeMetadata("logical and", std::regex("&&"), "&&",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::LOGICAL_OR,
   LexemeMetadata("logical or", std::regex("\\|\\|"), "||",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::BITWISE_AND,
   LexemeMetadata("bitwise and", std::regex("&"), "&",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::BITWISE_OR,
   LexemeMetadata("bitwise or", std::regex("\\|"), "|",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::BITWISE_XOR,
   LexemeMetadata("bitwise xor", std::regex("\\^"), "^",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::BITWISE_SHIFT_LEFT,
   LexemeMetadata("bitwise shift left", std::regex("<<"), "<<",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::BITWISE_SHIFT_RIGHT,
   LexemeMetadata("bitwise shift right", std::regex(">>"), ">>",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::LESS_THAN_OR_EQUAL,
   LexemeMetadata("less than or equal", std::regex("<="),
                  "<=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::GREATER_THAN_OR_EQUAL,
   LexemeMetadata("greater than or equal", std::regex(">="),
                  ">=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::LESS_THAN,
   LexemeMetadata("less than", std::regex("<"), "<",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::GREATER_THAN,
   LexemeMetadata("greater than", std::regex(">"), ">",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::NULL_COALESCE,
   LexemeMetadata("null coalesce", std::regex("\\?\\?"), "??",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},
  {TokenType::TERNARY,
   LexemeMetadata("ternary", std::regex("\\?"), "?",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::TERNARY_FALLBACK,
   LexemeMetadata("ternary fallback", std::regex(":"), ":",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::MULTIPLY_ASSIGN,
   LexemeMetadata("multiplication assign", std::regex("\\*="), "*=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                    LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {TokenType::DIVIDE_ASSIGN,
   LexemeMetadata("divide assign", std::regex("\\/="), "/=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                    LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {TokenType::ADD_ASSIGN,
   LexemeMetadata("addition assign", std::regex("\\+="), "+=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                    LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {TokenType::SUBTRACT_ASSIGN,
   LexemeMetadata("subtraction assign", std::regex("-="), "-=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                    LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {TokenType::ASSIGN_EQUALS,
   LexemeMetadata("equals", std::regex("="), "=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {TokenType::MULTIPLY,
   LexemeMetadata("multiply", std::regex("\\*"), "*",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::DIVIDE,
   LexemeMetadata("divide", std::regex("\\/"), "/",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::ADD, LexemeMetadata("add", std::regex("\\+"), "+",
                                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::SUBTRACT,
   LexemeMetadata("subtract", std::regex("-"), "-",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {TokenType::NOT, LexemeMetadata("logical not", std::regex("!"), "!",
                                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},
  {TokenType::BITWISE_NOT,
   LexemeMetadata("bitwise not", std::regex("~"), "~",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},

  /*
   * Syntax symbols
   */

  {TokenType::OPEN_BRACE,
   LexemeMetadata("open brace", std::regex("\\{"), "{", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::CLOSE_BRACE,
   LexemeMetadata("open brace", std::regex("\\}"), "}", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::OPEN_PARENTHESIS,
   LexemeMetadata("open parenthesis", std::regex("\\("), "(", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::CLOSE_PARENTHESIS,
   LexemeMetadata("close brace", std::regex("\\)"), ")", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::END_OF_STATEMENT,
   LexemeMetadata("end of statement", std::regex(";"), ";", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {TokenType::LIST_DELIMITER,
   LexemeMetadata("list delimiter", std::regex("\\,"), ",", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},

  {TokenType::IDENTIFIER, LexemeMetadata("identifier", std::regex("[A-Za-z_]+"), tl::nullopt,
                                         LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
};
#endif
