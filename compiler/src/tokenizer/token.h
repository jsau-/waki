#ifndef waki_tokenizer_token
#define waki_tokenizer_token

#include <string>

#include "lexeme_type.h"

struct Token {
  LexemeType type;
  std::string value;
  uint64_t lineNumber;
  uint64_t columnNumber;

  Token(LexemeType type, std::string value, uint64_t lineNumber = 0, uint64_t columnNumber = 0)
    : type(type), value(value), lineNumber(lineNumber), columnNumber(columnNumber) {}

  Token() : Token(LexemeType::UNKNOWN, "", 0, 0) {}
};

#endif
