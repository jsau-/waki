#ifndef waki_typechecker_uninferrable_type_error
#define waki_typechecker_uninferrable_type_error

#include <string>

#include "../tokenizer/lexeme_type.h"
#include "../tokenizer/lexemes.h"
#include "typechecker_error.h"

struct UninferrableTypeError : public TypecheckerError {
  UninferrableTypeError(std::string identifier, uint64_t line, uint64_t column,
                        LexemeType expressionType)
    : TypecheckerError(identifier, line, column) {
    auto lexemeMetadata = Lexemes::getInstance().getMetadata();

    this->error =
      std::string("Unable to infer data type for identifier '") + this->identifier +
      std::string("' declared at line ") + std::to_string(this->line) + std::string(", column ") +
      std::to_string(this->column) + std::string(". Assigned type ") +
      lexemeMetadata.at(expressionType).displayName +
      std::string(
        " is assignable to multiple data types. You must provide an explicit type declaration.");
  }
};

#endif
