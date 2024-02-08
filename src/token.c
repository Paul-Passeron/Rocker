#include "token.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static char *lexemes[TOK_COUNT] = {
    "", "", "", "", "let", ":", ",", "->", "=>", "{",
    "}", "(", ")", "in", "if", "then", "else", "rec",
    "pro", "match", "*", "-", "+", "/", "%", "||", "&&",
    "|", "^", "&", "<", "<=", ">", ">=", "=", "!="};

static token_type_t keywords[] = {
    TOK_LET,
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_IN,
    TOK_MATCH,
    TOK_PRO,
    TOK_REC,
};

static token_type_t operators[] = {
    TOK_STAR,
    TOK_MINUS,
    TOK_PLUS,
    TOK_DIV,
    TOK_MODULO,
    TOK_LOG_AND,
    TOK_LOG_OR,
    TOK_BIT_AND,
    TOK_BIT_OR,
    TOK_BIT_XOR,
    TOK_GRTR,
    TOK_GRTR_EQ,
    TOK_LSSR,
    TOK_LSSR_EQ,
    TOK_EQUAL,
    TOK_DIFF};

char *lexeme_of_type(token_type_t t)
{
    assert(TOK_COUNT == 36 && "Exhaustive handling of token types in lexeme_of_type");

    switch (t)
    {
    case TOK_IDENTIFIER:
        return "<identifier>";
    case TOK_CHR_LIT:
        return "<char literal>";
    case TOK_STR_LIT:
        return "<string literal>";
    case TOK_NUM_LIT:
        return "<numeric literal>";
    default:
        return lexemes[t];
    }
}

token_type_t type_of_lexeme(char *s)
{
    assert(TOK_COUNT == 36 && "Exhaustive handling of token types in type_of_lexeme");
    for (int i = 4; i < TOK_COUNT; i++)
        if (strcmp(lexemes[i], s) == 0)
            return i;
    return TOK_COUNT;
}

int is_type_keyword(token_type_t t)
{
    for (unsigned int i = 0; i < sizeof(keywords) / sizeof(token_type_t); i++)
        if (t == keywords[i])
            return 1;
    return 0;
}

int is_type_operator(token_type_t t)
{
    for (unsigned int i = 0; i < sizeof(keywords) / sizeof(token_type_t); i++)
        if (t == operators[i])
            return 1;
    return 0;
}

int is_lexeme_keyword(char *s)
{
    return is_type_keyword(type_of_lexeme(s));
}

void new_token_array(token_array_t *arr)
{
    arr->capacity = INIT_TOK_ARR;
    arr->length = 0;
    arr->data = malloc(sizeof(token_t) * arr->capacity);
}

void free_token(token_t tok)
{
    free(tok.lexeme);
}

void kill_token_array(token_array_t arr)
{
    for (int i = 0; i < arr.length; i++)
        free_token(arr.data[i]);
    if (arr.data != NULL)
        free(arr.data);
}

int get_precedence_aux(token_type_t t)
{
    switch (t)
    {
    case TOK_STAR:
        return 3;
    case TOK_DIV:
        return 3;
    case TOK_MODULO:
        return 3;
    case TOK_PLUS:
        return 4;
    case TOK_MINUS:
        return 4;
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
int get_precedence(token_type_t t)
{
    // Doing this because our precedence is reversed

    int res = get_precedence_aux(t);
    if (res == -1)
        return -1;
    return 13 - res;
}

int is_type_typ_def(token_type_t t)
{
    return t == TOK_PRO || t == TOK_REC;
}

void token_array_push(token_array_t *arr, token_t tok)
{
    if (arr->length >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(token_t));
    }
    arr->data[arr->length++] = tok;
}