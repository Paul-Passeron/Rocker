#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include "../RockerAllocator/alloc.h"
#include <stddef.h>
#include <string.h>

#define SV_Fmt "%.*s"
#define SV_Arg(sv) (int)(sv).length, (sv).data
#define SV_Static(cstr_lit)                                                    \
  { (cstr_lit), sizeof(cstr_lit) - 1 }

typedef struct string_view {
  char *data;
  size_t length;
} string_view;

string_view sv_from_parts(char *data, size_t length);

string_view sv_from_cstr(char *s);

char *string_of_sv(string_view s);

int svcmp(string_view s1, string_view s2);

#endif // STRING_VIEW_H