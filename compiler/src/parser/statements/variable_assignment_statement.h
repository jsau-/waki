#ifndef waki_parser_statements_variable_assignment_statement
#define waki_parser_statements_variable_assignment_statement

#include <memory>

#include "../expressions/expression.h"
#include "../types/assignment_operator.h"
#include "statement.h"

/**
 * Statement representing the assignment of an expression to a variable.
 * @example
 * ```waki
 * // Assignment of an integer literal expression to identifier `foo`
 * foo = 10;
 *
 * // Assignment of a function call expression to identifier `bar`
 * bar = myFunctionCall();
 * ```
 */
struct VariableAssignmentStatement : Statement {
  std::string identifier;
  AssignmentOperator assignmentOperator;
  std::shared_ptr<Expression> expression;

  VariableAssignmentStatement(std::string identifier,
                              AssignmentOperator assignmentOperator,
                              std::shared_ptr<Expression> expression)
      : identifier(identifier),
        assignmentOperator(assignmentOperator),
        expression(expression) {}

  virtual void acceptAstVisitor(AstVisitor& visitor) override {
    visitor.visitVariableAssignmentStatement(*this);
  };
};

#endif
