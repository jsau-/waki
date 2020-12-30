#ifndef waki_tokenizer_lexemes
#define waki_tokenizer_lexemes

#include <map>
#include <set>
#include <string>

#include "lexeme_flags.h"
#include "lexeme_metadata.h"
#include "lexeme_type.h"

struct Lexemes {
  static Lexemes &getInstance() {
    static Lexemes instance;
    return instance;
  }

  std::map<LexemeType, LexemeMetadata> getMetadata();
  std::set<LexemeType> getSignificantToTokenize();
  std::set<LexemeType> getDataTypes();
  std::set<LexemeType> getBinaryOperators();
  std::set<LexemeType> getLiterals();
  std::set<LexemeType> getUnaryOperators();
  std::set<LexemeType> getAssignmentOperators();
  std::set<LexemeType> getVariableModifiers();
  std::map<std::string, LexemeType> getReservedKeywords();

protected:
  // A map between all known lexeme types and metadata describing them
  std::map<LexemeType, LexemeMetadata> metadata;

  /*
   * A set of all lexeme types that are significant to tokenize. Used in the
   * tokenizer to determine whether or not we should discard a match or keep
   * it for the abstract syntax tree.
   */
  std::set<LexemeType> significantToTokenize;

  /**
   * A set of all lexeme types that are data types. Used in the parser largely
   * to determine the type of a variable declaration.
   */
  std::set<LexemeType> dataTypes;

  /**
   * A set of all lexeme types that are binary operators. Used in the parser
   * largely to determine if we're currently evaluating a binary expression.
   */
  std::set<LexemeType> binaryOperators;

  /**
   * A set of all literal lexeme types. Used in the parser to determine if the
   * current token is a literal value.
   */
  std::set<LexemeType> literals;

  /**
   * A set of all lexeme types that are unary operators. Used in the parser
   * largely to determine if we're currently evaluating a unary expression.
   */
  std::set<LexemeType> unaryOperators;

  /**
   * A set of all assignment operators. Used in the parser largely to determine
   * validity of a variable assignment statement. (i.e. we expect one of these
   * characters to follow an identifier.)
   */
  std::set<LexemeType> assignmentOperators;

  /**
   * A set of all lexemes which are used to modify a variable as part of a
   * variable declaration statement.
   */
  std::set<LexemeType> variableModifiers;

  /**
   * A set of all lexemes which are reserved keywords. In the case an
   * identifier matches one of these values in the tokenizer, the reserved
   * keyword should be returned instead (to prevent the programmer from trying
   * to re-assign something we've marked as reserved).
   */
  std::map<std::string, LexemeType> reservedKeywords;

private:
  Lexemes();
};

#endif
