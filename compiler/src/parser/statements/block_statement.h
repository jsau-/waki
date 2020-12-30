#ifndef waki_parser_statements_block_statement
#define waki_parser_statements_block_statement

#include <memory>
#include <vector>

#include "statement.h"

/**
 * A block statement is simply a list of statements, eg. the top-level of a
 * program, the body of a function, or the definition of a struct.
 */
struct BlockStatement : Statement {
  std::vector<std::shared_ptr<Statement>> statements;

  BlockStatement(std::vector<std::shared_ptr<Statement>> statements)
      : statements(statements) {}

  virtual void acceptAstVisitor(AstVisitor& visitor) override {
    visitor.visitBlockStatement(*this);
  };
};

#endif
