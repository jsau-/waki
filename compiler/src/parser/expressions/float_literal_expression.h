#ifndef waki_parser_expressions_float_literal_expression
#define waki_parser_expressions_float_literal_expression

#include "expression.h"

/**
 * Represents an expression of a floating point literal, eg. the right-hand side
 * of statement `float foo = 10.0f;`
 *                             ^
 *                             |
 */
struct FloatLiteralExpression : Expression {
  float value;

  FloatLiteralExpression(uint64_t line, uint64_t column, float value)
    : Expression(line, column), value(value) {}

  virtual void acceptAstVisitor(AstVisitor &visitor) override {
    visitor.visitFloatLiteralExpression(*this);
  };
};

#endif
