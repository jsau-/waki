#include "tokenizer.h"
#include "lexeme_type.h"
#include "lexemes.h"
#include "token.h"
#include "tokenizer_error.h"
#include <regex>
#include <sstream>

Tokenizer::Tokenizer(std::string sourceText) {
  this->sourceText = sourceText;
  this->line = 1;
  this->column = 1;
}

std::vector<Token> Tokenizer::tokenize() {
  auto tokens = std::vector<Token>();

  auto significantLexemes = Lexemes::getInstance().getSignificantToTokenize();

  Token latestToken;

  do {
    latestToken = this->nextMatch();

    auto isTokenExcluded = std::find(std::begin(significantLexemes), std::end(significantLexemes),
                                     latestToken.type) == std::end(significantLexemes);

    if (!isTokenExcluded) {
      tokens.push_back(latestToken);
    }
  } while (latestToken.type != LexemeType::END_OF_FILE);

  return tokens;
}

Token Tokenizer::nextMatch() {
  if (this->sourceText.length() == 0) {
    return Token(LexemeType::END_OF_FILE, "", this->line, this->column);
  }

  auto lexemeMetadata = Lexemes::getInstance().getMetadata();
  auto reservedKeywords = Lexemes::getInstance().getReservedKeywords();

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
      auto tokenValue = matches[0].str();

      /*
       * As written, an identifier might be a reserved word. In the case it is,
       * we want to switch over to using the token type for the reserved
       * keyword.
       *
       * This stops people from using our own keywords in naughty ways!
       *
       * TODO: We can probably tidy this up a bit!
       */
      if (tokenType == LexemeType::IDENTIFIER) {
        for (const auto &reservedKeyword : reservedKeywords) {
          std::smatch reservedMatches;

          if (std::regex_search(tokenValue, reservedMatches,
                                reservedKeyword.second,
                                std::regex_constants::match_continuous)) {
            if (reservedMatches[0].str() == tokenValue) {
              tokenType = reservedKeyword.first;
              break;
            }
          }
        }
      }

      this->eatChars(tokenValue.length());

      return Token(tokenType, tokenValue, this->line, this->column);
    }
  }

  throw TokenizerError(this->sourceText, this->line, this->column);
}

void Tokenizer::eatChars(uint64_t charsToEat) {
  // TODO: This won't work on Windows using \r\n will it?
  // TODO: Easy optimization - jump to the last-most newline in the block we
  // want to eat, and calculate the diff between its offset and the offset we
  // want to eat to; increment line by number of newlines; increment column by
  // difference in offsets
  for (uint64_t i = 0; i < charsToEat; i++) {
    if (this->sourceText[i] == '\n') {
      this->line++;
      this->column = 1;
    } else {
      this->column++;
    }
  }

  this->sourceText.erase(0, charsToEat);
}
