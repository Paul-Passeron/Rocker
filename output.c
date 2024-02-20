#include "./src/generation/fundefs.h"
#include "./src/generation/typedefs.h"
int main() {
  print((string){.data = "Hello, World !\n", .length = 16});
  return 0;
}
