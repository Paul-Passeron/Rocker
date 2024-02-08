#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"

void usage(char *name)
{
    printf("Usage:\n");
    printf("\t%s <input file>\n", name);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage(argv[0]);
        exit(1);
    }
    lexer_t l = new_lexer(argv[1]);
    while (lexer_peek(l))
    {
        token_t t = step_lexer(&l);
        printf("%5s -> %s\n", t.lexeme, lexeme_of_type(t.type));
        free(t.lexeme);
    }

    kill_lexer(l);
    return 0;
}