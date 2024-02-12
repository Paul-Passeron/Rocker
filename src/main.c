#include "generator.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

// void(*outer(void))
// {
//     int a = 1;
//     void print_a(void)
//     {
//         printf("%d\n", a);
//     }
//     return &print_a;
// }

void usage(char *name) {
  printf("Usage:\n");
  printf("\t%s <input file>\n", name);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage(argv[0]);
    exit(1);
  }
  lexer_t l = new_lexer(argv[1]);
  token_array_t arr = lex_program(&l);
  parser_t p = new_parser(arr, argv[1]);
  parse_program(&p);
  //   char out[] = "output.c";
  //   generator_t g = new_generator(p, out);
  //   generate_prolog();
  for (int i = 0; i < p.prog.length; i++) {
    printf("\n\n");
    ast_t a = p.prog.data[i];
    ast_print(a);
    // if (a->tag == ast_let_binding)
    // {
    //     // ast_t types = a->data.ast_let_binding.type_sig;
    //     // char *fun_name = a->data.ast_let_binding.name.lexeme;
    //     // generate_function_sig(fun_name, types,
    //     a->data.ast_let_binding.args);
    //     // generate_semicolon();
    //     generate_let_binding(a);
    // }
    // if (a->tag == ast_type_def)
    // {
    //     if (a->data.ast_type_def.is_rec)
    //         generate_rec_type(a);
    //     else
    //         generate_pro_type(a);
    // }
  }

  //   kill_generator(g);

  kill_lexer(l);

  // void (*fnc)(void) = outer();
  // fnc();

  return 0;
}
