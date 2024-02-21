#include "./src/generation/fundefs.h"
#include "./src/generation/typedefs.h"
void print_int(int n)
{int a = n / 10;
if (a)
print_int(a);
putchar(n % 10 + '0');
}int main()
{print_int(1234567890);
print((string){.data = "\n", .length = 2});
return 0;
}