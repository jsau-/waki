#ifndef waki_parser_expressions_signed_int_32_literal_expression
#define waki_parser_expressions_signed_int_32_literal_expression

#include <cstdint>

#include "expression.h"

/**
 * Represents an expression of a signed int32 literal, eg. the right-hand side
 * of statement `int foo = 10;`
 *                          ^
 *                          |
 */
struct SignedInt32LiteralExpression : Expression {
  std::int32_t value;

  SignedInt32LiteralExpression(std::int32_t value) : value(value){};

  virtual void acceptAstVisitor(AstVisitor& visitor) override {
    visitor.visitSignedInt32LiteralExpression(*this);
  };
};

#endif
