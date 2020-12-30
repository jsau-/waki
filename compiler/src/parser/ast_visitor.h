#ifndef waki_parser_ast_visitor
#define waki_parser_ast_visitor

struct BoolLiteralExpression;
struct DoubleLiteralExpression;
struct FloatLiteralExpression;
struct NullLiteralExpression;
struct SignedInt32LiteralExpression;
struct BlockStatement;
struct VariableAssignmentStatement;

struct AstVisitor {
  virtual ~AstVisitor() {};

  virtual void visitBoolLiteralExpression(BoolLiteralExpression& node) = 0;
  virtual void visitDoubleLiteralExpression(DoubleLiteralExpression& node) = 0;
  virtual void visitFloatLiteralExpression(FloatLiteralExpression& node) = 0;
  virtual void visitNullLiteralExpression() = 0;
  virtual void visitSignedInt32LiteralExpression(SignedInt32LiteralExpression& node) = 0;

  virtual void visitBlockStatement(BlockStatement& node) = 0;
  virtual void visitVariableAssignmentStatement(VariableAssignmentStatement& node) = 0;
};

#endif
