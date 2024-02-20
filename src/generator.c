#include "generator.h"
#include <assert.h>
#include <string.h>
#include "../RockerAllocator/alloc.h"
#include "ast.h"
#include "token.h"

generator_t new_generator(char* filename) {
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
  res.names = allocate_compiler_persistent(sizeof(char*) * res.capacity);
  res.scopes = allocate_compiler_persistent(sizeof(int) * res.capacity);
  return res;
}

ast_t get_ref(char* name, name_table_t table) {
  // get from top_scope
  int scope_max = -1;
  ast_t res = NULL;
  for (int i = 0; i < table.length; i++) {
    if (strcmp(table.names[i], name) == 0)
      if (table.scopes[i] > scope_max)
        res = table.refs.data[i];
  }
  return res;
}

void new_nt_scope(name_table_t* table) {
  table->scope++;
  return;
}

void end_nt_scope(name_table_t* table) {
  for (int i = table->length - 1; i >= 0; i--) {
    if (table->scopes[i] > table->scope)
      table->length--;
    else
      break;
  }
  table->scope--;
}

void reallocate_table(name_table_t* table) {
  table->capacity *= 2;
  table->names = reallocate_compiler_persistent(
      table->names, table->capacity * sizeof(char*));
  table->kinds = reallocate_compiler_persistent(
      table->names, table->capacity * sizeof(nt_kind));
  table->scopes = reallocate_compiler_persistent(table->scopes,
                                                 table->capacity * sizeof(int));
}

void push_nt(name_table_t* table, char* name, nt_kind kind, ast_t ref) {
  if (table->length >= table->capacity) {
    reallocate_table(table);
  }
  table->names[table->length] = name;
  table->kinds[table->length] = kind;
  table->scopes[table->length] = table->scope;
  push_ast_array(&table->refs, ref);
  table->length++;
}

void generate_type(FILE* f, ast_tupledef tuple) {
  token_array_t elems = tuple.signature;
  if (elems.length > 1) {
    assert(0 && "TODO: actually handle tuples in geenrate_type");
  }
  if (elems.length == 0) {
    assert(0 && "Unreachable");
  }
  fprintf(f, "%s", elems.data[0].lexeme);
}

void generate_expression(generator_t g, ast_t expr);

void generate_funcall(generator_t g, ast_t fun) {
  FILE* f = g.f;
  ast_funcall funcall = fun->data.funcall;
  fprintf(f, "%s(", funcall.name.lexeme);
  for (int i = 0; i < funcall.args.length; i++) {
    if (i > 0)
      fprintf(f, ", ");
    generate_expression(g, funcall.args.data[i]);
  }
  fprintf(f, ")");
}

int get_literal_string_length(token_t tok) {
  // TODO: handle escape characters
  return strlen(tok.lexeme) - 2;
}

void generate_expression(generator_t g, ast_t expr) {
  FILE* f = g.f;
  if (expr->tag == literal) {
    token_t tok = expr->data.literal.lit;
    if (tok.type != TOK_STR_LIT)
      fprintf(f, "%s", tok.lexeme);
    else {
      fprintf(f, "(string){.data = %s, .length = %d}", tok.lexeme,
              get_literal_string_length(tok));
    }
  } else if (expr->tag == identifier) {
    char* lexeme = expr->data.identifier.id.lexeme;
    ast_t def = get_ref(lexeme, g.table);
    if (def == NULL) {
      // TODO: error
      printf("Unexpected identifier '%s'.\n", lexeme);
      exit(1);
    }
    fprintf(f, "%s", lexeme);
  } else if (expr->tag == funcall) {
    generate_funcall(g, expr);
  } else {
    assert(0 && "TODO");
  }
}

void generate_vardef(generator_t g, ast_t var) {
  FILE* f = g.f;
  ast_vardef vardef = var->data.vardef;
  push_nt(&g.table, vardef.name.lexeme, NT_VAR, var);
  generate_type(f, vardef.type->data.tupledef);
  fprintf(f, " = ");
  generate_expression(g, vardef.expr);
}

void generate_match(generator_t g, ast_t match);

void generate_return(generator_t g, ast_t ret_ast) {
  FILE* f = g.f;
  fprintf(f, "return ");
  generate_expression(g, ret_ast->data.ret.expr);
  fprintf(f, ";\n");
}

void generate_statement(generator_t g, ast_t stmt) {
  FILE* f = g.f;
  if (stmt->tag == vardef) {
    generate_vardef(g, stmt);
  } else if (stmt->tag == match) {
    assert(0 && "TODO");
    generate_match(g, stmt);
  } else if (stmt->tag == ret) {
    generate_return(g, stmt);
  } else {
    generate_expression(g, stmt);
    fprintf(f, ";\n");
  }
}
void generate_compound(generator_t g, ast_t comp) {
  ast_compound compound = comp->data.compound;
  new_nt_scope(&g.table);
  for (int i = 0; i < compound.stmts.length; i++)
    generate_statement(g, compound.stmts.data[i]);
  end_nt_scope(&g.table);
}

void generate_fundef(generator_t g, ast_t fun) {
  // add to name table
  FILE* f = g.f;
  ast_fundef fundef = fun->data.fundef;
  new_nt_scope(&g.table);
  push_nt(&g.table, fundef.name.lexeme, NT_FUN, fun);
  generate_type(f, fundef.ret_type->data.tupledef);
  fprintf(f, " %s(", fundef.name.lexeme);
  for (int i = 0; i < fundef.args.length; i++) {
    push_nt(&g.table, fundef.args.data[i].lexeme, NT_VAR, fun);
    if (i > 0)
      fprintf(f, ", ");
    generate_type(f, fundef.types.data[i]->data.tupledef);
    fprintf(f, " ");
    fprintf(f, "%s", fundef.args.data[i].lexeme);
  }
  fprintf(f, "){\n");
  generate_compound(g, fundef.body);
  fprintf(f, "}\n");

  end_nt_scope(&g.table);
}

void transpile(generator_t g, ast_t program) {
  FILE* f = g.f;
  ast_array_t stmts = program->data.program.prog;
  (void)stmts;
  fprintf(f, "#include \"./src/generation/fundefs.h\"\n");
  fprintf(f, "#include \"./src/generation/typedefs.h\"\n");
  for (int i = 0; i < stmts.length; i++) {
    ast_t stmt = stmts.data[i];
    if (stmt->tag == fundef) {
      generate_fundef(g, stmt);
    }
  }
}