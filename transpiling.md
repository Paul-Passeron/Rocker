# Transpiling rules


## Prologue:
The C program starts with essential typedefs (string type, print funcction):
```C
#include <stdio.h>

typedef struct string {
    char *s;
    int length;
} string;

void print(string s){
    for(int i = 0; i < s.length; i++)
        putchar(s.s[i]);
}
```

## Type definition

Note: for the moment, Types cannot be recursive


### Record Types:
```
rec type_name => {
    Constructor1: type1,
    Constructor2: type2 -> type3,
    Constructor2: type4 -> type5 -> type6,
    ... 
}
```
Becomes
```C
typedef struct type_name {
    type1 Constructor1;
    type3 (*Constructor2(type2));
    type6 (*Constructor2(type4, type5));
    ...
} type_name;
```

### Product Types:
```
pro type_name => {
    Constructor1: type1,
    Constructor2: type2 -> type3,
    Constructor2: type4 -> type5 -> type6,
    ... 
}
```
Becomes
```C
typedef struct type_name {
    enum tag_type_name {
        Constructor1,
        Constructor2,
        Constructor3,
        ...
    } tag_type_name;

    union data_type_name {
        type1 Constructor1;
        type3 (*Constructor2(type2));
        type6 (*Constructor2(type4, type5));
        ...
    } data_type_name;
} type_name;
```

## Let bindings

### Simple funcction definition

```
let main : void -> int => {
    let () => print "Hello, World !\n" in
    0
}
```
Becomes
```C
int main(void){
    print((string){.s="Hello, World !\n", .length = 16});
    return 0;
}
```

### Simple variable definition
```
let main : void -> int => {
    let msg: string => "Hello, World !\n" in
    let () => print "Hello, World !\n" in
    0
}
```
Becomes
```C
int main(void){
    string msg = (string){.s="Hello, World !\n", .length = 16};
    print(msg);
    return 0;
}
```
<!-- 

```
let outer name : string -> void -> void => {
    let msg: string => "Hey " in
    let () => print "Producing inner funcction with name: " in
    let () => print name in
    let () => print "\n" in
    let inner: void -> void => {
        let () => print msg in
        let () => print name in
        print " !\n"
    } in
    inner
}

let func : void -> void => {outer "Paul"} in

let main : void -> int =>{
    let () => func () in
    0
}

```
Becomes
```C
struct outer_inner_closure
{
    string name;
    string msg;
};
typedef void (*ptr)(struct outer_inner_closure);

void inner(const struct outer_inner_closure closure)
{
    print(closure.msg);
    print(closure.name);
    return print((string){.s = " !\n", .length = 3});
}

ptr outer(struct outer_inner_closure *closure, string name)
{
    string msg = (string){.s = "Hey ", .length = 4};
    printf("Producing inner funcction with name: ");
    print(name);
    printf("\n");

    closure->msg = msg;
    closure->name = name;

    return &inner;
}

void func(void){

    struct outer_inner_closure tmp1;
    ptr func_implementation = outer(&tmp1, (string){.s = "Paul", .length = 4});
    func_implementation(tmp1);
}

int main(void){
    func();
    return 0;
}
``` -->
Where the inner funcction def would be in the outer funcction, we create the closure


We redefine the closure every-time but I don't think it's an issue as rocker is purely funcctionnal without side effects so the closure will essentially be constant

Name mangling will be necessary for funcctions that are defined in another scope in rocker but have the same name (they will end up in the same scope after C transpiling)



## Example

Rocker program:

```OCaml
let outer name : string -> void -> void => {
    let msg: string => "Hey " in
    let () => print "Producing inner funcction with name: " in
    let () => print name in
    let () => print "\n" in
    let inner : void -> void => {
        let () => print msg in
        let () => print name in
        print " !\n"
    } in
    inner
}

let func : void -> void => {
    outer "Paul"
}

let main : void -> int => {
    let () => print "Hello, World !\n" in
    let func2 : void -> void => outer "Marie" in
    let () => func () in
    let () => func () in
    let () => func2 () in
    let () => func2 () in
    0
}
```
Will translate to
```C
#include <stdio.h>

typedef struct string {
  char *s;
  int length;
} string;

void print(string s) {
  for (int i = 0; i < s.length; i++)
    putchar(s.s[i]);
}

typedef struct outer_closure {
  string name;
  string msg;
  char __closure__;
} outer_closure;

typedef struct main_closure {
  char __closure__;
} main_closure;

string s;

typedef struct global_closure {
  string s;
  char __closure__;
} global_closure;

typedef void (*inner_ptr)(outer_closure);
typedef void (*func_ptr)(global_closure);
typedef void (*func2_ptr)(main_closure);

void inner(const outer_closure closure) {
  print(closure.msg);
  print(closure.name);
  return print((string){" !\n", 3});
}

inner_ptr outer(struct outer_closure *closure, string name) {
  string msg = (string){"Hey ", 4};
  print((string){"Producing inner funcction with name: ", 36});
  print(name);
  print((string){"\n", 1});

  closure->msg = msg;
  closure->name = name;
  closure->__closure__ = 1;

  return &inner;
}

outer_closure tmp0;
inner_ptr inner_implementation0 = NULL;
global_closure tmp1;

outer_closure tmp2;
inner_ptr inner_implementation1 = NULL;
main_closure tmp3;

void func(struct global_closure closure) {
  ;
  return inner_implementation0(tmp0);
}

void func2(const main_closure closure) { return inner_implementation1(tmp2); }

int main(void) {
  // Global funcction implementation creation
  inner_implementation0 = outer(&tmp0, (string){"Paul", 4});

  // Following the control flow
  print((string){"Hello, world !\n", 15});

  tmp3 = (main_closure){.__closure__ = 0};
  inner_implementation1 = outer(&tmp2, (string){"Marie", 5});

  func(tmp1);
  func(tmp1);
  func2(tmp3);
  func2(tmp3);

  return 0;
}
```
