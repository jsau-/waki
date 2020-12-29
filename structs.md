# Structs

Structs are a data type for storing variables, or function declarations.

```waki
struct Foo {
  int bar;
  int baz;
  function getSum() returns int {
    return bar + baz;
  }
}
```

Default values for members can be defined as part of the struct. Any
instantiated instance will have these default values.

```waki
struct Foo {
  int bar = 10;
  int baz = 20;
}

Foo myFoo = Foo();
```

Structs can declare parameters that can be provided at instantiation time.
This is similar to constructors in C-like languages, except without the
requirement to write a specific constructor function.

```waki
struct Foo (int bar, int baz) {
  int bar = bar;
  int baz = baz;
}

Foo myFoo = Foo(10, 20);
```
