#ifndef waki_parser_statements_statement
#define waki_parser_statements_statement

#include "../ast_node.h"

struct Statement : AstNode {
  virtual ~Statement(){};
};

#endif
