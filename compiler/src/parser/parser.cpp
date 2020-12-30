#include "parser.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "expressions/binary_operator_expression.h"
#include "expressions/bool_literal_expression.h"
#include "expressions/double_literal_expression.h"
#include "expressions/float_literal_expression.h"
#include "expressions/identifier_expression.h"
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

bool Parser::hasPreviousToken() {
  return this->index > this->tokens.size() && !this->isAtEnd();
}

bool Parser::hasNextToken() {
  return this->tokens.size() > 0 && this->index < this->tokens.size();
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

bool Parser::checkNextTokenType(TokenType type) {
  if (!this->hasNextToken()) {
    return false;
  }

  return this->nextToken().type == type;
}

bool Parser::checkNextTokenType(std::vector<TokenType> types) {
  if (!this->hasNextToken()) {
    return false;
  }

  return std::find(std::begin(types), std::end(types),
                   this->nextToken().type) != std::end(types);
}

Token Parser::previousToken() { return this->tokens[this->index - 1]; }

Token Parser::currentToken() { return this->tokens[this->index]; }

Token Parser::nextToken() { return this->tokens[this->index + 1]; }

std::shared_ptr<Expression> Parser::parseExpression() {
  return this->parseCompoundAssignmentExpression();
}

std::shared_ptr<Expression> Parser::parseCompoundAssignmentExpression() {
  auto expression = this->parseLogicalOrExpression();

  auto validTokens = {
      TokenType::MULTIPLY_ASSIGN,
      TokenType::DIVIDE_ASSIGN,
      TokenType::ADD_ASSIGN,
      TokenType::SUBTRACT_ASSIGN,
      TokenType::NOT,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseLogicalOrExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseLogicalOrExpression() {
  auto expression = this->parseLogicalAndExpression();

  auto validTokens = {
      TokenType::LOGICAL_OR,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseLogicalAndExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseLogicalAndExpression() {
  auto expression = this->parseBitwiseOrExpression();

  auto validTokens = {TokenType::LOGICAL_AND};

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseBitwiseOrExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseBitwiseOrExpression() {
  auto expression = this->parseBitwiseXorExpression();

  auto validTokens = {TokenType::BITWISE_OR};

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseBitwiseXorExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseBitwiseXorExpression() {
  auto expression = this->parseBitwiseAndExpression();

  auto validTokens = {TokenType::BITWISE_XOR};

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseBitwiseAndExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseBitwiseAndExpression() {
  auto expression = this->parseEqualityExpression();

  auto validTokens = {TokenType::BITWISE_AND};

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseEqualityExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseEqualityExpression() {
  auto expression = this->parseRelationalExpression();

  auto validTokens = {
      TokenType::EQUALS,
      TokenType::NOT_EQUALS,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseRelationalExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseRelationalExpression() {
  auto expression = this->parseBitwiseShiftExpression();

  auto validTokens = {
      TokenType::GREATER_THAN,
      TokenType::GREATER_THAN_OR_EQUAL,
      TokenType::LESS_THAN,
      TokenType::LESS_THAN_OR_EQUAL,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseBitwiseShiftExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseBitwiseShiftExpression() {
  auto expression = this->parseAdditiveExpression();

  auto validTokens = {
      TokenType::BITWISE_SHIFT_LEFT,
      TokenType::BITWISE_SHIFT_RIGHT,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseAdditiveExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseAdditiveExpression() {
  auto expression = this->parseMultiplicativeExpression();

  auto validTokens = {
      TokenType::ADD,
      TokenType::SUBTRACT,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parseMultiplicativeExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseMultiplicativeExpression() {
  auto expression = this->parsePrimaryExpression();

  auto validTokens = {
      TokenType::MULTIPLY,
      TokenType::DIVIDE,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto binaryOperator = (BinaryOperator)this->advance().type;
    auto rhs = this->parsePrimaryExpression();
    expression = std::make_shared<BinaryOperatorExpression>(binaryOperator,
                                                            expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parsePrimaryExpression() {
  if (this->checkCurrentTokenType(TokenType::OPEN_PARENTHESIS)) {
    this->advance();
    auto expressionBody = this->parseExpression();
    this->assertCurrentTokenTypeAndAdvance(TokenType::CLOSE_PARENTHESIS);
    return expressionBody;
  }

  if (this->checkCurrentTokenType(TokenType::IDENTIFIER)) {
    auto identifierExpression = std::make_shared<IdentifierExpression>(this->currentToken().value);
    this->advance();
    return identifierExpression;
  }

  auto validLiteralTokens = {
      TokenType::BOOLEAN_LITERAL,
      TokenType::DOUBLE_LITERAL,
      TokenType::FLOAT_LITERAL,
      TokenType::NULL_LITERAL,
      TokenType::SIGNED_INTEGER_32_LITERAL,
      TokenType::STRING_LITERAL,
  };

  Token curToken = this->assertCurrentTokenType(validLiteralTokens);

  std::shared_ptr<Expression> literalExpression;

  switch (curToken.type) {
    case TokenType::BOOLEAN_LITERAL:
      literalExpression =
          std::make_shared<BoolLiteralExpression>(curToken.value == "true");
      break;
    case TokenType::DOUBLE_LITERAL:
      literalExpression =
          std::make_shared<DoubleLiteralExpression>(std::stod(curToken.value));
      break;
    case TokenType::FLOAT_LITERAL:
      literalExpression =
          std::make_shared<FloatLiteralExpression>(std::stof(curToken.value));
      break;
    case TokenType::NULL_LITERAL:
      literalExpression = std::make_shared<NullLiteralExpression>();
      break;
    case TokenType::SIGNED_INTEGER_32_LITERAL:
      literalExpression = std::make_shared<SignedInt32LiteralExpression>(
          std::stoi(curToken.value));
      break;
    case TokenType::STRING_LITERAL:
      literalExpression =
          std::make_shared<StringLiteralExpression>(curToken.value);
      break;
    // Should only be hit in the case we've not implemented a literal
    default:
      throw ParserError(curToken, validLiteralTokens);
  }

  this->advance();

  return literalExpression;
}

std::shared_ptr<Statement> Parser::parseStatement() {
  if (this->isAtEnd()) {
    // TODO: Should we be using `make_shared<SomeDerviedStatement>(nullptr)`?
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
  auto isMutable = false;
  auto isNullable = false;

  /*
   * TODO: This technically will allow nonsense like
   * `nullable nullable mutable mutable nullable int foo`, but I don't
   * particularly see any value in throwing a compiler error if people decide
   * to be excessive.
   *
   * Probably a sensible place to emit a warning though, eg. count mutables and
   * nullables, if either >= 1 emit a warning.
   */
  while (
      this->checkCurrentTokenType({TokenType::MUTABLE, TokenType::NULLABLE})) {
    auto variableModifier = this->advance();

    if (variableModifier.type == TokenType::MUTABLE) {
      isMutable = true;
    }

    if (variableModifier.type == TokenType::NULLABLE) {
      isNullable = true;
    }
  }

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
      dataType, identifier.value, assignmentOperator, expression, isMutable,
      isNullable);
}

bool Parser::isAtEnd() { return this->index >= this->tokens.size(); }
