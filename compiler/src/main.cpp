#include <iostream>
#include <string>
#include "emitter/waki_emitter.h"
#include "parser/parser.h"
#include "tokenizer/token_names.h"
#include "tokenizer/token.h"
#include "tokenizer/tokenizer.h"

int main() {
  auto input = R""""(
#import 'foo.waki';

namespace MyNamespace {
  int myInt = 10;

  MY_CONSTANT = 500.0f;

  mutable int myOtherInt = 2;
  float myFloat = 1.0f;

  // some stuff is bad
  myOtherInt = 4;
}

bool myBool = false;

myDerivedInt = myBool ? 10 : 20;

mutable nullable int myNullableInt;

myNullableInt *= 50;

myNullableInt /= 30;

myDerivedIntFromNull = myNullableInt ?? 50;

/**
 * Cool.
 * myOtherInt = 20;
 */
baz = 50;

function foo(int bar) returns int {
  return bar * 10;
}
  )"""";

  std::cout << "Instantiating tokenizer" << std::endl;

  auto tokenizer = Tokenizer(input);

  std::cout << "Tokenizing input" << std::endl;

  const auto tokens = tokenizer.tokenize();

  std::cout << "Tokens:" << std::endl;
  std::cout << "---------------------------" << std::endl;

  for (auto const& token: tokens) {
    std::cout
      << "Token: "
      << TOKEN_NAMES.at(token.type)
      << " (" << (int)token.type << ")"
      << " | value '" << token.value
      << "' | line number " << token.lineNumber
      << " | column number " << token.columnNumber
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
