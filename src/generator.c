#include "generator.h"
#include "../RockerAllocator/alloc.h"
#include "ast.h"
#include <assert.h>
#include <string.h>

generator_t new_generator(char *filename) {
  generator_t res;
  res.f = fopen(filename, "wb");
  if (res.f == NULL)
    perror("Could not open file !");
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

ast_t get_ref(char *name, name_table_t table) {
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

void new_nt_scope(name_table_t *table) {
  table->scope++;
  return;
}

void end_nt_scope(name_table_t *table) {
  for (int i = table->length - 1; i >= 0; i--) {
    if (table->scopes[i] > table->scope)
      table->length--;
    else
      break;
  }
  table->scope--;
}

void reallocate_table(name_table_t *table) {
  table->capacity *= 2;
  table->names = reallocate_compiler_persistent(
      table->names, table->capacity * sizeof(char *));
  table->kinds = reallocate_compiler_persistent(
      table->names, table->capacity * sizeof(nt_kind));
  table->scopes = reallocate_compiler_persistent(table->scopes,
                                                 table->capacity * sizeof(int));
}

void push_nt(name_table_t *table, char *name, nt_kind kind, ast_t ref) {
  if (table->length >= table->capacity) {
    reallocate_table(table);
  }
  table->names[table->length] = name;
  table->kinds[table->length] = kind;
  table->scopes[table->length] = table->scope;
  push_ast_array(&table->refs, ref);
  table->length++;
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

void generate_fundef(FILE *f, ast_fundef fundef) {
  generate_type(f, fundef.ret_type->data.tupledef);
  fprintf(f, " %s(", fundef.name.lexeme);
  for (int i = 0; i < fundef.args.length; i++) {
    if (i > 0)
      fprintf(f, ", ");
    generate_type(f, fundef.types.data[i]->data.tupledef);
    fprintf(f, " ");
    fprintf(f, "%s", fundef.args.data[i].lexeme);
  }
  fprintf(f, ");\n");
}

void transpile(generator_t g, ast_t program) {
  (void)program;
  FILE *f = g.f;
  ast_array_t stmts = program->data.program.prog;
  (void)stmts;
  fprintf(f, "#include \"./src/generation/fundefs.h\"\n");
  fprintf(f, "#include \"./src/generation/typedefs.h\"\n");
  fprintf(f, "int main(void){return 0;}\n");
  for (int i = 0; i < stmts.length; i++) {
    ast_t stmt = stmts.data[i];
    if (stmt->tag == fundef) {
      generate_fundef(f, stmt->data.fundef);
    }
  }
}