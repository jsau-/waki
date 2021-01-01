#ifndef waki_typechecker_identifier_table
#define waki_typechecker_identifier_table

#include <map>
#include <string>

#include "../tokenizer/lexeme_type.h"
#include "identifier.h"

/**
 * A table containing all identifiers found in the abstract syntax tree. Used
 * when walking the syntax tree to check if an identifier is actually currently
 * defined, and if so if it's of a valid type.
 */
struct IdentifierTable {
  IdentifierTable();

  // Define a found identifier in the AST
  Identifier defineIdentifier(std::string identifierName, LexemeType lexemeType, bool isMutable, bool isNullable, uint64_t line, uint64_t column);

  // Gets the datastructure representing an identifier for a given name.
  Identifier getIdentifierForName(std::string identifierName, uint64_t line, uint64_t column);

  // Gets the type of an identifier
  LexemeType getIdentifierType(std::string identifierName, uint64_t line, uint64_t column);

  // Gets if an identifier with a given name is actually defined
  bool isIdentifierDefined(std::string identifierName);

  // Is the identifier of a known type? Used to determine if we should
  // over-write based on
  bool isIdentifierOfKnownType(std::string identifierName, uint64_t line, uint64_t column);

  // Is the identifier mutable?
  bool isIdentifierMutable(std::string identifierName, uint64_t line, uint64_t column);

  // Is the identifier nullable?
  bool isIdentifierNullable(std::string identifierName, uint64_t line, uint64_t column);

  // Set the type of an identifier
  void setIdentifierType(std::string identifierName, LexemeType type, uint64_t line, uint64_t column);

private:
  void assertIdentifierDefined(std::string identifierName, uint64_t line, uint64_t column);
  void assertIdentifierUndefined(std::string IdentifierName, uint64_t line, uint64_t column);

  std::map<std::string, Identifier> identifiers;
};

#endif
