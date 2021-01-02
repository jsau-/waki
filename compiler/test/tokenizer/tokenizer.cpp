#include "../../src/tokenizer/token.h"
#include "../../src/tokenizer/tokenizer.h"
#include <catch2.h>

SCENARIO("Tokenizing source code", "[tokenizer]") {
  GIVEN("An integer literal declaration statement") {
    auto source = "int foo = 10;";

    WHEN("the input is tokenized") {
      auto tokenizer = Tokenizer(source);
      THEN("relevant tokens are returned") {
        auto tokens = tokenizer.tokenize();
        REQUIRE(tokens.size() == 5);

        auto tokenOne = tokens.at(0);
        REQUIRE(tokenOne.type == LexemeType::SIGNED_INTEGER_32);
        REQUIRE(tokenOne.lineNumber == 1);
        REQUIRE(tokenOne.columnNumber == 1);

        auto tokenTwo = tokens.at(1);
        REQUIRE(tokenTwo.type == LexemeType::IDENTIFIER);
        REQUIRE(tokenTwo.value == "foo");
        REQUIRE(tokenTwo.lineNumber == 1);
        REQUIRE(tokenTwo.columnNumber == 5);

        auto tokenThree = tokens.at(2);
        REQUIRE(tokenThree.type == LexemeType::ASSIGN_EQUALS);
        REQUIRE(tokenThree.lineNumber == 1);
        REQUIRE(tokenThree.columnNumber == 9);

        auto tokenFour = tokens.at(3);
        REQUIRE(tokenFour.type == LexemeType::SIGNED_INTEGER_32_LITERAL);
        REQUIRE(tokenFour.value == "10");
        REQUIRE(tokenFour.lineNumber == 1);
        REQUIRE(tokenFour.columnNumber == 11);

        auto tokenFive = tokens.at(4);
        REQUIRE(tokenFive.type == LexemeType::END_OF_STATEMENT);
        REQUIRE(tokenFive.lineNumber == 1);
        REQUIRE(tokenFive.columnNumber == 13);
      }
    }
  }
}
