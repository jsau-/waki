# Comments

All content contained within comments will be ignored by the compiler.

## Single-line comments

Single line comments can be started using `//`, and will terminate at the end
of the line.

```waki
// This is a single-line comment!
```

## Multi-line comments

Multi-line comments can be started using `/*`, and must be terminated by a
matching `*/` (failing to match will result in a compilation error). Nested
multi-line comments are not permitted.

```waki
/*
 * This is a multi-line comment.
 */
```
