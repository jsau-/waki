#ifndef waki_parser_parser_error
#define waki_parser_parser_error

#include <exception>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

#include "../tokenizer/lexeme_type.h"
#include "../tokenizer/lexemes.h"
#include "../tokenizer/token.h"

struct ParserError : public std::exception {
  Token token;
  std::set<LexemeType> expectedTokenTypes;
  std::string errorMsg;

  ParserError(Token token, std::set<LexemeType> expectedTokenTypes)
    : token(token), expectedTokenTypes(expectedTokenTypes) {
    std::string expectedTokenList;

    auto lexemeMetadata = Lexemes::getInstance().getMetadata();

    if (expectedTokenTypes.size() == 1) {
      expectedTokenList = lexemeMetadata.at(*expectedTokenTypes.begin()).displayName;
    } else {
      auto expectedTokenListStream = std::ostringstream();
      expectedTokenListStream << "one of " << std::endl;

      for (auto iter = expectedTokenTypes.begin(); iter != expectedTokenTypes.end(); ++iter) {
        expectedTokenListStream << " " << lexemeMetadata.at(*iter).displayName;
        if (std::next(iter) != expectedTokenTypes.end()) {
          expectedTokenListStream << std::endl;
        }
    }

      expectedTokenList = expectedTokenListStream.str();
    }

    this->errorMsg =
      std::string("Parser error at line ") + std::to_string(token.lineNumber) +
      std::string(", column ") + std::to_string(token.columnNumber) + std::string("\n\n") +
      std::string("Expected ") + expectedTokenList + std::string("\n\n") +
      "Received: " + lexemeMetadata.at(token.type).displayName + std::string("\n\n");
  };

  char const *what() const throw() { return this->errorMsg.c_str(); }
};

#endif
