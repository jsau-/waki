#include "function.h"

bool Function::operator==(const Function &rhs) const {
  return this->getName() == rhs.getName() && this->getArguments() == rhs.getArguments();
}
