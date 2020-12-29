#include <sstream>
#include "parser.h"
#include "parser_error.h"
#include "statement_creation_error.h"
#include "variable_declaration_statement.h"

Parser::Parser(std::string sourceText, std::vector<Token> tokens) {
  this->sourceText = sourceText;
  this->tokens = tokens;
  this->index = 0;
}

int Parser::parse() {
  try {
    auto foo = VariableDeclarationStatement(TokenType::BITWISE_AND);
    return 10;
  } catch (StatementCreationError statementCreationError) {
    throw ParserError(statementCreationError.reason, tokens[0]);
  } catch (...) {
    throw ParserError("Unexpected failure parsing token", tokens[0]);
  }
}
