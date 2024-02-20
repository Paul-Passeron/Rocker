#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../RockerAllocator/alloc.h"
#include "generator.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"

// #include "generator.h"

void usage(char* name) {
  printf("Usage:\n");
  printf("\t%s [flags] <input file> [output file] [flags]\n", name);
  printf("Possible flags:\n");
  printf("\t-t:\t\tPrints the ast\n");
  printf("\t-l:\t\tPrints the list of lexemes\n");
}

int main(int argc, char* argv[]) {
  init_compiler_stack();
  if (argc < 2) {
    usage(argv[0]);
    exit(1);
  }
  char* input = NULL;
  char* output = NULL;
  int print_tree = 0;
  int print_lexer = 0;

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
      else if (*(arg + 1) == 'l' && !print_tree)
        print_lexer = 1;
      else {
        printf("Unknown flag '%s'!\n", arg + 1);
        usage(argv[0]);
        exit(1);
      }

    } else if (input == NULL)
      input = arg;
    else if (output == NULL) {
      output = arg;
    } else {
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
  if (output == NULL)
    output = "out";

  lexer_t l = new_lexer(input);
  token_array_t prog = lex_program(&l);
  parser_t p = new_parser(prog);
  parse_program(&p);

  if (print_lexer)
    print_token_array(prog);
  if (print_tree)
    print_ast(p.prog);

  char* cout = allocate_compiler_persistent(strlen(output) + 3);
  sprintf(cout, "%s.c", output);
  generator_t g = new_generator(cout);
  transpile(g, p.prog);
  kill_generator(g);

  // compile C file
  char command[1024];
  sprintf(command, "gcc -static -o %s %s", output, cout);
  system(command);

  kill_compiler_stack();
  return 0;
}
