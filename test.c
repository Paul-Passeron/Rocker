#include "output.h"

int main() {
  global_closure __gcl = {0};
  _Z4test0_closure __lcl = {0};
  return _Z4test0(__gcl, &__lcl);
}