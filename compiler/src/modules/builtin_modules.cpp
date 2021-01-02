#include <algorithm>
#include <sstream>

#include "../tokenizer/lexemes.h"
#include "builtin_modules.h"
#include "epoch.h"
#include "module_error.h"

BuiltinModules::BuiltinModules() { this->registerFunction(std::make_shared<Epoch>()); }

void BuiltinModules::registerFunction(const std::shared_ptr<Function> function) {
  // Has an equivalent function already been defined?
  if (std::find_if(this->functions.begin(), this->functions.end(),
                   [&function](const std::shared_ptr<Function> existingFunction) {
                     return *function == *existingFunction;
                   }) != this->functions.end()) {
    auto sstream = std::stringstream();

    auto lexemeMetadata = Lexemes::getInstance().getMetadata();

    sstream << "Attempting to redefine function '" << function->getName() << "' with return type "
            << lexemeMetadata.at(function->getReturnType()).displayName;

    if (function->getArguments().size()) {
      sstream << " and arguments";

      for (const auto &identifier : function->getArguments()) {
        sstream << " (" << lexemeMetadata.at(identifier.type).displayName << ")";
      }
    }

    sstream << ".";

    throw ModuleError(sstream.str());
  }

  this->functions.push_back(function);
}

const std::vector<std::shared_ptr<Function>> BuiltinModules::getFunctions() const {
  return this->functions;
}
