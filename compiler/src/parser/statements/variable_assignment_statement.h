#ifndef waki_parser_statements_variable_assignment_statement
#define waki_parser_statements_variable_assignment_statement

#include <memory>

#include "../expressions/expression.h"
#include "../types/assignment_operator.h"
#include "../types/data_type.h"
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
  DataType dataType;
  std::string identifier;
  AssignmentOperator assignmentOperator;
  std::shared_ptr<Expression> expression;
  bool isMutable;
  bool isNullable;

  /*
   * TODO: We might want to track `bool isDeclaration` here and set that as
   * part of a later phase, eg. the typechecker. That'd let us check if we're
   * doing silly stuff like `*=` at declaration time which is very likely to be
   * a programmer error.
   */

  VariableAssignmentStatement(DataType dataType, std::string identifier,
                              AssignmentOperator assignmentOperator,
                              std::shared_ptr<Expression> expression,
                              bool isMutable = false, bool isNullable = false)
      : dataType(dataType),
        identifier(identifier),
        assignmentOperator(assignmentOperator),
        expression(expression),
        isMutable(isMutable),
        isNullable(isNullable) {}

  virtual void acceptAstVisitor(AstVisitor& visitor) override {
    visitor.visitVariableAssignmentStatement(*this);
  };
};

#endif
