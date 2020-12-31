#ifndef waki_typechecker_identifier_undefined_error
#define waki_typechecker_identifier_undefined_error

#include <string>

#include "typechecker_error.h"

struct IdentifierUndefinedError : public TypecheckerError {
  IdentifierUndefinedError(std::string identifier, uint64_t line, uint64_t column)
    : TypecheckerError(identifier, line, column) {
    this->errorMsg = std::string("Identifier '") + this->identifier +
                     std::string("' referenced at line ") + std::to_string(this->line) +
                     std::string(", column ") + std::to_string(this->column) +
                     std::string(" has not been defined");
  }

  const char *what() const throw() { return this->errorMsg.c_str(); };

private:
  std::string errorMsg;
};

#endif
