#include "generator.h"
#include "../RockerAllocator/alloc.h"
#include "ast.h"
#include "token.h"
#include <assert.h>
#include <string.h>

void generate_statement(generator_t *g, ast_t stmt);
void generate_compound(generator_t *g, ast_t comp);
void generate_tdef(generator_t *g, ast_t tdef_ast);
void generate_fundef(generator_t *g, ast_t fun);
generator_t new_generator(char *filename) {
  generator_t res;
  res.f = fopen(filename, "wb");
  if (res.f == NULL)
    perror("Could not open file !");
  res.table = new_name_table();
  return res;
}

void kill_generator(generator_t g) {
  fclose(g.f);
  return;
}

name_table_t new_name_table(void) {
  name_table_t res;
  res.length = 0;
  res.capacity = INIT_NT_CAP;
  res.scope = 0;
  res.refs = new_ast_array();
  res.kinds = allocate_compiler_persistent(sizeof(nt_kind) * res.capacity);
  res.names = allocate_compiler_persistent(sizeof(char *) * res.capacity);
  res.scopes = allocate_compiler_persistent(sizeof(int) * res.capacity);
  return res;
}

void generate_type(FILE *f, ast_tupledef tuple) {
  token_array_t elems = tuple.signature;
  if (elems.length > 1) {
    assert(0 && "TODO: actually handle tuples in geenrate_type");
  }
  if (elems.length == 0) {
    assert(0 && "Unreachable");
  }
  fprintf(f, "%s", elems.data[0].lexeme);
}

void generate_expression(generator_t *g, ast_t expr);

void generate_funcall(generator_t *g, ast_t fun) {
  FILE *f = g->f;
  ast_funcall funcall = fun->data.funcall;
  fprintf(f, "%s(", funcall.name.lexeme);
  for (int i = 0; i < funcall.args.length; i++) {
    if (i > 0)
      fprintf(f, ", ");
    generate_expression(g, funcall.args.data[i]);
  }
  fprintf(f, ")");
}

int calcEscapedLength(const char *str) {
  int length = 0;
  int i = 0;
  while (str[i]) {
    if (str[i] == '\\') { // Check if it is an escape character
      i++; // Move to the next character to interpret the escape sequence
      if (str[i] == 'n' || str[i] == 't' || str[i] == '\\' || str[i] == '"' ||
          str[i] == '\'' || str[i] == 'r') {
        length++; // These are single character escape sequences
      } else {
        length += 2; // For unrecognized escape sequences, count both characters
      }
    } else {
      length++;
    }
    i++;
  }
  return length - 1;
}

int get_literal_string_length(token_t tok) {
  return calcEscapedLength(tok.lexeme);
}

void generate_op(generator_t *g, ast_t expr) {
  ast_op op = expr->data.op;
  FILE *f = g->f;
  generate_expression(g, op.left);
  if (op.op == TOK_EQUAL)
    fprintf(f, " == ");
  else
    fprintf(f, " %s ", lexeme_of_type(op.op));
  generate_expression(g, op.right);
}

void generate_if_statement(generator_t *g, ast_t stmt) {
  FILE *f = g->f;
  ast_ifstmt ifstmt = stmt->data.ifstmt;
  fprintf(f, "if (");
  generate_expression(g, ifstmt.expression);
  fprintf(f, ")\n");
  generate_statement(g, ifstmt.body);
  if (ifstmt.elsestmt != NULL) {
    fprintf(f, "else\n");
    generate_statement(g, ifstmt.elsestmt);
  }
}

void generate_expression(generator_t *g, ast_t expr) {
  FILE *f = g->f;
  if (expr->tag == literal) {
    token_t tok = expr->data.literal.lit;
    if (tok.type != TOK_STR_LIT)
      fprintf(f, "%s", tok.lexeme);
    else {
      fprintf(f, "(string){.data = %s, .length = %d}", tok.lexeme,
              get_literal_string_length(tok));
    }
  } else if (expr->tag == identifier) {
    //   // ast_t def = get_ref(lexeme, g->table);
    //   // if (def == NULL) {
    //   //   // TODO: error
    //   //   printf("Unexpected identifier '%s'.\n", lexeme);
    //   //   exit(1);
    // }
    char *lexeme = expr->data.identifier.id.lexeme;
    fprintf(f, "%s", lexeme);
  } else if (expr->tag == funcall) {
    generate_funcall(g, expr);
  } else if (expr->tag == op) {
    generate_op(g, expr);
  } else if (expr->tag == ifstmt) {
    generate_if_statement(g, expr);
  } else if (expr->tag == compound) {
    generate_compound(g, expr);
  } else {
    printf("TAG is %d\n", expr->tag);
    assert(0 && "TODO");
  }
}

void generate_vardef(generator_t *g, ast_t var) {
  FILE *f = g->f;
  ast_vardef vardef = var->data.vardef;
  push_nt(&g->table, vardef.name.lexeme, NT_VAR, var);
  generate_type(f, vardef.type->data.tupledef);
  fprintf(f, " %s = ", vardef.name.lexeme);
  generate_expression(g, vardef.expr);
  fprintf(f, ";\n");
}

void generate_match(generator_t *g, ast_t match) {
  (void)g;
  (void)match;
}

void generate_return(generator_t *g, ast_t ret_ast) {
  FILE *f = g->f;
  fprintf(f, "return ");
  generate_expression(g, ret_ast->data.ret.expr);
  fprintf(f, ";\n");
}

