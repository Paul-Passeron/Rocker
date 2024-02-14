#include "generator.h"
#include "ast.h"
#include "token.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

closure_stack cl_stack;
doubles_table table;

void generate_type_name(token_array_t arr, FILE *f) {
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

void generate_function_signature(fun_def fun, FILE *f) {
  fprintf(f, "// Generating function definition for: %s\n", fun.name.lexeme);

  // if we havea simple return type (a vlue or void)
  // We expect all needed closures struct to be defined in the
  // transpiled code before this gets executed
  if (fun.return_type.length == 1) {
    // a normal C function, basically
    char *ret_type_name = fun.return_type.data[0].lexeme;
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

void type_args(typed_arg *arr, token_array_t args, ast_t type_sig) {
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

/*
typedef struct closure_t {
  typed_arg elems[TYPED_ARG_CAP];
  int length;
  char* name;
} closure_t;
*/

closure_t get_closure(ast_t let, char *outer_closure) {
  // a let binding is basically like so:
  // let name : type =>
  //  let ... in
  //  let ... in
  //  ...
  //  let ... in
  // value
  // First we have a let binding then either a value either match (considered
  // like a value) or finally an ast_in

  assert(let->tag == ast_let_binding && "Expected let binding in get_closure");
  struct ast_let_binding data = let->data.ast_let_binding;

  closure_t res;
  // Maybe we'll have to mangle
  res.name = data.name.lexeme;
  res.length = 0;
  memset(res.elems, 0, sizeof(res.elems));
  // First, we add the outer closure
  // As we onmy have the closure name, we create a fake token for a fake type
  char added[] = "_closure";
  char *closure_name = malloc(strlen(outer_closure) + strlen(added) + 1);
  sprintf(closure_name, "%s%s", outer_closure, added);
  token_t tok = {
      .col = -1, .lexeme = closure_name, .line = -1, .type = TOK_IDENTIFIER};
  token_array_t closure_type;
  new_token_array(&closure_type);
  token_array_push(&closure_type, tok);
  token_t name = {
      .col = -1, .lexeme = "outer_closure", .line = -1, .type = TOK_IDENTIFIER};
  typed_arg outer_closure_arg;
  outer_closure_arg.name = name;
  outer_closure_arg.type = closure_type;
  outer_closure_arg.allocated = 0;

  res.elems[res.length++] = outer_closure_arg;

  // We add the args of the let binding in the closure
  token_array_t type_sig = data.type_sig->data.ast_type.chain;
  for (int i = 0; i < data.args.length; i++) {
    typed_arg arg;
    arg.name = data.args.data[i];
    arg.allocated = 1;
    token_array_t type;
    new_token_array(&type);

    // single type for the moment
    token_array_push(&type, type_sig.data[i]);
    arg.type = type;
    res.elems[res.length++] = arg;
  }
  if (data.right->tag != ast_in)
    return res;

  ast_array_t arr = un_nest(data.right);
  for (int i = 0; i < arr.length; i++) {
    ast_t elem = arr.data[i];
    if (elem->tag == ast_let_binding) {
      // Then we add it to the closure if its is not a 'let ()'
      struct ast_let_binding elem_data = elem->data.ast_let_binding;
      if (!elem_data.is_void) {
        typed_arg arg;
        arg.allocated = 0;
        arg.name = elem_data.name;
        // for the moment, we don't save functions inside
        // closures are they are immutable and saved globally
        token_array_t type = elem_data.type_sig->data.ast_type.chain;
        if (type.length == 1) {
          arg.type = type;
          res.elems[res.length++] = arg;
        }
      }
    }
  }
  free(arr.data);
  return res;
}

void print_closure(closure_t closure) {
  printf("Closure '%s':\n", closure.name);
  for (int i = 0; i < closure.length; i++) {
    typed_arg arg = closure.elems[i];
    printf("   %s: %s\n", arg.name.lexeme, arg.type.data[0].lexeme);
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

void generate_prolog(FILE *f) {
  fprintf(f, "#include <stdio.h>\n\n");
  fprintf(f, "typedef struct string{");
  fprintf(f, "char *s;");
  fprintf(f, "int length;");
  fprintf(f, "}string;\n\n");
  fprintf(f, "void print(string s)");
  fprintf(f, "{");
  fprintf(f, "for (int i = 0; i < s.length; i++)");
  fprintf(f, "putchar(s.s[i]);");
  fprintf(f, "}\n\n");
}

void generate_closure_def(closure_t closure, FILE *f) {
  // TODO: mangle closure struct names
  fprintf(f, "typedef struct %s_closure {\n", closure.name);

  for (int i = 0; i < closure.length; i++) {
    generate_type_name(closure.elems[i].type, f);
    fprintf(f, " %s;\n", closure.elems[i].name.lexeme);
  }
  fprintf(f, "  char __closure__;\n} %s_closure;\n\n", closure.name);
}

int get_num_repeat(doubles_table t, char *name) {
  for (int i = 0; i < t.length; i++) {
    if (strcmp(t.names[i], name) == 0)
      return t.num[i];
  }
  return 0;
}

char *name_mangle(ast_t let_binding) {
  // is not meant to be called multiple times for
  // the same function !!!
  printf("name mangle\n");
  char *buffer = malloc(128);
  memset(buffer, 0, 128);
  struct ast_let_binding data = let_binding->data.ast_let_binding;
  char *function_mangler_prefix = "_Z";
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

void kill_closure(closure_t closure) {
  // First is outer closure which is allocated if it is global_closure
  // free_token(closure.elems[0].name);
  free_token(closure.elems[0].type.data[0]);
  free(closure.elems[0].type.data);

  for (int i = 1; i < closure.length; i++) {
    if (closure.elems[i].allocated) {
      free(closure.elems[i].type.data);
    }
  }
}
