#include "lexeme_metadata.h"

LexemeMetadata::LexemeMetadata(std::string displayName, tl::optional<std::regex> pattern,
                               tl::optional<std::string> codeRepresentation, int flags,
                               tl::optional<LexemeType> literalType, std::set<LexemeType> dataTypes)
  : displayName(displayName), pattern(pattern), codeRepresentation(codeRepresentation),
    flags(flags), literalType(literalType), dataTypes(dataTypes) {
  if (this->isReservedKeyword() && !pattern.has_value()) {
    /*
     * NB: This check is required for the safety of lexemes.cpp when building
     * the set of reserved keywords.
     *
     * This warning has been left in lexemes.cpp - if changing, cleanup there
     * too!
     */
    // TODO: Proper error
    throw std::runtime_error("Reserved keyword with no matching pattern. No sensible way to "
                             "handle. Please define a code representation for this type.");
  }

  if (this->isDataType() && !literalType.has_value()) {
    // TODO: Proper error
    throw std::runtime_error("Attempting to define a data type with no corresponding literal "
                             "value type. Please provide a corresponding literal type.");
  }

  if (this->isLiteral() && dataTypes.size() == 0) {
    // TODO: Proper error
    throw std::runtime_error("Attempting to define a literal type with no corresponding data "
                             "value types. Please provide at least one corresponding data type.");
  }
}

bool LexemeMetadata::isSignificantToTokenize() const {
  return this->checkFlag(LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE);
}

bool LexemeMetadata::isDataType() const { return this->checkFlag(LEXEMEFLAG_DATA_TYPE); }

bool LexemeMetadata::isBinaryOperator() const {
  return this->checkFlag(LEXEMEFLAG_BINARY_OPERATOR);
}

bool LexemeMetadata::isLiteral() const { return this->checkFlag(LEXEMEFLAG_LITERAL); }

bool LexemeMetadata::isReservedKeyword() const {
  return this->checkFlag(LEXEMEFLAG_RESERVED_KEYWORD);
}

bool LexemeMetadata::isUnaryOperator() const { return this->checkFlag(LEXEMEFLAG_UNARY_OPERATOR); }

bool LexemeMetadata::isLogicalOperator() const {
  return this->checkFlag(LEXEMEFLAG_LOGICAL_OPERATOR);
}

bool LexemeMetadata::isAssignmentOperator() const {
  return this->checkFlag(LEXEMEFLAG_ASSIGNMENT_OPERATOR);
}

bool LexemeMetadata::isVariableModifier() const {
  return this->checkFlag(LEXEMEFLAG_VARIABLE_MODIFIER);
}

bool LexemeMetadata::isAssignableToLiteralType(LexemeType literalType) const {
  return this->literalType.has_value() && this->literalType.value() == literalType;
}

bool LexemeMetadata::isAssignableToDataType(LexemeType dataType) const {
  return this->dataTypes.find(dataType) != this->dataTypes.end();
}

bool LexemeMetadata::checkFlag(int flag) const { return (this->flags & flag) == flag; }
