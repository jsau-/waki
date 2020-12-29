# Imports

Other script files can be imported using the following syntax:

```waki
#import '[path_to_script]';
```

eg.

```waki
#import './examples/namespace.waki`;
```

Imports must be performed at the start of a script file. If any significant
(i.e. non-comment) code is found before an import statement, a compilation error
will be raised.

All declarations made in imported scripts will then be available within the
current script. This includes namespaces, functions, struct declarations, and
variables. As a result, it may be advisable to namespace declarations
appropriately to prevent collisions between declarations.

In practical terms, think of importing another script as effectively just
copying its content to the top of your current source file.
