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
    TOK_KEYWORD,

} token_type_t;

#endif // TOKEN_H