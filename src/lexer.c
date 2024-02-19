#include "lexer.h"
#include "../RockerAllocator/alloc.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

lexer_t new_lexer(char *filename) {
  lexer_t res;
  res.col = 1;
  res.line = 1;
  res.cursor = 0;
  FILE *f = fopen(filename, "rb");
  if (f == NULL) {
    printf("Could not open file '%s': ", filename);
    fflush(stdout);
    perror("");
    exit(1);
  }
  res.filename = allocate_compiler_persistent(strlen(filename) + 1);
  strcpy(res.filename, filename);
  fseek(f, 0, SEEK_END);
  size_t file_size = ftell(f) + 1;
  fseek(f, 0, SEEK_SET);
  res.data = allocate_compiler_persistent(file_size);
  res.length = file_size;
  fread(res.data, 1, file_size, f);
  fclose(f);
  return res;
}

static char delimeters[] = ",:-+*/%&|!=(){}^ \n\'\"";

int is_delimeter(char c) {
  for (unsigned int i = 0; i < sizeof(delimeters); i++)
    if (c == delimeters[i])
      return 1;
  return 0;
}

char lexer_peek(lexer_t l) {
  if (l.cursor < l.length)
    return l.data[l.cursor];
  else {
    printf("Problem !\n");
    exit(1);
    return 0;
  }
}

int is_whitespace(char c) { return c == ' ' || c == '\n'; }

void lexer_consume(lexer_t *l) {
  char c = lexer_peek(*l);
  if (!c)
    return;
  if (c == '\n') {
    l->col = 1;
    l->line++;
  } else
    l->col++;
  l->cursor++;
}

int length_until_next_delimiter(lexer_t l) {
  int i = 0;
  while (!is_delimeter(lexer_peek(l))) {
    lexer_consume(&l);
    i++;
  }
  return i;
}

int length_of_delimiter(lexer_t l) {
  char c1 = lexer_peek(l);
  lexer_consume(&l);
  char c2 = lexer_peek(l);
  char str[3] = {c1, c2, 0};
  if (strcmp(str, "->") == 0)
    return 2;
  if (strcmp(str, "=>") == 0)
    return 2;
  if (strcmp(str, "&&") == 0)
    return 2;
  if (strcmp(str, "||") == 0)
    return 2;
  if (strcmp(str, ">=") == 0)
    return 2;
  if (strcmp(str, "<=") == 0)
    return 2;
  if (strcmp(str, "!=") == 0)
    return 2;
  if (strcmp(str, "::") == 0)
    return 2;
  if (c1 == ':' || c1 == ',' || c1 == '/' || c1 == '%' || c1 == '*' ||
      c1 == '+' || c1 == '-' || c1 == '^' || c1 == '{' || c1 == '}' ||
      c1 == '(' || c1 == ')' || c1 == '=' || c1 == '<' || c1 == '>')
    return 1;

  return -1;
}

int is_char_num(char c) { return c <= '9' && c >= '0'; }

int length_of_num_lit(lexer_t l) {
  int cter = 0;
  while (is_char_num(lexer_peek(l))) {
    cter++;
    lexer_consume(&l);
  }
  return cter;
}

int length_of_delimited_literal(lexer_t l, char c) {
  int cursor = l.cursor;
  char c1 = lexer_peek(l);
  if (c1 != c)
    return 0;
  lexer_consume(&l);
  while (lexer_peek(l) != c)
    lexer_consume(&l);
  return l.cursor - cursor + 1;
}

char *create_lexeme(lexer_t l, int length) {
  char *s = allocate_compiler_persistent(length + 1);
  if (s == NULL) {
    printf("Could not allocate memory\n");
    exit(1);
  }
  for (int i = 0; i < length; i++) {
    s[i] = l.data[l.cursor + i];
  }
  s[length] = 0;
  return s;
}
typedef enum comment_type_t { COM_SINGLE = 1, COM_MULTI } comment_type_t;

int is_comment(lexer_t l) {
  char c1 = lexer_peek(l);
  lexer_consume(&l);
  char c2 = lexer_peek(l);
  if (c1 != '/')
    return 0;
  if (c2 == '/')
    return COM_SINGLE;
  if (c2 == '*')
    return COM_MULTI;
  return 0;
}

int is_end_comment(lexer_t l, comment_type_t type) {
  if (type == 0)
    return 0;
  if (type == COM_SINGLE) {
    if (lexer_peek(l) == '\n')
      return 1;
  }

  else {
    char c1 = lexer_peek(l);
    lexer_consume(&l);
    char c2 = lexer_peek(l);
    return c1 == '*' && c2 == '/';
  }
  return 0;
}

void lexer_consume_n(lexer_t *l, int n) {
  for (int i = 0; i < n; i++)
    lexer_consume(l);
}

token_t step_lexer(lexer_t *l) {
  token_t res = {0};

  // Possible cases:
  // - we have a comment
  // - we have a literal
  // - we have a delimiter
  // - we have a keyword
  // - we have an identifier

  // First case: Comment
  while (is_comment(*l) || is_whitespace(lexer_peek(*l))) {
    int is_com_type = is_comment(*l);

    if (is_com_type) {
      lexer_consume_n(l, 2); // consume the initial comment 'declaration'
      while (!is_end_comment(*l, is_com_type)) {
        lexer_consume(l);
      }
      if (is_com_type == COM_MULTI)
        lexer_consume(l);
      lexer_consume(l); // consume the matching end;
    }
    while (is_whitespace(lexer_peek(*l)))
      lexer_consume(l);
  }
  if (lexer_peek(*l) == 0) {
    return (token_t){0};
  }
  res.col = l->col;
  res.line = l->line;
  // The case must fall through
  // Second case: Num Literal
  if (is_char_num(lexer_peek(*l))) {
    int length = length_of_num_lit(*l);
    res.lexeme = create_lexeme(*l, length);
    res.type = TOK_NUM_LIT;
    lexer_consume_n(l, length);
  }
  // Third case: Char Literal
  else if (lexer_peek(*l) == '\'') {
    int length = length_of_delimited_literal(*l, '\'');
    res.lexeme = create_lexeme(*l, length);
    res.type = TOK_CHR_LIT;
    lexer_consume_n(l, length);
  }
  // Fourth case: String Literal
  else if (lexer_peek(*l) == '\"') {
    int length = length_of_delimited_literal(*l, '\"');
    res.lexeme = create_lexeme(*l, length);
    res.type = TOK_STR_LIT;
    lexer_consume_n(l, length);
  }
  // Fifth case: Delimeter
  else if (is_delimeter(lexer_peek(*l))) {
    int length = length_of_delimiter(*l);
    res.lexeme = create_lexeme(*l, length);
    res.type = type_of_lexeme(res.lexeme);
    lexer_consume_n(l, length);
  }
  // Sixth case: Keyword or Identifier
  else {
    int length = length_until_next_delimiter(*l);
    res.lexeme = create_lexeme(*l, length);
    if (is_lexeme_keyword(res.lexeme))
      res.type = type_of_lexeme(res.lexeme);
    else
      res.type = TOK_IDENTIFIER;
    lexer_consume_n(l, length);
  }
  return res;
}

token_array_t lex_program(lexer_t *l) {
  if (l == NULL) // to make valgrind happy
    exit(1);
  token_array_t arr = new_token_array();
  while (lexer_peek(*l)) {
    token_t t = step_lexer(l);
    if (t.lexeme)
      token_array_push(&arr, t);
  }
  return arr;
}
