#ifndef waki_parser_expressions_expression
#define waki_parser_expressions_expression

#include "../ast_node.h"

struct Expression : AstNode {
  virtual ~Expression(){};
};

#endif
