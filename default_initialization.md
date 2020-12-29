# Default initialization

Every primitive data-type will be default initialized to some sensible base
value. This is to prevent having to explicitly define a base value for all
variable declarations which are not null.

In the case the variable is nullable, it will always be defaulted to null.

In the case the variable is not nullable, the following table denotes the
default values.

| Data Type | Default Value | Description |
| --- | --- | --- |
int | 0 | Integer literal 0 |
float | 0.0f | Float literal 0 |
double | 0.0d | Double literal 0 |
string | '' | Empty string |
bool | false | Boolean literal false |
