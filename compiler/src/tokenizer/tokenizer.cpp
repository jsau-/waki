#include <exception>
#include <sstream>
#include "token.h"
#include "token_patterns.h"
#include "token_type.h"
#include "tokenizer.h"

/*
 * Tokens we want to filter out before returning.
 */
const TokenType excludedTokenTypes[] = {
  TokenType::UNKNOWN,
  TokenType::WHITESPACE,
  TokenType::END_OF_FILE,
  TokenType::SINGLE_LINE_COMMENT,
  TokenType::MULTI_LINE_COMMENT,
};

Tokenizer::Tokenizer(std::string sourceText) {
  this->sourceText = sourceText;
  this->index = 0;
  this->line = 0;
  this->column = 0;
}

std::vector<Token> Tokenizer::tokenize() {
  auto tokens = std::vector<Token>();

  TokenizerMatch mostRecentMatch;

  do {
    mostRecentMatch = this->nextMatch();

    auto isTokenExcluded = std::find(
      std::begin(excludedTokenTypes),
      std::end(excludedTokenTypes),
      mostRecentMatch.token.type
    ) != std::end(excludedTokenTypes);

    if (!isTokenExcluded) {
      tokens.push_back(mostRecentMatch.token);
    }
  } while (
    mostRecentMatch.token.type != TokenType::END_OF_FILE
  );

  return tokens;
}

TokenizerMatch Tokenizer::nextMatch() {
  if (this->sourceText.length() <= this->index) {
    return TokenizerMatch(
      Token(TokenType::END_OF_FILE, "", this->line, this->column),
      0
    );
  }

  for (
    auto tokenizerPatternIterator = tokenPatterns.begin();
    tokenizerPatternIterator != tokenPatterns.end();
    tokenizerPatternIterator++
  ) {
    auto tokenType = tokenizerPatternIterator->first;
    auto tokenPattern = tokenizerPatternIterator->second;

    auto patternToCheck = std::string(1, this->sourceText[this->index]);
    auto currentCharIndex = this->index;

    std::string lastMatchingPattern = std::regex_match(patternToCheck, tokenPattern) ? patternToCheck : "";
    auto startLine = this->line;
    auto startColumn = this->column;

    do {
      // We currently match the current token - great, let's cache that
      if (std::regex_match(patternToCheck, tokenPattern)) {
        lastMatchingPattern = patternToCheck;
      /*
       * We _used_ to match this token, but we no longer do. Let's exit now so
       * we don't have to lookahead through the entire source file.
       */
      } else if (lastMatchingPattern != "") {
        break;
      }

      patternToCheck.append(std::string(1, this->sourceText[currentCharIndex + 1]));
      currentCharIndex++;
    } while (this->sourceText.length() > currentCharIndex + 1);

    if (lastMatchingPattern != "") {
      this->eatChars(lastMatchingPattern.length());

      return TokenizerMatch(
        Token(tokenType, lastMatchingPattern, startLine, startColumn),
        lastMatchingPattern.length()
      );
    }
  }

  // TODO: Proper error class/struct
  auto errorStream = std::ostringstream();

  errorStream
    << "Failed to tokenize source file."
    << " Error at line " << std::to_string(this->line)
    << ", column " << std::to_string(this->column)
    << "."
    << std::endl
    << "Near: '"
    << this->sourceText.substr(this->index, 10)
    << "'"
    << std::endl;

  throw std::runtime_error(errorStream.str());
}

void Tokenizer::eatChars(int charsToEat) {
  auto substring = this->sourceText.substr(this->index, charsToEat);

  for(char& curChar : substring) {
    if ('\n' == curChar) {
      this->line++;
      this->column = 0;
    } else {
      this->column++;
    }
  }

  this->index += charsToEat;
}
