#include "typechecker.h"
#include "../tokenizer/lexemes.h"
#include "identifier_undefined_error.h"
#include "type_error.h"

/*
 * TODO: Instead of throwing errors on failures, collect errors into an array,
 * eg. std::shared_ptr<TypecheckerError>[], and return that. Will allow us to
 * report on all type errors at once regardless of the number of issues. Much
 * easier to debug problems.
 */

Typechecker::Typechecker(std::shared_ptr<BlockStatement> ast) {
  this->ast = ast;
  this->identifierTable = IdentifierTable();
}

void Typechecker::check() { this->visitBlockStatement(*ast); }

// TODO: Certain binary operators will always return a fixed expression type,
// eg. &&
void Typechecker::visitBinaryOperatorExpression(BinaryOperatorExpression &node) {
  node.lhs->acceptAstVisitor(*this);
  auto lhsType = this->latestVisitedType;

  node.rhs->acceptAstVisitor(*this);
  auto rhsType = this->latestVisitedType;

  if (lhsType != rhsType) {
    // TODO: Line numbers
    throw TypeError(0, 0, lhsType, rhsType);
  }
}

void Typechecker::visitBoolLiteralExpression(BoolLiteralExpression &) {
  this->latestVisitedType = LexemeType::BOOLEAN_LITERAL;
}

void Typechecker::visitDoubleLiteralExpression(DoubleLiteralExpression &) {
  this->latestVisitedType = LexemeType::DOUBLE_LITERAL;
}

void Typechecker::visitFloatLiteralExpression(FloatLiteralExpression &) {
  this->latestVisitedType = LexemeType::FLOAT_LITERAL;
}

void Typechecker::visitIdentifierExpression(IdentifierExpression &node) {
  this->latestVisitedType = this->identifierTable.getIdentifierType(node.identifier);
}

void Typechecker::visitNullLiteralExpression() {
  this->latestVisitedType = LexemeType::NULL_LITERAL;
}

void Typechecker::visitSignedInt32LiteralExpression(SignedInt32LiteralExpression &) {
  this->latestVisitedType = LexemeType::SIGNED_INTEGER_32_LITERAL;
}

void Typechecker::visitStringLiteralExpression(StringLiteralExpression &) {
  this->latestVisitedType = LexemeType::STRING_LITERAL;
}

void Typechecker::visitBlockStatement(BlockStatement &node) {
  for (auto const &statement : node.statements) {
    statement->acceptAstVisitor(*this);
  }
}

void Typechecker::visitVariableAssignmentStatement(VariableAssignmentStatement &node) {
  auto lexemeMetadata = Lexemes::getInstance().getMetadata();

  auto hasIdentifierBeenDefined = this->identifierTable.isIdentifierDefined(node.identifier);

  /*
   * The lexeme is explicitly marked as a declaration, or it's the first time
   * we've encountered it (and hence we'll treat it as a declaration)
   */
  if (node.isDeclaration() || !hasIdentifierBeenDefined) {
    // TODO: Line numbers
    auto identifier = this->identifierTable.defineIdentifier(node.identifier, node.dataType,
                                                             node.isMutable, node.isNullable, 0, 0);

    /*
     * As part of a variable declaration, if no type were provided, eg. code
     * `foo = 10;` we need to infer it from
     */
    node.expression->acceptAstVisitor(*this);
    auto expressionType = this->latestVisitedType;
    auto lexemeMetadataForExpressionType = lexemeMetadata.at(expressionType);

    /*
     * If no explicit type were set on the identifier, we can safely just assign
     * it the corresponding literal type for the result of the RHS expression
     */
    if (!this->identifierTable.isIdentifierOfKnownType(identifier.name)) {
      if (lexemeMetadataForExpressionType.dataTypes.size() > 1) {
        // TODO: Proper error
        // TODO: When doing proper error, include information!
        throw std::runtime_error(
          "Unable to infer data type. Literal type XXX TODO XXX is assignable to multiple data "
          "types. You must define an explicit data type.");
      }

      auto inferredIdentifierType = *lexemeMetadataForExpressionType.dataTypes.begin();

      if (!this->identifierTable.isIdentifierNullable(identifier.name) &&
          LexemeType::NULL_LITERAL == expressionType) {
        // TODO: Proper error
        throw std::runtime_error(
          "Attempting to assign null literal to an identifier which is not nullable.");
      }

      this->identifierTable.setIdentifierType(identifier.name, inferredIdentifierType);
      /*
       * If an explicit type _were_ set on the identifier, we need to assert that
       * the RHS expression is assignable to its type.
       */
    } else {
      // TODO: Logic duplicated below
      auto isExpressionUnassignable =
        !lexemeMetadataForExpressionType.isAssignableToDataType(identifier.type);
      auto areNullChecksViolated =
        LexemeType::NULL_LITERAL == expressionType && !identifier.isNullable;

      if (isExpressionUnassignable || areNullChecksViolated) {
        throw TypeError(0, 0, identifier.type, expressionType);
      }
    }
    /*
     * The variable is both not marked as a declaration, and we've got a record
     * of it existing in our identifier table. We need to evaluate the type of
     * its RHS expression and assert that it matches our stored type.
     */
  } else {
    auto existingIdentifier = this->identifierTable.getIdentifierForName(node.identifier);

    if (!this->identifierTable.isIdentifierMutable(existingIdentifier.name)) {
      // TODO: Proper error
      throw std::runtime_error("Attempting to mutate a non-mutable identifier.");
    }

    auto lexemeMetadataForIdentifier = lexemeMetadata.at(existingIdentifier.type);

    node.expression->acceptAstVisitor(*this);
    auto expressionType = this->latestVisitedType;
    auto lexemeMetadataForExpression = lexemeMetadata.at(expressionType);

    auto isExpressionUnassignable =
      !lexemeMetadataForExpression.isAssignableToDataType(existingIdentifier.type);
    auto areNullChecksViolated =
      LexemeType::NULL_LITERAL == expressionType && !existingIdentifier.isNullable;

    if (isExpressionUnassignable || areNullChecksViolated) {
      throw TypeError(0, 0, existingIdentifier.type, expressionType);
    }
  }
}
