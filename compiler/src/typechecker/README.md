# Typechecker

The parser has generated us an abstract syntax tree representing the provided
source code. The typechecker is responsible for walking through that syntax
tree and raising any relevant type errors.

# How it works

The type of an expression generally boils down to recursively stepping through
it until we reach a terminal node, like an identifier or literal value. We can
then 
