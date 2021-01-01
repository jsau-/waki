#ifndef waki_typechecker_mutability_violation_error
#define waki_typechecker_mutability_violation_error

#include <string>

#include "typechecker_error.h"

struct MutabilityViolationError : public TypecheckerError {
  MutabilityViolationError(std::string identifier, uint64_t line, uint64_t column)
    : TypecheckerError(identifier, line, column) {
    this->error = std::string("Attempting to mutate identifier '") + this->identifier +
                  std::string("' declared at line ") + std::to_string(this->line) +
                  std::string(", column ") + std::to_string(this->column) +
                  std::string(". This variable is not mutable and hence cannot be changed.");
  }
};

#endif
