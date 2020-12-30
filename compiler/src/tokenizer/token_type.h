#ifndef waki_tokenizer_tokentype
#define waki_tokenizer_tokentype

/**
 * Note that the order of declaration here is important, and will affect the
 * precedence for token generation in the case two valid options are presented.
 * eg. If we defined integer literals before float literals, then `1.0f` might
 * be parsed as tokens `INT[1]` and `FLOAT[.0f]`.
 *
 * Additionally, this means any multi-character tokens which contain the same
 * characters as any single-character tokens will need to be defined _before_
 * the single-character tokens.
 */
enum class TokenType {
  /*
   * Syntactically unimportant values
   */

  UNKNOWN,
  WHITESPACE,
  SINGLE_LINE_COMMENT,
  END_OF_FILE,

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

  /*
   * NB: Identifier has been left 'til last to prevent us assigning identifiers
   * to reserved keywords or data types. Unfortunately that's meant that we
   * end up matching things like `float` when they're part of identifier names,
   * eg. `bool floating = false` being tokenized as `bool; float; ing; =; false`
   * which is obviously not ideal.
   *
   * TODO:
   *   - Move this to a higher precedence level than reserved key words so it
   *     gets tokenized first.
   *   - In tokenizer, if we've matched an identifier and we've exactly matched
   *     a reserved keyword, return the reserved keyword instead.
   */

  IDENTIFIER,
};

#endif
