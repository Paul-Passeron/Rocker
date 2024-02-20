#include "./src/generation/fundefs.h"
#include "./src/generation/typedefs.h"
int fact(int n) {
  {
    if (n <= 1)
      return 1;
    ;
    return n * fact(n - 1);
  }
}
void print_num(int n, int b) {
  {
    int a = n / b;
    if (a)
      print_num(a, b);
    ;
    putchar(n % b + '0');
  }
}
void print_decimal(int n) {
  { print_num(n, 10); }
}
void print_facts_aux(int goal, int num) {
  {
    if (num < goal) {
      print_decimal(fact(num));
      print((string){.data = "\n", .length = 2});
      print_facts_aux(goal, num + 1);
    };
  }
}
void print_facts(int n) {
  { print_facts_aux(n, 1); }
}
int main() {
  {
    print_facts(10);
    return 0;
  }
}
