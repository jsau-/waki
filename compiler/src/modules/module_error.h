#ifndef waki_modules_function_definition_error
#define waki_modules_function_definition_error

#include <exception>
#include <string>

struct ModuleError : public std::exception {
  ModuleError(std::string error) : error(error){};

  const char *what() const throw() { return this->error.c_str(); }

private:
  std::string error;
};

#endif
