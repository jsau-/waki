#include <algorithm>
#include <regex>
#include <set>
#include <string>

#include "lexemes.h"

Lexemes::Lexemes() {
  this->metadata = std::map<LexemeType, LexemeMetadata>({
    /*
     * Syntactically unimportant values
     */

    {LexemeType::UNKNOWN, LexemeMetadata("unknown")},
    {LexemeType::WHITESPACE, LexemeMetadata("whitespace", std::regex("\\s+"))},
    {LexemeType::SINGLE_LINE_COMMENT, LexemeMetadata("single line comment", std::regex("//.*"))},

    {LexemeType::IDENTIFIER, LexemeMetadata("identifier", std::regex("[A-Za-z_]+"), tl::nullopt,
                                            LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},

    /*
     * Data types
     */

    {LexemeType::SIGNED_INTEGER_32,
     LexemeMetadata("signed 32-bit integer variable", std::regex("int"), "int",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                      LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::FLOAT, LexemeMetadata("floating point variable", std::regex("float"), "float",
                                       LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                         LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::DOUBLE, LexemeMetadata("double-precision variable", std::regex("double"), "double",
                                        LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                          LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::BOOLEAN, LexemeMetadata("boolean variable", std::regex("bool"), "bool",
                                         LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                           LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::STRING, LexemeMetadata("string variable", std::regex("string"), "string",
                                        LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_DATA_TYPE |
                                          LEXEMEFLAG_RESERVED_KEYWORD)},

    /*
     * Data type modifiers
     */

    {LexemeType::MUTABLE,
     LexemeMetadata("mutable modifier", std::regex("mutable"), "mutable",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_VARIABLE_MODIFIER |
                      LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::NULLABLE,
     LexemeMetadata("nullable modifier", std::regex("nullable"), "nullable",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_VARIABLE_MODIFIER |
                      LEXEMEFLAG_RESERVED_KEYWORD)},

    /*
     * Data type literal values
     */

    {LexemeType::NULL_LITERAL, LexemeMetadata("null literal", std::regex("null"), "null",
                                              LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE |
                                                LEXEMEFLAG_RESERVED_KEYWORD | LEXEMEFLAG_LITERAL)},
    {LexemeType::FLOAT_LITERAL,
     LexemeMetadata("floating point literal", std::regex("[+-]?([0-9]*[.])?[0-9]+f"), tl::nullopt,
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_LITERAL)},
    {LexemeType::DOUBLE_LITERAL,
     LexemeMetadata("double-precision literal", std::regex("[+-]?([0-9]*[.])?[0-9]+d"), tl::nullopt,
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_LITERAL)},
    {LexemeType::SIGNED_INTEGER_32_LITERAL,
     LexemeMetadata("signed 32-bit integer literal", std::regex("[+-]?\\d+"), tl::nullopt,
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_LITERAL)},
    {LexemeType::BOOLEAN_LITERAL,
     LexemeMetadata("boolean literal", std::regex("true|false"), tl::nullopt,
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_LITERAL)},
    {LexemeType::STRING_LITERAL,
     LexemeMetadata("string literal", std::regex("'([^'\\\\]|\\\\.)*'"), tl::nullopt,
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_LITERAL)},

    /*
     * Keywords
     */

    {LexemeType::FUNCTION,
     LexemeMetadata("function", std::regex("function"), "function",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::FUNCTION_RETURNS,
     LexemeMetadata("returns", std::regex("returns"), "returns",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::RETURN,
     LexemeMetadata("return", std::regex("return"), "return",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::NAMESPACE,
     LexemeMetadata("namespace", std::regex("namespace"), "namespace",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},
    {LexemeType::IMPORT,
     LexemeMetadata("import", std::regex("import"), "import",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_RESERVED_KEYWORD)},

    /*
     * Operators
     */

    {LexemeType::EQUALS,
     LexemeMetadata("equality", std::regex("=="),
                    "==", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::NOT_EQUALS,
     LexemeMetadata("inequality", std::regex("!="),
                    "!=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::LOGICAL_AND,
     LexemeMetadata("logical and", std::regex("&&"), "&&",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::LOGICAL_OR,
     LexemeMetadata("logical or", std::regex("\\|\\|"), "||",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::BITWISE_AND,
     LexemeMetadata("bitwise and", std::regex("&"), "&",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::BITWISE_OR,
     LexemeMetadata("bitwise or", std::regex("\\|"), "|",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::BITWISE_XOR,
     LexemeMetadata("bitwise xor", std::regex("\\^"), "^",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::BITWISE_SHIFT_LEFT,
     LexemeMetadata("bitwise shift left", std::regex("<<"), "<<",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::BITWISE_SHIFT_RIGHT,
     LexemeMetadata("bitwise shift right", std::regex(">>"), ">>",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::LESS_THAN_OR_EQUAL,
     LexemeMetadata("less than or equal", std::regex("<="),
                    "<=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::GREATER_THAN_OR_EQUAL,
     LexemeMetadata("greater than or equal", std::regex(">="),
                    ">=", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::LESS_THAN,
     LexemeMetadata("less than", std::regex("<"), "<",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::GREATER_THAN,
     LexemeMetadata("greater than", std::regex(">"), ">",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::NULL_COALESCE,
     LexemeMetadata("null coalesce", std::regex("\\?\\?"), "??",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},
    {LexemeType::TERNARY,
     LexemeMetadata("ternary", std::regex("\\?"), "?",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::TERNARY_FALLBACK,
     LexemeMetadata("ternary fallback", std::regex(":"), ":",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::MULTIPLY_ASSIGN,
     LexemeMetadata("multiplication assign", std::regex("\\*="), "*=",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                      LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
    {LexemeType::DIVIDE_ASSIGN,
     LexemeMetadata("divide assign", std::regex("\\/="), "/=",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                      LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
    {LexemeType::ADD_ASSIGN,
     LexemeMetadata("addition assign", std::regex("\\+="), "+=",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                      LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
    {LexemeType::SUBTRACT_ASSIGN,
     LexemeMetadata("subtraction assign", std::regex("-="), "-=",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR |
                      LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
    {LexemeType::ASSIGN_EQUALS,
     LexemeMetadata("equals", std::regex("="), "=",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_ASSIGNMENT_OPERATOR)},
    {LexemeType::MULTIPLY,
     LexemeMetadata("multiply", std::regex("\\*"), "*",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::DIVIDE,
     LexemeMetadata("divide", std::regex("\\/"), "/",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::ADD,
     LexemeMetadata("add", std::regex("\\+"), "+",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::SUBTRACT,
     LexemeMetadata("subtract", std::regex("-"), "-",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_BINARY_OPERATOR)},
    {LexemeType::NOT,
     LexemeMetadata("logical not", std::regex("!"), "!",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},
    {LexemeType::BITWISE_NOT,
     LexemeMetadata("bitwise not", std::regex("~"), "~",
                    LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE | LEXEMEFLAG_UNARY_OPERATOR)},

    /*
     * Syntax symbols
     */

    {LexemeType::OPEN_BRACE,
     LexemeMetadata("open brace", std::regex("\\{"), "{", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
    {LexemeType::CLOSE_BRACE,
     LexemeMetadata("open brace", std::regex("\\}"), "}", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
    {LexemeType::OPEN_PARENTHESIS, LexemeMetadata("open parenthesis", std::regex("\\("), "(",
                                                  LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
    {LexemeType::CLOSE_PARENTHESIS,
     LexemeMetadata("close brace", std::regex("\\)"), ")", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
    {LexemeType::END_OF_STATEMENT,
     LexemeMetadata("end of statement", std::regex(";"), ";", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
    {LexemeType::LIST_DELIMITER,
     LexemeMetadata("list delimiter", std::regex("\\,"), ",", LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE)},
  });

  this->assignmentOperators = std::set<LexemeType>();
  this->binaryOperators = std::set<LexemeType>();
  this->dataTypes = std::set<LexemeType>();
  this->literals = std::set<LexemeType>();
  this->reservedKeywords = std::map<std::string, LexemeType>();
  this->significantToTokenize = std::set<LexemeType>();
  this->unaryOperators = std::set<LexemeType>();
  this->variableModifiers = std::set<LexemeType>();

  for (auto iterator : this->metadata) {
    auto lexemeType = iterator.first;
    auto lexemeMetadata = iterator.second;

    if (lexemeMetadata.isAssignmentOperator()) {
      this->assignmentOperators.insert(lexemeType);
    }

    if (lexemeMetadata.isBinaryOperator()) {
      this->binaryOperators.insert(lexemeType);
    }

    if (lexemeMetadata.isDataType()) {
      this->dataTypes.insert(lexemeType);
    }

    if (lexemeMetadata.isLiteral()) {
      this->literals.insert(lexemeType);
    }

    if (lexemeMetadata.isReservedKeyword()) {
      if (this->reservedKeywords.find(lexemeMetadata.codeRepresentation.value_or("")) !=
          this->reservedKeywords.end()) {
        // TODO: Proper error
        throw std::runtime_error(
          "Attempting to reserve word multiple times. This likely indicates a copy-paste error.");
      }

      this->reservedKeywords.insert({lexemeMetadata.codeRepresentation.value_or(""), lexemeType});
    }

    if (lexemeMetadata.isSignificantToTokenize()) {
      this->significantToTokenize.insert(lexemeType);
    }

    if (lexemeMetadata.isUnaryOperator()) {
      this->unaryOperators.insert(lexemeType);
    }

    if (lexemeMetadata.isVariableModifier()) {
      this->variableModifiers.insert(lexemeType);
    }
  }
}

std::map<LexemeType, LexemeMetadata> Lexemes::getMetadata() { return this->metadata; }
std::set<LexemeType> Lexemes::getSignificantToTokenize() { return this->significantToTokenize; }
std::set<LexemeType> Lexemes::getDataTypes() { return this->dataTypes; }
std::set<LexemeType> Lexemes::getBinaryOperators() { return this->binaryOperators; }
std::set<LexemeType> Lexemes::getLiterals() { return this->literals; }
std::set<LexemeType> Lexemes::getUnaryOperators() { return this->unaryOperators; }
std::set<LexemeType> Lexemes::getAssignmentOperators() { return this->assignmentOperators; }
std::set<LexemeType> Lexemes::getVariableModifiers() { return this->variableModifiers; }
std::map<std::string, LexemeType> Lexemes::getReservedKeywords() { return this->reservedKeywords; }
