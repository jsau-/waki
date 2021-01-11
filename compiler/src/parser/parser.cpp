#include "parser.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <tuple>

#include "../tokenizer/lexemes.h"
#include "expressions/binary_operator_expression.h"
#include "expressions/bool_literal_expression.h"
#include "expressions/double_literal_expression.h"
#include "expressions/float_literal_expression.h"
#include "expressions/identifier_expression.h"
#include "expressions/signed_int_32_literal_expression.h"
#include "expressions/string_literal_expression.h"
#include "parser_error.h"
#include "statements/conditional_statement.h"
#include "statements/variable_assignment_statement.h"

Parser::Parser(std::vector<Token> tokens) {
  this->tokens = tokens;
  this->index = 0;
}

std::shared_ptr<BlockStatement> Parser::parse() {
  auto rootBlock =
    std::make_shared<BlockStatement>(0, 0, std::vector<std::shared_ptr<Statement>>());

  while (!this->isAtEnd()) {
    /*
     * TODO: Some form of recoverability. Only being told about the _first_
     * parse error in a file might not be the best development experience -
     * eg. if you've missed semicolons on 20 different lines, you want to be
     * told about all of them.
     *
     * In the case a statement can't be parsed, catch the parse error,
     * swallow it (likely some kind of errors array), swallow tokens until we
     * reach something that looks like a sensible starting point.
     *
     * eg. Swallow all parse errors until we reach some terminal block of scope,
     * like a function end, or a semicolon. It won't be perfect, but it'll
     * definitely be better than an immediate exit.
     */
    auto parseResult = this->parseStatement();

    if (parseResult.has_value()) {
      rootBlock->statements.push_back(*parseResult);
    }
  }

  return rootBlock;
}

Token Parser::advance() {
  this->index++;
  return this->previousToken();
}

bool Parser::hasPreviousToken() const {
  return this->index > this->tokens.size() && !this->isAtEnd();
}

bool Parser::hasNextToken() const {
  return this->tokens.size() > 0 && this->index < this->tokens.size();
}

Token Parser::assertCurrentTokenType(LexemeType type) const {
  if (!this->checkCurrentTokenType(type)) {
    throw ParserError(this->currentToken(), {type});
  }

  return this->currentToken();
}

Token Parser::assertCurrentTokenType(std::set<LexemeType> types) const {
  if (!this->checkCurrentTokenType(types)) {
    throw ParserError(this->currentToken(), types);
  }

  return this->currentToken();
}

Token Parser::assertCurrentTokenTypeAndAdvance(LexemeType type) {
  this->assertCurrentTokenType(type);
  return this->advance();
}

Token Parser::assertCurrentTokenTypeAndAdvance(std::set<LexemeType> types) {
  this->assertCurrentTokenType(types);
  return this->advance();
}

bool Parser::checkCurrentTokenType(LexemeType type) const {
  return this->currentToken().type == type;
}

bool Parser::checkCurrentTokenType(std::set<LexemeType> types) const {
  return std::find(std::begin(types), std::end(types), this->currentToken().type) !=
         std::end(types);
}

bool Parser::checkNextTokenType(LexemeType type) const {
  if (!this->hasNextToken()) {
    return false;
  }

  return this->nextToken().type == type;
}

bool Parser::checkNextTokenType(std::set<LexemeType> types) const {
  if (!this->hasNextToken()) {
    return false;
  }

  return std::find(std::begin(types), std::end(types), this->nextToken().type) != std::end(types);
}

Token Parser::previousToken() const { return this->tokens[this->index - 1]; }

Token Parser::currentToken() const { return this->tokens[this->index]; }

Token Parser::nextToken() const { return this->tokens[this->index + 1]; }

std::shared_ptr<Expression> Parser::parseExpression() {
  return this->parseCompoundAssignmentExpression();
}

