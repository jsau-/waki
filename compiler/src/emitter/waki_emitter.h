#ifndef waki_emitter_javascript_emitter
#define waki_emitter_javascript_emitter

#include <sstream>

#include "../parser/ast_visitor.h"
#include "../parser/expressions/bool_literal_expression.h"
#include "../parser/expressions/double_literal_expression.h"
#include "../parser/expressions/float_literal_expression.h"
#include "../parser/expressions/null_literal_expression.h"
#include "../parser/expressions/signed_int_32_literal_expression.h"
#include "../parser/expressions/string_literal_expression.h"
#include "../parser/statements/block_statement.h"
#include "../parser/statements/variable_assignment_statement.h"

struct WakiEmitter : AstVisitor {
  virtual void visitBoolLiteralExpression(BoolLiteralExpression& node) override;
  virtual void visitDoubleLiteralExpression(
      DoubleLiteralExpression& node) override;
  virtual void visitFloatLiteralExpression(
      FloatLiteralExpression& node) override;
  virtual void visitNullLiteralExpression() override;
  virtual void visitSignedInt32LiteralExpression(
      SignedInt32LiteralExpression& node) override;
virtual void visitStringLiteralExpression(StringLiteralExpression& node) override;

  virtual void visitBlockStatement(BlockStatement& node) override;
  virtual void visitVariableAssignmentStatement(
      VariableAssignmentStatement& node) override;

  WakiEmitter(std::shared_ptr<BlockStatement> rootNode);

  std::string source();

 private:
  std::ostringstream sourceStream;
};

#endif
