#include "typechecker.h"
#include "../tokenizer/lexemes.h"
#include "identifier_undefined_error.h"
#include "mutability_violation_error.h"
#include "type_error.h"
#include "uninferrable_type_error.h"

Typechecker::Typechecker(std::shared_ptr<BlockStatement> ast) {
  this->ast = ast;
  this->identifierTable = IdentifierTable();
}

std::vector<std::shared_ptr<TypecheckerError>> Typechecker::check() {
  this->errors = {};
  this->visitBlockStatement(*ast);
  return this->errors;
}

void Typechecker::visitBinaryOperatorExpression(BinaryOperatorExpression &node) {
  node.lhs->acceptAstVisitor(*this);
  auto lhsType = this->latestVisitedType;

  node.rhs->acceptAstVisitor(*this);
  auto rhsType = this->latestVisitedType;

  auto operatorType = node.binaryOperator;
  auto metadataForOperator = Lexemes::getInstance().getMetadata().at(operatorType);

  if (metadataForOperator.isLogicalOperator()) {
    if (lhsType != LexemeType::BOOLEAN_LITERAL) {
      this->errors.push_back(std::make_shared<TypeError>(node.getLine(), node.getColumn(),
                                                         LexemeType::BOOLEAN_LITERAL, lhsType));
    }

    if (rhsType != LexemeType::BOOLEAN_LITERAL) {
      this->errors.push_back(std::make_shared<TypeError>(node.getLine(), node.getColumn(),
                                                         LexemeType::BOOLEAN_LITERAL, rhsType));
    }
  }

  if (lhsType != rhsType) {
    this->errors.push_back(
      std::make_shared<TypeError>(node.getLine(), node.getColumn(), lhsType, rhsType));
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
  try {
    this->latestVisitedType =
      this->identifierTable.getIdentifierType(node.identifier, node.getLine(), node.getColumn());
  } catch (const TypecheckerError &typecheckerError) {
    this->errors.push_back(std::make_shared<TypecheckerError>(typecheckerError));
  }
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

// TODO: Also check nullability of RHS - can't assign nullable int to int
void Typechecker::visitVariableAssignmentStatement(VariableAssignmentStatement &node) {
  try {
    auto lexemeMetadata = Lexemes::getInstance().getMetadata();

    auto hasIdentifierBeenDefined = this->identifierTable.isIdentifierDefined(node.identifier);

    /*
     * The lexeme is explicitly marked as a declaration, or it's the first time
     * we've encountered it (and hence we'll treat it as a declaration)
     */
    if (node.isDeclaration() || !hasIdentifierBeenDefined) {
      auto identifier =
        this->identifierTable.defineIdentifier(node.identifier, node.dataType, node.isMutable,
                                               node.isNullable, node.getLine(), node.getColumn());

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
      if (!this->identifierTable.isIdentifierOfKnownType(identifier.name, node.getLine(),
                                                         node.getColumn())) {
        if (lexemeMetadataForExpressionType.dataTypes.size() > 1) {
          this->errors.push_back(std::make_shared<UninferrableTypeError>(
            identifier.name, node.getLine(), node.getColumn(), expressionType));
        }

        // TODO: Logic duplicated below
        auto inferredIdentifierType = *lexemeMetadataForExpressionType.dataTypes.begin();

        auto areNullChecksViolated =
          LexemeType::NULL_LITERAL == expressionType && !identifier.isNullable;

        if (areNullChecksViolated) {
          this->errors.push_back(std::make_shared<TypeError>(
            node.getLine(), node.getColumn(), inferredIdentifierType, expressionType));
        }

        this->identifierTable.setIdentifierType(identifier.name, inferredIdentifierType,
                                                node.getLine(), node.getColumn());
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
          this->errors.push_back(std::make_shared<TypeError>(node.getLine(), node.getColumn(),
                                                             identifier.type, expressionType));
        }
      }
      /*
       * The variable is both not marked as a declaration, and we've got a record
       * of it existing in our identifier table. We need to evaluate the type of
       * its RHS expression and assert that it matches our stored type.
       */
    } else {
      auto existingIdentifier = this->identifierTable.getIdentifierForName(
        node.identifier, node.getLine(), node.getColumn());

      if (!this->identifierTable.isIdentifierMutable(existingIdentifier.name, node.getLine(),
                                                     node.getColumn())) {
        this->errors.push_back(std::make_shared<MutabilityViolationError>(
          existingIdentifier.name, node.getLine(), node.getColumn()));
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
        this->errors.push_back(std::make_shared<TypeError>(
          node.getLine(), node.getColumn(), existingIdentifier.type, expressionType));
      }
    }
  } catch (const TypecheckerError &typecheckerError) {
    this->errors.push_back(std::make_shared<TypecheckerError>(typecheckerError));
  }
}
