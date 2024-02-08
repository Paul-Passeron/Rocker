#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

lexer_t new_lexer(char *filename)
{
    lexer_t res;
    res.col = 1;
    res.line = 1;
    res.cursor = 0;
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        printf("Could not open file '%s': ", filename);
        fflush(stdout);
        perror("");
        exit(1);
    }
    res.filename = malloc(strlen(filename));
    strcpy(res.filename, filename);
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f) + 1;
    fseek(f, 0, SEEK_SET);
    res.data = malloc(file_size);
    res.length = file_size;
    fread(res.data, 1, file_size, f);
    return res;
}

void kill_lexer(lexer_t l)
{
    free(l.data);
    free(l.filename);
}

static char delimeters[] = ",:-+*/%&|!=\"\'0123456789(){}^";

int is_delimeter(char c)
{
    for (unsigned int i = 0; i < sizeof(delimeters); i++)
        if (c == delimeters[i])
            return 1;
    return 0;
}

char lexer_peek(lexer_t l)
{
    if (l.cursor - 1 < l.length)
        return l.data[l.cursor - 1];
    else
        return 0;
}

int is_whitespace(char c)
{
    return c == ' ' || c == '\n';
}

void lexer_consume(lexer_t *l)
{
    char c = lexer_peek(*l);
    if (!c)
        return;
    if (c == '\n')
    {
        l->col = 1;
        l->line++;
    }
    else
        l->col++;
    l->cursor++;
}

int length_until_next_delimiter(lexer_t l)
{
    int i;
    int cursor = l.cursor;
    for (i = l.cursor + 1; i < l.length; i++)
    {
        while (!is_delimeter(lexer_peek(l)))
            lexer_consume(&l);
    }
    return i - cursor;
}

int length_of_delimiter(lexer_t l)
{
    char c1 = lexer_peek(l);
    lexer_consume(&l);
    char c2 = lexer_peek(l);
    char str[2]={c1, c2, 0};
    

    return -1;

}

token_t step_lexer(lexer_t *l)
{
    token_t res = (token_t){0};

    while (is_whitespace(lexer_peek(*l)))
        lexer_consume(l);

    return res;
}