#include <sstream>
#include "parser.h"
#include "parser_error.h"
#include "expressions/bool_literal_expression.h"
#include "statements/variable_assignment_statement.h"

Parser::Parser(std::string sourceText, std::vector<Token> tokens) {
  this->sourceText = sourceText;
  this->tokens = tokens;
  this->index = 0;
}

std::shared_ptr<BlockStatement> Parser::parse() {
  auto rootBlock = std::make_shared<BlockStatement>(std::vector<std::shared_ptr<Statement>>());

  while (!this->isAtEnd()) {
    auto parseResult = this->parseStatement();
    rootBlock->statements.push_back(parseResult.statement);
    this->index += parseResult.consumedTokens;
  }

  return rootBlock;
}

ParseResult Parser::parseStatement() {
  std::shared_ptr<Statement> statement = std::make_shared<VariableAssignmentStatement>(
    "foo",
    AssignmentOperator::ASSIGN_EQUALS,
    std::make_shared<BoolLiteralExpression>(true)
  );

  return ParseResult(
    statement,
    10
  );
}

bool Parser::isAtEnd() {
  return this->index >= this->tokens.size();
}
