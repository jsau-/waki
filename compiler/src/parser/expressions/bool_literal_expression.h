#ifndef waki_parser_expressions_bool_literal_expression
#define waki_parser_expressions_bool_literal_expression

#include "expression.h"

/**
 * Represents an expression of a boolean literal, eg. the right-hand side of
 * statement `bool foo = false;`
 *                         ^
 *                         |
 */
struct BoolLiteralExpression : Expression {
  bool value;

  BoolLiteralExpression(uint64_t line, uint64_t column, bool value)
    : Expression(line, column), value(value){};

  virtual void acceptAstVisitor(AstVisitor &visitor) override {
    visitor.visitBoolLiteralExpression(*this);
  };
};

#endif
