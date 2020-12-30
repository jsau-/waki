#ifndef waki_tokenizer_lexemes
#define waki_tokenizer_lexemes

#include <regex>
#include <string>
#include <vector>

#include "lexeme_flags.h"
#include "lexeme_metadata.h"
#include "lexeme_type.h"

std::map<LexemeType, LexemeMetadata> LEXEMES = {
  /*
   * Syntactically unimportant values
   */

  {LexemeType::UNKNOWN, LexemeMetadata("unknown")},
  {LexemeType::WHITESPACE, LexemeMetadata("whitespace", std::regex("\\s+"))},
  {LexemeType::SINGLE_LINE_COMMENT, LexemeMetadata("single line comment", std::regex("//.*"))},

  /*
   * Data types
   */

  {LexemeType::SIGNED_INTEGER_32,
   LexemeMetadata("signed 32-bit integer variable", std::regex("int"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                    LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::FLOAT, LexemeMetadata("floating point variable", std::regex("float"), tl::nullopt,
                                     LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                       LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::DOUBLE,
   LexemeMetadata("double-precision variable", std::regex("double"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                    LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::BOOLEAN, LexemeMetadata("boolean variable", std::regex("bool"), tl::nullopt,
                                       LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                         LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::STRING, LexemeMetadata("string variable", std::regex("string"), tl::nullopt,
                                      LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                        LEXEMEFLAG_RESERVED_KEYWORD)},

  /*
   * Data type modifiers
   */

  {LexemeType::MUTABLE,
   LexemeMetadata("mutable modifier", std::regex("mutable"), "mutable",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_VARIABLE_MODIFIER |
                    LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::NULLABLE,
   LexemeMetadata("nullable modifier", std::regex("nullable"), "nullable",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_VARIABLE_MODIFIER |
                    LEXEMEFLAG_RESERVED_KEYWORD)},

  /*
   * Data type literal values
   */

  {LexemeType::NULL_LITERAL,
   LexemeMetadata("null literal", std::regex("null"), "null",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::FLOAT_LITERAL,
   LexemeMetadata("floating point literal", std::regex("[+-]?([0-9]*[.])?[0-9]+f"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::DOUBLE_LITERAL,
   LexemeMetadata("double-precision literal", std::regex("[+-]?([0-9]*[.])?[0-9]+d"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::SIGNED_INTEGER_32_LITERAL,
   LexemeMetadata("signed 32-bit integer literal", std::regex("[+-]?\\d+"), tl::nullopt,
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::BOOLEAN_LITERAL, LexemeMetadata("boolean literal", std::regex("true|false"),
                                               tl::nullopt, LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::STRING_LITERAL, LexemeMetadata("string literal", std::regex("'([^'\\\\]|\\\\.)*'"),
                                              tl::nullopt, LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},

  /*
   * Keywords
   */

  {LexemeType::FUNCTION,
   LexemeMetadata("function", std::regex("function"), "function",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::FUNCTION_RETURNS,
   LexemeMetadata("returns", std::regex("returns"), "returns",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::RETURN,
   LexemeMetadata("return", std::regex("return"), "return",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::NAMESPACE,
   LexemeMetadata("namespace", std::regex("namespace"), "namespace",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
  {LexemeType::IMPORT,
   LexemeMetadata("import", std::regex("import"), "import",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},

  /*
   * Operators
   */

  {LexemeType::EQUALS,
   LexemeMetadata("equality", std::regex("=="),
                  "==", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::NOT_EQUALS,
   LexemeMetadata("inequality", std::regex("!="),
                  "!=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::LOGICAL_AND,
   LexemeMetadata("logical and", std::regex("&&"), "&&",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::LOGICAL_OR,
   LexemeMetadata("logical or", std::regex("\\|\\|"), "||",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::BITWISE_AND,
   LexemeMetadata("bitwise and", std::regex("&"), "&",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::BITWISE_OR,
   LexemeMetadata("bitwise or", std::regex("\\|"), "|",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::BITWISE_XOR,
   LexemeMetadata("bitwise xor", std::regex("\\^"), "^",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::BITWISE_SHIFT_LEFT,
   LexemeMetadata("bitwise shift left", std::regex("<<"), "<<",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::BITWISE_SHIFT_RIGHT,
   LexemeMetadata("bitwise shift right", std::regex(">>"), ">>",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::LESS_THAN_OR_EQUAL,
   LexemeMetadata("less than or equal", std::regex("<="),
                  "<=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::GREATER_THAN_OR_EQUAL,
   LexemeMetadata("greater than or equal", std::regex(">="),
                  ">=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::LESS_THAN,
   LexemeMetadata("less than", std::regex("<"), "<",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::GREATER_THAN,
   LexemeMetadata("greater than", std::regex(">"), ">",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::NULL_COALESCE,
   LexemeMetadata("null coalesce", std::regex("\\?\\?"), "??",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},
  {LexemeType::TERNARY,
   LexemeMetadata("ternary", std::regex("\\?"), "?",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::TERNARY_FALLBACK,
   LexemeMetadata("ternary fallback", std::regex(":"), ":",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::MULTIPLY_ASSIGN,
   LexemeMetadata("multiplication assign", std::regex("\\*="), "*=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                    LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {LexemeType::DIVIDE_ASSIGN,
   LexemeMetadata("divide assign", std::regex("\\/="), "/=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                    LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {LexemeType::ADD_ASSIGN,
   LexemeMetadata("addition assign", std::regex("\\+="), "+=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                    LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {LexemeType::SUBTRACT_ASSIGN,
   LexemeMetadata("subtraction assign", std::regex("-="), "-=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                    LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {LexemeType::ASSIGN_EQUALS,
   LexemeMetadata("equals", std::regex("="), "=",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
  {LexemeType::MULTIPLY,
   LexemeMetadata("multiply", std::regex("\\*"), "*",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::DIVIDE,
   LexemeMetadata("divide", std::regex("\\/"), "/",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::ADD,
   LexemeMetadata("add", std::regex("\\+"), "+",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::SUBTRACT,
   LexemeMetadata("subtract", std::regex("-"), "-",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
  {LexemeType::NOT, LexemeMetadata("logical not", std::regex("!"), "!",
                                   LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},
  {LexemeType::BITWISE_NOT,
   LexemeMetadata("bitwise not", std::regex("~"), "~",
                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},

  /*
   * Syntax symbols
   */

  {LexemeType::OPEN_BRACE,
   LexemeMetadata("open brace", std::regex("\\{"), "{", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::CLOSE_BRACE,
   LexemeMetadata("open brace", std::regex("\\}"), "}", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::OPEN_PARENTHESIS,
   LexemeMetadata("open parenthesis", std::regex("\\("), "(", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::CLOSE_PARENTHESIS,
   LexemeMetadata("close brace", std::regex("\\)"), ")", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::END_OF_STATEMENT,
   LexemeMetadata("end of statement", std::regex(";"), ";", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  {LexemeType::LIST_DELIMITER,
   LexemeMetadata("list delimiter", std::regex("\\,"), ",", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},

  {LexemeType::IDENTIFIER, LexemeMetadata("identifier", std::regex("[A-Za-z_]+"), tl::nullopt,
                                          LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
};
#endif
