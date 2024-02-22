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
  print "Hello from Rocker!\n";
  return 0;
}

// Recursive function definition and simple case of pattern matching
let factorial (n: int) : int => {
  match n => {
    -> 0 => return 1;
    -> 1 => return 1;
    -> _ => return n * fact(n-1);
  }
}

// record type definition (struct)
rec rec_int_list_t => {
  Val: int,
  Next: int_list_t,
}

// product type definition
pro pro_int_list_t => {
  Cons : int * pro_int_list_t,
  None,
}


// Pattern matching user defined types

let print_list (list: pro_int_list_t): void => {
  match list => {
    -> Cons::(a, rest) => {
      print_int a;
      print " ";
      print_list(rest);
    }
    -> None => {}
  }
}
```

## TODO
- [x] Simple rec and pro type generation
- [x] Simple Hello World example compiling and working
- [x] Simple recursion example compiling and working
- [ ] Allow assignments
- [ ] Accessing fields of record types
- [ ] Get type of an expression (for match cases)
- [ ] Generation of match expressions
- [ ] Handle tuple types
- [ ] Typechecking
- [ ] Add loops (while and for, maybe foreach for array types)
- [ ] Maybe add a dynamic array type -> Figure out syntax for pushing / poping
- [ ] Add including files support