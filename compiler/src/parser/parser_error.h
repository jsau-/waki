#ifndef waki_parser_parser_error
#define waki_parser_parser_error

#include <exception>
#include <sstream>
#include <string>
#include <vector>

#include "../tokenizer/token.h"
#include "../tokenizer/token_names.h"
#include "../tokenizer/token_type.h"

struct ParserError : public std::exception {
  Token token;
  std::vector<TokenType> expectedTokenTypes;
  std::string errorMsg;

  ParserError(Token token, std::vector<TokenType> expectedTokenTypes)
      : token(token), expectedTokenTypes(expectedTokenTypes) {
    std::string expectedTokenList;

    if (expectedTokenTypes.size() == 1) {
      expectedTokenList = TOKEN_NAMES.at(expectedTokenTypes[0]);
    } else {
      auto expectedTokenListStream = std::ostringstream();
      expectedTokenListStream << "one of ";

      for (auto& expectedTokenType : expectedTokenTypes) {
        expectedTokenListStream << TOKEN_NAMES.at(expectedTokenType);
        if (&expectedTokenType != &expectedTokenTypes.back()) {
          expectedTokenListStream << ", ";
        }
      }

      expectedTokenList = expectedTokenListStream.str();
    }

    this->errorMsg =
        std::string("Parser error at line ") +
        std::to_string(token.lineNumber) + std::string(", column ") +
        std::to_string(token.columnNumber) + std::string("\n") +
        std::string("Expected ") + expectedTokenList + " but received " +
        TOKEN_NAMES.at(token.type) + std::string("\n") +
        "Near: " + token.value + std::string("\n");
  };

  char const* what() const throw() { return this->errorMsg.c_str(); }
};

#endif
