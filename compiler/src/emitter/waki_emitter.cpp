#include "waki_emitter.h"

#include <stdexcept>

#include "../tokenizer/lexeme_type.h"
#include "../tokenizer/lexemes.h"

WakiEmitter::WakiEmitter(std::shared_ptr<BlockStatement> rootNode) {
  this->sourceStream = std::ostringstream();
  rootNode->acceptAstVisitor(*this);
}

void WakiEmitter::visitBinaryOperatorExpression(BinaryOperatorExpression &node) {
  auto lexemeMetadata = Lexemes::getInstance().getMetadata();

  this->sourceStream << "(";

  node.lhs->acceptAstVisitor(*this);

  this->sourceStream << " "
                     << lexemeMetadata.at(node.binaryOperator).codeRepresentation.value_or("")
                     << " ";

  node.rhs->acceptAstVisitor(*this);

  this->sourceStream << ")";
}

void WakiEmitter::visitBoolLiteralExpression(BoolLiteralExpression &node) {
  this->sourceStream << (node.value ? "true" : "false");
}

void WakiEmitter::visitDoubleLiteralExpression(DoubleLiteralExpression &node) {
  this->sourceStream << std::to_string(node.value) << "d";
}

void WakiEmitter::visitFloatLiteralExpression(FloatLiteralExpression &node) {
  this->sourceStream << std::to_string(node.value) << "f";
}

void WakiEmitter::visitIdentifierExpression(IdentifierExpression &node) {
  this->sourceStream << node.identifier;
}

void WakiEmitter::visitNullLiteralExpression() {
  auto lexemesMetadata = Lexemes::getInstance().getMetadata();
  this->sourceStream
    << lexemesMetadata.at(LexemeType::NULL_LITERAL).codeRepresentation.value_or("");
}

void WakiEmitter::visitSignedInt32LiteralExpression(SignedInt32LiteralExpression &node) {
  this->sourceStream << std::to_string(node.value);
}

void WakiEmitter::visitStringLiteralExpression(StringLiteralExpression &node) {
  this->sourceStream << node.value;
}

void WakiEmitter::visitBlockStatement(BlockStatement &node) {
  for (auto const &statement : node.statements) {
    statement->acceptAstVisitor(*this);
  }
}

void WakiEmitter::visitConditionalStatement(ConditionalStatement &node) {
  auto lexemesMetadata = Lexemes::getInstance().getMetadata();

  // TODO: I think we should refactor out writing a given LexemeType to a member
  // func - we repeat this value_or stuff quite a lot and it's kinda
  // boilerplate-y
  this->sourceStream
    << lexemesMetadata.at(LexemeType::IF).codeRepresentation.value_or("") << " "
    << lexemesMetadata.at(LexemeType::OPEN_PARENTHESIS).codeRepresentation.value_or("");

  // Write if expression
  std::get<0>(node.ifBlock)->acceptAstVisitor(*this);

  this->sourceStream
    << lexemesMetadata.at(LexemeType::CLOSE_PARENTHESIS).codeRepresentation.value_or("") << " "
    << lexemesMetadata.at(LexemeType::OPEN_BRACE).codeRepresentation.value_or("")
    << std::endl;

  // Write if block
  std::get<1>(node.ifBlock)->acceptAstVisitor(*this);

  this->sourceStream << lexemesMetadata.at(LexemeType::CLOSE_BRACE).codeRepresentation.value_or("")
    << lexemesMetadata.at(LexemeType::END_OF_STATEMENT).codeRepresentation.value_or("")
    << std::endl;
}

void WakiEmitter::visitVariableAssignmentStatement(VariableAssignmentStatement &node) {
  auto lexemesMetadata = Lexemes::getInstance().getMetadata();

  if (node.isMutable) {
    this->sourceStream << lexemesMetadata.at(LexemeType::MUTABLE).codeRepresentation.value_or("")
                       << " ";
  }

  if (node.isNullable) {
    this->sourceStream << lexemesMetadata.at(LexemeType::NULLABLE).codeRepresentation.value_or("")
                       << " ";
  }

  if (lexemesMetadata.at(node.dataType).codeRepresentation.has_value()) {
    this->sourceStream << lexemesMetadata.at(node.dataType).codeRepresentation.value_or("") << " ";
  }

  this->sourceStream << node.identifier << " "
                     << lexemesMetadata.at(node.assignmentOperator).codeRepresentation.value_or("")
                     << " ";

  node.expression->acceptAstVisitor(*this);

  this->sourceStream << ";\n";
}

std::string WakiEmitter::source() { return this->sourceStream.str(); }
