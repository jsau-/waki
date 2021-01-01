#ifndef waki_modules_function
#define waki_modules_function

#include <vector>

#include "../tokenizer/lexeme_type.h"
#include "../typechecker/identifier.h"
#include "module.h"

/**
 * Datastructure representing an instance of a defined function in the lanuage.
 *
 * Functions should be unique across their names and argument sets (i.e. it's
 * valid to define the same function name multiple times, provided it has a
 * different set of arguments.)
 */
struct Function : public Module {
  Function(const std::string name) : Module(name){};

  // TODO: Tests!
  bool operator==(const Function &rhs) const;

  virtual std::string getDescription() const = 0;
  virtual LexemeType getReturnType() const = 0;
  virtual std::vector<Identifier> getArguments() const = 0;
};

#endif
