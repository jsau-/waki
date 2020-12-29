#include <iostream>
#include <string>
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

  Tokenizer tokenizer = Tokenizer(input);

  const std::vector<Token> tokens = tokenizer.tokenize();

  for (auto const& token: tokens) {
    std::cout
      << "Token: " << (int)token.type
      << " | value '" << token.value
      << "' | line number " << token.lineNumber
      << " | column number " << token.columnNumber
      << std::endl;
  }

  return 0;
}
