#ifndef waki_parser_statements_statement
#define waki_parser_statements_statement

#include "../ast_node.h"

struct Statement : AstNode {
  Statement(uint64_t line, uint64_t column)
    : AstNode(line, column) {}
  virtual ~Statement(){};
};

#endif
