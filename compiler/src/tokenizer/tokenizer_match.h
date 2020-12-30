#ifndef waki_tokenizer_tokenizer_match
#define waki_tokenizer_tokenizer_match

#include "token.h"

struct TokenizerMatch {
  Token token;
  uint64_t consumedCharacters;

  TokenizerMatch(Token token, uint64_t consumedCharacters)
      : token(token), consumedCharacters(consumedCharacters) {}
  TokenizerMatch() : TokenizerMatch(Token(), 0){};
};

#endif
