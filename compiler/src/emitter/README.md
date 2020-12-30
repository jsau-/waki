# Emitter

After the parser has generated an abstract syntax tree for us, we're able to
emit it to different targets.

Our starting point will actually be `waki` source code. This should allow us to
easily diagnose issues with the AST generation without having to bake in tree
rendering to the CLI.
