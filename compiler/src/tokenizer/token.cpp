#include "token.h"

bool Token::operator==(const Token &rhs) const {
  return this->type == rhs.type && this->value == rhs.value && this->lineNumber == rhs.lineNumber &&
         this->columnNumber == rhs.columnNumber;
}

bool Token::operator!=(const Token &rhs) const { return !(*this == rhs); }
