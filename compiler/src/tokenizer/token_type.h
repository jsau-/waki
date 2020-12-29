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
  UNKNOWN = 0,
  WHITESPACE = 1,
  SINGLE_LINE_COMMENT = 2,
  MULTI_LINE_COMMENT = 3,

  SIGNED_INTEGER_32 = 1000,
  FLOAT = 1001,
  DOUBLE = 1003,
  BOOLEAN = 1004,
  STRING = 1005,
  FUNCTION = 1006,
  FUNCTION_RETURNS = 1007,
  RETURN = 1008,
  MUTABLE = 1009,
  NULLABLE = 1010,
  NAMESPACE = 1011,
  IMPORT = 1012,

  NULL_LITERAL = 2000,
  FLOAT_LITERAL = 2001,
  DOUBLE_LITERAL = 2002,
  SIGNED_INTEGER_32_LITERAL = 2003,
  BOOLEAN_LITERAL = 2004,
  STRING_LITERAL = 2005,

  EQUALS = 3000,
  MULTIPLY = 3001,
  DIVIDE = 3002,
  ADD = 3003,
  SUBTRACT = 3004,
  LOGICAL_AND = 3005,
  LOGICAL_OR = 3006,
  BITWISE_AND = 3007,
  BITWISE_OR = 3008,
  BITWISE_XOR = 3009,
  BITWISE_NOT = 3010,
  BITWISE_SHIFT_LEFT = 3011,
  BITWISE_SHIFT_RIGHT = 3012,
  LESS_THAN_OR_EQUAL = 3013,
  GREATER_THAN_OR_EQUAL = 3014,
  LESS_THAN = 3015,
  GREATER_THAN = 3016,
  NULL_COALESCE = 3017,
  TERNARY = 3018,
  TERNARY_FALLBACK = 3019,

  OPEN_BRACE = 4000,
  CLOSE_BRACE = 4001,
  OPEN_PARENTHESIS = 4002,
  CLOSE_PARENTHESIS = 4003,

  END_OF_FILE = 5000,
  END_OF_STATEMENT = 5001,

  IDENTIFIER = 9999,
};

#endif
