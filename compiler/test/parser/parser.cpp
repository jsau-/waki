#include <catch2.h>
#include <vector>

#include "../../src/parser/parser.h"
#include "../../src/parser/statements/variable_assignment_statement.h"
#include "../../src/tokenizer/lexeme_type.h"
#include "../../src/tokenizer/token.h"

SCENARIO("Parsing a list of tokens", "[parser]") {
  GIVEN("An empty list of tokens") {
    WHEN("parsed") {
      auto tokens = std::vector<Token>();
      auto parser = Parser(tokens);
      auto ast = parser.parse();

      THEN("an empty block statement is returned") {
        REQUIRE(ast->getColumn() == 0);
        REQUIRE(ast->getLine() == 0);
        REQUIRE(ast->statements.size() == 0);
      }
    }
  }

  GIVEN("Tokens representing a variable assignment statement") {
    WHEN("not mutable, of unknown type") {
      std::vector<Token> tokens = {Token(LexemeType::IDENTIFIER, "varname", 0, 0),
                                   Token(LexemeType::ASSIGN_EQUALS, "=", 0, 8),
                                   Token(LexemeType::SIGNED_INTEGER_32_LITERAL, "10", 0, 10),
                                   Token(LexemeType::END_OF_STATEMENT, ";", 0, 11)};

      auto parser = Parser(tokens);

      auto ast = parser.parse();

      THEN("a variable assignment statement is returned") {
        REQUIRE(ast->statements.size() == 1);
        auto variableAssignmentStatement =
          std::dynamic_pointer_cast<VariableAssignmentStatement>(ast->statements.at(0));
        REQUIRE(variableAssignmentStatement->dataType == LexemeType::UNKNOWN);
        REQUIRE(variableAssignmentStatement->identifier == "varname");
        REQUIRE(variableAssignmentStatement->assignmentOperator == LexemeType::ASSIGN_EQUALS);
        REQUIRE(variableAssignmentStatement->isMutable == false);
      }
    }

    WHEN("not mutable, of known type") {
      std::vector<Token> tokens = {Token(LexemeType::SIGNED_INTEGER_32, "int", 0, 0),
                                   Token(LexemeType::IDENTIFIER, "varname", 0, 4),
                                   Token(LexemeType::ASSIGN_EQUALS, "=", 0, 12),
                                   Token(LexemeType::SIGNED_INTEGER_32_LITERAL, "10", 0, 14),
                                   Token(LexemeType::END_OF_STATEMENT, ";", 0, 15)};

      auto parser = Parser(tokens);

      auto ast = parser.parse();

      THEN("a variable assignment statement is returned") {
        REQUIRE(ast->statements.size() == 1);
        auto variableAssignmentStatement =
          std::dynamic_pointer_cast<VariableAssignmentStatement>(ast->statements.at(0));
        REQUIRE(variableAssignmentStatement->dataType == LexemeType::SIGNED_INTEGER_32);
        REQUIRE(variableAssignmentStatement->identifier == "varname");
        REQUIRE(variableAssignmentStatement->assignmentOperator == LexemeType::ASSIGN_EQUALS);
        REQUIRE(variableAssignmentStatement->isMutable == false);
      }
    }

    WHEN("mutable, of unknown type") {
      std::vector<Token> tokens = {Token(LexemeType::MUTABLE, "mutable", 0, 0),
                                   Token(LexemeType::IDENTIFIER, "varname", 0, 8),
                                   Token(LexemeType::ASSIGN_EQUALS, "=", 0, 16),
                                   Token(LexemeType::SIGNED_INTEGER_32_LITERAL, "10", 0, 18),
                                   Token(LexemeType::END_OF_STATEMENT, ";", 0, 11)};

      auto parser = Parser(tokens);

      auto ast = parser.parse();

      THEN("a variable assignment statement is returned") {
        REQUIRE(ast->statements.size() == 1);
        auto variableAssignmentStatement =
          std::dynamic_pointer_cast<VariableAssignmentStatement>(ast->statements.at(0));
        REQUIRE(variableAssignmentStatement->dataType == LexemeType::UNKNOWN);
        REQUIRE(variableAssignmentStatement->identifier == "varname");
        REQUIRE(variableAssignmentStatement->assignmentOperator == LexemeType::ASSIGN_EQUALS);
        REQUIRE(variableAssignmentStatement->isMutable == true);
      }
    }
  }
}
