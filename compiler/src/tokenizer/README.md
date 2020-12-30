# Tokenizer

The purpose of this module is to convert a raw text input into a set of tokens
which can then be used by the parser to create an abstract syntax tree
representing the program.

## Definitions

### Lexemes

We define a lexeme as the fundamental of syntax in the language. A lexeme
might be constant (eg. the word `int` meaning "integer variable"), or it might
be described by a pattern (eg. an integer literal being defined as a series of
digits).

Lexemes are the things that the language is made up of, and some or all of them
might appear in a given program.

The set of all lexemes in the language is defined in `lexemes.cpp`.

#### Tokens

Tokens are concrete occurences of lexemes. They happened in the provided source
code at a given line and column number, and they had some text content that the
tokenizer used to identify them.

The tokens we find in the source code are what we'll provide to the parser,
which will build an abstract syntax tree describing the program.

## How it works

Starting at the beginning of our source text, we try matching all known token
patterns until we have our first viable match.

After that we start seeking forward again, this time starting just after our
most recent match.

If we encounter a block we have no idea how to parse, we throw an error.

## Key information

* We don't care about program validity at this stage. Verifying correctness
of the grammar will be handled by the parser. Verifying correctness of
types and their usages will be handled by the type-checker.
* The output of this module will exclude syntactically irrevelant tokens like
whitespace or comments, as these aren't required by the parser to generate an
abstract syntax tree. (I might re-visit this if I decide to use a parse tree
instead, to preserve comments when transpiling to different target languages.)
