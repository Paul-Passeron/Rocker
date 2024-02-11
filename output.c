#include <stdio.h>
typedef struct {
  char *s;
  int length;
} string;
void print(string s) {
  for (int i = 0; i < s.length; i++)
    putchar(s.s[i]);
}

int main(void) {
  int a(void) {
    print((string){.s = "Hello World !\n", .length = 15});
    return 0;
  }
  print((string){.s = "Hello World !\n", .length = 15});
  a();
  return a();
}
int fact(int n) {
  int _tmp_match1 = n;
  if (_tmp_match1 == 0) {
    return 1
  } else if (_tmp_match1 == 1) {
    return 1
  } else if (_tmp_match1 == n) {
    return
  }
}
