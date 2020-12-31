#ifndef waki_tokenizer_lexeme_flags
#define waki_tokenizer_lexeme_flags

/*
 * A set of flags describing a given lexeme. Allows us to build collections of
 * different groups, like the set of all lexemes which are reserved keywords, or
 * the set of all lexemes which are data types.
 *
 * This kind of information is super useful when parsing tokens, 'cos it saves
 * us having to write out all possible lexemes that could match in a given
 * context.
 *
 * NB: The declarations made here are used as bitmask values in lexeme_metadata,
 * and lexemes. Make sure to keep all values strict powers of two, or this won't
 * work!
 */

// Nothing is significant about this lexeme
#define LEXEMEFLAG_NONE 0

/*
 * This lexeme is something the tokenizer should keep hold of to pass to the
 * parser
 */
#define LEXEMEFLAG_SIGNIFICANT_TO_TOKENIZE 1

// This lexeme represents a data type, eg. `int`
#define LEXEMEFLAG_DATA_TYPE 2

// This lexeme represents a binary operator
#define LEXEMEFLAG_BINARY_OPERATOR 4

// This lexeme represents a unary operator
#define LEXEMEFLAG_UNARY_OPERATOR 8

/*
 * This lexeme represents a logical operator, i.e. one which always returns a
 * boolean value.
 */
#define LEXEMEFLAG_LOGICAL_OPERATOR 16

// This lexeme represents an assignment operator
#define LEXEMEFLAG_ASSIGNMENT_OPERATOR 32

// This lexeme represents a variable modifier
#define LEXEMEFLAG_VARIABLE_MODIFIER 64

/*
 * This lexeme represents a reserved keyword, and hence the programmer should
 * not be allowed to declare an identifier with its name.
 */
#define LEXEMEFLAG_RESERVED_KEYWORD 128

// This lexeme represents a literal value of any data type
#define LEXEMEFLAG_LITERAL 256

#endif
