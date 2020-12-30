#ifndef waki_parser_parse_result
#define waki_parser_parse_result

#include <memory>
#include <vector>
#include "statements/statement.h"

struct ParseResult {
  std::shared_ptr<Statement> statement;
  size_t consumedTokens;

  ParseResult(std::shared_ptr<Statement> statement, size_t consumedTokens) : statement(statement), consumedTokens(consumedTokens) {}
};

#endif
