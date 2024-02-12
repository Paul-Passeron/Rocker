#include "generator.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

  char out[] = "out.c";
  FILE *f = fopen(out, "wb");
  if (f == NULL) {
    perror("\n");
  }
  generate_prolog(f);

  closure_t closure;
  closure.name = "global";
  closure.length = 0;
  generate_closure_def(closure, f);

  for (int i = 0; i < p.prog.length; i++) {
    printf("\n\n");
    ast_t a = p.prog.data[i];
    ast_print(a);

    if (a->tag == ast_let_binding) {

      closure_t clos;
      clos.name = a->data.ast_let_binding.name.lexeme;
      clos.length = 0;
      generate_closure_def(clos, f);
      generate_function_signature(fundef_from_let(a), f);
      fprintf(f, ";\n");
    }
  }

  fclose(f);
  execl("/usr/bin/clang-format", "--style=\"LLVM\"", "-i", out, NULL);

  //   kill_generator(g);

  kill_lexer(l);

  // void (*fnc)(void) = outer();
  // fnc();

  return 0;
}
