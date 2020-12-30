#include "tokenizer.h"
#include "lexemes.h"
#include "lexeme_type.h"
#include "token.h"
#include "tokenizer_error.h"
#include <regex>
#include <sstream>

Tokenizer::Tokenizer(std::string sourceText) {
  this->sourceText = sourceText;
  this->line = 0;
  this->column = 0;
}

std::vector<Token> Tokenizer::tokenize() {
  auto tokens = std::vector<Token>();

  auto significantLexemes = Lexemes::getInstance().getSignificantToTokenize();

  TokenizerMatch mostRecentMatch;

  do {
    mostRecentMatch = this->nextMatch();

    auto isTokenExcluded = std::find(std::begin(significantLexemes), std::end(significantLexemes),
                                     mostRecentMatch.token.type) == std::end(significantLexemes);

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

  auto lexemeMetadata = Lexemes::getInstance().getMetadata();

  for (auto tokenizerPatternIterator = lexemeMetadata.begin();
       tokenizerPatternIterator != lexemeMetadata.end(); tokenizerPatternIterator++) {
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
