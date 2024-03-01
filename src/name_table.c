#include "name_table.h"
#include "../RockerAllocator/alloc.h"
#include <stdio.h>
#include <string.h>

ast_t get_ref(string_view name, name_table_t table) {
  // get from top_scope
  ast_t res = NULL;
  for (int i = 0; i < table.length; i++) {
    if (svcmp(table.names[i], name) == 0)
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
    if (table->scopes[i] > table->scope) {
      table->length--;
      table->refs.length--;
    } else
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

void push_nt(name_table_t *table, string_view name, nt_kind kind, ast_t ref) {
  if (table->length >= table->capacity) {
    reallocate_table(table);
  }
  table->names[table->length] = name;
  table->kinds[table->length] = kind;
  table->scopes[table->length] = table->scope;
  push_ast_array(&table->refs, ref);
  table->length++;
}
