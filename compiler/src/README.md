# Compiler

Compiler for `waki` source code.

## Phases

The process of compiling `waki` can be reduced to the following chronological
steps:

### Tokenize

For the given source code, split it into tokens (atomic units of programming
code), eg. the word `int` denoting we're about to declare an integer variable.

### Parse

For an ordered set of tokens, generate an abstract syntax tree representing the
program.

(This might be extended to include an optimizer, eg. performing dead-code
elimination, or simplifying compile-time constants. Right now we'll likely
just be )

### Type-check

For a given abstract syntax tree, step through it and ensure all typings are
correct (i.e. all function calls are to defined functions; all variables are
assigned the correct types, etc.).

### Bytecode generation

For a given abstract syntax tree, generate some intermediate representation of
the code. This is likely to be LLVM.
