#ifndef waki_parser_parser
#define waki_parser_parser

#include <vector>
#include "../tokenizer/token.h"

struct Parser {
  Parser(std::string sourceText, std::vector<Token> tokens);

  int parse();

private:
  std::string sourceText;
  std::vector<Token> tokens;
  size_t index;
};

#endif
