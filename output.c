#include "./src/generation/fundefs.h"
#include "./src/generation/typedefs.h"
int square(int n) {
  return n * n;
}
int main() {
  string msg = (string){.data = "Hello, World !\n", .length = 16};
  string msg2 = msg;
  print(msg);
  print(msg2);
  putchar(square(3) + '0');
  return 0;
}
