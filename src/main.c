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
    printf("Trying to read file: %s\n", argv[1]);
    lexer_t l = new_lexer(argv[1]);
    (void)l;
    printf("Successfully read file %s\n", argv[1]);

    token_type_t test = TOK_MATCH;
    char test_string[] = "let";
    printf("Token %d is: %s\n", test, lexeme_of_type(test));
    printf("Token %s is: %d\n", test_string, type_of_lexeme(test_string));

    return 0;
}