#ifndef waki_typechecker_typechecker_error
#define waki_typechecker_typechecker_error

#include <cstdint>
#include <exception>
#include <string>

/**
 * Virtual struct for all typechecker errors, defining any shared fields common
 * across all typechecker errors.
 */
struct TypecheckerError : public std::exception {
  TypecheckerError(std::string identifier, uint64_t line, uint64_t column)
    : identifier(identifier), line(line), column(column) {}

  virtual ~TypecheckerError(){};

  uint64_t getLine() { return this->line; }
  uint64_t getColumn() { return this->column; }

protected:
  // The identifier name the typechecker error occurred for.
  std::string identifier;

  // The line the typechecker error occured at
  uint64_t line;

  // The column the typechecker error occured at
  uint64_t column;
};

#endif
