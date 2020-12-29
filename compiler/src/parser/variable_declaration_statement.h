#ifndef waki_parser_variable_declaration_statement
#define waki_parser_variable_declaration_statement

#include <exception>
#include <string>
#include <sstream>
#include "statement_creation_error.h"
#include "../tokenizer/token_names.h"
#include "../tokenizer/token_type.h"

struct VariableDeclarationStatement
{
  TokenType type;
  bool isNullable;
  bool isMutable;

  int32_t signedInteger32Value;
  float floatValue;
  double doubleValue;
  bool boolValue;
  std::string stringValue;

  VariableDeclarationStatement(TokenType type, std::string initialValue = "", bool isNullable = false, bool isMutable = false) : type(type), isNullable(isNullable), isMutable(isMutable)
  {
    switch (type)
    {
    case TokenType::SIGNED_INTEGER_32:
      this->signedInteger32Value = std::stoi(initialValue);
      break;
    case TokenType::FLOAT:
      this->floatValue = std::stof(initialValue);
      break;
    case TokenType::DOUBLE:
      this->doubleValue = std::stod(initialValue);
      break;
    case TokenType::STRING:
      this->stringValue = initialValue;
      break;
    default:
      auto errorStream = std::ostringstream();

      errorStream
          << "Failed to instantiate VariableDeclarationStatement."
          << std::endl
          << "Received unexpected token type of "
          << TOKEN_NAMES.at(type)
          << "."
          << std::endl;

      throw StatementCreationError(errorStream.str());
    }
  };
};

#endif
