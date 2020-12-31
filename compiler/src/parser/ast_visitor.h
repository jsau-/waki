#ifndef waki_parser_ast_visitor
#define waki_parser_ast_visitor

/*
 * NB: To avoid circular dependencies we've had to partially declare our
 * expression/statement structs.
 */
struct BinaryOperatorExpression;
struct BoolLiteralExpression;
struct DoubleLiteralExpression;
struct FloatLiteralExpression;
struct IdentifierExpression;
struct NullLiteralExpression;
struct SignedInt32LiteralExpression;
struct StringLiteralExpression;
struct BlockStatement;
struct VariableAssignmentStatement;

// TODO: Currently we just treat BlockStatement as our primary node; I think
// we should just define a ProgramStatement or something (which is effectively
// a BlockStatement), or in the least something to make it more clear that
// our concept of an AST is a BlockStatement.
struct AstVisitor {
  virtual ~AstVisitor(){};

  virtual void visitBinaryOperatorExpression(BinaryOperatorExpression& node) = 0;
  virtual void visitBoolLiteralExpression(BoolLiteralExpression& node) = 0;
  virtual void visitDoubleLiteralExpression(DoubleLiteralExpression& node) = 0;
  virtual void visitFloatLiteralExpression(FloatLiteralExpression& node) = 0;
  virtual void visitIdentifierExpression(IdentifierExpression& node) = 0;
  virtual void visitNullLiteralExpression() = 0;
  virtual void visitSignedInt32LiteralExpression(
      SignedInt32LiteralExpression& node) = 0;
  virtual void visitStringLiteralExpression(StringLiteralExpression& node) = 0;

  virtual void visitBlockStatement(BlockStatement& node) = 0;
  virtual void visitVariableAssignmentStatement(
      VariableAssignmentStatement& node) = 0;
};

#endif
