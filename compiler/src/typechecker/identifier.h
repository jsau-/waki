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

  // The line the identifier was declared at
  uint64_t lineDeclared;

  // The column the identifier was declared at
  uint64_t columnDeclared;

  Identifier(std::string name = "", LexemeType type = LexemeType::UNKNOWN, bool isMutable = false,
             uint64_t lineDeclared = 0, uint64_t columnDeclared = 0)
    : name(name), type(type), isMutable(isMutable), lineDeclared(lineDeclared),
      columnDeclared(columnDeclared) {}

  bool operator==(const Identifier &rhs) const;
};

#endif
