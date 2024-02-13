#include "ast.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ast_t new_ast(node_t n) {
  ast_t ptr = malloc(sizeof(node_t));
  if (ptr == NULL) {
    printf("Could not allocate memory\n");
    exit(1);
  }
  *ptr = n;
  return ptr;
}

ast_t new_op_ast(ast_t left, token_type_t op, ast_t right) {
  return new_ast((node_t){ast_operation,
                          {.ast_operation = {
                               .op = op,
                               .left = left,
                               .right = right,
                           }}});
}

void ast_array_push(ast_array_t* arr, ast_t a) {
  if (arr->length >= arr->capacity) {
    arr->capacity *= 2;
    arr->data = realloc(arr->data, arr->capacity * sizeof(ast_t));
  }
  arr->data[arr->length++] = a;
}

void new_ast_array(ast_array_t* arr) {
  arr->capacity = INIT_AST_ARR;
  arr->length = 0;
  arr->data = malloc(sizeof(ast_t) * arr->capacity);
}

void kill_ast_array(ast_array_t arr) {
  for (int i = 0; i < arr.length; i++) {
    free_ast(arr.data[i]);
  }
  free(arr.data);
}

void print_n_tabs(int n) {
  for (int i = 0; i < n; i++)
    printf("|   ");
}

void ast_print_aux(ast_t a, int d) {
  print_n_tabs(d);
  if (a == NULL)
    return;
  switch (a->tag) {
    case ast_type: {
      printf("Type: ");
      struct ast_type data = a->data.ast_type;
      for (int i = 0; i < data.chain.length; i++) {
        printf("%s", data.chain.data[i].lexeme);
        if (i != data.chain.length - 1)
          printf(" -> ");
      }
    } break;
    case ast_identifier: {
      struct ast_identifier data = a->data.ast_identifier;
      printf("Identifier: %s", data.id.lexeme);
    } break;
    case ast_let_binding: {
      struct ast_let_binding data = a->data.ast_let_binding;
      printf("Let binding:\n");
      if (data.type_sig != NULL) {
        ast_print_aux(data.type_sig, d + 1);
        printf("\n");
      }
      if (!data.is_void) {
        print_n_tabs(d + 1);
        printf("NAME: %s\n", data.name.lexeme);

        if (data.args.data != NULL && data.args.length > 0) {
          print_n_tabs(d + 1);
          printf("ARGS:");
          for (int i = 0; i < data.args.length; i++)
            printf(" '%s' ", data.args.data[i].lexeme);
          printf("\n");
        }
      }
      print_n_tabs(d + 1);
      printf("RIGHT:\n");
      ast_print_aux(data.right, d + 2);
      printf("\n");
    } break;
    case ast_literal: {
      struct ast_literal data = a->data.ast_literal;
      printf("Literal: %s", data.literal.lexeme);
    } break;
    case ast_operation: {
      struct ast_operation data = a->data.ast_operation;
      printf("Operation: %s\n", lexeme_of_type(data.op));
      print_n_tabs(d + 1);
      printf("LEFT:\n");
      ast_print_aux(data.left, d + 2);
      printf("\n");
      print_n_tabs(d + 1);
      printf("RIGHT:\n");
      ast_print_aux(data.right, d + 2);
    } break;
    case ast_curry: {
      struct ast_curry data = a->data.ast_curry;
      printf("Curry:\n");
      print_n_tabs(d + 1);
      printf("Caller:\n");
      ast_print_aux(data.caller, d + 2);
      printf("\n");
      print_n_tabs(d + 1);
      printf("Arg:\n");
      ast_print_aux(data.arg, d + 2);
    } break;
    case ast_in: {
      struct ast_in data = a->data.ast_in;
      printf("In:\n");
      print_n_tabs(d + 1);
      printf("First:\n");
      ast_print_aux(data.first, d + 2);
      print_n_tabs(d + 1);
      printf("Second:\n");
      ast_print_aux(data.second, d + 2);
    } break;
    case ast_match: {
      struct ast_match data = a->data.ast_match;
      printf("Match:\n");
      print_n_tabs(d + 1);
      printf("Expression to match:\n");
      ast_print_aux(data.to_match, d + 2);
      printf("\n");
      print_n_tabs(d + 1);
      printf("Cases:");
      for (int i = 0; i < data.cases.length; i++) {
        printf("\n");
        ast_print_aux(data.cases.data[i], d + 2);
      }
    } break;
    case ast_match_case: {
      struct ast_match_case data = a->data.ast_match_case;
      printf("Case:\n");
      ast_print_aux(data.matcher, d + 1);
      printf("\n");
      print_n_tabs(d + 1);
      printf("Expression:\n");
      ast_print_aux(data.expression, d + 2);
    } break;
    case ast_type_def: {
      struct ast_type_def data = a->data.ast_type_def;
      printf("Typedef (");
      if (data.is_rec)
        printf("record");
      else
        printf("product");
      printf(") '%s'\n", data.name.lexeme);
      print_n_tabs(d + 1);
      printf("Constructors:");
      for (int i = 0; i < data.constructors.length; i++) {
        printf("\n");
        ast_print_aux(data.constructors.data[i], d + 2);
      }
      printf("\n");
    } break;
    case ast_constructor: {
      struct ast_constructor data = a->data.ast_constructor;
      printf("Constructor '%s'\n", data.name.lexeme);
      print_n_tabs(d + 1);
      printf("Signature:\n");
      ast_print_aux(data.signature, d + 2);
    } break;
  }
}

