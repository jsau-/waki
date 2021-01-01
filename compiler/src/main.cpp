#include <CLI11.h>
#include <fstream>
#include <spdlog/spdlog.h>
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

  bool verbose;
  app.add_flag("-v,--verbose", verbose, "Include verbose output from compiler modules for better debugging.");

  CLI11_PARSE(app, argc, argv);

  if (verbose) {
    spdlog::set_level(spdlog::level::trace);
  } else {
    spdlog::set_level(spdlog::level::warn);
  }

  std::ifstream inFileStream(inFilePath);


  if (!inFileStream) {
    spdlog::critical("Error reading input file '{}'. {}.", inFilePath, strerror(errno));
    return -1;
  }

  std::string inFile((std::istreambuf_iterator<char>(inFileStream)),
                     (std::istreambuf_iterator<char>()));

  spdlog::trace("Instantiating tokenizer.");

  auto tokenizer = Tokenizer(inFile);

  spdlog::trace("Tokenizing input.");

  const auto tokens = tokenizer.tokenize();

  spdlog::trace("Received tokens:");

  auto lexemeMetadata = Lexemes::getInstance().getMetadata();

  for (auto const &token : tokens) {
    spdlog::trace("Token: {} ({}) | value '{}' | line number {} | column number ",
                  lexemeMetadata.at(token.type).displayName, token.type, token.value,
                  token.lineNumber, token.columnNumber);
  }

  spdlog::trace("Instantiating parser.");

  auto parser = Parser(inFile, tokens);

  spdlog::trace("Parsing tokens.");

  auto ast = parser.parse();

  spdlog::trace("Instantiating Waki emitter.");

  auto wakiEmitter = WakiEmitter(ast);

  spdlog::trace("Emitted Waki source code: \n{}", wakiEmitter.source());

  auto builtinModules = BuiltinModules();

  spdlog::trace("Found built-in modules:");

  for (const auto &builtinFunction : builtinModules.getFunctions()) {
    spdlog::trace("Has builtin function {}", builtinFunction->getName());
  }

  spdlog::trace("Instantiating typechecker:");

  auto typechecker = Typechecker(ast);

  auto typeErrors = typechecker.check();

  if (typeErrors.size() == 0) {
    spdlog::debug("No type errors.");
  } else {
    spdlog::error("Received {} type error(s)", typeErrors.size());
    for (const auto &typeError : typeErrors) {
      spdlog::error("Line: {}, column {}; {}", typeError->getLine(), typeError->getColumn(),
                    typeError->getError());
    }
  }

  return 0;
}
