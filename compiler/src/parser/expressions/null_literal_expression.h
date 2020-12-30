#ifndef waki_parser_expressions_null_literal_expression
#define waki_parser_expressions_null_literal_expression

#include "expression.h"

/**
 * Represents an expression of a null literal, eg. the right-hand side of
 * statement `nullable int foo = null;`
 *                                ^
 *                                |
 */
struct NullLiteralExpression : Expression {
  virtual void acceptAstVisitor(AstVisitor& visitor) override {
    visitor.visitNullLiteralExpression();
  };
};

#endif
