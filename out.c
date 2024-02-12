#include <stdio.h>

typedef struct {
  char* s;
  int length;
} string;

void print(string s) {
  for (int i = 0; i < s.length; i++)
    putchar(s.s[i]);
}

typedef struct global_closure {
  char __closure__;
} global_closure;

typedef struct print_name_closure {
  char __closure__;
} print_name_closure;

// Generating function definition for: print_name
void print_name(const global_closure __gcl,
                struct print_name_closure* __lcl,
                string name);
typedef struct print_name_closure {
  char __closure__;
} print_name_closure;

// Generating function definition for: print_name
void print_name(const global_closure __gcl,
                struct print_name_closure* __lcl,
                string name);
