#include "fundefs.h"
#include <stdio.h>

void print(string s) {
  for (int i = 0; i < s.length; i++)
    putchar(s.data[i]);
}

char *cstr(string s){
  return s.data;
}