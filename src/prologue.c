#include <stdio.h>

typedef struct {
  char* s;
  int length;
} string;

void print(string s) {
  for (int i = 0; i < s.length; i++)
    putchar(s.s[i]);
}