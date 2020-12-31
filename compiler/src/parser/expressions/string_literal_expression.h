#ifndef waki_parser_expressions_string_literal_expression
#define waki_parser_expressions_string_literal_expression

#include "expression.h"
#include <string>

/**
 * Represents an expression of a signed int32 literal, eg. the right-hand side
 * of statement `int foo = 10;`
 *                          ^
 *                          |
 */
struct StringLiteralExpression : Expression {
  std::string value;

  StringLiteralExpression(uint64_t line, uint64_t column, std::string value)
    : Expression(line, column), value(value){};

  virtual void acceptAstVisitor(AstVisitor &visitor) override {
    visitor.visitStringLiteralExpression(*this);
  };
};

#endif
