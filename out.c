#include <stdio.h>

typedef struct string{char *s;int length;}string;

void print(string s){for (int i = 0; i < s.length; i++)putchar(s.s[i]);}

typedef struct global_closure{char __closure__;}global_closure;

typedef struct test_closure {
global_closure outer_closure;
int a;
int b;
int c;
string you_should_see_that;
  char __closure__;
} test_closure;

