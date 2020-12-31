#ifndef waki_parser_expressions_double_literal_expression
#define waki_parser_expressions_double_literal_expression

#include "expression.h"

/**
 * Represents an expression of a double literal, eg. the right-hand side of
 * statement `double foo = 10.0;`
 *                          ^
 *                          |
 */
struct DoubleLiteralExpression : Expression {
  double value;

  DoubleLiteralExpression(uint64_t line, uint64_t column, double value)
    : Expression(line, column), value(value) {}

  virtual void acceptAstVisitor(AstVisitor &visitor) override {
    visitor.visitDoubleLiteralExpression(*this);
  };
};

#endif
