#include "parser.h"

#include <algorithm>
#include <sstream>

#include "expressions/float_literal_expression.h"
#include "parser_error.h"
#include "statements/variable_assignment_statement.h"

Parser::Parser(std::string sourceText, std::vector<Token> tokens) {
  this->sourceText = sourceText;
  this->tokens = tokens;
  this->index = 0;
}

std::shared_ptr<BlockStatement> Parser::parse() {
  auto rootBlock = std::make_shared<BlockStatement>(
      std::vector<std::shared_ptr<Statement>>());

  while (!this->isAtEnd()) {
    auto parseResult = this->parseStatement();
    rootBlock->statements.push_back(parseResult);
  }

  return rootBlock;
}

Token Parser::advance() {
  this->index++;
  return this->previousToken();
}

Token Parser::assertCurrentTokenType(TokenType type) {
  if (this->currentToken().type != type) {
    throw ParserError(this->currentToken(), {type});
  }

  return this->currentToken();
}

Token Parser::assertCurrentTokenType(std::vector<TokenType> types) {
  if (std::find(std::begin(types), std::end(types),
                this->currentToken().type) == std::end(types)) {
    throw ParserError(this->currentToken(), types);
  }

  return this->currentToken();
}

Token Parser::assertCurrentTokenTypeAndAdvance(TokenType type) {
  this->assertCurrentTokenType(type);
  return this->advance();
}

Token Parser::assertCurrentTokenTypeAndAdvance(std::vector<TokenType> types) {
  this->assertCurrentTokenType(types);
  return this->advance();
}

Token Parser::previousToken() {
  // TODO: This is gonna break when we're near SOF.
  return this->tokens[this->index - 1];
}

Token Parser::currentToken() { return this->tokens[this->index]; }

Token Parser::nextToken() {
  // TODO: This is gonna break when we're near EOF.
  return this->tokens[this->index + 1];
}

std::shared_ptr<Expression> Parser::parseExpression() {
  return this->parseFloatLiteralExpression();
}

std::shared_ptr<FloatLiteralExpression> Parser::parseFloatLiteralExpression() {
  auto floatLiteral =
      this->assertCurrentTokenTypeAndAdvance(TokenType::FLOAT_LITERAL);
  return std::make_shared<FloatLiteralExpression>(
      std::stof(floatLiteral.value));
}

std::shared_ptr<Statement> Parser::parseStatement() {
  return this->parseVariableAssignmentStatement();
}

std::shared_ptr<Statement> Parser::parseVariableAssignmentStatement() {
  auto identifier =
      this->assertCurrentTokenTypeAndAdvance(TokenType::IDENTIFIER);

  // TODO: Tokens holding metadata about their type?
  auto assignmentOperator = this->assertCurrentTokenTypeAndAdvance(
      {TokenType::MULTIPLY_ASSIGN, TokenType::DIVIDE_ASSIGN,
       TokenType::ADD_ASSIGN, TokenType::SUBTRACT_ASSIGN,
       TokenType::ASSIGN_EQUALS});

  auto expression = this->parseExpression();

  this->assertCurrentTokenTypeAndAdvance(TokenType::END_OF_STATEMENT);

  return std::make_shared<VariableAssignmentStatement>(
      identifier.value, AssignmentOperator::ASSIGN_EQUALS, expression);
}

bool Parser::isAtEnd() { return this->index >= this->tokens.size(); }
