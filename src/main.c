#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "generator.h"

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
    char out[] = "output.c\n";
    generator_t g = new_generator(p, out);
    for (int i = 0; i < p.prog.length; i++)
    {
        printf("\n\n");
        ast_t a = p.prog.data[i];
        ast_print(a);
        if (a->tag == ast_let_binding)
        {
            ast_t types = a->data.ast_let_binding.type_sig;
            char *fun_name = a->data.ast_let_binding.left->data.ast_identifier.id.lexeme;
            generate_function_sig(fun_name, types);
            generate_semicolon();
        }
    }

    kill_generator(g);

    kill_lexer(l);

    return 0;
}
