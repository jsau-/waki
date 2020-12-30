#ifndef waki_parser_statements_binary_operator_expression
#define waki_parser_statements_binary_operator_expression

#include <memory>

#include "expression.h"
#include "../types/binary_operator.h"

/**
 * Statement representing a binary operation, i.e. one with a LHS and RHS
 * expression, and an operator between them.
 * @example
 * ```waki
 * //          This section is the expression
 * //         _______________________________
 * //        |                               |
 * int foo = currentTimeInSeconds() + (8 * 2);
 * //                 |             |    |
 *                    |         Operator |
 * //                LHS                RHS
 * ```
 */
struct BinaryOperatorExpression : Expression {
  BinaryOperator binaryOperator;
  std::shared_ptr<Expression> lhs;
  std::shared_ptr<Expression> rhs;

  BinaryOperatorExpression(BinaryOperator binaryOperator,
                          std::shared_ptr<Expression> lhs,
                          std::shared_ptr<Expression> rhs)
      : binaryOperator(binaryOperator), lhs(lhs), rhs(rhs) {}

  virtual void acceptAstVisitor(AstVisitor& visitor) override {
    visitor.visitBinaryOperatorExpression(*this);
  };
};

#endif
