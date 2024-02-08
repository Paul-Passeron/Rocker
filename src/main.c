#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"
#include "parser.h"
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
    token_array_t arr = lex_program(&l);
    parser_t p = new_parser(arr, argv[1]);
    parse_program(&p);

    ast_print(p.prog.data[0]);

    kill_lexer(l);
    return 0;
}