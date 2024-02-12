#include <stdio.h>

typedef struct {
  char *s;
  int length;
} string;

void print(string s) {
  for (int i = 0; i < s.length; i++)
    putchar(s.s[i]);
}

typedef struct global_closure {
  char __closure__;
} global_closure;

typedef struct main_closure {
  char __closure__;
} main_closure;

// Generating function definition for: main
int main(const struct global_closure global_closure,
         struct main_closure *local_closure);
