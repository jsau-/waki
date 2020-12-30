#ifndef waki_tokenizer_tokentype
#define waki_tokenizer_tokentype

/**
 * NB: I've assigned explicit values for now. I think there might be some
 * optimizations we can do with cached lexer results.
 *
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
  UNKNOWN,
  WHITESPACE,
  SINGLE_LINE_COMMENT,

  SIGNED_INTEGER_32,
  FLOAT,
  DOUBLE,
  BOOLEAN,
  STRING,
  FUNCTION,
  FUNCTION_RETURNS,
  RETURN,
  MUTABLE,
  NULLABLE,
  NAMESPACE,
  IMPORT,

  NULL_LITERAL,
  FLOAT_LITERAL,
  DOUBLE_LITERAL,
  SIGNED_INTEGER_32_LITERAL,
  BOOLEAN_LITERAL,
  STRING_LITERAL,

  EQUALS,
  LOGICAL_AND,
  LOGICAL_OR,
  BITWISE_AND,
  BITWISE_OR,
  BITWISE_XOR,
  BITWISE_NOT,
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

  OPEN_BRACE,
  CLOSE_BRACE,
  OPEN_PARENTHESIS,
  CLOSE_PARENTHESIS,

  END_OF_FILE,
  END_OF_STATEMENT,

  IDENTIFIER,
};

#endif
