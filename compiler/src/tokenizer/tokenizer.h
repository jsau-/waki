#ifndef waki_tokenizer_tokenizer
#define waki_tokenizer_tokenizer

#include <string>
#include <vector>

#include "token.h"

struct Tokenizer {
  Tokenizer(std::string sourceText);

  /**
   * Generate a syntactically-significant set of tokens.
   */
  std::vector<Token> tokenize();

 private:
  std::string sourceText;

  uint64_t line;
  uint64_t column;

  Token nextMatch();
  void eatChars(int charsToEat);
};

#endif
