#include "identifier_table.h"
#include "identifier_already_defined_error.h"
#include "identifier_undefined_error.h"

IdentifierTable::IdentifierTable() { this->identifiers = std::map<std::string, Identifier>(); }

void IdentifierTable::assertIdentifierDefined(std::string identifierName) {
  if (!this->isIdentifierDefined(identifierName)) {
    // TODO: Line numbers
    throw IdentifierUndefinedError(identifierName, 0, 0);
  }
}

void IdentifierTable::assertIdentifierUndefined(std::string identifierName) {
  if (this->isIdentifierDefined(identifierName)) {
    auto existingIdentifier = this->getIdentifierForName(identifierName);

    // TODO: Line numbers
    throw IdentifierAlreadyDefinedError(identifierName, 0, 0, existingIdentifier.lineDeclared,
                                        existingIdentifier.columnDeclared);
  }
}

Identifier IdentifierTable::defineIdentifier(std::string identifierName, LexemeType lexemeType,
                                             bool isMutable, bool isNullable, uint64_t lineDeclared,
                                             uint64_t columnDeclared) {
  this->assertIdentifierUndefined(identifierName);

  auto identifier =
    Identifier(identifierName, lexemeType, isMutable, isNullable, lineDeclared, columnDeclared);

  this->identifiers.emplace(identifierName, identifier);

  return identifier;
}

Identifier IdentifierTable::getIdentifierForName(std::string identifierName) {
  this->assertIdentifierDefined(identifierName);
  return this->identifiers.at(identifierName);
}

LexemeType IdentifierTable::getIdentifierType(std::string identifierName) {
  this->assertIdentifierDefined(identifierName);
  return this->identifiers.at(identifierName).type;
}

bool IdentifierTable::isIdentifierDefined(std::string identifierName) {
  return this->identifiers.find(identifierName) != this->identifiers.end();
}

bool IdentifierTable::isIdentifierOfKnownType(std::string identifierName) {
  auto identifier = this->getIdentifierForName(identifierName);
  return identifier.type != LexemeType::UNKNOWN;
}

bool IdentifierTable::isIdentifierMutable(std::string identifierName) {
  auto identifier = this->getIdentifierForName(identifierName);
  return identifier.isMutable;
}

bool IdentifierTable::isIdentifierNullable(std::string identifierName) {
  auto identifier = this->getIdentifierForName(identifierName);
  return identifier.isNullable;
}

void IdentifierTable::setIdentifierType(std::string identifierName, LexemeType type) {
  this->assertIdentifierDefined(identifierName);
  this->identifiers[identifierName].type = type;
}
