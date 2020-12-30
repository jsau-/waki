#ifndef waki_tokenizer_lexeme_metadata
#define waki_tokenizer_lexeme_metadata

#include <optional.h>

#include <regex>
#include <string>

#include "lexeme_flags.h"

/**
 * Metadata used to augment a known lexeme in the language.
 */
struct LexemeMetadata {
  /**
   * The display name for the lexeme. Useful for presenting error messages,
   * eg. `Expected identifier, but received function return.`
   *                   ^                    |______________|
   *                    \                     /
   *                      Lexeme display names
   */
  std::string displayName;

  /**
   * Regular expression used to recognize the lexeme in unparsed source code.
   * Useful to tokenize a given source file.
   */
  tl::optional<std::regex> pattern;

  /**
   * How the lexeme should be represented if written in valid waki code.
   * Useful when emitting waki from an existing abstract syntax tree.
   */
  tl::optional<std::string> codeRepresentation;

  /**
   * Flags applied to the lexeme to describe its behaviour. Used to easily
   * express multiple properties without requiring tens of parameters
   */
  int flags;

  /**
   * Is this lexeme significant enough that we should maintain it after
   * tokenization? Examples of lexemes that we might want to discard include
   * whitespace and comments.
   */
  bool isSignificantToTokenize() {
    return (this->flags & LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE) == LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE;
  };

  /**
   * Does this lexeme represent a data type? eg. `int`
   */
  bool isDataType() { return (this->flags & LEXEMEFLAG_DATA_TYPE) == LEXEMEFLAG_DATA_TYPE; };

  /**
   * Does this lexeme represent a binary operator? i.e. one with a left and
   * right operand.
   */
  bool isBinaryOperator() {
    return (this->flags & LEXEMEFLAG_BINARY_OPERATOR) == LEXEMEFLAG_BINARY_OPERATOR;
  };

  /**
   * Does this lexeme represent a reserved keyword?
   */
  bool isReservedKeyword() {
    return (this->flags & LEXEMEFLAG_RESERVED_KEYWORD) == LEXEMEFLAG_RESERVED_KEYWORD;
  }

  /**
   * Does this lexeme represent a unary operator? i.e. one with only a right
   * operand.
   */
  bool isUnaryOperator() {
    return (this->flags & LEXEMEFLAG_UNARY_OPERATOR) == LEXEMEFLAG_UNARY_OPERATOR;
  };

  /**
   * Does this lexeme represent an assignment operator? i.e. is it used to
   * assign the result of a right-hand-side expression to some variable?
   */
  bool isAssignmentOperator() {
    return (this->flags & LEXEMEFLAG_ASSIGNMENT_OPERATOR) == LEXEMEFLAG_ASSIGNMENT_OPERATOR;
  };

  /**
   * Does this lexeme in some way modify a variable declaration? eg. Does
   * it mark a variable as mutable?
   */
  bool isVariableModifier() {
    return (this->flags & LEXEMEFLAG_VARIABLE_MODIFIER) == LEXEMEFLAG_VARIABLE_MODIFIER;
  };

  LexemeMetadata(std::string displayName, tl::optional<std::regex> pattern = tl::nullopt,
                 tl::optional<std::string> codeRepresentation = tl::nullopt,
                 int flags = LEXEMEFLAG_NONE)
    : displayName(displayName), pattern(pattern), codeRepresentation(codeRepresentation),
      flags(flags) {}
};

#endif
