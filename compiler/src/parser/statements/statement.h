#ifndef waki_parser_statements_statement
#define waki_parser_statements_statement

#include "../ast_node.h"

struct Statement : AstNode {
  Statement(uint64_t lineDeclared, uint64_t columnDeclared)
    : lineDeclared(lineDeclared), columnDeclared(columnDeclared) {}
  virtual ~Statement(){};

  uint64_t getLineDeclared() { return this->lineDeclared; }
  uint64_t getColumnDeclared() { return this->columnDeclared; }

protected:
  /*
   * The line the statement was declared at. Note that this will not necessarily
   * be the line that a portion of the statement occurs at, but it should
   * loosely approximate where something happened.
   */
  uint64_t lineDeclared;

  /*
   * The column the statement was declared at. Note that this will not necessarily
   * be the line that a portion of the statement occurs at, but it should
   * loosely approximate where something happened.
   */
  uint64_t columnDeclared;
};

#endif
