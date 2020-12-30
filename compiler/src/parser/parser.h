#ifndef waki_parser_parser
#define waki_parser_parser

#include <memory>
#include <vector>
#include "parse_result.h"
#include "statements/block_statement.h"
#include "../tokenizer/token.h"

struct Parser {
  Parser(std::string sourceText, std::vector<Token> tokens);

  std::shared_ptr<BlockStatement> parse();

private:
  std::string sourceText;
  std::vector<Token> tokens;
  size_t index;

  ParseResult parseStatement();

  bool isAtEnd();
};

#endif
