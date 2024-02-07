/*****************************************************
 * ROCKER LEXER HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef LEXER_H
#define LEXER_H

/*****************************************************
 * Primary Lexer structure
 * Will go through the file to create
 * the token array
 *****************************************************/
typedef struct lexer
{
    int col;
    int line;
    char *data;
    int cursor;
    char *filename;
} lexer_t;

#endif // LEXER_H