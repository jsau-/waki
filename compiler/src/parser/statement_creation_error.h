#ifndef waki_parser_statement_creation_error
#define waki_parser_statement_creation_error

#include <exception>
#include <string>
#include <sstream>

struct StatementCreationError : public std::exception {
  std::string reason;
  std::string errorMsg;

  StatementCreationError(std::string reason) : reason(reason) {
    auto errorStream = std::ostringstream();

    errorStream
      << "Statement creation error: "
      << reason;

    this->errorMsg = errorStream.str();
  };

  char const* what() const throw() {
    return this->errorMsg.c_str();
  }
};

#endif
