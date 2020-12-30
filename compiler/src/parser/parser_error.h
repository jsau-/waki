#ifndef waki_parser_parser_error
#define waki_parser_parser_error

#include <exception>
#include <string>
#include "../tokenizer/token.h"

struct ParserError : public std::exception {
  std::string reason;
  Token token;
  std::string errorMsg;

  ParserError(std::string reason, Token token) : reason(reason), token(token) {
    this->errorMsg = std::string("Parser error at line ")
      + std::to_string(token.lineNumber)
      + std::string(", column ")
      + std::to_string(token.columnNumber)
      + std::string("\n")
      + reason
      + std::string("\n")
      + "Near: "
      + token.value
      + std::string("\n");
  };

  char const* what() const throw() {
    return this->errorMsg.c_str();
  }
};

#endif
