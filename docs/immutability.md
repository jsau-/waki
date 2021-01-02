# Immutability

Unless explicitly instructed at declaration, variables will be immutable to
prevent modification. This includes variables declared in global or
function-level scope, as well as members of `struct`s.

This should allow us to implement optimisations like pass-by-reference for
struct types without an explicit `reference<MyStructType>`, or risking function
side-effects.

```waki
// Will throw a compilation error as foo is not mutable
int foo = 10;
foo = 20;

// Valid because bar is mutable
int bar = 10;
bar = 20;
```

A major benefit of this is preventing programmers from re-assigning function
parameters part-way through function bodies, making the identifier not clearly
reflect the current use-case for the variable.

Consider the following function which calculates the price of a cake:

```waki
function priceOfCake(int numLayers, bool hasFrosting) returns int {
  numLayers *= 10;

  if (hasFrosting) {
    numLayers += 20;
  }

  return numLayers;
}
```

While the above code will work, because we're modifying our parameter it's not
clear that we're actually calculating the price from it. A better alternative
might look more like:

```waki
function priceOfCake(int numLayers, bool hasFrosting) returns int {
  mutable int price = numLayers * 10;

  if (hasFrosting) {
    price += 20;
  }

  return price;
}
```
