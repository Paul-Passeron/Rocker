#include "ast.h"
#include "../RockerAllocator/alloc.h"

ast_t new_ast(node_t node) {
  ast_t ptr = allocate_compiler_persistent(sizeof(node_t));
  *ptr = node;
  return ptr;
}

ast_array_t new_ast_array(void) {
  ast_array_t res;
  res.data = allocate_compiler_persistent(sizeof(ast_t) * INIT_AST_ARR);
  res.length = 0;
  res.capacity = INIT_AST_ARR;
  return res;
}

void push_ast_array(ast_array_t *arr, ast_t a) {
  if (arr->capacity <= arr->length) {
    arr->capacity *= 2;
    arr->data = reallocate_compiler_persistent(arr->data, arr->capacity * sizeof(ast_t));
  }
  arr->data[arr->length++] = a;
}
