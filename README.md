# Rocker Programming Langauge

Rocker is meant to be a compiled functionnal language, with some similarities with ML languages.

## Features:
- user defined types
- pattern matching
- int literals
- char literals
- string literals
- curryfication


Rocker is not a lazily evaluated language



## Implementation details
- The lexer was pretty straightforward, just matching strings known strings from longest to smallest
- The parser is going to be a recursive descent parser following the grammar in 'grammar.bnf'
- For the actual compilation: No idea at the moment