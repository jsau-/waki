#ifndef waki_parser_parser
#define waki_parser_parser

#include <memory>
#include <vector>

#include "../tokenizer/token.h"
#include "expressions/expression.h"
#include "statements/block_statement.h"
#include "statements/statement.h"

struct Parser {
  Parser(std::string sourceText, std::vector<Token> tokens);

  std::shared_ptr<BlockStatement> parse();

 private:
  std::string sourceText;
  std::vector<Token> tokens;
  size_t index;

  Token advance();
  Token assertCurrentTokenType(TokenType type);
  Token assertCurrentTokenType(std::vector<TokenType> types);
  Token assertCurrentTokenTypeAndAdvance(TokenType type);
  Token assertCurrentTokenTypeAndAdvance(std::vector<TokenType> types);
  bool checkCurrentTokenType(TokenType type);
  bool checkCurrentTokenType(std::vector<TokenType> types);

  Token previousToken();
  Token currentToken();
  Token nextToken();

  std::shared_ptr<Expression> parseExpression();
  std::shared_ptr<BoolLiteralExpression> parseBoolLiteralExpression();
  std::shared_ptr<DoubleLiteralExpression> parseDoubleLiteralExpression();
  std::shared_ptr<FloatLiteralExpression> parseFloatLiteralExpression();
  std::shared_ptr<NullLiteralExpression> parseNullLiteralExpression();
  std::shared_ptr<SignedInt32LiteralExpression> parseSignedInt32LiteralExpression();
  std::shared_ptr<StringLiteralExpression> parseStringLiteralExpression();

  std::shared_ptr<Statement> parseStatement();
  std::shared_ptr<Statement> parseVariableAssignmentStatement();

  bool isAtEnd();
};

#endif
