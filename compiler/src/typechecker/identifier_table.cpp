#include "identifier_table.h"
#include "identifier_already_defined_error.h"
#include "identifier_undefined_error.h"

IdentifierTable::IdentifierTable() { this->identifiers = std::map<std::string, Identifier>(); }

void IdentifierTable::assertIdentifierDefined(std::string identifierName, uint64_t line,
                                              uint64_t column) const {
  if (!this->isIdentifierDefined(identifierName)) {
    throw IdentifierUndefinedError(identifierName, line, column);
  }
}

void IdentifierTable::assertIdentifierUndefined(std::string identifierName, uint64_t line,
                                                uint64_t column) const {
  if (this->isIdentifierDefined(identifierName)) {
    auto existingIdentifier = this->getIdentifierForName(identifierName, line, column);

    throw IdentifierAlreadyDefinedError(identifierName, line, column,
                                        existingIdentifier.lineDeclared,
                                        existingIdentifier.columnDeclared);
  }
}

Identifier IdentifierTable::defineIdentifier(std::string identifierName, LexemeType lexemeType,
                                             bool isMutable, bool isNullable, uint64_t line,
                                             uint64_t column) {
  this->assertIdentifierUndefined(identifierName, line, column);

  auto identifier = Identifier(identifierName, lexemeType, isMutable, isNullable, line, column);

  this->identifiers.emplace(identifierName, identifier);

  return identifier;
}

Identifier IdentifierTable::getIdentifierForName(std::string identifierName, uint64_t line,
                                                 uint64_t column) const {
  this->assertIdentifierDefined(identifierName, line, column);
  return this->identifiers.at(identifierName);
}

LexemeType IdentifierTable::getIdentifierType(std::string identifierName, uint64_t line,
                                              uint64_t column) const {
  this->assertIdentifierDefined(identifierName, line, column);
  return this->identifiers.at(identifierName).type;
}

bool IdentifierTable::isIdentifierDefined(std::string identifierName) const {
  return this->identifiers.find(identifierName) != this->identifiers.end();
}

bool IdentifierTable::isIdentifierOfKnownType(std::string identifierName, uint64_t line,
                                              uint64_t column) const {
  auto identifier = this->getIdentifierForName(identifierName, line, column);
  return identifier.type != LexemeType::UNKNOWN;
}

bool IdentifierTable::isIdentifierMutable(std::string identifierName, uint64_t line,
                                          uint64_t column) const {
  auto identifier = this->getIdentifierForName(identifierName, line, column);
  return identifier.isMutable;
}

bool IdentifierTable::isIdentifierNullable(std::string identifierName, uint64_t line,
                                           uint64_t column) const {
  auto identifier = this->getIdentifierForName(identifierName, line, column);
  return identifier.isNullable;
}

void IdentifierTable::setIdentifierType(std::string identifierName, LexemeType type, uint64_t line,
                                        uint64_t column) {
  this->assertIdentifierDefined(identifierName, line, column);
  this->identifiers[identifierName].type = type;
}
