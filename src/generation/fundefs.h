#ifndef ROCKER_FUNDEFS
#define ROCKER_FUNDEFS

#include <stdio.h>
#include "typedefs.h"

void print(string s);
char* string_to_cstr(string s);
char get_nth_char(string s, int n);
string append_string(string s, char c);
string concat_string(string s1, string s2);
int get_string_length(string s);
void set_nth_char(string s, int n, char c);
string read_file(string filename);
string new_string(string s);
void write_string_to_file(string s, string filename);

#endif  // ROCKER_FUNDEFS