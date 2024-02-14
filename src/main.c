#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "compiler.h"

void usage(char* name) {
  printf("Usage:\n");
  printf("\t%s [flags] <input file> [output file]\n", name);
  printf("Possible flags:\n");
  printf("\t-t:\t\tPrints the ast\n");
  printf("\t-m:t\tPrints the list of mangled names\n");
}

void print_program(ast_array_t prog) {
  for (int i = 0; i < prog.length; i++) {
    printf("\n");
    ast_t a = prog.data[i];
    ast_print(a);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    usage(argv[0]);
    exit(1);
  }
  char* input = NULL;
  char* output = NULL;
  int print_tree = 0;
  int print_mangled = 0;

  for (int i = 1; i < argc; i++) {
    char* arg = argv[i];
    if (*arg == '-') {
      // This is a flag
      if (strlen(arg) == 1) {
        printf("Unexpected empty flag !\n");
        usage(argv[0]);
        exit(1);
      } else if (*(arg + 1) == 't' && !print_tree)
        print_tree = 1;
      else if (*(arg + 1) == 'm' && !print_mangled)
        print_mangled = 1;
      else {
        printf("Unknown flag '%s'!\n", arg + 1);
        usage(argv[0]);
        exit(1);
      }

    } else if (input == NULL)
      input = arg;
    else if (output == NULL)
      output = arg;
    else {
      printf("Unexpected argument '%s' !\n", arg);
      usage(argv[0]);
      exit(1);
    }
  }
  if (input == NULL) {
    printf("Expected input !\n");
    usage(argv[0]);
    exit(1);
  }
  if (output == NULL) {
    output = "out.c";
  }
  compiler_t c;
  ast_array_t arr = generate_ast_prog_file(&c, input);
  if (print_tree)
    print_program(arr);

  FILE* f = fopen(output, "wb");
  generate_prolog(f);
  fprintf(
      f, "typedef struct global_closure{char __closure__;}global_closure;\n\n");

  for (int i = 0; i < arr.length; i++) {
    ast_t a = arr.data[i];
    if (a->tag == ast_let_binding) {
      closure_t closure = get_closure(a, "global");
      // temporary forced global outer closure
      print_closure(closure);
      generate_closure_def(closure, f);
    }
  }

  fclose(f);

  (void)output;
  kill_compiler(c);

  return 0;
}
