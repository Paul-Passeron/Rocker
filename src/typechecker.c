#include "typechecker.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "generator.h"
#include "name_table.h"
#include "token.h"

rocker_type_t get_error_type(void) {
  return (rocker_type_t){error_type, {.builtin = 1}};
}

rocker_type_t type_of_tupledef(typechecker_t tc, ast_tupledef t) {
  if (t.signature.length > 1)
    assert(0 && "TODO: handle tuples in typechecking");
  if (t.signature.length == 0)
    return get_error_type();
  char* type_name = t.signature.data[0].lexeme;
  // Is it builtin ?
  if (strcmp(type_name, "int") == 0)
    return (rocker_type_t){builtin_int, {.builtin = 1}};
  if (strcmp(type_name, "char") == 0)
    return (rocker_type_t){builtin_char, {.builtin = 1}};
  if (strcmp(type_name, "string") == 0)
    return (rocker_type_t){builtin_string, {.builtin = 1}};
  if (strcmp(type_name, "bool") == 0)
    return (rocker_type_t){builtin_bool, {.builtin = 1}};
  // Is it user-defined ?
  ast_t ref = get_ref(type_name, tc.nt);
  if (ref == NULL)
    return get_error_type();
  // must be tupledef
  return (rocker_type_t){user_defined, {.user_defined_type = {type_name}}};
  // This type does not exist !
  return get_error_type();
}

rocker_type_t get_type_of_expr(typechecker_t tc, ast_t expr) {
  if (expr->tag == literal) {
    token_type_t t = expr->data.literal.lit.type;
    switch (t) {
      case TOK_STR_LIT:
        return (rocker_type_t){builtin_string, {.builtin = 1}};
      case TOK_CHR_LIT:
        return (rocker_type_t){builtin_char, {.builtin = 1}};
      case TOK_NUM_LIT:
        return (rocker_type_t){builtin_int, {.builtin = 1}};
      default:
        return get_error_type();
    }
  } else if (expr->tag == funcall) {
    ast_t fundef = get_ref(expr->data.funcall.name.lexeme, tc.nt);
    if (fundef == NULL)
      return get_error_type();
    ast_fundef fun = fundef->data.fundef;
    return type_of_tupledef(tc, fun.ret_type->data.tupledef);
  }
  return get_error_type();
}
int are_types_compatibles(typechecker_t tc,
                          rocker_type_t t1,
                          rocker_type_t t2) {
  // for the moment we won't handle non-builtin types
  if (t1.tag == error_type || t2.tag == error_type)
    return 0;
  if (t1.tag == user_defined || t2.tag == user_defined)
    return 1;
  if (t1.tag == t2.tag)
    return 1;
  if ((t1.tag == builtin_char && t2.tag == builtin_int) ||
      (t1.tag == builtin_int && t2.tag == builtin_char))
    return 1;
  if ((t1.tag == builtin_bool && t2.tag == builtin_int) ||
      (t1.tag == builtin_int && t2.tag == builtin_bool))
    return 1;
  if ((t1.tag == builtin_bool && t2.tag == builtin_char) ||
      (t1.tag == builtin_char && t2.tag == builtin_bool))
    return 1;
  (void)tc;
  return 0;
}

int tc_program(ast_t program) {
  ast_program prog = program->data.program;
  typechecker_t tc;
  tc.current_function = NULL;

  // Creating the initial name table !
  tc.nt = new_name_table();
  // pushing builtin types into the name table
  push_nt(&tc.nt, "int", NT_BUILTIN_TYPE, program);
  push_nt(&tc.nt, "char", NT_BUILTIN_TYPE, program);
  push_nt(&tc.nt, "string", NT_BUILTIN_TYPE, program);
  push_nt(&tc.nt, "bool", NT_BUILTIN_TYPE, program);
  new_nt_scope(&tc.nt);
  for (int i = 0; i < prog.prog.length; i++) {
    ast_t stmt = prog.prog.data[i];
    if (stmt->tag == tdef) {
      // add it to the name_table
      char* name = stmt->data.tdef.name.lexeme;
      nt_kind kind = NT_USER_TYPE;
      push_nt(&tc.nt, name, kind, stmt);
    }
    if (stmt->tag == vardef) {
      // global variable that we add to the name table !
      char* name = stmt->data.vardef.name.lexeme;
      nt_kind kind = NT_VAR;
      push_nt(&tc.nt, name, kind, stmt);
    }
    if (stmt->tag == fundef) {
      char* name = stmt->data.fundef.name.lexeme;
      nt_kind kind = NT_FUN;
      push_nt(&tc.nt, name, kind, stmt);
    }
  }

  // checking var definitions
  for (int i = 0; i < prog.prog.length; i++) {
    ast_t stmt = prog.prog.data[i];
    if (stmt->tag == vardef) {
      ast_vardef vardef = stmt->data.vardef;
      rocker_type_t expr_type = get_type_of_expr(tc, vardef.expr);
      rocker_type_t expected = type_of_tupledef(tc, vardef.type->data.tupledef);
      if (!are_types_compatibles(tc, expr_type, expected))
        return 0;
    }
  }

  end_nt_scope(&tc.nt);
  return 1;
}
