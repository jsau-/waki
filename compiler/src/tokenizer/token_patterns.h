#ifndef waki_tokenizer_token_patterns
#define waki_tokenizer_token_patterns

#include <map>
#include <regex>

#include "./token_type.h"

/**
 * Non-exhaustive set of patterns that can be used to identify tokens. Note that
 * certain tokens will be omitted from the list if no relevant pattern could be
 * used to match them (eg. END_OF_FILE)
 */
const std::map<TokenType, std::regex> TOKEN_PATTERNS = {
    {TokenType::WHITESPACE, std::regex("\\s+")},
    {TokenType::SINGLE_LINE_COMMENT, std::regex("//.*")},

    /*
     * TODO: This is pretty dumb, and will trigger identifier declarations
     * containing these tokens, eg. `doubleInterval`. This is obviously not
     * something we want.
     */
    {TokenType::SIGNED_INTEGER_32, std::regex("int")},
    {TokenType::FLOAT, std::regex("float")},
    {TokenType::DOUBLE, std::regex("double")},
    {TokenType::BOOLEAN, std::regex("bool")},
    {TokenType::STRING, std::regex("string")},
    {TokenType::FUNCTION, std::regex("function")},
    {TokenType::FUNCTION_RETURNS, std::regex("returns")},
    {TokenType::RETURN, std::regex("return")},
    {TokenType::MUTABLE, std::regex("mutable")},
    {TokenType::NULLABLE, std::regex("nullable")},
    {TokenType::NAMESPACE, std::regex("namespace")},
    {TokenType::IMPORT, std::regex("#import")},

    {TokenType::NULL_LITERAL, std::regex("null")},
    {TokenType::FLOAT_LITERAL, std::regex("[+-]?([0-9]*[.])?[0-9]+f")},
    {TokenType::DOUBLE_LITERAL, std::regex("[+-]?([0-9]*[.])?[0-9]+d")},
    {TokenType::SIGNED_INTEGER_32_LITERAL, std::regex("[+-]?\\d+")},
    {TokenType::BOOLEAN_LITERAL, std::regex("true|false")},
    {TokenType::STRING_LITERAL, std::regex("'([^'\\\\]|\\\\.)*'")},

    {TokenType::EQUALS, std::regex("==")},
    {TokenType::LOGICAL_AND, std::regex("&&")},
    {TokenType::LOGICAL_OR, std::regex("\\|\\|")},
    {TokenType::BITWISE_AND, std::regex("&")},
    {TokenType::BITWISE_OR, std::regex("\\|")},
    {TokenType::BITWISE_XOR, std::regex("\\^")},
    {TokenType::BITWISE_NOT, std::regex("~")},
    {TokenType::BITWISE_SHIFT_LEFT, std::regex("<<")},
    {TokenType::BITWISE_SHIFT_RIGHT, std::regex(">>")},
    {TokenType::LESS_THAN_OR_EQUAL, std::regex("<=")},
    {TokenType::GREATER_THAN_OR_EQUAL, std::regex(">=")},
    {TokenType::LESS_THAN, std::regex("<")},
    {TokenType::GREATER_THAN, std::regex(">")},
    {TokenType::NULL_COALESCE, std::regex("\\?\\?")},
    {TokenType::TERNARY, std::regex("\\?")},
    {TokenType::TERNARY_FALLBACK, std::regex(":")},
    {TokenType::MULTIPLY_ASSIGN, std::regex("\\*=")},
    {TokenType::DIVIDE_ASSIGN, std::regex("\\/=")},
    {TokenType::ADD_ASSIGN, std::regex("\\+=")},
    {TokenType::SUBTRACT_ASSIGN, std::regex("-=")},
    {TokenType::ASSIGN_EQUALS, std::regex("=")},
    {TokenType::MULTIPLY, std::regex("\\*")},
    {TokenType::DIVIDE, std::regex("\\/")},
    {TokenType::ADD, std::regex("\\+")},
    {TokenType::SUBTRACT, std::regex("-")},

    {TokenType::OPEN_BRACE, std::regex("\\{")},
    {TokenType::CLOSE_BRACE, std::regex("\\}")},
    {TokenType::OPEN_PARENTHESIS, std::regex("\\(")},
    {TokenType::CLOSE_PARENTHESIS, std::regex("\\)")},

    {TokenType::END_OF_STATEMENT, std::regex(";")},

    {TokenType::IDENTIFIER, std::regex("[A-Za-z_]+")},
};

#endif
