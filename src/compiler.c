#include "compiler.h"

ast_array_t generate_ast_prog_file(char* filename) {
  compiler_t comp;
  comp.lexer = new_lexer(filename);
  comp.parser = new_parser(lex_program(&comp.lexer), filename);
  parse_program(&comp.parser);
  return comp.parser.prog;
}