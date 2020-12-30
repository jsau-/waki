#include <iostream>
#include <string>

#include "emitter/waki_emitter.h"
#include "parser/parser.h"
#include "tokenizer/token.h"
#include "tokenizer/token_names.h"
#include "tokenizer/tokenizer.h"

int main() {
  auto input = R""""(
;;;;fLiteral = 30.0040f;

iLiteral += 20;
// Brapadoo! ;;;;;;;;;;;;;;;;;;;

bLiteral = false;
bLiteralTwo = true;

dLiteral *= -10.0d;

sLiteral = 'Wow. This is a string!';;
  )"""";

  std::cout << "Instantiating tokenizer" << std::endl;

  auto tokenizer = Tokenizer(input);

  std::cout << "Tokenizing input" << std::endl;

  const auto tokens = tokenizer.tokenize();

  std::cout << "Tokens:" << std::endl;
  std::cout << "---------------------------" << std::endl;

  for (auto const& token : tokens) {
    std::cout << "Token: " << TOKEN_NAMES.at(token.type) << " ("
              << (int)token.type << ")"
              << " | value '" << token.value << "' | line number "
              << token.lineNumber << " | column number " << token.columnNumber
              << std::endl;
  }
  std::cout << "---------------------------" << std::endl << std::endl;

  std::cout << "Instantiating parser" << std::endl;

  auto parser = Parser(input, tokens);

  std::cout << "Parsing tokens" << std::endl;

  auto ast = parser.parse();

  std::cout << "Instantiating emitter" << std::endl;

  auto wakiEmitter = WakiEmitter(ast);

  std::cout << std::endl << "Emitted source:" << std::endl;
  std::cout << "---------------------------" << std::endl;

  std::cout << wakiEmitter.source();

  return 0;
}
