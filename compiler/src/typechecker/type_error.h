#ifndef waki_typechecker_type_error
#define waki_typechecker_type_error

#include <string>

#include "../tokenizer/lexeme_type.h"
#include "../tokenizer/lexemes.h"
#include "typechecker_error.h"

struct TypeError : public TypecheckerError {
  TypeError(uint64_t line, uint64_t column, LexemeType expectedType, LexemeType receivedType)
    // TODO: Suggests identifier shouldn't be member of TypecheckerError
    : TypecheckerError("", line, column), expectedType(expectedType), receivedType(receivedType) {
    auto lexemeMetadata = Lexemes::getInstance().getMetadata();
    auto metadataForExpected = lexemeMetadata.at(expectedType);
    auto metadataForReceived = lexemeMetadata.at(receivedType);

    this->errorMsg = std::string("Received unexpected type on line ") + std::to_string(this->line) +
                     std::string(", column ") + std::to_string(this->column) +
                     std::string(". Expected ") + metadataForExpected.displayName +
                     " but received " + metadataForReceived.displayName;
  }

  const char *what() const throw() { return this->errorMsg.c_str(); }

private:
  std::string errorMsg;

  LexemeType expectedType;
  LexemeType receivedType;
};

#endif
