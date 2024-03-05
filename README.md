# Rocker Programming Langauge

Rocker is meant to be a compiled programming language, with aspects of imperative programming and modern features like pattern-matching

The memory management is occulted from the user, no pointers. This is in part thanks to the simple allocator library [RockerAlloc](https://github.com/Paul-Passeron/RockerAllocator.git)

## Features:
- user defined types
- pattern matching
- int literals
- char literals
- string literals
- memory safety

This language is transpiled to C for the moment

## Example code:

```
let main() : int => {
  print("Hello from Rocker!\n");
  return 0;
}
```

## Compilation
```
./rocker examples/hello_world.rkr
./a.out
```

## Usage:
```
Usage:
        ./rocker [flags] <input file> [output file]
Possible flags:
        '-t' or '--tmp'      :   Does not remove the temporary transpiled C files
        '-c' or '--transpile':   Only transpiles the Rocker to C but does not compile to a native executable
        '-l' or '--lexer'    :   Prints the tokens contained in the file and included files
        '-h' or '--help'     :   Displays this message
        '-v' or '--verbose'  :   Prints infos and commands ran by the compiler
```
## Progress
- [x] Simple rec and pro type generation
- [x] Simple Hello World example compiling and working
- [x] Simple recursion example compiling and working
- [x] Deprecate Tuples (using record types because all types are forward-declared)
- [x] Allow assignments
- [x] Accessing fields of record types
- [x] Add integer for loops 
- [x] Add while loops
- [x] Maybe add a dynamic array type -> Figure out syntax for pushing / poping
- [x] Use string views for lexemes (limit the ammount of allocated data)
- [x] Add including files support
- [x] Improve including files support
- [x] The Rocker version of the compiler can lex/tokenize itself
- [x] The Rocker version of the compiler can parse itself
- [x] Self-Hosting
- [x] Made exit memory-safe
## TODO
- [ ] Pattern matching product types
- [ ] Get type of an expression (for match cases)
- [ ] Generation of match expressions
- [ ] Typechecking
- [ ] Add foreach loop for array types
- [ ] Add variadic functions support
- [ ] Support multi-dim arrays
- [ ] Support accessing constructors without name binding
