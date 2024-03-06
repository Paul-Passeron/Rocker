# Rocker Programming Langauge

Rocker is meant to be a compiled programming language, with aspects of imperative programming and modern features like pattern-matching

The memory management is occulted from the user, no pointers. This is in part thanks to the simple allocator library [RockerAlloc](https://github.com/Paul-Passeron/RockerAllocator.git)

## Features (Goal):
- user defined types
- pattern matching
- int literals
- char literals
- string literals
- memory safety

This language is transpiled to C for the moment

## Example code:

```
let main() : void => {
  print("Hello from Rocker!\n");
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
        '-o' or '--output'    :  Sets the output path of the executable and of the transpiled C file
        '-t' or '--tmp'       :  Does not remove the temporary transpiled C files
        '-c' or '--transpile' :  Only transpiles the Rocker to C but does not compile to a native executable
        '-l' or '--lexer'     :  Prints the tokens contained in the file and included files
        '-h' or '--help'      :  Displays this message
        '-v' or '--verbose'   :  Prints infos and commands ran by the compiler
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
- [x] Typechecking
- [x] Add foreach loop for array types (iter loop)
## TODO
- [ ] Pattern matching product types
- [ ] Get type of an expression (for match cases)
- [ ] Generation of match expressions
- [ ] Add variadic functions support
- [ ] Support multi-dim arrays
- [ ] Support accessing constructors without name binding
- [ ] Mark and sweep garbage collector
- [ ] Add '=' support for comparison between strings (s1 = s2 <=> streq(s1, s2)) 

## Warning
The C version of the compiler is not actively maintained, only the rocker one is.
The reason for that is that there is a bootstrapper compiler that can compile the current rocker compiler and that it is simpler to write the compiler in Rocker rather than in C. 
