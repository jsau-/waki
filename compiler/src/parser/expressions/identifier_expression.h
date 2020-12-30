#ifndef waki_parser_expressions_identifier_expression
#define waki_parser_expressions_identifier_expression

#include <string>
#include "expression.h"

/**
 * Represents an expression referencing an identifier.
 * @example
 * ```waki
 * int foo = 10;
 * int bar = foo;
 * //         ^
 * //     Identifier
 * ```
 */
struct IdentifierExpression : Expression {
  std::string identifier;

  IdentifierExpression(std::string identifier) : identifier(identifier) {};

  virtual void acceptAstVisitor(AstVisitor& visitor) override {
    visitor.visitIdentifierExpression(*this);
  };
};

#endif
