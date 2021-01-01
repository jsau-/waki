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
  TypecheckerError(std::string identifier, uint64_t line, uint64_t column, std::string error = "")
    : identifier(identifier), line(line), column(column), error(error) {}

  TypecheckerError(const TypecheckerError &other)
    : identifier(other.identifier), line(other.line), column(other.column), error(other.error) {}

  TypecheckerError() = delete;

  virtual ~TypecheckerError(){};

  std::string getIdentifier() const { return this->identifier; }
  std::string getError() const { return this->error; }
  uint64_t getLine() const { return this->line; }
  uint64_t getColumn() const { return this->column; }

protected:
  // The identifier name the typechecker error occurred for.
  std::string identifier;

  // The line the typechecker error occured at
  uint64_t line;

  // The column the typechecker error occured at
  uint64_t column;

  // The reason for the error
  std::string error;
};

#endif
