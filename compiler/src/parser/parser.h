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
  bool hasPreviousToken();
  bool hasNextToken();

  Token assertCurrentTokenType(LexemeType type);
  Token assertCurrentTokenType(std::vector<LexemeType> types);
  Token assertCurrentTokenTypeAndAdvance(LexemeType type);
  Token assertCurrentTokenTypeAndAdvance(std::vector<LexemeType> types);
  bool checkCurrentTokenType(LexemeType type);
  bool checkCurrentTokenType(std::vector<LexemeType> types);
  bool checkNextTokenType(LexemeType type);
  bool checkNextTokenType(std::vector<LexemeType> types);

  Token previousToken();
  Token currentToken();
  Token nextToken();

  /*
   * NB: The way expression parsing is implemented is we just try to parse
   * the lowest precedence expression operator first.
   *
   * If they find a token that matches their expression type, they'll parse.
   * If they don't, they'll call the parser for the next precedence level,
   * working through all expression types until we reach terminal expression
   * nodes like literals.
   *
   * The precedence order of operators should be (from highest to lowest):
   *   - unary; eg. !
   *   - multiplicative; * / %
   *   - additive; + -
   *   - bitwise shift; << >>
   *   - relational; < > <= >= etc.
   *   - equality; == != etc.
   *   - bitwise and; &
   *   - bitwise xor; ^
   *   - bitwise or; |
   *   - logical and; &&
   *   - logical or; ||
   *   - compound assignment; *= /= etc.
   *
   * After we've passed all possible operators, we've reached what we'll call
   * a primary expression. These can be thought of as the atomic form an
   * expression, either comprised of a literal value or a nested expression.
   */
  std::shared_ptr<Expression> parseExpression();
  std::shared_ptr<Expression> parseCompoundAssignmentExpression();
  std::shared_ptr<Expression> parseLogicalOrExpression();
  std::shared_ptr<Expression> parseLogicalAndExpression();
  std::shared_ptr<Expression> parseBitwiseOrExpression();
  std::shared_ptr<Expression> parseBitwiseXorExpression();
  std::shared_ptr<Expression> parseBitwiseAndExpression();
  std::shared_ptr<Expression> parseEqualityExpression();
  std::shared_ptr<Expression> parseRelationalExpression();
  std::shared_ptr<Expression> parseBitwiseShiftExpression();
  std::shared_ptr<Expression> parseAdditiveExpression();
  std::shared_ptr<Expression> parseMultiplicativeExpression();
  std::shared_ptr<Expression> parsePrimaryExpression();

  std::shared_ptr<Statement> parseStatement();
  std::shared_ptr<Statement> parseVariableAssignmentStatement();

  bool isAtEnd();
};

#endif
