#ifndef waki_tokenizer_tokenizer
#define waki_tokenizer_tokenizer

#include <string>
#include <vector>

#include "token.h"

struct Tokenizer {
  Tokenizer(std::string sourceText);

  /**
   * Generate a syntactically-significant set of tokens, which the parser can
   * use to build an abstract syntax tree representing the program.
   */
  std::vector<Token> tokenize();

 private:
  // The source text file we're attempting to tokenize
  std::string sourceText;

  /*
   * The current line we've reached while tokenizing. Allows us to instantiate
   * individual token structs with values describing _where_ they happened in
   * the program s.t. our errors are more programmer-friendly.
   */
  uint64_t line;

  /*
   * The current column we've reached while tokenizing. Allows us to instantiate
   * individual token structs with values describing _where_ they happened in
   * the program s.t. our errors are more programmer-friendly.
   */
  uint64_t column;

  // Get the next matching token from the source file
  Token nextMatch();

  /*
   * After matching a token, we want to advance the tokenizer past its current
   * position. For now, this is actually implemented as literally removing N
   * characters from the start of the source text - this simplifies the regex
   * checks pretty significantly.
   *
   * This seems performant enough for source files ~10k lines, so we'll leave it
   * as is for now - if we need to optimise this _might_ be somewhere to
   * profile.
   */
  void eatChars(uint64_t charsToEat);
};

#endif
