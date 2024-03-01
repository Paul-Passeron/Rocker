#include "stringview.h"

string_view sv_from_parts(char *data, size_t length) {
  return (string_view){data, length};
}

string_view sv_from_cstr(char *s) {
  if (s == NULL)
    return (string_view){0};
  return sv_from_parts(s, strlen(s));
}

char *string_of_sv(string_view s) {
  char *data = (char *)allocate_compiler_persistent(s.length + 1);
  memcpy(data, s.data, s.length);
  data[s.length] = 0;
  return data;
}

int svcmp(string_view s1, string_view s2) {
  if (s1.length != s2.length)
    return 1;
  size_t l = s1.length;
  if (s2.length < l)
    l = s2.length;
  for (size_t i = 0; i < l; i++)
    if (s1.data[i] != s2.data[i])
      return 1;
  return 0;
}