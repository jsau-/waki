#ifndef waki_typechecker_identifier
#define waki_typechecker_identifier

#include <string>

#include "../tokenizer/lexeme_type.h"

/**
 * An instance of an identifier that occurred as part of the abstract syntax
 * tree. Used to track the original declaration types of identifiers and
 * their types.
 */
struct Identifier {
  // The identifier's name
  std::string name;

  // The type of the identifier (either declared, or inferred from some
  // expression)
  LexemeType type;

  // Is the identifier mutable?
  bool isMutable;

  // Is the identifier nullable?
  bool isNullable;

  // The line the identifier was declared at
  uint64_t lineDeclared;

  // The column the identifier was declared at
  uint64_t columnDeclared;

  Identifier(std::string name = "", LexemeType type = LexemeType::UNKNOWN, bool isMutable = false, bool isNullable = false, uint64_t lineDeclared = 0, uint64_t columnDeclared = 0)
    : name(name), type(type), isMutable(isMutable), isNullable(isNullable), lineDeclared(lineDeclared), columnDeclared(columnDeclared) {}
};

#endif
