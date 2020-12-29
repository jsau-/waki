#ifndef waki_parser_parser_error
#define waki_parser_parser_error

#include <exception>
#include <string>
#include <sstream>
#include "../tokenizer/token.h"

struct ParserError : public std::exception {
  std::string reason;
  Token token;
  std::string errorMsg;

  ParserError(std::string reason, Token token) : reason(reason), token(token) {
    auto errorStream = std::ostringstream();

    errorStream
      << "Parser error at line "
      << std::to_string(token.lineNumber)
      << ", column "
      << std::to_string(token.columnNumber)
      << ". "
      << std::endl
      << reason
      << "Near: "
      << token.value
      << std::endl;

    this->errorMsg = errorStream.str();
  };

  char const* what() const throw() {
    return this->errorMsg.c_str();
  }
};

#endif
