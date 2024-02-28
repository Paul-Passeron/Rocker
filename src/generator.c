#include "generator.h"
#include "../RockerAllocator/alloc.h"
#include "ast.h"
#include "name_table.h"
#include "token.h"
#include <assert.h>
#include <string.h>

void generate_statement(generator_t *g, ast_t stmt);
void generate_compound(generator_t *g, ast_t comp);
void generate_tdef(generator_t *g, ast_t tdef_ast);
void generate_fundef(generator_t *g, ast_t fun);
int is_builtin_typename(char *name);
void generate_sub_as_expression(generator_t *g, ast_t expr);
void generate_assignement(generator_t *g, ast_t assignment);

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

void generate_type(FILE *f, ast_t a) {
  ast_type type = a->data.type;
  if (type.is_array)
    fprintf(f, "__internal_dynamic_array_t");
  else
    fprintf(f, "%s", type.name.lexeme);
}

void generate_expression(generator_t *g, ast_t expr);

void generate_append(generator_t *g, ast_funcall funcall) {
  FILE *f = g->f;
  if (funcall.args.length != 2) {
    printf("TODO: append has 2 arguments");
    exit(1);
  }
  ast_t arr = funcall.args.data[0];
  if (arr->tag != identifier) {
    printf("Arrays must be bound by name for the moment\n");
    exit(1);
  }
  char *name = arr->data.identifier.id.lexeme;
  ast_t ref = get_ref(name, g->table);
  if (ref == NULL) {
    printf("Array is not declared in the current scope\n");
    exit(1);
  }
  if (ref->tag != vardef) {

    printf("Arrays must be declared as variables: %d\n", ref->tag);
    exit(1);
  }
  ast_type type = ref->data.vardef.type->data.type;
  char *type_name = type.name.lexeme;
  fprintf(f, "%s_push_array(", type_name);
  generate_expression(g, funcall.args.data[0]);
  fprintf(f, ", ");
  generate_expression(g, funcall.args.data[1]);
  fprintf(f, ")");
}

void generate_get(generator_t *g, ast_funcall funcall) {
  FILE *f = g->f;
  if (funcall.args.length != 2) {
    printf("TODO: get has 2 arguments");
    exit(1);
  }
  ast_t arr = funcall.args.data[0];
  if (arr->tag != identifier) {
    printf("Arrays must be bound by name for the moment\n");
    exit(1);
  }
  char *name = arr->data.identifier.id.lexeme;
  ast_t ref = get_ref(name, g->table);
  if (ref == NULL) {
    printf("Array is not declared in the current scope\n");
    exit(1);
  }
  if (ref->tag != vardef) {
    printf("Arrays must be declared as variables\n");
    exit(1);
  }
  ast_type type = ref->data.vardef.type->data.type;
  char *type_name = type.name.lexeme;
  fprintf(f, "%s_get_elem(", type_name);
  generate_expression(g, funcall.args.data[0]);
  fprintf(f, ", ");
  generate_expression(g, funcall.args.data[1]);
  fprintf(f, ")");
}

void generate_set(generator_t *g, ast_funcall funcall) {
  FILE *f = g->f;
  if (funcall.args.length != 3) {
    printf("TODO: set has 3 arguments");
    exit(1);
  }
  ast_t arr = funcall.args.data[0];
  if (arr->tag != identifier) {
    printf("Arrays must be bound by name for the moment\n");
    exit(1);
  }
  char *name = arr->data.identifier.id.lexeme;
  ast_t ref = get_ref(name, g->table);
  if (ref == NULL) {
    printf("Array is not declared in the current scope\n");
    exit(1);
  }
  if (ref->tag != vardef) {
    printf("Arrays must be declared as variables: %d\n", ref->tag);
    exit(1);
  }
  ast_type type = ref->data.vardef.type->data.type;
  char *type_name = type.name.lexeme;
  fprintf(f, "%s_set_elem(", type_name);
  generate_expression(g, funcall.args.data[0]);
  fprintf(f, ", ");
  generate_expression(g, funcall.args.data[1]);
  fprintf(f, ", ");
  generate_expression(g, funcall.args.data[2]);
  fprintf(f, ")");
}

