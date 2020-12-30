#ifndef waki_parser_statements_binary_operator_expression
#define waki_parser_statements_binary_operator_expression

#include <memory>

#include "../../tokenizer/lexeme_type.h"
#include "../../tokenizer/lexemes.h"
#include "expression.h"

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
  LexemeType binaryOperator;
  std::shared_ptr<Expression> lhs;
  std::shared_ptr<Expression> rhs;

  BinaryOperatorExpression(LexemeType binaryOperator, std::shared_ptr<Expression> lhs,
                           std::shared_ptr<Expression> rhs)
    : binaryOperator(binaryOperator), lhs(lhs), rhs(rhs) {
    auto binaryOperators = Lexemes::getInstance().getBinaryOperators();

    if (binaryOperators.find(binaryOperator) == binaryOperators.end()) {
      // TODO: Proper error
      throw std::runtime_error("Unexpected binary operator.");
    }
  }

  virtual void acceptAstVisitor(AstVisitor &visitor) override {
    visitor.visitBinaryOperatorExpression(*this);
  };
};

#endif
