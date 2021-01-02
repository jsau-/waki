#include "../../src/tokenizer/token.h"
#include <catch2.h>

SCENARIO("Token construction", "[token]") {
  GIVEN("A token is instantiated") {
    WHEN("no constructor params are provided") {
      auto token = Token();

      THEN("it returns an unknown token") {
        REQUIRE(token.type == LexemeType::UNKNOWN);
        REQUIRE(token.value == "");
        REQUIRE(token.lineNumber == 0);
        REQUIRE(token.columnNumber == 0);
      }
    }
  }
}

SCENARIO("Comparing tokens", "[token]") {
  GIVEN("Two tokens") {
    Token tokenOne;
    Token tokenTwo;

    WHEN("their lexeme type, value, line and column numbers are equal") {
      tokenOne = Token(LexemeType::SINGLE_LINE_COMMENT, "//", 19, 42);
      tokenTwo = Token(LexemeType::SINGLE_LINE_COMMENT, "//", 19, 42);

      THEN("the tokens are equal") { REQUIRE(tokenOne == tokenTwo); }
    }

    WHEN("their lexeme type is not equal") {
      tokenOne = Token(LexemeType::SINGLE_LINE_COMMENT, "//", 19, 42);
      tokenTwo = Token(LexemeType::MULTIPLY, "*", 19, 42);

      THEN("the tokens are not equal") { REQUIRE(tokenOne != tokenTwo); }
    }

    WHEN("their value is not equal") {
      tokenOne = Token(LexemeType::IDENTIFIER, "foo", 19, 42);
      tokenTwo = Token(LexemeType::IDENTIFIER, "bar", 19, 42);

      THEN("the tokens are not equal") { REQUIRE(tokenOne != tokenTwo); }
    }

    WHEN("their line number is not equal") {
      tokenOne = Token(LexemeType::IDENTIFIER, "foo", 1, 42);
      tokenTwo = Token(LexemeType::IDENTIFIER, "bar", 19, 42);

      THEN("the tokens are not equal") { REQUIRE(tokenOne != tokenTwo); }
    }

    WHEN("ther column number is not equal") {
      tokenOne = Token(LexemeType::IDENTIFIER, "foo", 19, 1);
      tokenTwo = Token(LexemeType::IDENTIFIER, "bar", 19, 42);

      THEN("the tokens are not equal") { REQUIRE(tokenOne != tokenTwo); }
    }
  }
}
