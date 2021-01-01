#include "identifier.h"

bool Identifier::operator==(const Identifier &rhs) const {
  return this->name == rhs.name && this->type == rhs.type && this->isMutable == rhs.isMutable &&
         this->isNullable == rhs.isNullable && this->lineDeclared == rhs.lineDeclared &&
         this->columnDeclared == rhs.columnDeclared;
}
