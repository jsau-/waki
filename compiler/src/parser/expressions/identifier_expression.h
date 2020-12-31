#ifndef waki_parser_expressions_identifier_expression
#define waki_parser_expressions_identifier_expression

#include "expression.h"
#include <string>

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

  IdentifierExpression(uint64_t line, uint64_t column, std::string identifier)
    : Expression(line, column), identifier(identifier){};

  virtual void acceptAstVisitor(AstVisitor &visitor) override {
    visitor.visitIdentifierExpression(*this);
  };
};

#endif
