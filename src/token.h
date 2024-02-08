/*****************************************************
 * ROCKER TOKEN HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef TOKEN_H
#define TOKEN_H

/*****************************************************
 * Primary Token Type enumeration
 * Holds info about what kind of token one is
 * i.e. a Literal, a keyword, a semicolon...
 *****************************************************/

typedef enum token_type_t
{
    TOK_IDENTIFIER,
    TOK_CHR_LIT,
    TOK_STR_LIT,
    TOK_NUM_LIT,
    TOK_LET,
    TOK_COLON,
    TOK_COMMA,
    TOK_SMALL_ARROW,
    TOK_BIG_ARROW,
    TOK_OPEN_BRACE,
    TOK_CLOSE_BRACE,
    TOK_OPEN_PAREN,
    TOK_CLOSE_PAREN,
    TOK_IN,
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_REC,
    TOK_PRO,
    TOK_MATCH,
    TOK_STAR,
    TOK_MINUS,
    TOK_PLUS,
    TOK_DIV,
    TOK_MODULO,
    TOK_LOG_OR,
    TOK_LOG_AND,
    TOK_BIT_OR,
    TOK_BIT_XOR,
    TOK_BIT_AND,
    TOK_LSSR,
    TOK_LSSR_EQ,
    TOK_GRTR,
    TOK_GRTR_EQ,
    TOK_EQUAL,
    TOK_DIFF,

    TOK_COUNT

} token_type_t;

char *lexeme_of_type(token_type_t);
token_type_t type_of_lexeme(char *);
int is_lexeme_keyword(char *s);
int is_type_keyword(token_type_t t);

typedef struct token_t
{
    token_type_t type;
    char *lexeme;
    int col;
    int line;
} token_t;

typedef struct token_array_t
{
    token_t *data;
    int length;
    int capacity;
} token_array_t;

#endif // TOKEN_H