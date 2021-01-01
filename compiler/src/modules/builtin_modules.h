#ifndef waki_modules_builtin_modules
#define waki_modules_builtin_modules

#include <memory>
#include <vector>

#include "function.h"

/**
 * A collection of built-in libary modules.
 */
struct BuiltinModules {
  BuiltinModules();

  const std::vector<std::shared_ptr<Function>> getFunctions() const;

private:
  void registerFunction(const std::shared_ptr<Function> function);
  std::vector<std::shared_ptr<Function>> functions;
};

#endif
