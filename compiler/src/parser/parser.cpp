#include "parser.h"

#include <algorithm>
#include <sstream>

#include "expressions/bool_literal_expression.h"
#include "expressions/double_literal_expression.h"
#include "expressions/float_literal_expression.h"
#include "expressions/null_literal_expression.h"
#include "expressions/signed_int_32_literal_expression.h"
#include "expressions/string_literal_expression.h"
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
    /*
     * parseStatement returns nullptr if there was nothing to do (eg. we
     * reached the end as part of the current parse iteration), hence the need
     * to explicitly check it's actually a valid ptr.
     */
    if (parseResult) {
      rootBlock->statements.push_back(parseResult);
    }
  }

  return rootBlock;
}

Token Parser::advance() {
  this->index++;
  return this->previousToken();
}

Token Parser::assertCurrentTokenType(TokenType type) {
  if (!this->checkCurrentTokenType(type)) {
    throw ParserError(this->currentToken(), {type});
  }

  return this->currentToken();
}

Token Parser::assertCurrentTokenType(std::vector<TokenType> types) {
  if (!this->checkCurrentTokenType(types)) {
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

bool Parser::checkCurrentTokenType(TokenType type) {
  return this->currentToken().type == type;
}

bool Parser::checkCurrentTokenType(std::vector<TokenType> types) {
  return std::find(std::begin(types), std::end(types),
                   this->currentToken().type) != std::end(types);
}

Token Parser::previousToken() {
  // TODO: This is gonna break when we're near SOF.
  return this->tokens[this->index - 1];
}

Token Parser::currentToken() {
  // TODO: Handle the case we don't _have_ a currentToken
  return this->tokens[this->index];
}

Token Parser::nextToken() {
  // TODO: This is gonna break when we're near EOF.
  return this->tokens[this->index + 1];
}

std::shared_ptr<Expression> Parser::parseExpression() {
  switch (this->currentToken().type) {
    case TokenType::BOOLEAN_LITERAL:
      return this->parseBoolLiteralExpression();
    case TokenType::DOUBLE_LITERAL:
      return this->parseDoubleLiteralExpression();
    case TokenType::FLOAT_LITERAL:
      return this->parseFloatLiteralExpression();
    case TokenType::NULL_LITERAL:
      return this->parseNullLiteralExpression();
    case TokenType::SIGNED_INTEGER_32_LITERAL:
      return this->parseSignedInt32LiteralExpression();
    case TokenType::STRING_LITERAL:
      return this->parseStringLiteralExpression();
    default:
      throw ParserError(this->currentToken(),
                        {
                            TokenType::BOOLEAN_LITERAL,
                            TokenType::DOUBLE_LITERAL,
                            TokenType::FLOAT_LITERAL,
                            TokenType::NULL_LITERAL,
                            TokenType::SIGNED_INTEGER_32_LITERAL,
                            TokenType::STRING_LITERAL,
                        });
  }
}

std::shared_ptr<BoolLiteralExpression> Parser::parseBoolLiteralExpression() {
  auto boolLiteral =
      this->assertCurrentTokenTypeAndAdvance(TokenType::BOOLEAN_LITERAL);
  return std::make_shared<BoolLiteralExpression>(boolLiteral.value == "true");
}

std::shared_ptr<DoubleLiteralExpression>
Parser::parseDoubleLiteralExpression() {
  auto doubleLiteral =
      this->assertCurrentTokenTypeAndAdvance(TokenType::DOUBLE_LITERAL);
  return std::make_shared<DoubleLiteralExpression>(
      // TODO: stod probably isn't something we want to _keep_
      std::stod(doubleLiteral.value));
}

std::shared_ptr<FloatLiteralExpression> Parser::parseFloatLiteralExpression() {
  auto floatLiteral =
      this->assertCurrentTokenTypeAndAdvance(TokenType::FLOAT_LITERAL);
  return std::make_shared<FloatLiteralExpression>(
      // TODO: stof probably isn't something we want to _keep_
      std::stof(floatLiteral.value));
}

std::shared_ptr<NullLiteralExpression> Parser::parseNullLiteralExpression() {
  this->assertCurrentTokenTypeAndAdvance(TokenType::NULL_LITERAL);
  return std::make_shared<NullLiteralExpression>();
}

std::shared_ptr<SignedInt32LiteralExpression>
Parser::parseSignedInt32LiteralExpression() {
  auto signedInt32Literal = this->assertCurrentTokenTypeAndAdvance(
      TokenType::SIGNED_INTEGER_32_LITERAL);
  return std::make_shared<SignedInt32LiteralExpression>(
      // TODO: stoi probably isn't something we want to _keep_
      std::stoi(signedInt32Literal.value));
}

std::shared_ptr<StringLiteralExpression>
Parser::parseStringLiteralExpression() {
  auto stringLiteral =
      this->assertCurrentTokenTypeAndAdvance(TokenType::STRING_LITERAL);
  return std::make_shared<StringLiteralExpression>(stringLiteral.value);
}

std::shared_ptr<Statement> Parser::parseStatement() {
  if (this->isAtEnd()) {
    // TODO: Should I be using `make_shared<SomeDerviedStatement>(nullptr)`?
    return nullptr;
  }

  /*
   * Empty statements aren't "wrong" enough to warrant a parse error.
   * TODO: Warnings
   */
  if (this->checkCurrentTokenType(TokenType::END_OF_STATEMENT)) {
    this->advance();
    return this->parseStatement();
  }

  return this->parseVariableAssignmentStatement();
}

std::shared_ptr<Statement> Parser::parseVariableAssignmentStatement() {
  auto dataType = DataType::UNKNOWN;

  if (this->checkCurrentTokenType(
          {{TokenType::SIGNED_INTEGER_32, TokenType::FLOAT, TokenType::DOUBLE,
            TokenType::BOOLEAN, TokenType::STRING}})) {
    dataType = (DataType)this->advance().type;
  }

  auto identifier =
      this->assertCurrentTokenTypeAndAdvance(TokenType::IDENTIFIER);

  // TODO: Tokens holding metadata about their type?
  auto operatorToken = this->assertCurrentTokenTypeAndAdvance(
      {TokenType::MULTIPLY_ASSIGN, TokenType::DIVIDE_ASSIGN,
       TokenType::ADD_ASSIGN, TokenType::SUBTRACT_ASSIGN,
       TokenType::ASSIGN_EQUALS});

  // TODO: This is probably just mega unsafe.
  AssignmentOperator assignmentOperator =
      (AssignmentOperator)operatorToken.type;

  /*
   * TODO: Make sure typechecker actually checks this stuff is sensible.
   * eg. it doesn't make sense to do `bool += true`. That way madness lies.
   */
  auto expression = this->parseExpression();

  this->assertCurrentTokenTypeAndAdvance(TokenType::END_OF_STATEMENT);

  return std::make_shared<VariableAssignmentStatement>(
      dataType, identifier.value, assignmentOperator, expression);
}

bool Parser::isAtEnd() { return this->index >= this->tokens.size(); }
