#ifndef waki_parser_ast_node
#define waki_parser_ast_node

#include "ast_visitor.h"

struct AstNode {
  virtual ~AstNode() {};
  virtual void acceptAstVisitor(AstVisitor& visitor) = 0;
};

#endif
