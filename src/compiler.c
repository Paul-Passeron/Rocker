#include "compiler.h"

ast_array_t generate_ast_prog_file(compiler_t* comp, char* filename) {
  comp->lexer = new_lexer(filename);
  comp->parser = new_parser(lex_program(&comp->lexer), filename);
  parse_program(&comp->parser);
  return comp->parser.prog;
}
void kill_compiler(compiler_t c) {
  // kill_ast_array(c.parser.prog);
  kill_lexer(c.lexer);
  kill_parser(c.parser);
}