# Tests

Test for the Waki compiler. This project uses
[Catch2 v2](https://github.com/catchorg/Catch2/blob/v2.x/docs/).

The directory structure should mirror that of the main `src` directory to make
jumping between files easy!

## Running the test suite

A normal compile of the application generates an executable in
`build/test/wakitest` (relative to the project root directory). Running that
executable will show test output for all registered test files.

## Writing a test file

The basic template for a test file looks like:

```cpp
#include <catch2.h>

TEST_CASE("Test case name", "[File name]") { REQUIRE(1 == 0); }
```

For more details about using Catch2 see
https://github.com/catchorg/Catch2/blob/v2.x/docs/.
