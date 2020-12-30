#include "tokenizer.h"
#include "lexemes.h"
#include "lexeme_type.h"
#include "token.h"
#include "tokenizer_error.h"
#include <regex>
#include <sstream>

/*
 * Tokens we want to filter out before returning.
 */
const LexemeType excludedTokenTypes[] = {
  LexemeType::UNKNOWN,
  LexemeType::WHITESPACE,
  LexemeType::END_OF_FILE,
  LexemeType::SINGLE_LINE_COMMENT,
};

Tokenizer::Tokenizer(std::string sourceText) {
  this->sourceText = sourceText;
  this->line = 0;
  this->column = 0;
}

std::vector<Token> Tokenizer::tokenize() {
  auto tokens = std::vector<Token>();

  TokenizerMatch mostRecentMatch;

  do {
    mostRecentMatch = this->nextMatch();

    auto isTokenExcluded = std::find(std::begin(excludedTokenTypes), std::end(excludedTokenTypes),
                                     mostRecentMatch.token.type) != std::end(excludedTokenTypes);

    if (!isTokenExcluded) {
      tokens.push_back(mostRecentMatch.token);
    }
  } while (mostRecentMatch.token.type != LexemeType::END_OF_FILE);

  return tokens;
}

TokenizerMatch Tokenizer::nextMatch() {
  if (this->sourceText.length() == 0) {
    return TokenizerMatch(Token(LexemeType::END_OF_FILE, "", this->line, this->column), 0);
  }

  for (auto tokenizerPatternIterator = Lexemes::metadata.begin();
       tokenizerPatternIterator != Lexemes::metadata.end(); tokenizerPatternIterator++) {
    auto tokenType = tokenizerPatternIterator->first;
    auto tokenPattern = tokenizerPatternIterator->second.pattern;

    std::smatch matches;

    if (!tokenPattern.has_value()) {
      continue;
    }

    if (std::regex_search(this->sourceText, matches, *tokenPattern,
                          std::regex_constants::match_continuous)) {
      auto tokenizerMatch = TokenizerMatch(
        Token(tokenType, matches[0].str(), this->line, this->column), matches[0].str().length());

      this->eatChars(matches[0].str().length());

      return tokenizerMatch;
    }
  }

  throw TokenizerError(this->sourceText, this->line, this->column);
}

void Tokenizer::eatChars(int charsToEat) {
  for (int i = 0; i < charsToEat; i++) {
    if (this->sourceText[i] == '\n') {
      this->line++;
      this->column = 0;
    } else {
      this->column++;
    }
  }

  this->sourceText.erase(0, charsToEat);
}
