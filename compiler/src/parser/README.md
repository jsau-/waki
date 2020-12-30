# Parser

The purpose of this module is to convert a set of tokens into an abstract
syntax tree which can be used in later stages of the compiler, eg. to convert
to bytecode or emit in some other target language.

## How it works

The tokenizer has generated us a list of tokens in the order the occur in the
source file.

Starting at the first token, we figure out what the tokens are actually trying
to do. This might be possible by just looking at the next token, or we might
have to look ahead indefinitely until we find something that can provide the
relevant context.

Some useful examples that might demonstrate this concept a bit better:

```waki
/*
 * Depending on our language grammar, the first token `doesCakeHaveFrosting`
 * being an identifier might be enough to tell us this is a variable assignment
 * statement. For the purpose of this example, let's say it does.
 *
 * Our second token is `=`, which we'd expect for a variable assignment
 * statement. If it weren't, we'd likely raise an error to indicate that
 * parsing failed.
 *
 * The third token is an integer literal, which tells us we're trying to do an
 * integer literal assignment.
 *
 * The fourth token tells us that the statement is over. We can
doesCakeHaveFrosting = 20;
```

## Key information

We don't care about program validity at this stage, just syntax validity. This
is an important distinction - it's not the parser's job for example to determine
whether a variable assignment is being provided with an invalid data type. We'll
validate the syntax tree at a later stage to check things like type correctness.

However, we do care if things are _syntactically_ wrong, eg. we tried to declare
a function using an integer literal as its name.

In terms of implementation there are two main sets of data we're working with
here - expressions and statements.

### Statements

At a high-level statements are effectively units of code that accomplish
something like assigning to a variable, or an `if/else` block.

### Expressions

Expressions are operations composed of identifiers, literal values, and
operators. Generally they resolve to some literal value.

eg. `x + 1`, or `!x`

Traditionally languages might permit standalone expressions to be statements.
I don't think I'll permit that in `waki`, because some examples tend to be
programmer error (eg. mis-typing `x + 1` instead of `x += 1`). This might mean
there are two different types of function calls, statement function calls and
expression function calls (the former where we chose to discard the return
type of the function; the latter being where we try to use it).
