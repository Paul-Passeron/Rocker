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
        return "";
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
    {
        if (t == keywords[i])
            return 1;
    }
    return 0;
}
int is_lexeme_keyword(char *s)
{
    return is_type_keyword(type_of_lexeme(s));
}

int is_type_keyword(token_type_t t)
{
    for (unsigned int i = 0; i < sizeof(keywords) / sizeof(token_type_t); i++)
    {
        if (t == keywords[i])
            return 1;
    }
    return 0;
}
int is_lexeme_keyword(char *s)
{
    return is_type_keyword(type_of_lexeme(s));
}