void generate_statement(generator_t *g, ast_t stmt) {
  FILE *f = g->f;
  if (stmt->tag == vardef) {
    generate_vardef(g, stmt);
  } else if (stmt->tag == match) {
    assert(0 && "TODO");
    generate_match(g, stmt);
  } else if (stmt->tag == ret) {
    generate_return(g, stmt);
  } else if (stmt->tag == compound) {
    generate_compound(g, stmt);
  } else if (stmt->tag == ifstmt) {
    generate_if_statement(g, stmt);
  } else if (stmt->tag == tdef) {
    generate_tdef(g, stmt);
  } else if (stmt->tag == fundef) {
    generate_fundef(g, stmt);
  } else {
    generate_expression(g, stmt);
    fprintf(f, ";\n");
  }
}
void generate_compound(generator_t *g, ast_t comp) {
  FILE *f = g->f;
  fprintf(f, "{");
  ast_compound compound = comp->data.compound;
  new_nt_scope(&g->table);
  for (int i = 0; i < compound.stmts.length; i++)
    generate_statement(g, compound.stmts.data[i]);
  end_nt_scope(&g->table);
  fprintf(f, "}");
}

void generate_fundef(generator_t *g, ast_t fun) {
  // add to name table
  FILE *f = g->f;
  ast_fundef fundef = fun->data.fundef;
  new_nt_scope(&g->table);
  push_nt(&g->table, fundef.name.lexeme, NT_FUN, fun);
  generate_type(f, fundef.ret_type->data.tupledef);
  fprintf(f, " %s(", fundef.name.lexeme);
  for (int i = 0; i < fundef.args.length; i++) {
    push_nt(&g->table, fundef.args.data[i].lexeme, NT_VAR, fun);
    if (i > 0)
      fprintf(f, ", ");
    generate_type(f, fundef.types.data[i]->data.tupledef);
    fprintf(f, " ");
    fprintf(f, "%s", fundef.args.data[i].lexeme);
  }
  fprintf(f, ")\n");
  if (strcmp(fundef.name.lexeme, "main") == 0) {
    fprintf(f, "{\n");
    fprintf(f, "init_compiler_stack();\n");
    generate_compound(g, fundef.body);
    fprintf(f, "kill_compiler_stack();\n");
    fprintf(f, "}\n");

  } else {
    generate_compound(g, fundef.body);
  }
  end_nt_scope(&g->table);
}

int is_builtin_typename(char *name) {
  if (strcmp(name, "bool") == 0)
    return 1;
  if (strcmp(name, "int") == 0)
    return 1;
  if (strcmp(name, "string") == 0)
    return 1;
  if (strcmp(name, "void") == 0)
    return 1;
  return 0;
}

void generate_forward_defs(generator_t *g, ast_t program) {
  FILE *f = g->f;
  ast_array_t stmts = program->data.program.prog;
  for (int i = 0; i < stmts.length; i++) {
    ast_t stmt = stmts.data[i];
    if (stmt->tag == tdef) {
      struct ast_tdef tdef = stmt->data.tdef;
      char *name = tdef.name.lexeme;
      if (is_builtin_typename(name))
        fprintf(f, "typedef struct %s %s;\n", name, name);
      else
        fprintf(f, "typedef struct %s *%s;\n", name, name);
    }
  }
}

void generate_tdef(generator_t *g, ast_t tdef_ast) {
  FILE *f = g->f;
  struct ast_tdef tdef = tdef_ast->data.tdef;
  char *name = tdef.name.lexeme;
  // fprintf(f, "typedef struct %s %s;\n", name, name);
  fprintf(f, "struct %s{\n", name);
  if (tdef.t == TDEF_PRO) {
    fprintf(f, "enum {\n");
    for (int i = 0; i < tdef.constructors.length; i++) {
      ast_cons cons = tdef.constructors.data[i]->data.cons;
      if (i > 0)
        fprintf(f, ",\n");
      fprintf(f, "%s", cons.name.lexeme);
    }
    fprintf(f, "\n} tag; \n");
    fprintf(f, "union {\n");
    for (int i = 0; i < tdef.constructors.length; i++) {
      ast_cons cons = tdef.constructors.data[i]->data.cons;
      ast_tupledef tuple = cons.type->data.tupledef;
      if (strcmp(tuple.signature.data[0].lexeme, "void") != 0) {
        generate_type(f, cons.type->data.tupledef);
        fprintf(f, " %s;", cons.name.lexeme);
      }
    }
    fprintf(f, "} data;");
  } else {
    for (int i = 0; i < tdef.constructors.length; i++) {
      ast_cons cons = tdef.constructors.data[i]->data.cons;
      ast_tupledef tuple = cons.type->data.tupledef;
      if (strcmp(tuple.signature.data[0].lexeme, "void") != 0) {
        generate_type(f, cons.type->data.tupledef);
        fprintf(f, " %s;", cons.name.lexeme);
      }
    }
  }
  fprintf(f, "};\n");

  return;
}

void transpile(generator_t *g, ast_t program) {
  FILE *f = g->f;
  ast_array_t stmts = program->data.program.prog;
  fprintf(f, "#include \"./src/generation/fundefs.h\"\n");
  fprintf(f, "#include \"./src/generation/fundefs_internal.h\"\n");
  fprintf(f, "#include \"./src/generation/typedefs.h\"\n");
  fprintf(f, "#include \"./RockerAllocator/alloc.h\"\n");
  generate_forward_defs(g, program);

  for (int i = 0; i < stmts.length; i++) {
    ast_t stmt = stmts.data[i];
    generate_statement(g, stmt);
  }
}