void ast_print(ast_t a) {
  ast_print_aux(a, 0);
}

void uncurry_aux(ast_array_t* arr, ast_t a) {
  if (a->tag != ast_curry)
    return ast_array_push(arr, a);
  struct ast_curry data = a->data.ast_curry;
  uncurry_aux(arr, data.caller);
  return ast_array_push(arr, data.arg);
}

ast_array_t uncurry(ast_t curr) {
  ast_array_t res;
  new_ast_array(&res);
  uncurry_aux(&res, curr);
  return res;
}

void free_ast(ast_t a) {
  if (a == NULL)
    return;
  switch (a->tag) {
    case ast_type: {
      struct ast_type data = a->data.ast_type;
      free(data.chain.data);
    } break;
    case ast_identifier: break;
    case ast_let_binding: {
      struct ast_let_binding data = a->data.ast_let_binding;
      // free_token_array(data.args);
      free(data.args.data);
      free_ast(data.type_sig);
      free_ast(data.right);
      // if (!data.is_void)
      //   free_token(data.name);
    } break;
    case ast_literal:  break;
    case ast_operation: {
      struct ast_operation data = a->data.ast_operation;
      free_ast(data.left);
      free_ast(data.right);
      // free_token(data.op);
    } break;
    case ast_curry: {
      struct ast_curry data = a->data.ast_curry;
      free_ast(data.arg);
      free_ast(data.caller);
    } break;
    case ast_in: {
      struct ast_in data = a->data.ast_in;
      free_ast(data.first);
      free_ast(data.second);
    } break;
    case ast_match: {
      struct ast_match data = a->data.ast_match;
      free_ast(data.to_match);
      kill_ast_array(data.cases);
    } break;
    case ast_match_case: {
      struct ast_match_case data = a->data.ast_match_case;
      free_ast(data.expression);
      free_ast(data.matcher);
    } break;
    case ast_type_def: {
      struct ast_type_def data = a->data.ast_type_def;
      // free_token(data.name);
      kill_ast_array(data.constructors);
    } break;
    case ast_constructor: {
      struct ast_constructor data = a->data.ast_constructor;
      // free_token(data.name);
      free_ast(data.signature);
    } break;
    
  }
  free(a);
}