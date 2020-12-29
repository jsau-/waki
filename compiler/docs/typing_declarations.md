# Typing declarations

All variables are required to have known types at compilation-time for
correctness-checking.

Explicity type declarations can be omitted if the type can be inferred from an
immediate assignment.

eg.

```waki
// Type can be inferred as integer from right-hand-side immediate assignment.
myVariable = 10;

// No immediate assignment, so type must be explicitly declared.
int myVariable;

/*
 * If desired, an explicit type can be provided even with right-hand-side
 * immediate assignment. This might be desirable if you want to track
 * type-errors as close to declarations as possible when refactoring. Without
 * this the type error would be noted as happening wherever this variable was
 * next used incorrectly.
 */
int myVariable = 10;
```
