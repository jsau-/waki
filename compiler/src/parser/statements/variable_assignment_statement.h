#ifndef waki_parser_statements_variable_assignment_statement
#define waki_parser_statements_variable_assignment_statement

#include <memory>

#include "../../tokenizer/lexeme_type.h"
#include "../../tokenizer/lexemes.h"
#include "../expressions/expression.h"
#include "statement.h"

/**
 * Statement representing the assignment of an expression to a variable.
 * @example
 * ```waki
 * // Assignment of an integer literal expression to identifier `foo`
 * foo = 10;
 *
 * // Assignment of a function call expression to identifier `bar`
 * bar = myFunctionCall();
 * ```
 */
struct VariableAssignmentStatement : Statement {
  LexemeType dataType;
  std::string identifier;
  LexemeType assignmentOperator;
  std::shared_ptr<Expression> expression;
  bool isMutable;
  bool isNullable;

  VariableAssignmentStatement(uint64_t line, uint64_t column, LexemeType dataType,
                              std::string identifier, LexemeType assignmentOperator,
                              std::shared_ptr<Expression> expression, bool isMutable = false,
                              bool isNullable = false)
    : Statement(line, column), dataType(dataType),
      identifier(identifier), assignmentOperator(assignmentOperator), expression(expression),
      isMutable(isMutable), isNullable(isNullable) {
    auto lexemes = Lexemes::getInstance();
    auto assignmentOperators = lexemes.getAssignmentOperators();
    auto dataTypes = lexemes.getDataTypes();

    if (assignmentOperators.find(assignmentOperator) == assignmentOperators.end()) {
      // TODO: Proper error
      throw std::runtime_error("Invalid assignment operator provided.");
    }

    // TODO: Is UNKNOWN how we want to represent this? Maybe we should provide
    // std::optional<LexemeType>?
    if ((dataTypes.find(dataType) == dataTypes.end()) && (dataType != LexemeType::UNKNOWN)) {
      // TODO: Proper error
      throw std::runtime_error("Invalid data type provided.");
    }
  }

  virtual void acceptAstVisitor(AstVisitor &visitor) override {
    visitor.visitVariableAssignmentStatement(*this);
  };

  /*
   * Is this variable assignment definitely a declaration statement?
   * We only expect this to be the case where we have an explicit declaration
   * type, or a modifier word was provided.
   */
  bool isDeclaration() {
    return this->isMutable || this->isNullable || this->dataType != LexemeType::UNKNOWN;
  }
};

#endif
