#ifndef waki_tokenizer_token
#define waki_tokenizer_token

#include <string>

#include "lexeme_type.h"

/**
 * Struct describing an instance of a lexeme matched by the tokenizer. As well
 * as the token's type and value, we also track any useful metadata that will
 * be useful later for raising errors to the programmer, like where in the
 * source file this token occurred.
 */
struct Token {
  LexemeType type;
  std::string value;
  uint64_t lineNumber;
  uint64_t columnNumber;

  Token(LexemeType type, std::string value, uint64_t lineNumber = 0, uint64_t columnNumber = 0)
    : type(type), value(value), lineNumber(lineNumber), columnNumber(columnNumber) {}

  Token() : Token(LexemeType::UNKNOWN, "", 0, 0) {}

  bool operator==(const Token &rhs) const;
  bool operator!=(const Token &rhs) const;
};

#endif
