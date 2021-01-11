#ifndef waki_parser_parser
#define waki_parser_parser

#include <optional.h>
#include <memory>
#include <set>

#include "../tokenizer/token.h"
#include "expressions/expression.h"
#include "statements/block_statement.h"
#include "statements/statement.h"

struct Parser {
  Parser(std::vector<Token> tokens);

  std::shared_ptr<BlockStatement> parse();

private:
  std::vector<Token> tokens;
  size_t index;

  /*
   * Increment our index tracking our position in the list of tokens, and return
   * the token we were previously indexed on.
   */
  Token advance();

  // Do we have a previous token to inspect?
  bool hasPreviousToken() const ;

  // Do we have a next token to inspect?
  bool hasNextToken() const;

  // Throw an error if the current token is not of given type.
  Token assertCurrentTokenType(LexemeType type) const;

  // Throw an error if the current token is not one of a set of types.
  Token assertCurrentTokenType(std::set<LexemeType> types) const;

  /*
   * Throw an error if the current token is not of given type; otherwise
   * advance to the next token, returning the token we were previously indexed
   * on.
   */
  Token assertCurrentTokenTypeAndAdvance(LexemeType type);

  /*
   * Throw an error if the current token is not one of a set of types; otherwise
   * advance to the next token, returning the token we were previously indexed
   * on.
   */
  Token assertCurrentTokenTypeAndAdvance(std::set<LexemeType> types);

  // Is the token we're currently indexed on of given type?
  bool checkCurrentTokenType(LexemeType type) const;

  // Is the token we're curently indexed on one of a set of types?
  bool checkCurrentTokenType(std::set<LexemeType> types) const;

  // Is the token immediately after the one we're indexed on of given type?
  bool checkNextTokenType(LexemeType type) const;

  /*
   * Is the token immediate after the one we're indexed on one of a set of
   * types?
   */
  bool checkNextTokenType(std::set<LexemeType> types) const;

  /*
   * Get the previous token to the one we're currently indexed on.
   * TODO: Return tl::optional<Token>
   */
  Token previousToken() const;

  // Get the token we're currently indexed on.
  Token currentToken() const;

  /*
   * Get the next token immediately following the one we're indexed on.
   * TODO: Return tl::optional<Token>
   */
  Token nextToken() const;

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

  tl::optional<std::shared_ptr<Statement>> parseStatement();
  std::shared_ptr<Statement> parseVariableAssignmentStatement();
  std::shared_ptr<Statement> parseConditionalStatement();

  bool isAtEnd() const;
};

#endif
