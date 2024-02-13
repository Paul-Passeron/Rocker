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

## Example program:
Syntax may change
```OCaml
let fact n : int -> int => {
  match n => {
    -> 0 => 1
    -> 1 => 1
    -> _ => n * fact (n-1)
  }
}
```
```OCaml
let main void -> int => {
  let () => print "Hello, World !\n" in
  0
}
```