std::shared_ptr<Expression> Parser::parseCompoundAssignmentExpression() {
  auto expression = this->parseLogicalOrExpression();

  auto validTokens = {
    LexemeType::MULTIPLY_ASSIGN,
    LexemeType::DIVIDE_ASSIGN,
    LexemeType::ADD_ASSIGN,
    LexemeType::SUBTRACT_ASSIGN,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseLogicalOrExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseLogicalOrExpression() {
  auto expression = this->parseLogicalAndExpression();

  auto validTokens = {
    LexemeType::LOGICAL_OR,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseLogicalAndExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseLogicalAndExpression() {
  auto expression = this->parseBitwiseOrExpression();

  auto validTokens = {LexemeType::LOGICAL_AND};

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseBitwiseOrExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseBitwiseOrExpression() {
  auto expression = this->parseBitwiseXorExpression();

  auto validTokens = {LexemeType::BITWISE_OR};

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseBitwiseXorExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseBitwiseXorExpression() {
  auto expression = this->parseBitwiseAndExpression();

  auto validTokens = {LexemeType::BITWISE_XOR};

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseBitwiseAndExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseBitwiseAndExpression() {
  auto expression = this->parseEqualityExpression();

  auto validTokens = {LexemeType::BITWISE_AND};

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseEqualityExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseEqualityExpression() {
  auto expression = this->parseRelationalExpression();

  auto validTokens = {
    LexemeType::EQUALS,
    LexemeType::NOT_EQUALS,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseRelationalExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseRelationalExpression() {
  auto expression = this->parseBitwiseShiftExpression();

  auto validTokens = {
    LexemeType::GREATER_THAN,
    LexemeType::GREATER_THAN_OR_EQUAL,
    LexemeType::LESS_THAN,
    LexemeType::LESS_THAN_OR_EQUAL,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseBitwiseShiftExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseBitwiseShiftExpression() {
  auto expression = this->parseAdditiveExpression();

  auto validTokens = {
    LexemeType::BITWISE_SHIFT_LEFT,
    LexemeType::BITWISE_SHIFT_RIGHT,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseAdditiveExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseAdditiveExpression() {
  auto expression = this->parseMultiplicativeExpression();

  auto validTokens = {
    LexemeType::ADD,
    LexemeType::SUBTRACT,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parseMultiplicativeExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parseMultiplicativeExpression() {
  auto expression = this->parsePrimaryExpression();

  auto validTokens = {
    LexemeType::MULTIPLY,
    LexemeType::DIVIDE,
  };

  if (this->checkCurrentTokenType(validTokens)) {
    auto token = this->advance();
    auto rhs = this->parsePrimaryExpression();
    expression = std::make_shared<BinaryOperatorExpression>(token.lineNumber, token.columnNumber,
                                                            token.type, expression, rhs);
  }

  return expression;
}

std::shared_ptr<Expression> Parser::parsePrimaryExpression() {
  auto literals = Lexemes::getInstance().getLiterals();

  if (this->checkCurrentTokenType(LexemeType::OPEN_PARENTHESIS)) {
    this->advance();
    auto expressionBody = this->parseExpression();
    this->assertCurrentTokenTypeAndAdvance(LexemeType::CLOSE_PARENTHESIS);
    return expressionBody;
  }

  if (this->checkCurrentTokenType(LexemeType::IDENTIFIER)) {
    auto identifierExpression = std::make_shared<IdentifierExpression>(
      this->currentToken().lineNumber, this->currentToken().columnNumber,
      this->currentToken().value);
    this->advance();
    return identifierExpression;
  }

  Token curToken = this->assertCurrentTokenType(literals);

  std::shared_ptr<Expression> literalExpression;

  // TODO: We'll probably want to rethink the parsing here using `stox`
  switch (curToken.type) {
  case LexemeType::BOOLEAN_LITERAL:
    literalExpression = std::make_shared<BoolLiteralExpression>(
      curToken.lineNumber, curToken.columnNumber, curToken.value == "true");
    break;
  case LexemeType::DOUBLE_LITERAL:
    literalExpression = std::make_shared<DoubleLiteralExpression>(
      curToken.lineNumber, curToken.columnNumber, std::stod(curToken.value));
    break;
  case LexemeType::FLOAT_LITERAL:
    literalExpression = std::make_shared<FloatLiteralExpression>(
      curToken.lineNumber, curToken.columnNumber, std::stof(curToken.value));
    break;
  case LexemeType::SIGNED_INTEGER_32_LITERAL:
    literalExpression = std::make_shared<SignedInt32LiteralExpression>(
      curToken.lineNumber, curToken.columnNumber, std::stoi(curToken.value));
    break;
  case LexemeType::STRING_LITERAL:
    literalExpression = std::make_shared<StringLiteralExpression>(
      curToken.lineNumber, curToken.columnNumber, curToken.value);
    break;
  // Should only be hit in the case we've not implemented a literal
  default:
    throw ParserError(curToken, literals);
  }

  this->advance();

  return literalExpression;
}

tl::optional<std::shared_ptr<Statement>> Parser::parseStatement() {
  if (this->isAtEnd()) {
    return tl::nullopt;
  }

  /*
   * Empty statements aren't "wrong" enough to warrant a parse error.
   * TODO: Warnings
   */
  if (this->checkCurrentTokenType(LexemeType::END_OF_STATEMENT)) {
    this->advance();
    return tl::nullopt;
  }

  auto statement = tl::optional<std::shared_ptr<Statement>>();

  if (this->currentToken().type == LexemeType::IF) {
    statement = this->parseConditionalStatement();
  } else {
    statement = this->parseVariableAssignmentStatement();
  }

  return statement;
}

std::shared_ptr<Statement> Parser::parseVariableAssignmentStatement() {
  auto dataTypes = Lexemes::getInstance().getDataTypes();
  auto variableModifiers = Lexemes::getInstance().getVariableModifiers();
  auto dataType = LexemeType::UNKNOWN;
  auto isMutable = false;

  Token firstToken = this->currentToken();

  /*
   * TODO: This technically will allow nonsense like
   * `mutable mutable int foo`, but I don't
   * particularly see any value in throwing a compiler error if people decide
   * to be excessive.
   *
   * Probably a sensible place to emit a warning though, eg. count mutables and
   * if >= 1 emit a warning.
   */
  while (this->checkCurrentTokenType(variableModifiers)) {
    auto variableModifier = this->advance();

    if (variableModifier.type == LexemeType::MUTABLE) {
      isMutable = true;
    }
  }

  if (this->checkCurrentTokenType(dataTypes)) {
    dataType = this->advance().type;
  }

  auto identifier = this->assertCurrentTokenTypeAndAdvance(LexemeType::IDENTIFIER);

  auto assignOperators = Lexemes::getInstance().getAssignmentOperators();

  auto operatorToken = this->assertCurrentTokenTypeAndAdvance(assignOperators);

  auto expression = this->parseExpression();

  this->assertCurrentTokenTypeAndAdvance(LexemeType::END_OF_STATEMENT);

  return std::make_shared<VariableAssignmentStatement>(
    firstToken.lineNumber, firstToken.columnNumber, dataType, identifier.value, operatorToken.type,
    expression, isMutable);
}

std::shared_ptr<Statement> Parser::parseConditionalStatement() {
  auto ifToken = this->assertCurrentTokenTypeAndAdvance(LexemeType::IF);
  this->assertCurrentTokenTypeAndAdvance(LexemeType::OPEN_PARENTHESIS);
  auto ifExpression = this->parseExpression();
  this->assertCurrentTokenTypeAndAdvance(LexemeType::CLOSE_PARENTHESIS);
  this->assertCurrentTokenTypeAndAdvance(LexemeType::OPEN_BRACE);

  auto currentToken = this->currentToken();

  auto ifBlock =
    std::make_shared<BlockStatement>(currentToken.lineNumber, currentToken.columnNumber);

  while (!this->checkCurrentTokenType(LexemeType::CLOSE_BRACE)) {
    auto nextStatement = this->parseStatement();

    // TODO: Warning if no value?
    if (nextStatement.has_value()) {
      ifBlock->statements.push_back(*nextStatement);
    }
  }

  this->assertCurrentTokenTypeAndAdvance(LexemeType::CLOSE_BRACE);

  this->assertCurrentTokenTypeAndAdvance(LexemeType::END_OF_STATEMENT);

  return std::make_shared<ConditionalStatement>(
    ifToken.lineNumber, ifToken.columnNumber,
    std::tuple<std::shared_ptr<Expression>, std::shared_ptr<BlockStatement>>(ifExpression,
                                                                             ifBlock));
}

bool Parser::isAtEnd() const { return this->index >= this->tokens.size(); }
