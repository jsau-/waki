# Nullability

Every primitive data-type can be marked as nullable.

By default all variables are *not* nullable, and attempting to assign the
`null` literal to them is a compilation error.

```waki
// Will default initialize to 0
mutable int myNonNullableInt;

// Will raise compilation error
myNonNullableInt = null;

// Will default initialize to null
nullable int myNullableInt;
```

Nullable values can be thought of as a super-set encompassing the non-nullables.
As a result we can, for example, provide non-nullable integers to functions
whose signature denotes their parameter _could_ be nullable.

```waki
int myNumCakeLayers = 10;

function<nullable int> priceOfCake(nullable int numCakeLayers) {
  if (numCakeLayers) {
    return numCakeLayers * 10;
  }

  return null;
}

price = priceOfCake(myNumCakeLayers);
```

Conversely, we _cannot_ provide a nullable value to a function whose signature
denotes their parameter _cannot_ be nullable.

```waki
nullable int myNumCakeLayers;

function priceOfCake(int numCakeLayers) returns int {
  return numCakeLayers * 10;
}

// Will throw a compilation error as `myNumCakeLayers` could be null.
price = priceOfCake(myNumCakeLayers);
```

As a result, it's the programmer's responsibility to coalesce nullable types
ahead-of-time.

```waki
nullable int myNumCakeLayers;

function priceOfCake(int numCakeLayers) returns int {
  return numCakeLayers * 10;
}

/*
 * Coalescing the nullable variable `myNumCakeLayers` will prevent a compilation
 * error.
 */
price = priceOfCake(myNumCakeLayers ?? 0);
```