void generate_funcall(generator_t *g, ast_t fun) {
  FILE *f = g->f;
  ast_funcall funcall = fun->data.funcall;
  if (strcmp(funcall.name.lexeme, "append") == 0) {
    generate_append(g, funcall);
  } else if (strcmp(funcall.name.lexeme, "get") == 0) {
    generate_get(g, funcall);
  } else if (strcmp(funcall.name.lexeme, "set") == 0) {
    generate_set(g, funcall);
  } else {
    fprintf(f, "%s(", funcall.name.lexeme);
    for (int i = 0; i < funcall.args.length; i++) {
      if (i > 0)
        fprintf(f, ", ");
      generate_expression(g, funcall.args.data[i]);
    }
    fprintf(f, ")");
  }
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

void generate_array_funcs(generator_t *g, char *type_name) {
  FILE *f = g->f;
  fprintf(f, "__internal_dynamic_array_t %s_make_array(void) {\n", type_name);
  fprintf(f, "return __internal_make_array(sizeof(int));\n");
  fprintf(f, "}\n\n");
  fprintf(f, "void %s_push_array(__internal_dynamic_array_t arr, %s elem) {\n",
          type_name, type_name);
  fprintf(f, "  __internal_push_array(arr, &elem);\n");
  fprintf(f, "}\n\n");
  fprintf(f, "%s %s_pop_array(__internal_dynamic_array_t arr) {\n", type_name,
          type_name);
  fprintf(f, "  %s *res = __internal_pop_array(arr);\n", type_name);
  fprintf(f, "  return *res;\n");
  fprintf(f, "}\n\n");
  fprintf(f, "%s %s_get_elem(__internal_dynamic_array_t arr, size_t index) {\n",
          type_name, type_name);
  fprintf(f, "  %s *res = __internal_get_elem(arr, index);\n", type_name);
  fprintf(
      f,
      "  if (res == NULL){ printf(\"NULL ELEMENT IN %s_get_elem\"); exit(1);}",
      type_name);

  fprintf(f, "  return *res;\n");
  fprintf(f, "}\n\n");
  fprintf(f,
          "void %s_set_elem(__internal_dynamic_array_t arr, size_t index, "
          "%s elem) {\n",
          type_name, type_name);
  fprintf(f, "  __internal_set_elem(arr, index, &elem);\n");
  fprintf(f, "}\n\n");
  fprintf(f,
          "void %s_insert(__internal_dynamic_array_t arr, size_t index, "
          "%s elem) {\n",
          type_name, type_name);
  fprintf(f, "  __internal_insert(arr, index, &elem);\n");
  fprintf(f, "}\n\n");
}

void generate_sub(generator_t *g, ast_t sub_ast, int is_rec) {
  FILE *f = g->f;
  ast_sub sub = sub_ast->data.sub;
  assert(sub.path.length == 1 && "TODO; implement nested subs");
  if (is_rec) {
    generate_sub_as_expression(g, sub_ast);
  } else {
    // We check if the expr is a wildcard
    int is_wild = 0;
    if (sub.expr->tag == literal)
      if (sub.expr->data.literal.lit.type == TOK_WILDCARD)
        is_wild = 1;
    fprintf(f, "{.tag = %s", sub.path.data[0].lexeme);
    if (!is_wild) {
      fprintf(f, ", .data = ");
      generate_expression(g, sub.expr);
    }
    fprintf(f, "}");
  }
}

void generate_loop(generator_t *g, ast_t loop_ast) {
  FILE *f = g->f;
  ast_loop loop = loop_ast->data.loop;
  new_nt_scope(&g->table);
  push_nt(&g->table, loop.variable.lexeme, NT_VAR, loop_ast);
  fprintf(f, "for(int %s =", loop.variable.lexeme);
  generate_expression(g, loop.start);
  fprintf(f, "; i <= ");
  generate_expression(g, loop.end);
  fprintf(f, "; i++)\n");
  generate_statement(g, loop.statement);
  end_nt_scope(&g->table);
}

void generate_sub_as_expression(generator_t *g, ast_t expr) {
  FILE *f = g->f;
  ast_sub sub = expr->data.sub;
  assert(sub.path.length == 1 && "SUB AS EXPRESSION LENGTH LIMIT\n");
  fprintf(f, "%s->", sub.path.data[0].lexeme);
  generate_expression(g, sub.expr);
}

void generate_while_loop(generator_t *g, ast_t loop) {
  FILE *f = g->f;
  ast_while_loop while_loop = loop->data.while_loop;
  fprintf(f, "while (");
  generate_expression(g, while_loop.condition);
  fprintf(f, ")\n");
  generate_statement(g, while_loop.statement);
}

void generate_enum_tdef(generator_t *g, ast_t expr) {
  FILE *f = g->f;
  ast_enum_tdef enum_tdef = expr->data.enum_tdef;
  fprintf(f, "enum %s {\n", enum_tdef.name.lexeme);
  for (int i = 0; i < enum_tdef.items.length; i++) {
    if (i > 0)
      fprintf(f, ",\n");
    fprintf(f, "%s", enum_tdef.items.data[i].lexeme);
  }
  fprintf(f, "};\n");
}

void generate_expression(generator_t *g, ast_t expr) {
  FILE *f = g->f;
  if (expr->tag == literal) {
    token_t tok = expr->data.literal.lit;
    if (tok.type != TOK_STR_LIT)
      fprintf(f, "%s", tok.lexeme);
    else
      fprintf(f, "new_string((string){.data = %s, .length = %d})", tok.lexeme,
              get_literal_string_length(tok) - 1);
  } else if (expr->tag == identifier) {
    char *lexeme = expr->data.identifier.id.lexeme;
    fprintf(f, "%s", lexeme);
  } else if (expr->tag == funcall)
    generate_funcall(g, expr);
  else if (expr->tag == op)
    generate_op(g, expr);
  else if (expr->tag == ifstmt)
    generate_if_statement(g, expr);
  else if (expr->tag == compound)
    generate_compound(g, expr);
  else if (expr->tag == loop)
    generate_loop(g, expr);
  else if (expr->tag == sub)
    generate_sub_as_expression(g, expr);
  else if (expr->tag == assign)
    generate_assignement(g, expr);
  else if (expr->tag == while_loop)
    generate_while_loop(g, expr);

  else {
    printf("TAG is %d\n", expr->tag);
    assert(0 && "TODO");
  }
}

void generate_assignement(generator_t *g, ast_t assignment) {
  FILE *f = g->f;
  ast_assign assign = assignment->data.assign;
  generate_expression(g, assign.target);
  fprintf(f, " = ");
  generate_expression(g, assign.expr);
}

void generate_vardef(generator_t *g, ast_t var) {
  FILE *f = g->f;
  ast_vardef vardef = var->data.vardef;
  push_nt(&g->table, vardef.name.lexeme, NT_VAR, var);
  char *type_name = vardef.type->data.type.name.lexeme;
  if (vardef.type->data.type.is_array) {
    generate_type(f, vardef.type);
    fprintf(f, " %s = \n", vardef.name.lexeme);
    if (vardef.expr->tag != literal) {
      generate_expression(g, vardef.expr);
      fprintf(f, ";\n");
    } else if (vardef.expr->data.literal.lit.type != TOK_ARR_DECL) {
      printf("Cannot declare arrays this way yet\n");
      exit(1);
    } else
      fprintf(f, "__internal_make_array(sizeof(%s));\n", type_name);
  } else if (is_builtin_typename(type_name)) {
    generate_type(f, vardef.type);
    fprintf(f, " %s = ", vardef.name.lexeme);
    // Temporary, we'll need to store the constructors in the name table, with
    // a flag saying if it's void or not
    if (vardef.expr->tag == sub)
      generate_sub_as_expression(g, vardef.expr);
    else
      generate_expression(g, vardef.expr);
    fprintf(f, ";\n");
  } else if (!is_builtin_typename(type_name) &&
             vardef.expr->tag == record_expr) {
    fprintf(f, "struct ");
    generate_type(f, vardef.type);
    fprintf(f, " tmp_%s = ", vardef.name.lexeme);
    ast_record_expr rec = vardef.expr->data.record_expr;
    if (vardef.is_rec) {
      fprintf(f, "{\n");
      for (int i = 0; i < rec.names.length; i++) {
        if (i > 0)
          fprintf(f, ",\n");
        ast_t expr = rec.exprs.data[i];
        fprintf(f, ".%s = ", rec.names.data[i].lexeme);
        if (expr->tag == sub)
          generate_sub_as_expression(g, expr);
        else
          generate_expression(g, expr);
      }
      fprintf(f, "};");

    } else {
      if (vardef.expr->tag == sub) {
        generate_sub_as_expression(g, vardef.expr);
      } else {
        generate_expression(g, vardef.expr);
      }
      fprintf(f, ";\n");
    }
    generate_type(f, vardef.type);
    fprintf(f, " %s = allocate_compiler_persistent(sizeof(struct ",
            vardef.name.lexeme);
    generate_type(f, vardef.type);
    fprintf(f, "));\n");
    fprintf(f, "*%s = tmp_%s;\n", vardef.name.lexeme, vardef.name.lexeme);
  } else {
    generate_type(f, vardef.type);
    fprintf(f, " %s = ", vardef.name.lexeme);
    // Temporary, we'll need to store the constructors in the name table, with
    // a flag saying if it's void or not
    if (vardef.expr->tag == sub)
      generate_sub_as_expression(g, vardef.expr);
    else
      generate_expression(g, vardef.expr);
    fprintf(f, ";\n");
  }
}

void generate_match(generator_t *g, ast_t match) {
  (void)g;
  (void)match;
}

void generate_return(generator_t *g, ast_t ret_ast) {
  FILE *f = g->f;
  fprintf(f, "return ");
  if (ret_ast->data.ret.expr != NULL)
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

  } else if (stmt->tag == enum_tdef)
    generate_enum_tdef(g, stmt);
  else {
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
  if (strcmp(fundef.name.lexeme, "main") != 0) {
    generate_type(f, fundef.ret_type);
    fprintf(f, " %s(", fundef.name.lexeme);
    for (int i = 0; i < fundef.args.length; i++) {
      push_nt(&g->table, fundef.args.data[i].lexeme, NT_VAR, fun);
      if (i > 0)
        fprintf(f, ", ");
      generate_type(f, fundef.types.data[i]);
      fprintf(f, " ");
      fprintf(f, "%s", fundef.args.data[i].lexeme);
    }
    fprintf(f, ")\n");
    generate_compound(g, fundef.body);
    fprintf(f, "\n\n");
  } else {
    fprintf(f, "int main() {\n");
    fprintf(f, "init_compiler_stack();\n");
    generate_compound(g, fundef.body);
    fprintf(f, "kill_compiler_stack();\n");
    fprintf(f, "return 0;\n");
    fprintf(f, "}\n\n");
  }
  end_nt_scope(&g->table);
}

int is_builtin_typename(char *name) {
  if (strcmp(name, "boolean") == 0)
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
      fprintf(f, "typedef struct %s *%s;\n", name, name);
    }
    if (stmt->tag == enum_tdef) {
      struct ast_tdef tdef = stmt->data.tdef;
      char *name = tdef.name.lexeme;
      fprintf(f, "typedef enum %s %s;\n", name, name);
    }
  }

  for (int i = 0; i < stmts.length; i++) {
    ast_t stmt = stmts.data[i];
    if (stmt->tag == fundef) {
      ast_fundef fundef = stmt->data.fundef;
      if (strcmp(fundef.name.lexeme, "main") != 0) {

        generate_type(f, fundef.ret_type);

        fprintf(f, " %s(", fundef.name.lexeme);
        for (int i = 0; i < fundef.args.length; i++) {
          if (i > 0)
            fprintf(f, ", ");
          generate_type(f, fundef.types.data[i]);
          fprintf(f, " ");
          fprintf(f, "%s", fundef.args.data[i].lexeme);
        }
        fprintf(f, ");\n\n");
      }
    }
  }

  for (int i = 0; i < stmts.length; i++) {
    ast_t stmt = stmts.data[i];
    if (stmt->tag == tdef) {
      struct ast_tdef tdef = stmt->data.tdef;
      char *name = tdef.name.lexeme;
      generate_array_funcs(g, name);
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
      ast_type type = cons.type->data.type;
      if (strcmp(type.name.lexeme, "void") != 0) {
        generate_type(f, cons.type);
        fprintf(f, " %s;", cons.name.lexeme);
      }
    }
    fprintf(f, "} data;");
  } else {
    for (int i = 0; i < tdef.constructors.length; i++) {
      ast_cons cons = tdef.constructors.data[i]->data.cons;
      ast_type type = cons.type->data.type;
      if (strcmp(type.name.lexeme, "void") != 0) {
        generate_type(f, cons.type);
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
