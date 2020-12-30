#ifndef waki_tokenizer_token_names
#define waki_tokenizer_token_names

#include <map>
#include <string>

#include "token_type.h"

const std::map<TokenType, std::string> TOKEN_NAMES = {
    {TokenType::WHITESPACE, "whitespace"},
    {TokenType::SINGLE_LINE_COMMENT, "single-line comment"},

    {TokenType::SIGNED_INTEGER_32, "signed 32-bit integer"},
    {TokenType::FLOAT, "float"},
    {TokenType::DOUBLE, "double"},
    {TokenType::BOOLEAN, "boolean"},
    {TokenType::STRING, "string"},
    {TokenType::FUNCTION, "function"},
    {TokenType::FUNCTION_RETURNS, "function return"},
    {TokenType::RETURN, "return"},
    {TokenType::MUTABLE, "mutable variable modifier"},
    {TokenType::NULLABLE, "nullable variable modifier"},
    {TokenType::NAMESPACE, "namespace"},
    {TokenType::IMPORT, "import"},

    {TokenType::NULL_LITERAL, "null literal"},
    {TokenType::FLOAT_LITERAL, "float literal"},
    {TokenType::DOUBLE_LITERAL, "double literal"},
    {TokenType::SIGNED_INTEGER_32_LITERAL, "signed 32-bit integer literal"},
    {TokenType::BOOLEAN_LITERAL, "boolean literal"},
    {TokenType::STRING_LITERAL, "string literal"},

    {TokenType::EQUALS, "=="},
    {TokenType::LOGICAL_AND, "&&"},
    {TokenType::LOGICAL_OR, "||"},
    {TokenType::BITWISE_AND, "&"},
    {TokenType::BITWISE_OR, "|"},
    {TokenType::BITWISE_XOR, "^"},
    {TokenType::BITWISE_NOT, "~"},
    {TokenType::BITWISE_SHIFT_LEFT, "<<"},
    {TokenType::BITWISE_SHIFT_RIGHT, ">>"},
    {TokenType::LESS_THAN_OR_EQUAL, "<="},
    {TokenType::GREATER_THAN_OR_EQUAL, ">="},
    {TokenType::LESS_THAN, "<"},
    {TokenType::GREATER_THAN, ">"},
    {TokenType::NULL_COALESCE, "??"},
    {TokenType::TERNARY, "?"},
    {TokenType::TERNARY_FALLBACK, ":"},
    {TokenType::MULTIPLY_ASSIGN, "*="},
    {TokenType::DIVIDE_ASSIGN, "/="},
    {TokenType::ADD_ASSIGN, "+="},
    {TokenType::SUBTRACT_ASSIGN, "-="},
    {TokenType::ASSIGN_EQUALS, "="},
    {TokenType::MULTIPLY, "*"},
    {TokenType::DIVIDE, "/"},
    {TokenType::ADD, "+"},
    {TokenType::SUBTRACT, "-"},

    {TokenType::OPEN_BRACE, "{"},
    {TokenType::CLOSE_BRACE, "}"},
    {TokenType::OPEN_PARENTHESIS, "("},
    {TokenType::CLOSE_PARENTHESIS, ")"},

    {TokenType::END_OF_STATEMENT, ";"},

    {TokenType::IDENTIFIER, "identifier"},
};

#endif
