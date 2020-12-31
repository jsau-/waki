#ifndef waki_typechecker_identifier_already_defined_error
#define waki_typechecker_identifier_already_defined_error

#include <string>

#include "typechecker_error.h"

struct IdentifierAlreadyDefinedError : public TypecheckerError {
  IdentifierAlreadyDefinedError(std::string identifier, uint64_t line, uint64_t column,
                                uint64_t lineOriginallyDeclaredAt,
                                uint64_t columnOriginallyDeclaredAt)
    : TypecheckerError(identifier, line, column),
      lineOriginallyDeclaredAt(lineOriginallyDeclaredAt),
      columnOriginallyDeclaredAt(columnOriginallyDeclaredAt) {
    this->errorMsg = std::string("Identifier '") + this->identifier +
                     std::string("' declared at line ") + std::to_string(this->line) +
                     std::string(", column ") + std::to_string(this->column) +
                     std::string(" has already been declared on line ") +
                     std::to_string(this->lineOriginallyDeclaredAt) + std::string(", column ") +
                     std::to_string(this->columnOriginallyDeclaredAt);
  }

  const char *what() const throw() { return this->errorMsg.c_str(); }

private:
  std::string errorMsg;

  // The line the identifier was originally declared at
  uint64_t lineOriginallyDeclaredAt;

  // The column the identifier was originally declared at
  uint64_t columnOriginallyDeclaredAt;
};

#endif
