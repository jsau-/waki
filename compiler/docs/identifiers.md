# Identifiers

Identifiers are the names given to namespaces, structs, functions, or variables.

Identifiers must meet the following criteria (failing to do so will result in
a compilation error):

* Contain no whitespace
* Use only alphabetic characters or underscores (i.e. conform to regex
`[A-Za-z_]+`)

Additionally, it's invalid to re-define the same identifier at the same level
of scope, or any level of descendant scope.

```waki
int myIdentifier;

// Will throw compilation error - identifier has already been defined above.
int myIdentifier;

function myFunction (int foo) returns int {
  /*
   * Will throw compilation error - identifier has already been defined in an
   * upper scope.
   */
  int myIdentifier;
}
```
