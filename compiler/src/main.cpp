#include <CLI11.h>
#include <fstream>
#include <iostream>
#include <string>

#include "emitter/waki_emitter.h"
#include "modules/builtin_modules.h"
#include "parser/parser.h"
#include "tokenizer/lexemes.h"
#include "tokenizer/token.h"
#include "tokenizer/tokenizer.h"
#include "typechecker/typechecker.h"

int main(int argc, char **argv) {
  CLI::App app{"Waki programming language compiler."};

  std::string inFilePath;
  app.add_option("-i,--in-file", inFilePath, "Path to input file to compile.")->required();

  CLI11_PARSE(app, argc, argv);

  std::ifstream inFileStream(inFilePath);

  if (!inFileStream) {
    std::cerr << "Error reading file '" << inFilePath << "'. " << strerror(errno) << std::endl;
    return -1;
  }

  std::string inFile((std::istreambuf_iterator<char>(inFileStream)),
                     (std::istreambuf_iterator<char>()));

    std::cout << "Instantiating tokenizer" << std::endl;

    auto tokenizer = Tokenizer(inFile);

    std::cout << "Tokenizing input" << std::endl;

    const auto tokens = tokenizer.tokenize();

    std::cout << "Tokens:" << std::endl;
    std::cout << "---------------------------" << std::endl;

    auto lexemeMetadata = Lexemes::getInstance().getMetadata();

    for (auto const &token : tokens) {
      std::cout << "Token: " << lexemeMetadata.at(token.type).displayName << " (" <<
      (int)token.type
                << ")"
                << " | value '" << token.value << "' | line number " << token.lineNumber
                << " | column number " << token.columnNumber << std::endl;
    }
    std::cout << "---------------------------" << std::endl << std::endl;

    std::cout << "Instantiating parser" << std::endl;

    auto parser = Parser(inFile, tokens);

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
      std::cout << "Line: " << typeError->getLine() << ", column: " << typeError->getColumn() <<
      "; "
                << typeError->getError() << std::endl;
    }

  return 0;
}
