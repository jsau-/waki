#ifndef waki_parser_expressions_expression
#define waki_parser_expressions_expression

#include "../ast_node.h"

struct Expression : AstNode {
  Expression(uint64_t line, uint64_t column) : AstNode(line, column) {}
  virtual ~Expression(){};
};

#endif
