# Namespacing

All declarations made at the top-most scope level (i.e. outside of namespaces,
structs, or function blocks) are considered global.

Namespacing is a means to prevent collisions between identifiers, effectively
acting as a block of scope. This allows libraries to define identifiers which
are likely to collide with those added by the programmer.

For example, if we were writing a library `foo` we might enclose all our files
in a `foo` namespace, eg.

```waki
namespace foo {
  struct Vector3(int x, int y, int z) {
    int x = x;
    int y = y;
    int z = z;
  };
};
```

When using that in our program, we reference the struct using that namespace,
eg.

```waki
#import 'foo/vector3.waki';
myVec = foo.Vector3();
```
