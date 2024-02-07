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
    res.filename = malloc(strlen(filename));
    free(res.filename);
    // strcpy(res.filename, )
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        printf("Could not open file '%s': ", filename);
        fflush(stdout);
        perror("");
        exit(1);
    }
    // res.data =
    return res;
}

void kill_lexer(lexer_t l)
{
    (void)l;
}
