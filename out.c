#include "./src/generation/fundefs.h"
#include "./src/generation/fundefs_internal.h"
#include "./src/generation/typedefs.h"
#include "./RockerAllocator/alloc.h"
int exp_rapide(int x, int n)
{if (n == 0)
return 1;
if (n == 1)
return x;
if (n % 2 == 0)
return exp_rapide(x * x, n / 2);
int new_n = n - 1;
return x * exp_rapide(x * x, new_n / 2);
}void print_int(int n)
{int a = n / 10;
if (a)
print_int(a);
putchar(n % 10 + '0');
}int main()
{
init_compiler_stack();
{for(int i =0; i <= 10; i++)
{print((string){.data = "2^", .length = 3});
print_int(i);
print((string){.data = " = ", .length = 4});
print_int(exp_rapide(2, i));
print((string){.data = "\n", .length = 2});
};
return 0;
}kill_compiler_stack();
}
