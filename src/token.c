#include "token.h"
#include "../RockerAllocator/alloc.h"
#include "stringview.h"
#include <assert.h>

static string_view lexemes[TOK_COUNT] = {
    SV_Static(""),        SV_Static(""),       SV_Static(""),
    SV_Static(""),        SV_Static("let"),    SV_Static(":"),
    SV_Static(","),       SV_Static("->"),     SV_Static("=>"),
    SV_Static("{"),       SV_Static("}"),      SV_Static("("),
    SV_Static(")"),       SV_Static("if"),     SV_Static("then"),
    SV_Static("else"),    SV_Static("rec"),    SV_Static("pro"),
    SV_Static("match"),   SV_Static("return"), SV_Static("*"),
    SV_Static("-"),       SV_Static("+"),      SV_Static("/"),
    SV_Static("%"),       SV_Static("||"),     SV_Static("&&"),
    SV_Static("|"),       SV_Static("^"),      SV_Static("&"),
    SV_Static("<"),       SV_Static("<="),     SV_Static(">"),
    SV_Static(">="),      SV_Static("="),      SV_Static("!="),
    SV_Static("_"),       SV_Static("::"),     SV_Static(";"),
    SV_Static("loop"),    SV_Static("while"),  SV_Static("do"),
    SV_Static("include"), SV_Static("enum"),   SV_Static("[]")};

static token_type_t keywords[] = {
    TOK_MATCH, TOK_PRO,     TOK_REC,  TOK_WILDCARD, TOK_RETURN, TOK_SUB,
    TOK_LET,   TOK_IF,      TOK_THEN, TOK_ELSE,     TOK_LOOP,   TOK_WHILE,
    TOK_DO,    TOK_INCLUDE, TOK_ENUM, TOK_ARR_DECL};

static token_type_t operators[] = {
    TOK_STAR,   TOK_MINUS,   TOK_PLUS,   TOK_DIV,     TOK_MODULO, TOK_LOG_AND,
    TOK_LOG_OR, TOK_BIT_AND, TOK_BIT_OR, TOK_BIT_XOR, TOK_GRTR,   TOK_GRTR_EQ,
    TOK_LSSR,   TOK_LSSR_EQ, TOK_EQUAL,  TOK_DIFF};

string_view lexeme_of_type(token_type_t t) {
  assert(TOK_COUNT == 45 &&
         "Exhaustive handling of token types in lexeme_of_type");

  switch (t) {
  case TOK_IDENTIFIER:
    return (string_view)SV_Static("<identifier>");
  case TOK_CHR_LIT:
    return (string_view)SV_Static("<char literal>");
  case TOK_STR_LIT:
    return (string_view)SV_Static("<string literal>");
  case TOK_NUM_LIT:
    return (string_view)SV_Static("<numeric literal>");
  default:
    return lexemes[t];
  }
}

token_type_t type_of_lexeme(string_view s) {
  assert(TOK_COUNT == 45 &&
         "Exhaustive handling of token types in type_of_lexeme");
  for (int i = 4; i < TOK_COUNT; i++)
    if (svcmp(lexemes[i], s) == 0)
      return i;
  return TOK_COUNT;
}

int is_type_keyword(token_type_t t) {
  for (unsigned int i = 0; i < sizeof(keywords) / sizeof(token_type_t); i++)
    if (t == keywords[i])
      return 1;
  return 0;
}

int is_type_operator(token_type_t t) {
  for (unsigned int i = 0; i < sizeof(operators) / sizeof(token_type_t); i++)
    if (t == operators[i])
      return 1;
  return 0;
}

int is_lexeme_keyword(string_view s) {
  return is_type_keyword(type_of_lexeme(s));
}

token_array_t new_token_array(void) {
  token_array_t res;
  res.capacity = INIT_TOK_ARR;
  res.length = 0;
  res.data = allocate_compiler_persistent(sizeof(token_t) * res.capacity);
  return res;
}

int get_precedence_aux(token_type_t t) {
  switch (t) {
  case TOK_STAR:
    return 2;
  case TOK_DIV:
    return 2;
  case TOK_MODULO:
    return 2;
  case TOK_PLUS:
    return 4;
  case TOK_MINUS:
    return 3;
  case TOK_GRTR:
    return 6;
  case TOK_LSSR:
    return 6;
  case TOK_LSSR_EQ:
    return 6;
  case TOK_GRTR_EQ:
    return 6;
  case TOK_EQUAL:
    return 7;
  case TOK_DIFF:
    return 7;
  case TOK_BIT_AND:
    return 8;
  case TOK_BIT_XOR:
    return 9;
  case TOK_BIT_OR:
    return 10;
  case TOK_LOG_AND:
    return 11;
  case TOK_LOG_OR:
    return 12;
  default:
    return -1;
  }
}
int get_precedence(token_type_t t) {
  // Doing this because our precedence is reversed

  int res = get_precedence_aux(t);
  if (res == -1)
    return -1;
  return 13 - res;
}

int is_type_typ_def(token_type_t t) {
  return t == TOK_PRO || t == TOK_REC || t == TOK_ENUM;
}

void token_array_push(token_array_t *arr, token_t tok) {
  if (arr->length >= arr->capacity) {
    arr->capacity *= 2;
    arr->data = (token_t *)reallocate_compiler_persistent(
        arr->data, arr->capacity * sizeof(token_t));
  }
  arr->data[arr->length++] = tok;
}

// void print_token_array(token_array_t arr) {
//   for (int i = 0; i < arr.length; i++)
//     print_token(arr.data[i]);
// }
// void print_token(token_t t) {
//   printf("-> Type: %s\n   Lexeme: %s\n\n", lexeme_of_type(t.type), t.lexeme);
// }
