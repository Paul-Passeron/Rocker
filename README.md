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
// Simple function definition

let main() : int => {
  print("Hello from Rocker!\n");
  return 0;
}
```

## TODO
- [x] Simple rec and pro type generation
- [x] Simple Hello World example compiling and working
- [x] Simple recursion example compiling and working
- [x] Deprecate Tuples (using record types because all types are forward-declared)
- [x] Allow assignments
- [x] Accessing fields of record types
- [ ] Pattern matching product types
- [ ] Get type of an expression (for match cases)
- [ ] Generation of match expressions
- [ ] Typechecking
- [x] Add integer for loops 
- [x] Add while loops 
- [ ] Add foreach loop for array types
- [ ] Maybe add a dynamic array type -> Figure out syntax for pushing / poping
- [x] Add including files support
- [ ] Improve including files support
- [ ] Self-Hosting
