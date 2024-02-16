#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "token.h"
#include "ast.h"
#include "lexer.h"

#ifndef ROCKER_ALLOC_IMPLEMENTATION
#define ROCKER_ALLOC_IMPLEMENTATION
#endif
#ifndef COMPILER_GLOBAL
#define COMPILER_GLOBAL
#endif
#include "../RockerAllocator/alloc.h"


// #include "generator.h"

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
  init_compiler_stack();
  if (argc < 2) {
    usage(argv[0]);
    exit(1);
  }
  char* input = NULL;
  char* output = NULL;
  int print_tree = 0;

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
  if (output == NULL) {
    output = "out.c";
  }
  lexer_t l = new_lexer(input);
  token_array_t prog = lex_program(&l);
  print_token_array(prog);
  if (print_tree)
    assert(0 && "TODO: reimplement parsing\n");
  (void)output;
  kill_compiler_stack();
  return 0;
}
