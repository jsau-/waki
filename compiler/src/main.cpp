#include <iostream>
#include <string>
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

myNullableInt = 50;

myNullableInt = null;

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

  auto tokenizer = Tokenizer(input);

  const auto tokens = tokenizer.tokenize();

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

  auto parser = Parser(input, tokens);

  auto ast = parser.parse();

  std::cout << ast;

  return 0;
}
