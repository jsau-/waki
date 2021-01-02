#include "../../src/tokenizer/token.h"
#include <catch2.h>

SCENARIO("Token construction", "[Token]") {
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
