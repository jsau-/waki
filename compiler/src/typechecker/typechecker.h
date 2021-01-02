#ifndef waki_typechecker_typechecker
#define waki_typechecker_typechecker

#include <memory>
#include <vector>

#include "../parser/ast_visitor.h"
#include "../parser/expressions/binary_operator_expression.h"
#include "../parser/expressions/bool_literal_expression.h"
#include "../parser/expressions/double_literal_expression.h"
#include "../parser/expressions/float_literal_expression.h"
#include "../parser/expressions/identifier_expression.h"
#include "../parser/expressions/null_literal_expression.h"
#include "../parser/expressions/signed_int_32_literal_expression.h"
#include "../parser/expressions/string_literal_expression.h"
#include "../parser/statements/block_statement.h"
#include "../parser/statements/conditional_statement.h"
#include "../parser/statements/variable_assignment_statement.h"
#include "identifier.h"
#include "identifier_table.h"
#include "typechecker_error.h"

struct Typechecker : public AstVisitor {
  // TODO: Should probably actually have some type properly denoting this is
  // a root node
  Typechecker(std::shared_ptr<BlockStatement> ast);

  /**
   * Check all types in the provided AST, and return all found errors.
   * Note that certain errors may have cascaded as a result of the earliest
   * error. The programmer should be prompted to address errors in the order
   * they were presented.
   */
  std::vector<std::shared_ptr<TypecheckerError>> check();

protected:
  virtual void visitBinaryOperatorExpression(BinaryOperatorExpression &node) override;
  virtual void visitBoolLiteralExpression(BoolLiteralExpression &node) override;
  virtual void visitDoubleLiteralExpression(DoubleLiteralExpression &node) override;
  virtual void visitFloatLiteralExpression(FloatLiteralExpression &node) override;
  virtual void visitIdentifierExpression(IdentifierExpression &node) override;
  virtual void visitNullLiteralExpression() override;
  virtual void visitSignedInt32LiteralExpression(SignedInt32LiteralExpression &node) override;
  virtual void visitStringLiteralExpression(StringLiteralExpression &node) override;

  virtual void visitBlockStatement(BlockStatement &node) override;
  virtual void visitConditionalStatement(ConditionalStatement &node) override;
  virtual void visitVariableAssignmentStatement(VariableAssignmentStatement &node) override;

private:
  std::shared_ptr<BlockStatement> ast;
  std::vector<std::shared_ptr<TypecheckerError>> errors;
  IdentifierTable identifierTable;

  // Cached type of the most recently visited node
  LexemeType latestVisitedType;
};

#endif
