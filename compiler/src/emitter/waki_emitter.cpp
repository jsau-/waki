#include "waki_emitter.h"

#include <stdexcept>

WakiEmitter::WakiEmitter(std::shared_ptr<BlockStatement> rootNode) {
  this->sourceStream = std::ostringstream();
  rootNode->acceptAstVisitor(*this);
}

void WakiEmitter::visitBoolLiteralExpression(BoolLiteralExpression& node) {
  this->sourceStream << (node.value ? "true" : "false");
}

void WakiEmitter::visitDoubleLiteralExpression(DoubleLiteralExpression& node) {
  this->sourceStream << std::to_string(node.value) << "d";
}

void WakiEmitter::visitFloatLiteralExpression(FloatLiteralExpression& node) {
  this->sourceStream << std::to_string(node.value) << "f";
}

void WakiEmitter::visitNullLiteralExpression() { this->sourceStream << "null"; }

void WakiEmitter::visitSignedInt32LiteralExpression(
    SignedInt32LiteralExpression& node) {
  this->sourceStream << std::to_string(node.value);
}

void WakiEmitter::visitStringLiteralExpression(StringLiteralExpression& node) {
  this->sourceStream << node.value;
}

void WakiEmitter::visitBlockStatement(BlockStatement& node) {
  for (auto const& statement : node.statements) {
    statement->acceptAstVisitor(*this);
  }
}

void WakiEmitter::visitVariableAssignmentStatement(
    VariableAssignmentStatement& node) {
  // TODO: Token definition should probably include this!
  switch (node.dataType) {
    case DataType::UNKNOWN:
      break;
    case DataType::BOOLEAN:
      this->sourceStream << "bool ";
      break;
    case DataType::DOUBLE:
      this->sourceStream << "double ";
      break;
    case DataType::FLOAT:
      this->sourceStream << "float ";
      break;
    case DataType::SIGNED_INTEGER_32:
      this->sourceStream << "int ";
      break;
    case DataType::STRING:
      this->sourceStream << "string ";
      break;
    default:
      throw std::runtime_error("Unexpected assignment operator");
  }

  this->sourceStream << node.identifier << " ";

  // TODO: Token definition should probably include this!
  switch (node.assignmentOperator) {
    case AssignmentOperator::ADD_ASSIGN:
      this->sourceStream << "+=";
      break;
    case AssignmentOperator::ASSIGN_EQUALS:
      this->sourceStream << "=";
      break;
    case AssignmentOperator::DIVIDE_ASSIGN:
      this->sourceStream << "/=";
      break;
    case AssignmentOperator::MULTIPLY_ASSIGN:
      this->sourceStream << "*=";
      break;
    case AssignmentOperator::SUBTRACT_ASSIGN:
      this->sourceStream << "-=";
      break;
    default:
      throw std::runtime_error("Unexpected assignment operator");
  }

  this->sourceStream << " ";

  node.expression->acceptAstVisitor(*this);

  this->sourceStream << ";\n";
}

std::string WakiEmitter::source() { return this->sourceStream.str(); }
