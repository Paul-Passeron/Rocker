#include "./src/generation/fundefs.h"
#include "./src/generation/typedefs.h"
int main() {
  string msg = (string){.data = "Hello, World !\n\n\n", .length = 18};
  print(msg);
  return 0;
}
