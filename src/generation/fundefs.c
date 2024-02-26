#include "fundefs.h"
#include <stdio.h>
#include <string.h>
#include "../../RockerAllocator/alloc.h"

void print(string s) {
  for (int i = 0; i < s.length; i++)
    putchar(s.data[i]);
}

char* string_to_cstr(string s) {
  return s.data;
}

string cstr_to_string(char* cstr) {
  return (string){.data = cstr, .length = strlen(cstr)};
}

char get_nth_char(string s, int n) {
  if (n > s.length)
    return 0;
  return s.data[n];
}

string append_string(string s, char c) {
  char* tmp = allocate_compiler_persistent(s.length + 2);
  memcpy(tmp, s.data, s.length);
  tmp[s.length] = c;
  tmp[s.length + 1] = 0;
  s.length++;
  s.data = reallocate_compiler_persistent(s.data, s.length + 2);
  return (string){.data = tmp, .length = s.length};
}

string concat_string(string s1, string s2) {
  char* buffer = allocate_compiler_persistent(s1.length + s2.length + 1);
  memcpy(buffer, s1.data, s1.length);
  memcpy(&buffer[s1.length], s2.data, s2.length);
  buffer[s1.length + s2.length] = 0;
  return (string){.data = buffer, .length = s1.length + s2.length};
}

int get_string_length(string s) {
  return s.length;
}

void set_nth_char(string s, int n, char c) {
  if (s.length > n)
    s.data[n] = c;
  else
    append_string(s, c);
}

string read_file(string filename) {
  FILE* f = fopen(string_to_cstr(filename), "rb");
  if (f == NULL) {
    printf("Unable to open file \"%s\"", string_to_cstr(filename));
    exit(1);
  }
  fseek(f, 0, SEEK_END);
  size_t length = ftell(f);
  fseek(f, 0, SEEK_SET);
  char* buffer = allocate_compiler_persistent(length + 1);
  fread(buffer, 1, length, f);
  buffer[length] = 0;
  fclose(f);
  return cstr_to_string(buffer);
}

string new_string(string s) {
  string res;
  res.data = allocate_compiler_persistent(s.length + 1);
  res.length = s.length;
  memcpy(res.data, s.data, s.length + 1);
  return res;
}