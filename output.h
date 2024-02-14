#include <stdio.h>

typedef struct string {
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

typedef struct _Z4test0_closure _Z4test0_closure;

typedef int (*_Z4test0_ptr)(global_closure, _Z4test0_closure*);

// Generating function definition for: test
int _Z4test0(const global_closure __gcl, _Z4test0_closure* __lcl);

struct _Z4test0_closure {
  global_closure outer_closure;
  int a;
  char __closure__;
};

// Generating function definition for: test
int _Z4test0(const global_closure __gcl, _Z4test0_closure* __lcl) {
  __lcl->__closure__ = 1;
  __lcl->a = 3;
  return 10;
}
