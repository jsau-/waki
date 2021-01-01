#include <iostream>
#include <string>

#include "emitter/waki_emitter.h"
#include "modules/builtin_modules.h"
#include "parser/parser.h"
#include "tokenizer/lexemes.h"
#include "tokenizer/token.h"
#include "tokenizer/tokenizer.h"
#include "typechecker/typechecker.h"

int main() {
  auto input = R""""(
mutable bool iLiteral = false;
bool iLiteral = 20;
mutable bool iLiteral = 52; mutable bool iLiteral = false;

iLiteral = null;
// Brapadoo! ;;;;;;;;;;;;;;;;;;;

mutable bool bLiteral = false;
bLiteral = true;

dLiteral *= -10.0d;

string stringystroo = null;

// myBinaryOp = 10 + 20;

myOtherBinaryOp = (((true) && false)) || false;
  )"""";

  std::cout << "Instantiating tokenizer" << std::endl;

  auto tokenizer = Tokenizer(input);

  std::cout << "Tokenizing input" << std::endl;

  const auto tokens = tokenizer.tokenize();

  std::cout << "Tokens:" << std::endl;
  std::cout << "---------------------------" << std::endl;

  auto lexemeMetadata = Lexemes::getInstance().getMetadata();

  for (auto const &token : tokens) {
    std::cout << "Token: " << lexemeMetadata.at(token.type).displayName << " (" << (int)token.type
              << ")"
              << " | value '" << token.value << "' | line number " << token.lineNumber
              << " | column number " << token.columnNumber << std::endl;
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

  std::cout << wakiEmitter.source() << std::endl ;

  auto builtinModules = BuiltinModules();

  std::cout << std::endl << "Builtin modules:" << std::endl;
  std::cout << "---------------------------" << std::endl;
  for (const auto& builtinFunction : builtinModules.getFunctions()) {
    std::cout << "Has builtin function " << builtinFunction->getName() << std::endl;
  }

  std::cout << std::endl<< "Typechecker:" << std::endl;
  std::cout << "---------------------------" << std::endl;

  auto typechecker = Typechecker(ast);

  auto typeErrors = typechecker.check();

  std::cout << "Received " << typeErrors.size() << " type error(s)" << std::endl;

  for (const auto &typeError : typeErrors) {
    std::cout << "Line: " << typeError->getLine() << ", column: " << typeError->getColumn() << "; "
              << typeError->getError() << std::endl;
  }

  return 0;
}
