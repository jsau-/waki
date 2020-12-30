#ifndef waki_tokenizer_lexeme_type
#define waki_tokenizer_lexeme_type

/**
 * NB: The enum values here are used elsewhere in the program as keys, eg. in
 * `std::map` which has a defined iteration order (eg. keys ascending). As a
 * result, it's important to place lexeme definitions in the order we'd want
 * them to be parsed.
 *
 * That means any lexemes whose code representations include another lexeme's
 * code representation *MUST* be declared first.
 *
 * eg. Lexeme with code representation `foobar` must appear before the lexeme
 * with code representation `foo`, otherwise we'll match `foo` and never match
 * `foobar`.
 */
enum class LexemeType {
  /*
   * Syntactically unimportant values
   */

  UNKNOWN,
  WHITESPACE,
  SINGLE_LINE_COMMENT,
  END_OF_FILE,

  IDENTIFIER,

  /*
   * Data types
   */

  SIGNED_INTEGER_32,
  FLOAT,
  DOUBLE,
  BOOLEAN,
  STRING,

  /*
   * Data type modifiers
   */

  MUTABLE,
  NULLABLE,

  /*
   * Data type literal values
   */

  NULL_LITERAL,
  FLOAT_LITERAL,
  DOUBLE_LITERAL,
  SIGNED_INTEGER_32_LITERAL,
  BOOLEAN_LITERAL,
  STRING_LITERAL,

  /*
   * Keywords
   */

  FUNCTION,
  FUNCTION_RETURNS,
  RETURN,
  NAMESPACE,
  IMPORT,

  /*
   * Operators
   */

  EQUALS,
  NOT_EQUALS,
  LOGICAL_AND,
  LOGICAL_OR,
  BITWISE_AND,
  BITWISE_OR,
  BITWISE_XOR,
  BITWISE_SHIFT_LEFT,
  BITWISE_SHIFT_RIGHT,
  LESS_THAN_OR_EQUAL,
  GREATER_THAN_OR_EQUAL,
  LESS_THAN,
  GREATER_THAN,
  NULL_COALESCE,
  TERNARY,
  TERNARY_FALLBACK,
  MULTIPLY_ASSIGN,
  DIVIDE_ASSIGN,
  ADD_ASSIGN,
  SUBTRACT_ASSIGN,
  ASSIGN_EQUALS,
  MULTIPLY,
  DIVIDE,
  ADD,
  SUBTRACT,
  NOT,
  BITWISE_NOT,

  /*
   * Syntax symbols
   */

  OPEN_BRACE,
  CLOSE_BRACE,
  OPEN_PARENTHESIS,
  CLOSE_PARENTHESIS,
  END_OF_STATEMENT,
  LIST_DELIMITER,
};

#endif
