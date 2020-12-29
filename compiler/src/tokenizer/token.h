#ifndef waki_tokenizer_token
#define waki_tokenizer_token

#include <string>
#include "token_type.h"

struct Token {
  TokenType type;
  std::string value;
  uint64_t lineNumber;
  uint64_t columnNumber;

  Token(
    TokenType type,
    std::string value,
    uint64_t lineNumber = 0,
    uint64_t columnNumber = 0
  ) : type(type), value(value), lineNumber(lineNumber), columnNumber(columnNumber) {}

  Token() : Token(TokenType::UNKNOWN, "", 0, 0) {}
};

#endif
