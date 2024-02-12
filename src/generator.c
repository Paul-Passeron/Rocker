#include "generator.h"
#include "ast.h"
#include "token.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

closure_stack cl_stack;
doubles_table table;

void generate_type_name(token_array_t arr, FILE* f) {
  // Single type
  if (arr.length == 1) {
    fprintf(f, "%s", arr.data[0].lexeme);
    // Function-types should not be supported in this
    // function

  } else {
    printf("Could not generate empty type !\n");
    exit(1);
  }
}

void generate_function_signature(fun_def fun, FILE* f) {
  fprintf(f, "// Generating function definition for: %s\n", fun.name.lexeme);

  // if we havea simple return type (a vlue or void)
  // We expect all needed closures struct to be defined in the
  // transpiled code before this gets executed
  if (fun.return_type.length == 1) {
    // a normal C function, basically
    char* ret_type_name = fun.return_type.data[0].lexeme;
    fprintf(f,
            "%s %s(const %s_closure __gcl, struct "
            "%s_closure *__lcl",
            ret_type_name, fun.name.lexeme, fun.closure_name, fun.name.lexeme);
    for (int i = 0; i < fun.arity; i++) {
      typed_arg t = fun.args[i];
      fprintf(f, ", ");
      generate_type_name(t.type, f);
      fprintf(f, " %s", t.name.lexeme);
    }
    fprintf(f, ")\n");
  } else {
    assert(0 && "TODO: function type support in generate_function_signature");
  }
}
int get_type_sig_length(ast_t type_sig) {
  struct ast_type data = type_sig->data.ast_type;
  return data.chain.length;
}

void type_args(typed_arg* arr, token_array_t args, ast_t type_sig) {
  for (int i = 0; i < args.length; i++) {
    typed_arg res;
    res.name = args.data[i];
    token_array_t t;
    new_token_array(&t);
    token_array_push(&t, type_sig->data.ast_type.chain.data[i]);
    res.type = t;
    arr[i] = res;
  }
}

fun_def fundef_from_let(ast_t bind) {
  struct ast_let_binding binding = bind->data.ast_let_binding;
  token_array_t return_type;
  new_token_array(&return_type);
  struct ast_type type_data = binding.type_sig->data.ast_type;
  int type_l = type_data.chain.length;
  for (int i = binding.args.length; i < type_l; i++) {
    if (strcmp(type_data.chain.data[i].lexeme, "void") || i != 0)
      token_array_push(&return_type, type_data.chain.data[i]);
  }
  fun_def res;
  res.arity = binding.args.length;
  res.return_type = return_type;
  if (cl_stack.length > 0)
    res.closure_name = cl_stack.data[cl_stack.length - 1].name;
  else
    res.closure_name = "global";
  res.name = binding.name;
  type_args(res.args, binding.args, binding.type_sig);
  return res;
}

void generate_prolog(FILE* f) {
  fprintf(f, "#include <stdio.h>\n\n");
  fprintf(f, "typedef struct\n");
  fprintf(f, "{\n");
  fprintf(f, "    char *s;\n");
  fprintf(f, "    int length;\n");
  fprintf(f, "} string;\n\n");
  fprintf(f, "void print(string s)\n");
  fprintf(f, "{\n");
  fprintf(f, "    for (int i = 0; i < s.length; i++)\n");
  fprintf(f, "        putchar(s.s[i]);\n");
  fprintf(f, "}\n");
  fprintf(f, "\n");
}

void generate_closure_def(closure_t closure, FILE* f) {
  // TODO: mangle closure struct names
  fprintf(f, "typedef struct %s_closure {\n", closure.name);
  if (closure.length > 0)
    assert(0 && "TODO: non-empty closure generation");
  fprintf(f, "  char __closure__;\n} %s_closure;\n\n", closure.name);
}

int get_num_repeat(doubles_table t, char* name) {
  for (int i = 0; i < t.length; i++) {
    if (strcmp(t.names[i], name) == 0)
      return t.num[i];
  }
  return 0;
}

char* name_mangle(ast_t let_binding) {
  // is not meant to be called multiple times for
  // the same function !!!
  char* buffer = malloc(128);
  memset(buffer, 0, 128);
  struct ast_let_binding data = let_binding->data.ast_let_binding;
  char* function_mangler_prefix = "_Z";
  int num = get_num_repeat(table, data.name.lexeme);
  sprintf(buffer, "%s%ld%s%i\n", function_mangler_prefix,
          strlen(data.name.lexeme), data.name.lexeme, num);
  // We increment the counter
  if (num == 0) {
    table.names[table.length] = data.name.lexeme;
    table.num[table.length++] = 1;
  } else {
    for (int i = 0; i < table.length; i++)
      if (strcmp(table.names[i], data.name.lexeme) == 0) {
        table.num[i] += 1;
        break;
      }
  }
  return buffer;
}