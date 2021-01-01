#ifndef waki_tokenizer_lexeme_metadata
#define waki_tokenizer_lexeme_metadata

#include <optional.h>

#include <regex>
#include <set>
#include <string>

#include "lexeme_flags.h"
#include "lexeme_type.h"

/**
 * Metadata used to augment a known lexeme in the language.
 */
struct LexemeMetadata {
  LexemeMetadata(std::string displayName, tl::optional<std::regex> pattern = tl::nullopt,
                 tl::optional<std::string> codeRepresentation = tl::nullopt,
                 int flags = LEXEMEFLAG_NONE, tl::optional<LexemeType> literalType = tl::nullopt,
                 std::set<LexemeType> dataTypes = {});

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
   * If this lexeme is a data type, the literal type it corresponds to.
   */
  tl::optional<LexemeType> literalType;

  /**
   * If this lexeme is a literal type, the set of data types it can be
   * used for.
   */
  std::set<LexemeType> dataTypes;

  /**
   * Is this lexeme significant enough that we should maintain it after
   * tokenization? Examples of lexemes that we might want to discard include
   * whitespace and comments.
   */
  bool isSignificantToTokenize() const;

  /**
   * Does this lexeme represent a data type? eg. `int`
   */
  bool isDataType() const;

  /**
   * Does this lexeme represent a binary operator? i.e. one with a left and
   * right operand.
   */
  bool isBinaryOperator() const;

  /**
   * Is this lexeme a literal value?
   */
  bool isLiteral() const;

  /**
   * Does this lexeme represent a reserved keyword that we want to restrict
   * other lexemes (or identifiers in source code) from being able to use?
   *
   * Of major use in the tokenizer to handle the case where our identifier
   * lexeme overzealously tries to match one of our internal keywords.
   */
  bool isReservedKeyword() const;

  /**
   * Does this lexeme represent a unary operator? i.e. one with only a right
   * operand.
   */
  bool isUnaryOperator() const;

  /**
   * Does this lexeme represent a logical operator? i.e. one which always
   * returns boolean
   */
  bool isLogicalOperator() const;

  /**
   * Does this lexeme represent an assignment operator? i.e. is it used to
   * assign the result of a right-hand-side expression to some variable?
   */
  bool isAssignmentOperator() const;

  /**
   * Does this lexeme in some way modify a variable declaration? eg. Does
   * it mark a variable as mutable?
   */
  bool isVariableModifier() const;

  /**
   * Is this lexeme assignable to a given literal type? This lexeme is a data
   * type, and that data type can hold a literal value of the provided type.
   *
   * eg. Bool variable can hold a bool literal.
   *
   * TODO: I'm pretty sure this and related code in lexemes.cpp can be removed
   */
  bool isAssignableToLiteralType(LexemeType literalType) const;

  /**
   * Is this lexeme assignable to a given data type? i.e. This lexeme is a
   * literal value, and that literal type can be assigned to the given lexeme.
   *
   * eg. Bool literal is assignable to bool
   */
  bool isAssignableToDataType(LexemeType dataType) const;

private:
  bool checkFlag(int flag) const;
};

#endif
