#ifndef waki_parser_ast_node
#define waki_parser_ast_node

#include "ast_visitor.h"

struct AstNode {
  AstNode(uint64_t line, uint64_t column) : line(line), column(column) {}
  virtual ~AstNode(){};
  virtual void acceptAstVisitor(AstVisitor& visitor) = 0;

  uint64_t getLine() const { return this->line; }
  uint64_t getColumn() const { return this->column; }

protected:
  /*
   * The line the node was declared. Note that this will be the start of the
   * declaration, so for certain nodes like higher-level statements or
   * expressions the location you're looking for might actually be further
   * along than this.
   */
  uint64_t line;

  /*
   * The column the node was declared. Note that this will be the start of the
   * declaration, so for certain nodes like higher-level statements or
   * expressions the location you're looking for might actually be further
   * along than this.
   */
  uint64_t column;
};

#endif
