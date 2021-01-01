#include <algorithm>

#include "builtin_modules.h"
#include "epoch.h"
#include "module_error.h"

BuiltinModules::BuiltinModules() {
  this->registerFunction(std::make_shared<Epoch>());
}

void BuiltinModules::registerFunction(const std::shared_ptr<Function> function) {
  // Has an equivalent function already been defined?
  if (std::find_if(this->functions.begin(), this->functions.end(),
                   [&function](const std::shared_ptr<Function> existingFunction) {
                     return *function == *existingFunction;
                   }) != this->functions.end()) {
    // TODO: More detailed error msg
    throw ModuleError("Attempting to redefine function.");
  }

  this->functions.push_back(function);
}

const std::vector<std::shared_ptr<Function>> BuiltinModules::getFunctions() const {
  return this->functions;
}
