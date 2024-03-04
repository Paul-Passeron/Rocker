#include "./src/generation/fundefs.h"
#include "./src/generation/fundefs_internal.h"
#include "./src/generation/typedefs.h"
#include "./RockerAllocator/alloc.h"
typedef struct file*file;

__internal_dynamic_array_t file_make_array(void) {
return __internal_make_array(sizeof(file));
}

 void file_push_array(__internal_dynamic_array_t arr, file elem) {
  __internal_push_array(arr, &elem);
}

file file_pop_array(__internal_dynamic_array_t arr) {
 file *res = __internal_pop_array(arr);
  return *res;
}

file file_get_elem(__internal_dynamic_array_t arr, size_t index) {
 file *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN file_get_elem"); exit(1);}  return *res;
}

void file_set_elem(__internal_dynamic_array_t arr, size_t index, file elem) {
  __internal_set_elem(arr, index, &elem);
}

void file_insert(__internal_dynamic_array_t arr, size_t index, file elem) {
  __internal_insert(arr, index, &elem);
}

typedef enum file_mode file_mode;
typedef enum token_type token_type;
typedef struct token*token;

__internal_dynamic_array_t token_make_array(void) {
return __internal_make_array(sizeof(token));
}

 void token_push_array(__internal_dynamic_array_t arr, token elem) {
  __internal_push_array(arr, &elem);
}

token token_pop_array(__internal_dynamic_array_t arr) {
 token *res = __internal_pop_array(arr);
  return *res;
}

token token_get_elem(__internal_dynamic_array_t arr, size_t index) {
 token *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN token_get_elem"); exit(1);}  return *res;
}

void token_set_elem(__internal_dynamic_array_t arr, size_t index, token elem) {
  __internal_set_elem(arr, index, &elem);
}

void token_insert(__internal_dynamic_array_t arr, size_t index, token elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct lexer*lexer;

__internal_dynamic_array_t lexer_make_array(void) {
return __internal_make_array(sizeof(lexer));
}

 void lexer_push_array(__internal_dynamic_array_t arr, lexer elem) {
  __internal_push_array(arr, &elem);
}

lexer lexer_pop_array(__internal_dynamic_array_t arr) {
 lexer *res = __internal_pop_array(arr);
  return *res;
}

lexer lexer_get_elem(__internal_dynamic_array_t arr, size_t index) {
 lexer *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN lexer_get_elem"); exit(1);}  return *res;
}

void lexer_set_elem(__internal_dynamic_array_t arr, size_t index, lexer elem) {
  __internal_set_elem(arr, index, &elem);
}

void lexer_insert(__internal_dynamic_array_t arr, size_t index, lexer elem) {
  __internal_insert(arr, index, &elem);
}

typedef enum comment_type comment_type;
typedef struct ast_data*ast_data;

__internal_dynamic_array_t ast_data_make_array(void) {
return __internal_make_array(sizeof(ast_data));
}

 void ast_data_push_array(__internal_dynamic_array_t arr, ast_data elem) {
  __internal_push_array(arr, &elem);
}

ast_data ast_data_pop_array(__internal_dynamic_array_t arr) {
 ast_data *res = __internal_pop_array(arr);
  return *res;
}

ast_data ast_data_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_data *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_data_get_elem"); exit(1);}  return *res;
}

void ast_data_set_elem(__internal_dynamic_array_t arr, size_t index, ast_data elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_data_insert(__internal_dynamic_array_t arr, size_t index, ast_data elem) {
  __internal_insert(arr, index, &elem);
}

typedef enum ast_kind ast_kind;
typedef struct ast_op*ast_op;

__internal_dynamic_array_t ast_op_make_array(void) {
return __internal_make_array(sizeof(ast_op));
}

 void ast_op_push_array(__internal_dynamic_array_t arr, ast_op elem) {
  __internal_push_array(arr, &elem);
}

ast_op ast_op_pop_array(__internal_dynamic_array_t arr) {
 ast_op *res = __internal_pop_array(arr);
  return *res;
}

ast_op ast_op_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_op *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_op_get_elem"); exit(1);}  return *res;
}

void ast_op_set_elem(__internal_dynamic_array_t arr, size_t index, ast_op elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_op_insert(__internal_dynamic_array_t arr, size_t index, ast_op elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_literal*ast_literal;

__internal_dynamic_array_t ast_literal_make_array(void) {
return __internal_make_array(sizeof(ast_literal));
}

 void ast_literal_push_array(__internal_dynamic_array_t arr, ast_literal elem) {
  __internal_push_array(arr, &elem);
}

ast_literal ast_literal_pop_array(__internal_dynamic_array_t arr) {
 ast_literal *res = __internal_pop_array(arr);
  return *res;
}

ast_literal ast_literal_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_literal *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_literal_get_elem"); exit(1);}  return *res;
}

void ast_literal_set_elem(__internal_dynamic_array_t arr, size_t index, ast_literal elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_literal_insert(__internal_dynamic_array_t arr, size_t index, ast_literal elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_identifier*ast_identifier;

__internal_dynamic_array_t ast_identifier_make_array(void) {
return __internal_make_array(sizeof(ast_identifier));
}

 void ast_identifier_push_array(__internal_dynamic_array_t arr, ast_identifier elem) {
  __internal_push_array(arr, &elem);
}

ast_identifier ast_identifier_pop_array(__internal_dynamic_array_t arr) {
 ast_identifier *res = __internal_pop_array(arr);
  return *res;
}

ast_identifier ast_identifier_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_identifier *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_identifier_get_elem"); exit(1);}  return *res;
}

void ast_identifier_set_elem(__internal_dynamic_array_t arr, size_t index, ast_identifier elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_identifier_insert(__internal_dynamic_array_t arr, size_t index, ast_identifier elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_fundef*ast_fundef;

__internal_dynamic_array_t ast_fundef_make_array(void) {
return __internal_make_array(sizeof(ast_fundef));
}

 void ast_fundef_push_array(__internal_dynamic_array_t arr, ast_fundef elem) {
  __internal_push_array(arr, &elem);
}

ast_fundef ast_fundef_pop_array(__internal_dynamic_array_t arr) {
 ast_fundef *res = __internal_pop_array(arr);
  return *res;
}

ast_fundef ast_fundef_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_fundef *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_fundef_get_elem"); exit(1);}  return *res;
}

void ast_fundef_set_elem(__internal_dynamic_array_t arr, size_t index, ast_fundef elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_fundef_insert(__internal_dynamic_array_t arr, size_t index, ast_fundef elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_funcall*ast_funcall;

__internal_dynamic_array_t ast_funcall_make_array(void) {
return __internal_make_array(sizeof(ast_funcall));
}

 void ast_funcall_push_array(__internal_dynamic_array_t arr, ast_funcall elem) {
  __internal_push_array(arr, &elem);
}

ast_funcall ast_funcall_pop_array(__internal_dynamic_array_t arr) {
 ast_funcall *res = __internal_pop_array(arr);
  return *res;
}

ast_funcall ast_funcall_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_funcall *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_funcall_get_elem"); exit(1);}  return *res;
}

void ast_funcall_set_elem(__internal_dynamic_array_t arr, size_t index, ast_funcall elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_funcall_insert(__internal_dynamic_array_t arr, size_t index, ast_funcall elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_ret*ast_ret;

__internal_dynamic_array_t ast_ret_make_array(void) {
return __internal_make_array(sizeof(ast_ret));
}

 void ast_ret_push_array(__internal_dynamic_array_t arr, ast_ret elem) {
  __internal_push_array(arr, &elem);
}

ast_ret ast_ret_pop_array(__internal_dynamic_array_t arr) {
 ast_ret *res = __internal_pop_array(arr);
  return *res;
}

ast_ret ast_ret_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_ret *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_ret_get_elem"); exit(1);}  return *res;
}

void ast_ret_set_elem(__internal_dynamic_array_t arr, size_t index, ast_ret elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_ret_insert(__internal_dynamic_array_t arr, size_t index, ast_ret elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_vardef*ast_vardef;

__internal_dynamic_array_t ast_vardef_make_array(void) {
return __internal_make_array(sizeof(ast_vardef));
}

 void ast_vardef_push_array(__internal_dynamic_array_t arr, ast_vardef elem) {
  __internal_push_array(arr, &elem);
}

ast_vardef ast_vardef_pop_array(__internal_dynamic_array_t arr) {
 ast_vardef *res = __internal_pop_array(arr);
  return *res;
}

ast_vardef ast_vardef_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_vardef *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_vardef_get_elem"); exit(1);}  return *res;
}

void ast_vardef_set_elem(__internal_dynamic_array_t arr, size_t index, ast_vardef elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_vardef_insert(__internal_dynamic_array_t arr, size_t index, ast_vardef elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_match*ast_match;

__internal_dynamic_array_t ast_match_make_array(void) {
return __internal_make_array(sizeof(ast_match));
}

 void ast_match_push_array(__internal_dynamic_array_t arr, ast_match elem) {
  __internal_push_array(arr, &elem);
}

ast_match ast_match_pop_array(__internal_dynamic_array_t arr) {
 ast_match *res = __internal_pop_array(arr);
  return *res;
}

ast_match ast_match_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_match *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_match_get_elem"); exit(1);}  return *res;
}

void ast_match_set_elem(__internal_dynamic_array_t arr, size_t index, ast_match elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_match_insert(__internal_dynamic_array_t arr, size_t index, ast_match elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_matchcase*ast_matchcase;

__internal_dynamic_array_t ast_matchcase_make_array(void) {
return __internal_make_array(sizeof(ast_matchcase));
}

 void ast_matchcase_push_array(__internal_dynamic_array_t arr, ast_matchcase elem) {
  __internal_push_array(arr, &elem);
}

ast_matchcase ast_matchcase_pop_array(__internal_dynamic_array_t arr) {
 ast_matchcase *res = __internal_pop_array(arr);
  return *res;
}

ast_matchcase ast_matchcase_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_matchcase *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_matchcase_get_elem"); exit(1);}  return *res;
}

void ast_matchcase_set_elem(__internal_dynamic_array_t arr, size_t index, ast_matchcase elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_matchcase_insert(__internal_dynamic_array_t arr, size_t index, ast_matchcase elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_sub*ast_sub;

__internal_dynamic_array_t ast_sub_make_array(void) {
return __internal_make_array(sizeof(ast_sub));
}

 void ast_sub_push_array(__internal_dynamic_array_t arr, ast_sub elem) {
  __internal_push_array(arr, &elem);
}

ast_sub ast_sub_pop_array(__internal_dynamic_array_t arr) {
 ast_sub *res = __internal_pop_array(arr);
  return *res;
}

ast_sub ast_sub_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_sub *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_sub_get_elem"); exit(1);}  return *res;
}

void ast_sub_set_elem(__internal_dynamic_array_t arr, size_t index, ast_sub elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_sub_insert(__internal_dynamic_array_t arr, size_t index, ast_sub elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_type*ast_type;

__internal_dynamic_array_t ast_type_make_array(void) {
return __internal_make_array(sizeof(ast_type));
}

 void ast_type_push_array(__internal_dynamic_array_t arr, ast_type elem) {
  __internal_push_array(arr, &elem);
}

ast_type ast_type_pop_array(__internal_dynamic_array_t arr) {
 ast_type *res = __internal_pop_array(arr);
  return *res;
}

ast_type ast_type_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_type *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_type_get_elem"); exit(1);}  return *res;
}

void ast_type_set_elem(__internal_dynamic_array_t arr, size_t index, ast_type elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_type_insert(__internal_dynamic_array_t arr, size_t index, ast_type elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_program*ast_program;

__internal_dynamic_array_t ast_program_make_array(void) {
return __internal_make_array(sizeof(ast_program));
}

 void ast_program_push_array(__internal_dynamic_array_t arr, ast_program elem) {
  __internal_push_array(arr, &elem);
}

ast_program ast_program_pop_array(__internal_dynamic_array_t arr) {
 ast_program *res = __internal_pop_array(arr);
  return *res;
}

ast_program ast_program_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_program *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_program_get_elem"); exit(1);}  return *res;
}

void ast_program_set_elem(__internal_dynamic_array_t arr, size_t index, ast_program elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_program_insert(__internal_dynamic_array_t arr, size_t index, ast_program elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_compound*ast_compound;

__internal_dynamic_array_t ast_compound_make_array(void) {
return __internal_make_array(sizeof(ast_compound));
}

 void ast_compound_push_array(__internal_dynamic_array_t arr, ast_compound elem) {
  __internal_push_array(arr, &elem);
}

ast_compound ast_compound_pop_array(__internal_dynamic_array_t arr) {
 ast_compound *res = __internal_pop_array(arr);
  return *res;
}

ast_compound ast_compound_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_compound *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_compound_get_elem"); exit(1);}  return *res;
}

void ast_compound_set_elem(__internal_dynamic_array_t arr, size_t index, ast_compound elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_compound_insert(__internal_dynamic_array_t arr, size_t index, ast_compound elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_ifstmt*ast_ifstmt;

__internal_dynamic_array_t ast_ifstmt_make_array(void) {
return __internal_make_array(sizeof(ast_ifstmt));
}

 void ast_ifstmt_push_array(__internal_dynamic_array_t arr, ast_ifstmt elem) {
  __internal_push_array(arr, &elem);
}

ast_ifstmt ast_ifstmt_pop_array(__internal_dynamic_array_t arr) {
 ast_ifstmt *res = __internal_pop_array(arr);
  return *res;
}

ast_ifstmt ast_ifstmt_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_ifstmt *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_ifstmt_get_elem"); exit(1);}  return *res;
}

void ast_ifstmt_set_elem(__internal_dynamic_array_t arr, size_t index, ast_ifstmt elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_ifstmt_insert(__internal_dynamic_array_t arr, size_t index, ast_ifstmt elem) {
  __internal_insert(arr, index, &elem);
}

typedef enum tdef_type tdef_type;
typedef struct ast_tdef*ast_tdef;

__internal_dynamic_array_t ast_tdef_make_array(void) {
return __internal_make_array(sizeof(ast_tdef));
}

 void ast_tdef_push_array(__internal_dynamic_array_t arr, ast_tdef elem) {
  __internal_push_array(arr, &elem);
}

ast_tdef ast_tdef_pop_array(__internal_dynamic_array_t arr) {
 ast_tdef *res = __internal_pop_array(arr);
  return *res;
}

ast_tdef ast_tdef_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_tdef *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_tdef_get_elem"); exit(1);}  return *res;
}

void ast_tdef_set_elem(__internal_dynamic_array_t arr, size_t index, ast_tdef elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_tdef_insert(__internal_dynamic_array_t arr, size_t index, ast_tdef elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_cons*ast_cons;

__internal_dynamic_array_t ast_cons_make_array(void) {
return __internal_make_array(sizeof(ast_cons));
}

 void ast_cons_push_array(__internal_dynamic_array_t arr, ast_cons elem) {
  __internal_push_array(arr, &elem);
}

ast_cons ast_cons_pop_array(__internal_dynamic_array_t arr) {
 ast_cons *res = __internal_pop_array(arr);
  return *res;
}

ast_cons ast_cons_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_cons *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_cons_get_elem"); exit(1);}  return *res;
}

void ast_cons_set_elem(__internal_dynamic_array_t arr, size_t index, ast_cons elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_cons_insert(__internal_dynamic_array_t arr, size_t index, ast_cons elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_record_expr*ast_record_expr;

__internal_dynamic_array_t ast_record_expr_make_array(void) {
return __internal_make_array(sizeof(ast_record_expr));
}

 void ast_record_expr_push_array(__internal_dynamic_array_t arr, ast_record_expr elem) {
  __internal_push_array(arr, &elem);
}

ast_record_expr ast_record_expr_pop_array(__internal_dynamic_array_t arr) {
 ast_record_expr *res = __internal_pop_array(arr);
  return *res;
}

ast_record_expr ast_record_expr_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_record_expr *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_record_expr_get_elem"); exit(1);}  return *res;
}

void ast_record_expr_set_elem(__internal_dynamic_array_t arr, size_t index, ast_record_expr elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_record_expr_insert(__internal_dynamic_array_t arr, size_t index, ast_record_expr elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_loop*ast_loop;

__internal_dynamic_array_t ast_loop_make_array(void) {
return __internal_make_array(sizeof(ast_loop));
}

 void ast_loop_push_array(__internal_dynamic_array_t arr, ast_loop elem) {
  __internal_push_array(arr, &elem);
}

ast_loop ast_loop_pop_array(__internal_dynamic_array_t arr) {
 ast_loop *res = __internal_pop_array(arr);
  return *res;
}

ast_loop ast_loop_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_loop *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_loop_get_elem"); exit(1);}  return *res;
}

void ast_loop_set_elem(__internal_dynamic_array_t arr, size_t index, ast_loop elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_loop_insert(__internal_dynamic_array_t arr, size_t index, ast_loop elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_assign*ast_assign;

__internal_dynamic_array_t ast_assign_make_array(void) {
return __internal_make_array(sizeof(ast_assign));
}

 void ast_assign_push_array(__internal_dynamic_array_t arr, ast_assign elem) {
  __internal_push_array(arr, &elem);
}

ast_assign ast_assign_pop_array(__internal_dynamic_array_t arr) {
 ast_assign *res = __internal_pop_array(arr);
  return *res;
}

ast_assign ast_assign_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_assign *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_assign_get_elem"); exit(1);}  return *res;
}

void ast_assign_set_elem(__internal_dynamic_array_t arr, size_t index, ast_assign elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_assign_insert(__internal_dynamic_array_t arr, size_t index, ast_assign elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_while_loop*ast_while_loop;

__internal_dynamic_array_t ast_while_loop_make_array(void) {
return __internal_make_array(sizeof(ast_while_loop));
}

 void ast_while_loop_push_array(__internal_dynamic_array_t arr, ast_while_loop elem) {
  __internal_push_array(arr, &elem);
}

ast_while_loop ast_while_loop_pop_array(__internal_dynamic_array_t arr) {
 ast_while_loop *res = __internal_pop_array(arr);
  return *res;
}

ast_while_loop ast_while_loop_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_while_loop *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_while_loop_get_elem"); exit(1);}  return *res;
}

void ast_while_loop_set_elem(__internal_dynamic_array_t arr, size_t index, ast_while_loop elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_while_loop_insert(__internal_dynamic_array_t arr, size_t index, ast_while_loop elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast_enum_tdef*ast_enum_tdef;

__internal_dynamic_array_t ast_enum_tdef_make_array(void) {
return __internal_make_array(sizeof(ast_enum_tdef));
}

 void ast_enum_tdef_push_array(__internal_dynamic_array_t arr, ast_enum_tdef elem) {
  __internal_push_array(arr, &elem);
}

ast_enum_tdef ast_enum_tdef_pop_array(__internal_dynamic_array_t arr) {
 ast_enum_tdef *res = __internal_pop_array(arr);
  return *res;
}

ast_enum_tdef ast_enum_tdef_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast_enum_tdef *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_enum_tdef_get_elem"); exit(1);}  return *res;
}

void ast_enum_tdef_set_elem(__internal_dynamic_array_t arr, size_t index, ast_enum_tdef elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_enum_tdef_insert(__internal_dynamic_array_t arr, size_t index, ast_enum_tdef elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct ast*ast;

__internal_dynamic_array_t ast_make_array(void) {
return __internal_make_array(sizeof(ast));
}

 void ast_push_array(__internal_dynamic_array_t arr, ast elem) {
  __internal_push_array(arr, &elem);
}

ast ast_pop_array(__internal_dynamic_array_t arr) {
 ast *res = __internal_pop_array(arr);
  return *res;
}

ast ast_get_elem(__internal_dynamic_array_t arr, size_t index) {
 ast *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN ast_get_elem"); exit(1);}  return *res;
}

void ast_set_elem(__internal_dynamic_array_t arr, size_t index, ast elem) {
  __internal_set_elem(arr, index, &elem);
}

void ast_insert(__internal_dynamic_array_t arr, size_t index, ast elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct parser*parser;

__internal_dynamic_array_t parser_make_array(void) {
return __internal_make_array(sizeof(parser));
}

 void parser_push_array(__internal_dynamic_array_t arr, parser elem) {
  __internal_push_array(arr, &elem);
}

parser parser_pop_array(__internal_dynamic_array_t arr) {
 parser *res = __internal_pop_array(arr);
  return *res;
}

parser parser_get_elem(__internal_dynamic_array_t arr, size_t index) {
 parser *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN parser_get_elem"); exit(1);}  return *res;
}

void parser_set_elem(__internal_dynamic_array_t arr, size_t index, parser elem) {
  __internal_set_elem(arr, index, &elem);
}

void parser_insert(__internal_dynamic_array_t arr, size_t index, parser elem) {
  __internal_insert(arr, index, &elem);
}

typedef enum nt_kind nt_kind;
typedef struct constructor_spec*constructor_spec;

__internal_dynamic_array_t constructor_spec_make_array(void) {
return __internal_make_array(sizeof(constructor_spec));
}

 void constructor_spec_push_array(__internal_dynamic_array_t arr, constructor_spec elem) {
  __internal_push_array(arr, &elem);
}

constructor_spec constructor_spec_pop_array(__internal_dynamic_array_t arr) {
 constructor_spec *res = __internal_pop_array(arr);
  return *res;
}

constructor_spec constructor_spec_get_elem(__internal_dynamic_array_t arr, size_t index) {
 constructor_spec *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN constructor_spec_get_elem"); exit(1);}  return *res;
}

void constructor_spec_set_elem(__internal_dynamic_array_t arr, size_t index, constructor_spec elem) {
  __internal_set_elem(arr, index, &elem);
}

void constructor_spec_insert(__internal_dynamic_array_t arr, size_t index, constructor_spec elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct type_spec*type_spec;

__internal_dynamic_array_t type_spec_make_array(void) {
return __internal_make_array(sizeof(type_spec));
}

 void type_spec_push_array(__internal_dynamic_array_t arr, type_spec elem) {
  __internal_push_array(arr, &elem);
}

type_spec type_spec_pop_array(__internal_dynamic_array_t arr) {
 type_spec *res = __internal_pop_array(arr);
  return *res;
}

type_spec type_spec_get_elem(__internal_dynamic_array_t arr, size_t index) {
 type_spec *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN type_spec_get_elem"); exit(1);}  return *res;
}

void type_spec_set_elem(__internal_dynamic_array_t arr, size_t index, type_spec elem) {
  __internal_set_elem(arr, index, &elem);
}

void type_spec_insert(__internal_dynamic_array_t arr, size_t index, type_spec elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct nt_fun*nt_fun;

__internal_dynamic_array_t nt_fun_make_array(void) {
return __internal_make_array(sizeof(nt_fun));
}

 void nt_fun_push_array(__internal_dynamic_array_t arr, nt_fun elem) {
  __internal_push_array(arr, &elem);
}

nt_fun nt_fun_pop_array(__internal_dynamic_array_t arr) {
 nt_fun *res = __internal_pop_array(arr);
  return *res;
}

nt_fun nt_fun_get_elem(__internal_dynamic_array_t arr, size_t index) {
 nt_fun *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN nt_fun_get_elem"); exit(1);}  return *res;
}

void nt_fun_set_elem(__internal_dynamic_array_t arr, size_t index, nt_fun elem) {
  __internal_set_elem(arr, index, &elem);
}

void nt_fun_insert(__internal_dynamic_array_t arr, size_t index, nt_fun elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct nt_var*nt_var;

__internal_dynamic_array_t nt_var_make_array(void) {
return __internal_make_array(sizeof(nt_var));
}

 void nt_var_push_array(__internal_dynamic_array_t arr, nt_var elem) {
  __internal_push_array(arr, &elem);
}

nt_var nt_var_pop_array(__internal_dynamic_array_t arr) {
 nt_var *res = __internal_pop_array(arr);
  return *res;
}

nt_var nt_var_get_elem(__internal_dynamic_array_t arr, size_t index) {
 nt_var *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN nt_var_get_elem"); exit(1);}  return *res;
}

void nt_var_set_elem(__internal_dynamic_array_t arr, size_t index, nt_var elem) {
  __internal_set_elem(arr, index, &elem);
}

void nt_var_insert(__internal_dynamic_array_t arr, size_t index, nt_var elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct nt_elem*nt_elem;

__internal_dynamic_array_t nt_elem_make_array(void) {
return __internal_make_array(sizeof(nt_elem));
}

 void nt_elem_push_array(__internal_dynamic_array_t arr, nt_elem elem) {
  __internal_push_array(arr, &elem);
}

nt_elem nt_elem_pop_array(__internal_dynamic_array_t arr) {
 nt_elem *res = __internal_pop_array(arr);
  return *res;
}

nt_elem nt_elem_get_elem(__internal_dynamic_array_t arr, size_t index) {
 nt_elem *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN nt_elem_get_elem"); exit(1);}  return *res;
}

void nt_elem_set_elem(__internal_dynamic_array_t arr, size_t index, nt_elem elem) {
  __internal_set_elem(arr, index, &elem);
}

void nt_elem_insert(__internal_dynamic_array_t arr, size_t index, nt_elem elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct nt*nt;

__internal_dynamic_array_t nt_make_array(void) {
return __internal_make_array(sizeof(nt));
}

 void nt_push_array(__internal_dynamic_array_t arr, nt elem) {
  __internal_push_array(arr, &elem);
}

nt nt_pop_array(__internal_dynamic_array_t arr) {
 nt *res = __internal_pop_array(arr);
  return *res;
}

nt nt_get_elem(__internal_dynamic_array_t arr, size_t index) {
 nt *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN nt_get_elem"); exit(1);}  return *res;
}

void nt_set_elem(__internal_dynamic_array_t arr, size_t index, nt elem) {
  __internal_set_elem(arr, index, &elem);
}

void nt_insert(__internal_dynamic_array_t arr, size_t index, nt elem) {
  __internal_insert(arr, index, &elem);
}

typedef struct gen*gen;

__internal_dynamic_array_t gen_make_array(void) {
return __internal_make_array(sizeof(gen));
}

 void gen_push_array(__internal_dynamic_array_t arr, gen elem) {
  __internal_push_array(arr, &elem);
}

gen gen_pop_array(__internal_dynamic_array_t arr) {
 gen *res = __internal_pop_array(arr);
  return *res;
}

gen gen_get_elem(__internal_dynamic_array_t arr, size_t index) {
 gen *res = __internal_get_elem(arr, index);
  if (res == NULL){ printf("NULL ELEMENT IN gen_get_elem"); exit(1);}  return *res;
}

void gen_set_elem(__internal_dynamic_array_t arr, size_t index, gen elem) {
  __internal_set_elem(arr, index, &elem);
}

void gen_insert(__internal_dynamic_array_t arr, size_t index, gen elem) {
  __internal_insert(arr, index, &elem);
}

file open_file(string filename, file_mode mode);
void close_file(file f);
void pfile(file f, string s);
void implemented(string s);
void compiler_assert(boolean b, string s);
void print_int(int n);
string string_of_int(int n);
string create_string(string src, int offset, int length);
string cons_str(string src, int offset);
string lexeme_of_type(token_type type);
token_type type_of_lexeme(string lexeme);
boolean is_type_keyword(int type);
boolean is_type_operator(int type);
boolean is_lexeme_keyword(string s);
int get_precedence(token_type t);
void print_list_types(__internal_dynamic_array_t _l);
boolean is_whitespace(char c);
boolean is_delimeter(char c);
lexer new_lexer(string filename);
char lexer_peek(lexer l);
void lexer_consume(lexer l);
int length_until_next_delimeter(lexer l);
int length_of_delimeter(lexer l);
boolean is_char_num(char c);
int length_of_num_lit(lexer l);
int length_of_delimited_literal(lexer l, char c);
comment_type is_comment(lexer l);
boolean is_end_comment(lexer l, int type);
void lexer_consume_n(lexer l, int n);
string create_lexeme(lexer l, int length);
void step_lexer(lexer l);
void lex_program(lexer l);
parser new_parser(__internal_dynamic_array_t _l);
token_type peek_type(parser p);
token peek_token(parser p);
token consume_token(parser p);
void print_error_prefix(parser p);
void expect(parser p, token_type t);
parser copy_parser(parser p);
boolean is_assign(parser p);
ast parse_assign(parser p);
ast parse_cons(parser p);
ast parse_tdef(parser p);
ast parse_ret(parser p);
ast parse_literal(parser p);
ast parse_sub(parser p);
ast parse_if(parser p);
ast parse_enum(parser p);
ast parse_statement(parser p);
ast parse_matchcase(parser p);
ast parse_match(parser p);
ast parse_compound(parser p);
ast parse_var_def(parser p);
ast parse_fundef(parser p);
ast parse_loop(parser p);
boolean is_primary(parser p);
boolean is_funcall(parser p);
ast parse_funcall(parser p);
ast parse_while_loop(parser p);
ast parse_record_expression(parser p);
ast parse_type(parser p);
ast parse_identifier(parser p);
ast parse_leaf(parser p);
boolean is_sub(parser p);
boolean is_leaf(parser p);
ast parse_primary(parser p);
ast parse_expression(parser p);
ast parse_expression_aux(parser p, int min_prec);
ast parse_increasing_precedence(parser p, ast left, int min_prec);
boolean has_been_included(parser p, string filename);
void parse_program(parser p);
nt_elem get_ref(string name, nt table);
nt new_nt();
void new_nt_scope(nt table);
void end_nt_scope(nt table);
void push_nt(nt table, string name, nt_elem elem);
type_spec get_builtin_type(string name);
nt_elem get_nt_fun(ast_fundef fundef);
nt_elem nt_builtin_vardef(string name, string type);
nt_elem get_nt_var(ast_vardef vardef);
type_spec nt_type_of_ast(ast a);
nt_elem get_builtin_type_tdef(string name);
void setup_name_table(nt table);
gen new_gen(string filename);
void kill_generator(gen g);
void generate_type(gen g, ast a);
void generate_gen_type_fun(gen g, ast_funcall funcall, string suffixe);
void generate_append(gen g, ast_funcall funcall);
void generate_get(gen g, ast_funcall funcall);
void generate_set(gen g, ast_funcall funcall);
void generate_pop(gen g, ast_funcall funcall);
void generate_funcall(gen g, ast fun);
int get_lit_str_length(string s);
void generate_op(gen g, ast expr);
void generate_if_statement(gen g, ast stmt);
void generate_array_funcs(gen g, string type_name);
void generate_loop(gen g, ast loop_ast);
void generate_sub_as_expression(gen g, ast expr);
void generate_while_loop(gen g, ast l);
void generate_enum_tdef(gen g, ast expr);
void generate_expression(gen g, ast expr);
void generate_assign(gen g, ast expr);
boolean is_builtin_typename(string name);
void generate_vardef(gen g, ast var);
void generate_return(gen g, ast ret_ast);
void generate_statement(gen g, ast a);
void generate_tdef(gen g, ast a);
void generate_compound(gen g, ast expr);
void generate_fundef_proto(gen g, ast fun, boolean add);
void generate_fundef(gen g, ast fun);
void generate_forward_defs(gen g, ast program);
void transpile(gen g, ast program);
void type_check(ast prog);
void usage(string prog_name);
struct file{
string Filename;
string Data;
int Mode;
};
enum file_mode {
READ_MODE,
WRITE_MODE,
CLOSED
};
file open_file(string filename, file_mode mode){
file res;
{
struct file __internal_tmp = {
.Filename = filename,
.Data = new_string((string){.data = "", .length = 0}),
.Mode = mode};
res = allocate_compiler_persistent(sizeof(struct file));
*res = __internal_tmp;
}
if (mode==READ_MODE)
res->Data = read_file(filename);
else
if (mode!=WRITE_MODE)
{
print(new_string((string){.data = "Could not open file \'", .length = 21}));
print(filename);
print(new_string((string){.data = "\': Invalid mode specified\n", .length = 26}));
exit(1);

}
return res;

}


void close_file(file f){
write_string_to_file(f->Data, f->Filename);
f->Data = new_string((string){.data = "", .length = 0});
f->Filename = new_string((string){.data = "", .length = 0});

}


void pfile(file f, string s){
f->Data = concat_string(f->Data, s);

}


void implemented(string s){
print(new_string((string){.data = "TODO: ", .length = 6}));
print(s);
print(new_string((string){.data = " is not yet implemented\n", .length = 24}));
exit(1);

}


void compiler_assert(boolean b, string s){
if (b==0)
{
print(new_string((string){.data = "Assertion failed: ", .length = 18}));
print(s);
exit(1);

}

}


void print_int(int n){
int a = n/10;
if (a)
print_int(a);
putchar(n%10+'0');

}


string string_of_int(int n){
__internal_dynamic_array_t chars = char_make_array();
if (n==0)
char_push_array(chars, '0');
while (n>0)
{
char_push_array(chars, n%10+'0');
n = n/10;

}
string res = new_string((string){.data = "", .length = 0});
for(int i =0; i <= (int)get_length(chars)-1; i++)res = append_string(res, char_get_elem(chars, get_length(chars)-1-i));
return res;

}


string create_string(string src, int offset, int length){
string res = new_string((string){.data = "", .length = 0});
for(int i =0; i <= (int)length-1; i++){
char c = get_nth_char(src, offset+i);
res = append_string(res, c);

}
return res;

}


string cons_str(string src, int offset){
return create_string(src, offset, get_string_length(src)-offset);

}


enum token_type {
TOK_IDENTIFIER,
TOK_CHR_LIT,
TOK_STR_LIT,
TOK_NUM_LIT,
TOK_LET,
TOK_COLON,
TOK_COMMA,
TOK_SMALL_ARROW,
TOK_BIG_ARROW,
TOK_OPEN_BRACE,
TOK_CLOSE_BRACE,
TOK_OPEN_PAREN,
TOK_CLOSE_PAREN,
TOK_IF,
TOK_THEN,
TOK_ELSE,
TOK_REC,
TOK_PRO,
TOK_MATCH,
TOK_RETURN,
TOK_STAR,
TOK_MINUS,
TOK_PLUS,
TOK_DIV,
TOK_MODULO,
TOK_LOG_OR,
TOK_LOG_AND,
TOK_BIT_OR,
TOK_BIT_XOR,
TOK_BIT_AND,
TOK_LSSR,
TOK_LSSR_EQ,
TOK_GRTR,
TOK_GRTR_EQ,
TOK_EQUAL,
TOK_DIFF,
TOK_WILDCARD,
TOK_SUB,
TOK_SEMICOL,
TOK_LOOP,
TOK_WHILE,
TOK_DO,
TOK_INCLUDE,
TOK_ENUM,
TOK_ARR_DECL,
TOK_COUNT
};
struct token{
token_type Type;
string Lexeme;
int Col;
int Line;
string Filename;
};
string lexeme_of_type(token_type type){
if (type==TOK_IDENTIFIER)
return new_string((string){.data = "TOK_IDENTIFIER", .length = 14});
if (type==TOK_CHR_LIT)
return new_string((string){.data = "TOK_CHR_LIT", .length = 11});
if (type==TOK_STR_LIT)
return new_string((string){.data = "TOK_STR_LIT", .length = 11});
if (type==TOK_NUM_LIT)
return new_string((string){.data = "TOK_NUM_LIT", .length = 11});
if (type==TOK_LET)
return new_string((string){.data = "TOK_LET", .length = 7});
if (type==TOK_COLON)
return new_string((string){.data = "TOK_COLON", .length = 9});
if (type==TOK_COMMA)
return new_string((string){.data = "TOK_COMMA", .length = 9});
if (type==TOK_SMALL_ARROW)
return new_string((string){.data = "TOK_SMALL_ARROW", .length = 15});
if (type==TOK_BIG_ARROW)
return new_string((string){.data = "TOK_BIG_ARROW", .length = 13});
if (type==TOK_OPEN_BRACE)
return new_string((string){.data = "TOK_OPEN_BRACE", .length = 14});
if (type==TOK_CLOSE_BRACE)
return new_string((string){.data = "TOK_CLOSE_BRACE", .length = 15});
if (type==TOK_OPEN_PAREN)
return new_string((string){.data = "TOK_OPEN_PAREN", .length = 14});
if (type==TOK_CLOSE_PAREN)
return new_string((string){.data = "TOK_CLOSE_PAREN", .length = 15});
if (type==TOK_IF)
return new_string((string){.data = "TOK_IF", .length = 6});
if (type==TOK_THEN)
return new_string((string){.data = "TOK_THEN", .length = 8});
if (type==TOK_ELSE)
return new_string((string){.data = "TOK_ELSE", .length = 8});
if (type==TOK_REC)
return new_string((string){.data = "TOK_REC", .length = 7});
if (type==TOK_PRO)
return new_string((string){.data = "TOK_PRO", .length = 7});
if (type==TOK_MATCH)
return new_string((string){.data = "TOK_MATCH", .length = 9});
if (type==TOK_RETURN)
return new_string((string){.data = "TOK_RETURN", .length = 10});
if (type==TOK_STAR)
return new_string((string){.data = "*", .length = 1});
if (type==TOK_MINUS)
return new_string((string){.data = "-", .length = 1});
if (type==TOK_PLUS)
return new_string((string){.data = "+", .length = 1});
if (type==TOK_DIV)
return new_string((string){.data = "/", .length = 1});
if (type==TOK_MODULO)
return new_string((string){.data = "%", .length = 1});
if (type==TOK_LOG_OR)
return new_string((string){.data = "||", .length = 2});
if (type==TOK_LOG_AND)
return new_string((string){.data = "&&", .length = 2});
if (type==TOK_BIT_OR)
return new_string((string){.data = "|", .length = 1});
if (type==TOK_BIT_XOR)
return new_string((string){.data = "^", .length = 1});
if (type==TOK_BIT_AND)
return new_string((string){.data = "&", .length = 1});
if (type==TOK_LSSR)
return new_string((string){.data = "<", .length = 1});
if (type==TOK_LSSR_EQ)
return new_string((string){.data = "<=", .length = 2});
if (type==TOK_GRTR)
return new_string((string){.data = ">", .length = 1});
if (type==TOK_GRTR_EQ)
return new_string((string){.data = ">=", .length = 2});
if (type==TOK_EQUAL)
return new_string((string){.data = "=", .length = 1});
if (type==TOK_DIFF)
return new_string((string){.data = "!=", .length = 2});
if (type==TOK_WILDCARD)
return new_string((string){.data = "_", .length = 1});
if (type==TOK_SUB)
return new_string((string){.data = "TOK_SUB", .length = 7});
if (type==TOK_SEMICOL)
return new_string((string){.data = "TOK_SEMICOL", .length = 11});
if (type==TOK_LOOP)
return new_string((string){.data = "TOK_LOOP", .length = 8});
if (type==TOK_DO)
return new_string((string){.data = "TOK_DO", .length = 6});
if (type==TOK_INCLUDE)
return new_string((string){.data = "TOK_INCLUDE", .length = 11});
if (type==TOK_ENUM)
return new_string((string){.data = "TOK_ENUM", .length = 8});
if (type==TOK_ARR_DECL)
return new_string((string){.data = "TOK_ARR_DECL", .length = 12});
return new_string((string){.data = "ERROR", .length = 5});

}


token_type type_of_lexeme(string lexeme){
if (str_eq(lexeme, new_string((string){.data = "let", .length = 3})))
return TOK_LET;
if (str_eq(lexeme, new_string((string){.data = ":", .length = 1})))
return TOK_COLON;
if (str_eq(lexeme, new_string((string){.data = ",", .length = 1})))
return TOK_COMMA;
if (str_eq(lexeme, new_string((string){.data = "->", .length = 2})))
return TOK_SMALL_ARROW;
if (str_eq(lexeme, new_string((string){.data = "=>", .length = 2})))
return TOK_BIG_ARROW;
if (str_eq(lexeme, new_string((string){.data = "{", .length = 1})))
return TOK_OPEN_BRACE;
if (str_eq(lexeme, new_string((string){.data = "}", .length = 1})))
return TOK_CLOSE_BRACE;
if (str_eq(lexeme, new_string((string){.data = "(", .length = 1})))
return TOK_OPEN_PAREN;
if (str_eq(lexeme, new_string((string){.data = ")", .length = 1})))
return TOK_CLOSE_PAREN;
if (str_eq(lexeme, new_string((string){.data = "if", .length = 2})))
return TOK_IF;
if (str_eq(lexeme, new_string((string){.data = "then", .length = 4})))
return TOK_THEN;
if (str_eq(lexeme, new_string((string){.data = "else", .length = 4})))
return TOK_ELSE;
if (str_eq(lexeme, new_string((string){.data = "rec", .length = 3})))
return TOK_REC;
if (str_eq(lexeme, new_string((string){.data = "pro", .length = 3})))
return TOK_PRO;
if (str_eq(lexeme, new_string((string){.data = "match", .length = 5})))
return TOK_MATCH;
if (str_eq(lexeme, new_string((string){.data = "return", .length = 6})))
return TOK_RETURN;
if (str_eq(lexeme, new_string((string){.data = "*", .length = 1})))
return TOK_STAR;
if (str_eq(lexeme, new_string((string){.data = "-", .length = 1})))
return TOK_MINUS;
if (str_eq(lexeme, new_string((string){.data = "+", .length = 1})))
return TOK_PLUS;
if (str_eq(lexeme, new_string((string){.data = "/", .length = 1})))
return TOK_DIV;
if (str_eq(lexeme, new_string((string){.data = "%", .length = 1})))
return TOK_MODULO;
if (str_eq(lexeme, new_string((string){.data = "||", .length = 2})))
return TOK_LOG_OR;
if (str_eq(lexeme, new_string((string){.data = "&&", .length = 2})))
return TOK_LOG_AND;
if (str_eq(lexeme, new_string((string){.data = "|", .length = 1})))
return TOK_BIT_OR;
if (str_eq(lexeme, new_string((string){.data = "^", .length = 1})))
return TOK_BIT_XOR;
if (str_eq(lexeme, new_string((string){.data = "&", .length = 1})))
return TOK_BIT_AND;
if (str_eq(lexeme, new_string((string){.data = "<", .length = 1})))
return TOK_LSSR;
if (str_eq(lexeme, new_string((string){.data = "<=", .length = 2})))
return TOK_LSSR_EQ;
if (str_eq(lexeme, new_string((string){.data = ">", .length = 1})))
return TOK_GRTR;
if (str_eq(lexeme, new_string((string){.data = ">=", .length = 2})))
return TOK_GRTR_EQ;
if (str_eq(lexeme, new_string((string){.data = "=", .length = 1})))
return TOK_EQUAL;
if (str_eq(lexeme, new_string((string){.data = "!=", .length = 2})))
return TOK_DIFF;
if (str_eq(lexeme, new_string((string){.data = "_", .length = 1})))
return TOK_WILDCARD;
if (str_eq(lexeme, new_string((string){.data = "::", .length = 2})))
return TOK_SUB;
if (str_eq(lexeme, new_string((string){.data = ";", .length = 1})))
return TOK_SEMICOL;
if (str_eq(lexeme, new_string((string){.data = "loop", .length = 4})))
return TOK_LOOP;
if (str_eq(lexeme, new_string((string){.data = "while", .length = 5})))
return TOK_WHILE;
if (str_eq(lexeme, new_string((string){.data = "do", .length = 2})))
return TOK_DO;
if (str_eq(lexeme, new_string((string){.data = "include", .length = 7})))
return TOK_INCLUDE;
if (str_eq(lexeme, new_string((string){.data = "enum", .length = 4})))
return TOK_ENUM;
if (str_eq(lexeme, new_string((string){.data = "[]", .length = 2})))
return TOK_ARR_DECL;
return TOK_COUNT;

}


boolean is_type_keyword(int type){
if (type==TOK_MATCH)
return true;
if (type==TOK_PRO)
return true;
if (type==TOK_REC)
return true;
if (type==TOK_WILDCARD)
return true;
if (type==TOK_RETURN)
return true;
if (type==TOK_SUB)
return true;
if (type==TOK_LET)
return true;
if (type==TOK_IF)
return true;
if (type==TOK_THEN)
return true;
if (type==TOK_ELSE)
return true;
if (type==TOK_LOOP)
return true;
if (type==TOK_WHILE)
return true;
if (type==TOK_DO)
return true;
if (type==TOK_INCLUDE)
return true;
if (type==TOK_ENUM)
return true;
return false;

}


boolean is_type_operator(int type){
if (type==TOK_STAR)
return true;
if (type==TOK_MINUS)
return true;
if (type==TOK_PLUS)
return true;
if (type==TOK_DIV)
return true;
if (type==TOK_MODULO)
return true;
if (type==TOK_LOG_OR)
return true;
if (type==TOK_LOG_AND)
return true;
if (type==TOK_BIT_OR)
return true;
if (type==TOK_BIT_XOR)
return true;
if (type==TOK_BIT_AND)
return true;
if (type==TOK_LSSR)
return true;
if (type==TOK_LSSR_EQ)
return true;
if (type==TOK_GRTR)
return true;
if (type==TOK_GRTR_EQ)
return true;
if (type==TOK_EQUAL)
return true;
if (type==TOK_DIFF)
return true;
return false;

}


boolean is_lexeme_keyword(string s){
return is_type_keyword(type_of_lexeme(s));

}


int get_precedence(token_type t){
if (t==TOK_STAR)
return 11;
if (t==TOK_DIV)
return 11;
if (t==TOK_MODULO)
return 11;
if (t==TOK_PLUS)
return 9;
if (t==TOK_MINUS)
return 10;
if (t==TOK_GRTR)
return 7;
if (t==TOK_LSSR)
return 7;
if (t==TOK_GRTR_EQ)
return 7;
if (t==TOK_LSSR_EQ)
return 7;
if (t==TOK_EQUAL)
return 6;
if (t==TOK_DIFF)
return 6;
if (t==TOK_BIT_AND)
return 5;
if (t==TOK_BIT_XOR)
return 4;
if (t==TOK_BIT_OR)
return 3;
if (t==TOK_LOG_AND)
return 2;
if (t==TOK_LOG_OR)
return 1;
return 0;

}


void print_list_types(__internal_dynamic_array_t _l){
__internal_dynamic_array_t l = _l;
for(int i =0; i <= (int)get_length(l)-1; i++){
token t = token_get_elem(l, i);
token_type typ = t->Type;
string s = lexeme_of_type(typ);
print(s);
print(new_string((string){.data = "\n", .length = 1}));

}

}


boolean is_whitespace(char c){
if (c==' ')
return true;
if (c=='\n')
return true;
if (c=='\t')
return true;
return false;

}


boolean is_delimeter(char c){
string delimeters = new_string((string){.data = "><;,:-+*/%&|!=(){}^ \n\'\"[]", .length = 25});
int len = get_string_length(delimeters);
for(int i =0; i <= (int)len-1; i++){
if (get_nth_char(delimeters, i)==c)
return true;

}
return false;

}


struct lexer{
string Data;
int Cursor;
int Col;
int Line;
string Filename;
__internal_dynamic_array_t Toks;
};
lexer new_lexer(string filename){
string data = read_file(filename);
__internal_dynamic_array_t toks = token_make_array();
lexer res;
{
struct lexer __internal_tmp = {
.Data = data,
.Cursor = 0,
.Col = 1,
.Line = 1,
.Filename = filename,
.Toks = toks};
res = allocate_compiler_persistent(sizeof(struct lexer));
*res = __internal_tmp;
}
return res;

}


char lexer_peek(lexer l){
if (l->Cursor<get_string_length(l->Data))
return get_nth_char(l->Data, l->Cursor);
return 0;

}


void lexer_consume(lexer l){
char c = lexer_peek(l);
l->Cursor = l->Cursor+1;
if (c=='\n')
{
l->Col = 1;
l->Line = l->Line+1;

}
else
if (c!=0)
l->Col = l->Col+1;

}


int length_until_next_delimeter(lexer l){
int i = 0;
int cursor = l->Cursor;
while (is_delimeter(lexer_peek(l))==false)
{
i = i+1;
lexer_consume(l);

}
l->Cursor = cursor;
return i;

}


int length_of_delimeter(lexer l){
char c1 = lexer_peek(l);
l->Cursor = l->Cursor+1;
char c2 = lexer_peek(l);
l->Cursor = l->Cursor-1;
string s = new_string((string){.data = "", .length = 0});
s = append_string(s, c1);
s = append_string(s, c2);
if (str_eq(s, new_string((string){.data = "->", .length = 2})))
return 2;
if (str_eq(s, new_string((string){.data = "=>", .length = 2})))
return 2;
if (str_eq(s, new_string((string){.data = "&&", .length = 2})))
return 2;
if (str_eq(s, new_string((string){.data = "||", .length = 2})))
return 2;
if (str_eq(s, new_string((string){.data = ">=", .length = 2})))
return 2;
if (str_eq(s, new_string((string){.data = "<=", .length = 2})))
return 2;
if (str_eq(s, new_string((string){.data = "!=", .length = 2})))
return 2;
if (str_eq(s, new_string((string){.data = "::", .length = 2})))
return 2;
if (str_eq(s, new_string((string){.data = "[]", .length = 2})))
return 2;
if (c1==':')
return 1;
if (c1==',')
return 1;
if (c1=='/')
return 1;
if (c1=='%')
return 1;
if (c1=='*')
return 1;
if (c1=='+')
return 1;
if (c1=='-')
return 1;
if (c1=='^')
return 1;
if (c1=='{')
return 1;
if (c1=='}')
return 1;
if (c1=='(')
return 1;
if (c1==')')
return 1;
if (c1=='=')
return 1;
if (c1=='<')
return 1;
if (c1=='>')
return 1;
if (c1==';')
return 1;
return 0;

}


boolean is_char_num(char c){
return c<='9'&&c>='0';

}


int length_of_num_lit(lexer l){
int cur = l->Cursor;
int cter = 0;
while (is_char_num(lexer_peek(l)))
{
l->Cursor = l->Cursor+1;
cter = cter+1;

}
l->Cursor = cur;
return cter;

}


int length_of_delimited_literal(lexer l, char c){
int cursor = l->Cursor;
char c1 = lexer_peek(l);
if (c1!=c)
return 0;
l->Cursor = l->Cursor+1;
boolean pass = false;
while (lexer_peek(l)!=c||pass)
{
if (pass)
pass = false;
else
if (lexer_peek(l)=='\\')
pass = true;
l->Cursor = l->Cursor+1;

}
int res = l->Cursor-cursor+1;
l->Cursor = cursor;
return res;

}


enum comment_type {
NOT_COM,
COM_SINGLE,
COM_MULTI
};
comment_type is_comment(lexer l){
int cursor = l->Cursor;
char c = lexer_peek(l);
if (c!='/')
return 0;
l->Cursor = l->Cursor+1;
c = lexer_peek(l);
if (c=='/')
{
l->Cursor = cursor;
return COM_SINGLE;

}
if (c=='*')
{
l->Cursor = cursor;
return COM_MULTI;

}
l->Cursor = cursor;
return NOT_COM;

}


boolean is_end_comment(lexer l, int type){
if (type==0)
return 0;
if (type==COM_SINGLE)
return lexer_peek(l)=='\n';
string s = new_string((string){.data = "", .length = 0});
append_string(s, lexer_peek(l));
l->Cursor = l->Cursor+1;
append_string(s, lexer_peek(l));
boolean res = str_eq(s, new_string((string){.data = "*/", .length = 2}));
l->Cursor = l->Cursor-1;
return res;

}


void lexer_consume_n(lexer l, int n){
for(int i =1; i <= (int)n; i++){
lexer_consume(l);

}

}


string create_lexeme(lexer l, int length){
return create_string(l->Data, l->Cursor, length);

}


void step_lexer(lexer l){
token res;
{
struct token __internal_tmp = {
.Filename = l->Filename,
.Col = l->Col,
.Line = l->Line};
res = allocate_compiler_persistent(sizeof(struct token));
*res = __internal_tmp;
}
while (is_comment(l)||is_whitespace(lexer_peek(l)))
{
int com_type = is_comment(l);
if (com_type)
{
lexer_consume_n(l, 2);
while (is_end_comment(l, com_type)==false)
lexer_consume(l);
if (com_type==COM_MULTI)
lexer_consume(l);
lexer_consume(l);

}
while (is_whitespace(lexer_peek(l)))
lexer_consume(l);

}
if (lexer_peek(l)==0)
return ;
res->Col = l->Col;
res->Line = l->Line;
if (is_char_num(lexer_peek(l)))
{
int length = length_of_num_lit(l);
res->Lexeme = create_lexeme(l, length);
res->Type = TOK_NUM_LIT;
lexer_consume_n(l, length);

}
else
if (lexer_peek(l)=='\'')
{
int length = length_of_delimited_literal(l, '\'');
res->Lexeme = create_lexeme(l, length);
res->Type = TOK_CHR_LIT;
lexer_consume_n(l, length);

}
else
if (lexer_peek(l)=='\"')
{
int length = length_of_delimited_literal(l, '\"');
res->Lexeme = create_lexeme(l, length);
res->Type = TOK_STR_LIT;
lexer_consume_n(l, length);

}
else
if (is_delimeter(lexer_peek(l)))
{
int length = length_of_delimeter(l);
res->Lexeme = create_lexeme(l, length);
res->Type = type_of_lexeme(res->Lexeme);
lexer_consume_n(l, length);

}
else
{
int length = length_until_next_delimeter(l);
res->Lexeme = create_lexeme(l, length);
if (is_lexeme_keyword(res->Lexeme))
res->Type = type_of_lexeme(res->Lexeme);
else
res->Type = TOK_IDENTIFIER;
lexer_consume_n(l, length);

}
__internal_dynamic_array_t toks = l->Toks;
token_push_array(toks, res);

}


void lex_program(lexer l){
while (lexer_peek(l))
step_lexer(l);

}


struct ast_data{
ast_op data_op;
ast_literal data_literal;
ast_identifier data_identifier;
ast_fundef data_fundef;
ast_funcall data_funcall;
ast_ret data_ret;
ast_vardef data_vardef;
ast_match data_match;
ast_matchcase data_matchcase;
ast_sub data_sub;
ast_program data_program;
ast_compound data_compound;
ast_ifstmt data_ifstmt;
ast_tdef data_tdef;
ast_cons data_cons;
ast_record_expr data_record_expr;
ast_loop data_loop;
ast_assign data_assign;
ast_while_loop data_while_loop;
ast_enum_tdef data_enum_tdef;
ast_type data_type;
};
enum ast_kind {
tag_op,
tag_literal,
tag_identifier,
tag_fundef,
tag_funcall,
tag_ret,
tag_vardef,
tag_match,
tag_matchcase,
tag_sub,
tag_program,
tag_compound,
tag_ifstmt,
tag_tdef,
tag_cons,
tag_record_expr,
tag_loop,
tag_assign,
tag_while_loop,
tag_enum_tdef,
tag_type
};
struct ast_op{
token_type op;
ast left;
ast right;
};
struct ast_literal{
token lit;
};
struct ast_identifier{
token id;
};
struct ast_fundef{
token name;
__internal_dynamic_array_t args;
__internal_dynamic_array_t types;
ast body;
ast ret_type;
};
struct ast_funcall{
token name;
__internal_dynamic_array_t args;
};
struct ast_ret{
ast expr;
};
struct ast_vardef{
token name;
boolean is_rec;
ast expr;
ast type;
};
struct ast_match{
ast expr;
__internal_dynamic_array_t cases;
};
struct ast_matchcase{
ast expr;
ast body;
};
struct ast_sub{
__internal_dynamic_array_t path;
ast expr;
};
struct ast_type{
token name;
boolean is_array;
};
struct ast_program{
__internal_dynamic_array_t prog;
};
struct ast_compound{
__internal_dynamic_array_t stmts;
};
struct ast_ifstmt{
ast expr;
ast body;
ast elsestmt;
};
enum tdef_type {
TDEF_REC,
TDEF_PRO,
TDEF_ENUM,
TDEF_BUILTIN
};
struct ast_tdef{
token name;
tdef_type t;
__internal_dynamic_array_t constructors;
};
struct ast_cons{
token name;
ast type;
};
struct ast_record_expr{
__internal_dynamic_array_t names;
__internal_dynamic_array_t exprs;
};
struct ast_loop{
token variable;
ast start;
ast end;
ast statement;
};
struct ast_assign{
ast target;
ast expr;
};
struct ast_while_loop{
ast condition;
ast statement;
};
struct ast_enum_tdef{
token name;
__internal_dynamic_array_t items;
};
struct ast{
ast_kind Tag;
ast_data Data;
};
struct parser{
__internal_dynamic_array_t Toks;
ast Prog;
int Cursor;
__internal_dynamic_array_t Includes;
};
parser new_parser(__internal_dynamic_array_t _l){
__internal_dynamic_array_t l = _l;
__internal_dynamic_array_t includes = string_make_array();
parser res;
{
struct parser __internal_tmp = {
.Toks = l,
.Prog = NULL,
.Cursor = 0,
.Includes = includes};
res = allocate_compiler_persistent(sizeof(struct parser));
*res = __internal_tmp;
}
if (get_length(l)>0)
{
token tok = token_get_elem(l, 0);
string main_file = tok->Filename;
string abs_path = get_abs_path(main_file);
string_push_array(includes, abs_path);

}
return res;

}


token_type peek_type(parser p){
token tok = peek_token(p);
return tok->Type;

}


token peek_token(parser p){
__internal_dynamic_array_t toks = p->Toks;
return token_get_elem(toks, p->Cursor);

}


token consume_token(parser p){
token res = peek_token(p);
p->Cursor = p->Cursor+1;
return res;

}


void print_error_prefix(parser p){
token tok = peek_token(p);
print(tok->Filename);
print(new_string((string){.data = ":", .length = 1}));
print_int(tok->Line);
print(new_string((string){.data = ":", .length = 1}));
print_int(tok->Col);

}


void expect(parser p, token_type t){
token_type a = peek_type(p);
if (a!=t)
{
print_error_prefix(p);
print(new_string((string){.data = " Expected ", .length = 10}));
print(lexeme_of_type(t));
print(new_string((string){.data = " but got: ", .length = 10}));
print(lexeme_of_type(a));
print(new_string((string){.data = "\n", .length = 1}));
exit(1);

}

}


parser copy_parser(parser p){
__internal_dynamic_array_t toks = p->Toks;
__internal_dynamic_array_t includes = p->Includes;
parser res;
{
struct parser __internal_tmp = {
.Toks = toks,
.Prog = p->Prog,
.Cursor = p->Cursor,
.Includes = includes};
res = allocate_compiler_persistent(sizeof(struct parser));
*res = __internal_tmp;
}
return res;

}


boolean is_assign(parser p){
parser _p = copy_parser(p);
int scope = 0;
token_type current = peek_type(_p);
consume_token(_p);
boolean break_cond = false;
if (current==TOK_OPEN_BRACE||current==TOK_CLOSE_BRACE)
return false;
while (scope>=0&&current!=TOK_BIG_ARROW&&break_cond==false)
{
if (current==TOK_OPEN_BRACE||current==TOK_OPEN_BRACE)
scope = scope+1;
else
if (current==TOK_CLOSE_BRACE||current==TOK_CLOSE_BRACE)
scope = scope-1;
else
if (current==TOK_COMMA||current==TOK_SEMICOL||current==TOK_COLON||current==TOK_LOOP||current==TOK_SMALL_ARROW)
break_cond = true;
if (break_cond==false)
{
current = peek_type(_p);
consume_token(_p);

}

}
return current==TOK_BIG_ARROW;

}


ast parse_assign(parser p){
expect(p, TOK_IDENTIFIER);
ast target = parse_expression(p);
expect(p, TOK_BIG_ARROW);
consume_token(p);
ast expr = parse_expression(p);
expect(p, TOK_SEMICOL);
consume_token(p);
ast_kind tag = tag_assign;
ast_assign data_assign;
{
struct ast_assign __internal_tmp = {
.target = target,
.expr = expr};
data_assign = allocate_compiler_persistent(sizeof(struct ast_assign));
*data_assign = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_assign = data_assign};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_cons(parser p){
expect(p, TOK_IDENTIFIER);
token name = consume_token(p);
expect(p, TOK_COLON);
consume_token(p);
ast t = parse_type(p);
if (peek_type(p)==TOK_COMMA)
consume_token(p);
ast_cons cons;
{
struct ast_cons __internal_tmp = {
.name = name,
.type = t};
cons = allocate_compiler_persistent(sizeof(struct ast_cons));
*cons = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_cons = cons};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_cons,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_tdef(parser p){
tdef_type type = 0;
if (peek_type(p)==TOK_REC)
type = TDEF_REC;
else
if (peek_type(p)==TOK_PRO)
type = TDEF_PRO;
else
expect(p, TOK_REC);
consume_token(p);
expect(p, TOK_IDENTIFIER);
token name = consume_token(p);
expect(p, TOK_BIG_ARROW);
consume_token(p);
expect(p, TOK_OPEN_BRACE);
consume_token(p);
__internal_dynamic_array_t conss = ast_make_array();
while (peek_type(p)!=TOK_CLOSE_BRACE)
ast_push_array(conss, parse_cons(p));
consume_token(p);
ast_tdef data_tdef;
{
struct ast_tdef __internal_tmp = {
.name = name,
.t = type,
.constructors = conss};
data_tdef = allocate_compiler_persistent(sizeof(struct ast_tdef));
*data_tdef = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_tdef = data_tdef};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_tdef,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_ret(parser p){
expect(p, TOK_RETURN);
consume_token(p);
ast_ret data_ret;
{
struct ast_ret __internal_tmp = {
.expr = NULL};
data_ret = allocate_compiler_persistent(sizeof(struct ast_ret));
*data_ret = __internal_tmp;
}
if (peek_type(p)!=TOK_SEMICOL)
data_ret->expr = parse_expression(p);
expect(p, TOK_SEMICOL);
consume_token(p);
ast_data data;
{
struct ast_data __internal_tmp = {
.data_ret = data_ret};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_ret,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_literal(parser p){
ast_literal data_literal;
{
struct ast_literal __internal_tmp = {
.lit = consume_token(p)};
data_literal = allocate_compiler_persistent(sizeof(struct ast_literal));
*data_literal = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_literal = data_literal};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_literal,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_sub(parser p){
__internal_dynamic_array_t path = token_make_array();
token_push_array(path, consume_token(p));
boolean exit_cond = false;
while (peek_type(p)==TOK_SUB&&exit_cond==false)
{
consume_token(p);
if (is_sub(p))
token_push_array(path, consume_token(p));
else
exit_cond = true;

}
ast expr = parse_expression(p);
ast_sub data_sub;
{
struct ast_sub __internal_tmp = {
.path = path,
.expr = expr};
data_sub = allocate_compiler_persistent(sizeof(struct ast_sub));
*data_sub = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_sub = data_sub};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_sub,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_if(parser p){
expect(p, TOK_IF);
consume_token(p);
ast condition = parse_expression(p);
expect(p, TOK_THEN);
consume_token(p);
ast body = parse_statement(p);
ast_ifstmt data_ifstmt;
{
struct ast_ifstmt __internal_tmp = {
.expr = condition,
.body = body,
.elsestmt = NULL};
data_ifstmt = allocate_compiler_persistent(sizeof(struct ast_ifstmt));
*data_ifstmt = __internal_tmp;
}
if (peek_type(p)==TOK_ELSE)
{
consume_token(p);
data_ifstmt->elsestmt = parse_statement(p);

}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_ifstmt = data_ifstmt};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_ifstmt,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_enum(parser p){
expect(p, TOK_ENUM);
consume_token(p);
expect(p, TOK_IDENTIFIER);
token name = consume_token(p);
expect(p, TOK_BIG_ARROW);
consume_token(p);
expect(p, TOK_OPEN_BRACE);
consume_token(p);
__internal_dynamic_array_t elems = token_make_array();
boolean break_cond = false;
while (peek_type(p)!=TOK_CLOSE_BRACE&&break_cond==false)
{
expect(p, TOK_IDENTIFIER);
token_push_array(elems, consume_token(p));
if (peek_type(p)!=TOK_COMMA)
break_cond = true;
else
consume_token(p);

}
expect(p, TOK_CLOSE_BRACE);
consume_token(p);
ast_enum_tdef data_enum_tdef;
{
struct ast_enum_tdef __internal_tmp = {
.name = name,
.items = elems};
data_enum_tdef = allocate_compiler_persistent(sizeof(struct ast_enum_tdef));
*data_enum_tdef = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_enum_tdef = data_enum_tdef};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_enum_tdef,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_statement(parser p){
token_type a = peek_type(p);
if (a==TOK_IF)
return parse_if(p);
if (a==TOK_ENUM)
return parse_enum(p);
if (a==TOK_PRO||a==TOK_REC)
return parse_tdef(p);
if (a==TOK_WHILE)
return parse_while_loop(p);
if (is_assign(p))
return parse_assign(p);
if (a==TOK_LOOP)
return parse_loop(p);
if (a==TOK_RETURN)
return parse_ret(p);
if (a==TOK_MATCH)
return parse_match(p);
if (a==TOK_OPEN_BRACE)
return parse_compound(p);
if (a==TOK_LET)
{
parser p2 = copy_parser(p);
consume_token(p2);
consume_token(p2);
if (peek_type(p2)==TOK_OPEN_PAREN)
return parse_fundef(p);
return parse_var_def(p);

}
ast res = parse_expression(p);
expect(p, TOK_SEMICOL);
consume_token(p);
return res;

}


ast parse_matchcase(parser p){
implemented(new_string((string){.data = "parse_matchcase", .length = 15}));
return NULL;

}


ast parse_match(parser p){
implemented(new_string((string){.data = "parse_match", .length = 11}));
return NULL;

}


ast parse_compound(parser p){
expect(p, TOK_OPEN_BRACE);
consume_token(p);
__internal_dynamic_array_t stmts = ast_make_array();
while (peek_type(p)!=TOK_CLOSE_BRACE)
ast_push_array(stmts, parse_statement(p));
consume_token(p);
ast_compound data_compound;
{
struct ast_compound __internal_tmp = {
.stmts = stmts};
data_compound = allocate_compiler_persistent(sizeof(struct ast_compound));
*data_compound = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_compound = data_compound};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_compound,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_var_def(parser p){
expect(p, TOK_LET);
consume_token(p);
token id = consume_token(p);
expect(p, TOK_COLON);
consume_token(p);
ast type = parse_type(p);
expect(p, TOK_BIG_ARROW);
consume_token(p);
ast_vardef data_vardef;
{
struct ast_vardef __internal_tmp = {
.name = id,
.is_rec = false,
.expr = NULL,
.type = type};
data_vardef = allocate_compiler_persistent(sizeof(struct ast_vardef));
*data_vardef = __internal_tmp;
}
if (peek_type(p)==TOK_OPEN_BRACE)
{
data_vardef->is_rec = true;
consume_token(p);
data_vardef->expr = parse_record_expression(p);

}
else
if (peek_type(p)==TOK_ARR_DECL)
data_vardef->expr = parse_literal(p);
else
data_vardef->expr = parse_expression(p);
expect(p, TOK_SEMICOL);
consume_token(p);
ast_data data;
{
struct ast_data __internal_tmp = {
.data_vardef = data_vardef};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_vardef,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_fundef(parser p){
expect(p, TOK_LET);
consume_token(p);
token id = consume_token(p);
expect(p, TOK_OPEN_PAREN);
consume_token(p);
__internal_dynamic_array_t args = token_make_array();
__internal_dynamic_array_t types = ast_make_array();
boolean break_cond = false;
while (peek_type(p)!=TOK_CLOSE_PAREN&&break_cond==false)
{
expect(p, TOK_IDENTIFIER);
token_push_array(args, consume_token(p));
expect(p, TOK_COLON);
consume_token(p);
ast_push_array(types, parse_type(p));
if (peek_type(p)!=TOK_COMMA)
break_cond = true;
else
consume_token(p);

}
expect(p, TOK_CLOSE_PAREN);
consume_token(p);
expect(p, TOK_COLON);
consume_token(p);
ast type = parse_type(p);
expect(p, TOK_BIG_ARROW);
consume_token(p);
ast body = parse_compound(p);
ast_fundef data_fundef;
{
struct ast_fundef __internal_tmp = {
.name = id,
.args = args,
.types = types,
.body = body,
.ret_type = type};
data_fundef = allocate_compiler_persistent(sizeof(struct ast_fundef));
*data_fundef = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_fundef = data_fundef};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_fundef,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_loop(parser p){
expect(p, TOK_LOOP);
consume_token(p);
expect(p, TOK_IDENTIFIER);
token var_name = consume_token(p);
expect(p, TOK_COLON);
consume_token(p);
ast begin = parse_expression(p);
expect(p, TOK_SMALL_ARROW);
consume_token(p);
ast end = parse_expression(p);
expect(p, TOK_BIG_ARROW);
consume_token(p);
ast body = parse_statement(p);
ast_loop data_loop;
{
struct ast_loop __internal_tmp = {
.variable = var_name,
.start = begin,
.end = end,
.statement = body};
data_loop = allocate_compiler_persistent(sizeof(struct ast_loop));
*data_loop = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_loop = data_loop};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_loop,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


boolean is_primary(parser p){
token_type t = peek_type(p);
return t==TOK_OPEN_BRACE||t==TOK_OPEN_PAREN||t==TOK_IDENTIFIER||t==TOK_STR_LIT||t==TOK_CHR_LIT||t==TOK_NUM_LIT||t==TOK_WILDCARD||t==TOK_ARR_DECL;

}


boolean is_funcall(parser p){
parser p2 = copy_parser(p);
if (peek_type(p2)!=TOK_IDENTIFIER)
return false;
consume_token(p2);
if (peek_type(p2)!=TOK_OPEN_PAREN)
return false;
return true;

}


ast parse_funcall(parser p){
token id = consume_token(p);
expect(p, TOK_OPEN_PAREN);
consume_token(p);
__internal_dynamic_array_t args = ast_make_array();
boolean break_cond = false;
while (peek_type(p)!=TOK_CLOSE_PAREN&&break_cond==false)
{
ast_push_array(args, parse_expression(p));
if (peek_type(p)!=TOK_COMMA)
break_cond = true;
else
consume_token(p);

}
expect(p, TOK_CLOSE_PAREN);
consume_token(p);
ast_funcall data_funcall;
{
struct ast_funcall __internal_tmp = {
.name = id,
.args = args};
data_funcall = allocate_compiler_persistent(sizeof(struct ast_funcall));
*data_funcall = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_funcall = data_funcall};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_funcall,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_while_loop(parser p){
expect(p, TOK_WHILE);
consume_token(p);
ast condition = parse_expression(p);
expect(p, TOK_DO);
consume_token(p);
ast statement = parse_statement(p);
ast_while_loop data_while_loop;
{
struct ast_while_loop __internal_tmp = {
.condition = condition,
.statement = statement};
data_while_loop = allocate_compiler_persistent(sizeof(struct ast_while_loop));
*data_while_loop = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_while_loop = data_while_loop};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_while_loop,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_record_expression(parser p){
__internal_dynamic_array_t names = token_make_array();
__internal_dynamic_array_t exprs = ast_make_array();
boolean break_cond = false;
while (peek_type(p)!=TOK_CLOSE_BRACE&&break_cond==false)
{
expect(p, TOK_IDENTIFIER);
token cons_name = consume_token(p);
token_push_array(names, cons_name);
expect(p, TOK_BIG_ARROW);
consume_token(p);
ast expr = parse_expression(p);
ast_push_array(exprs, expr);
if (peek_type(p)!=TOK_COMMA)
break_cond = true;
else
consume_token(p);

}
expect(p, TOK_CLOSE_BRACE);
consume_token(p);
ast_record_expr data_record_expr;
{
struct ast_record_expr __internal_tmp = {
.exprs = exprs,
.names = names};
data_record_expr = allocate_compiler_persistent(sizeof(struct ast_record_expr));
*data_record_expr = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_record_expr = data_record_expr};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_record_expr,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_type(parser p){
expect(p, TOK_IDENTIFIER);
token name = consume_token(p);
boolean is_arr = false;
if (peek_type(p)==TOK_ARR_DECL)
{
consume_token(p);
is_arr = true;

}
ast_type data_type;
{
struct ast_type __internal_tmp = {
.name = name,
.is_array = is_arr};
data_type = allocate_compiler_persistent(sizeof(struct ast_type));
*data_type = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_type = data_type};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_type,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_identifier(parser p){
token t = consume_token(p);
ast_identifier data_identifier;
{
struct ast_identifier __internal_tmp = {
.id = t};
data_identifier = allocate_compiler_persistent(sizeof(struct ast_identifier));
*data_identifier = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_identifier = data_identifier};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_identifier,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


ast parse_leaf(parser p){
if (is_funcall(p))
return parse_funcall(p);
token_type t = peek_type(p);
if (t==TOK_IDENTIFIER)
return parse_identifier(p);
return parse_literal(p);

}


boolean is_sub(parser p){
parser p2 = copy_parser(p);
if (peek_type(p2)!=TOK_IDENTIFIER)
return false;
consume_token(p2);
if (peek_type(p2)!=TOK_SUB)
return false;
return true;

}


boolean is_leaf(parser p){
token_type type = peek_type(p);
return type==TOK_STR_LIT||type==TOK_CHR_LIT||type==TOK_NUM_LIT||type==TOK_WILDCARD||type==TOK_IDENTIFIER||type==TOK_ARR_DECL;

}


ast parse_primary(parser p){
if (is_funcall(p))
return parse_funcall(p);
if (is_sub(p))
return parse_sub(p);
if (is_leaf(p))
return parse_leaf(p);
if (peek_type(p)==TOK_OPEN_PAREN)
{
consume_token(p);
ast res = parse_expression(p);
if (peek_type(p)!=TOK_CLOSE_PAREN)
{
print_error_prefix(p);
print(new_string((string){.data = "TODO: Unclosed parenthesis\n", .length = 27}));
exit(1);

}
consume_token(p);
return res;

}
if (peek_type(p)==TOK_OPEN_BRACE)
return parse_record_expression(p);
print_error_prefix(p);
print(new_string((string){.data = " TODO: Could not parse as primary \'", .length = 35}));
print(lexeme_of_type(peek_type(p)));
print(new_string((string){.data = "\'\n", .length = 2}));
exit(1);
return NULL;

}


ast parse_expression(parser p){
token_type a = peek_type(p);
if (a==TOK_OPEN_PAREN)
{
consume_token(p);
ast res = parse_expression(p);
expect(p, TOK_CLOSE_PAREN);
consume_token(p);
return res;

}
if (a==TOK_OPEN_BRACE)
{
consume_token(p);
return parse_record_expression(p);

}
return parse_expression_aux(p, 0);

}


ast parse_expression_aux(parser p, int min_prec){
ast left = parse_primary(p);
boolean break_cond = false;
while (break_cond==false)
{
ast node = parse_increasing_precedence(p, left, min_prec);
if (node==left)
break_cond = true;
else
left = node;

}
return left;

}


ast parse_increasing_precedence(parser p, ast left, int min_prec){
token_type next = peek_type(p);
if (is_type_operator(next)==false)
return left;
int next_prec = get_precedence(next);
if (next_prec<min_prec)
return left;
consume_token(p);
ast right = parse_expression_aux(p, next_prec);
ast_op data_op;
{
struct ast_op __internal_tmp = {
.op = next,
.left = left,
.right = right};
data_op = allocate_compiler_persistent(sizeof(struct ast_op));
*data_op = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_op = data_op};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_op,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
return res;

}


boolean has_been_included(parser p, string filename){
__internal_dynamic_array_t includes = p->Includes;
int len = get_length(includes);
for(int i =0; i <= (int)len-1; i++)if (str_eq(filename, string_get_elem(includes, i)))
return true;
return false;

}


void parse_program(parser p){
__internal_dynamic_array_t prog = ast_make_array();
__internal_dynamic_array_t tokens = p->Toks;
__internal_dynamic_array_t includes = p->Includes;
while (p->Cursor<get_length(tokens))
{
tokens = p->Toks;
if (peek_type(p)==TOK_INCLUDE)
{
consume_token(p);
expect(p, TOK_STR_LIT);
token fn = consume_token(p);
string filename = create_string(fn->Lexeme, 1, get_string_length(fn->Lexeme)-2);
string abs_path = get_abs_path(filename);
if (has_been_included(p, abs_path)==false)
{
string_push_array(includes, abs_path);
lexer l = new_lexer(filename);
lex_program(l);
__internal_dynamic_array_t toks = l->Toks;
__internal_dynamic_array_t new_toks = token_make_array();
for(int i =0; i <= (int)p->Cursor-1; i++)token_push_array(new_toks, token_get_elem(tokens, i));
for(int i =0; i <= (int)get_length(toks)-1; i++)token_push_array(new_toks, token_get_elem(toks, i));
for(int i =p->Cursor; i <= (int)get_length(tokens)-1; i++)token_push_array(new_toks, token_get_elem(tokens, i));
p->Toks = new_toks;

}

}
else
ast_push_array(prog, parse_statement(p));

}
ast_program data_program;
{
struct ast_program __internal_tmp = {
.prog = prog};
data_program = allocate_compiler_persistent(sizeof(struct ast_program));
*data_program = __internal_tmp;
}
ast_data data;
{
struct ast_data __internal_tmp = {
.data_program = data_program};
data = allocate_compiler_persistent(sizeof(struct ast_data));
*data = __internal_tmp;
}
ast res;
{
struct ast __internal_tmp = {
.Tag = tag_program,
.Data = data};
res = allocate_compiler_persistent(sizeof(struct ast));
*res = __internal_tmp;
}
p->Prog = res;

}


enum nt_kind {
tdef,
fdef,
vdef
};
struct constructor_spec{
string name;
type_spec type;
};
struct type_spec{
string base_type;
int arrays;
boolean is_builtin;
tdef_type tdef_kind;
__internal_dynamic_array_t constructors;
};
struct nt_fun{
type_spec ret_type;
__internal_dynamic_array_t args;
};
struct nt_var{
type_spec type;
};
struct nt_elem{
nt_kind Tag;
string name;
int scope;
type_spec tdef;
nt_fun fun;
nt_var var;
};
struct nt{
__internal_dynamic_array_t elems;
int scope;
};
nt_elem get_ref(string name, nt table){
__internal_dynamic_array_t elems = table->elems;
int max_scope = 0-1;
nt_elem res = NULL;
for(int i =0; i <= (int)get_length(elems)-1; i++){
nt_elem elem = nt_elem_get_elem(elems, i);
if (str_eq(elem->name, name)&&max_scope<elem->scope)
{
if (elem->Tag==tdef)
return elem;
max_scope = elem->scope;
res = elem;

}

}
return res;

}


nt new_nt(){
__internal_dynamic_array_t elems = nt_elem_make_array();
nt res;
{
struct nt __internal_tmp = {
.elems = elems,
.scope = 0};
res = allocate_compiler_persistent(sizeof(struct nt));
*res = __internal_tmp;
}
return res;

}


void new_nt_scope(nt table){
table->scope = table->scope+1;

}


void end_nt_scope(nt table){
__internal_dynamic_array_t elems = table->elems;
int i = get_length(elems)-1;
boolean break_cond = false;
while (i>=0&&break_cond==false)
{
nt_elem elem = nt_elem_get_elem(elems, i);
if (elem->scope<table->scope)
break_cond = true;
else
nt_elem_pop_array(elems);
i = i-1;

}

}


void push_nt(nt table, string name, nt_elem elem){
__internal_dynamic_array_t elems = table->elems;
nt_elem res;
{
struct nt_elem __internal_tmp = {
.Tag = elem->Tag,
.name = elem->name,
.tdef = elem->tdef,
.fun = elem->fun,
.var = elem->var};
res = allocate_compiler_persistent(sizeof(struct nt_elem));
*res = __internal_tmp;
}
res->scope = table->scope;
nt_elem_push_array(elems, res);

}


type_spec get_builtin_type(string name){
type_spec res;
{
struct type_spec __internal_tmp = {
.base_type = name,
.arrays = 0,
.is_builtin = true,
.tdef_kind = TDEF_BUILTIN,
.constructors = NULL};
res = allocate_compiler_persistent(sizeof(struct type_spec));
*res = __internal_tmp;
}
return res;

}


nt_elem get_nt_fun(ast_fundef fundef){
__internal_dynamic_array_t nt_args = type_spec_make_array();
__internal_dynamic_array_t types = fundef->types;
for(int i =0; i <= (int)get_length(types)-1; i++)type_spec_push_array(nt_args, nt_type_of_ast(ast_get_elem(types, i)));
nt_fun fundef_elem;
{
struct nt_fun __internal_tmp = {
.ret_type = nt_type_of_ast(fundef->ret_type),
.args = nt_args};
fundef_elem = allocate_compiler_persistent(sizeof(struct nt_fun));
*fundef_elem = __internal_tmp;
}
nt_elem elem;
{
struct nt_elem __internal_tmp = {
.Tag = fdef,
.name = fundef->name->Lexeme,
.fun = fundef_elem};
elem = allocate_compiler_persistent(sizeof(struct nt_elem));
*elem = __internal_tmp;
}
return elem;

}


nt_elem nt_builtin_vardef(string name, string type){
nt_var elem_var;
{
struct nt_var __internal_tmp = {
.type = get_builtin_type(type)};
elem_var = allocate_compiler_persistent(sizeof(struct nt_var));
*elem_var = __internal_tmp;
}
nt_elem elem;
{
struct nt_elem __internal_tmp = {
.Tag = vdef,
.name = name,
.var = elem_var};
elem = allocate_compiler_persistent(sizeof(struct nt_elem));
*elem = __internal_tmp;
}
return elem;

}


nt_elem get_nt_var(ast_vardef vardef){
nt_var elem_var;
{
struct nt_var __internal_tmp = {
.type = nt_type_of_ast(vardef->type)};
elem_var = allocate_compiler_persistent(sizeof(struct nt_var));
*elem_var = __internal_tmp;
}
nt_elem elem;
{
struct nt_elem __internal_tmp = {
.Tag = vdef,
.name = vardef->name->Lexeme,
.var = elem_var};
elem = allocate_compiler_persistent(sizeof(struct nt_elem));
*elem = __internal_tmp;
}
return elem;

}


type_spec nt_type_of_ast(ast a){
ast_type type = a->Data->data_type;
type_spec res;
{
struct type_spec __internal_tmp = {
.base_type = type->name->Lexeme,
.is_builtin = is_builtin_typename(type->name->Lexeme),
.tdef_kind = TDEF_BUILTIN,
.constructors = NULL};
res = allocate_compiler_persistent(sizeof(struct type_spec));
*res = __internal_tmp;
}
return res;

}


nt_elem get_builtin_type_tdef(string name){
nt_elem elem;
{
struct nt_elem __internal_tmp = {
.Tag = tdef,
.name = name,
.tdef = get_builtin_type(name)};
elem = allocate_compiler_persistent(sizeof(struct nt_elem));
*elem = __internal_tmp;
}
return elem;

}


void setup_name_table(nt table){
push_nt(table, new_string((string){.data = "int", .length = 3}), get_builtin_type_tdef(new_string((string){.data = "int", .length = 3})));
push_nt(table, new_string((string){.data = "boolean", .length = 7}), get_builtin_type_tdef(new_string((string){.data = "boolean", .length = 7})));
push_nt(table, new_string((string){.data = "char", .length = 4}), get_builtin_type_tdef(new_string((string){.data = "char", .length = 4})));
push_nt(table, new_string((string){.data = "string", .length = 6}), get_builtin_type_tdef(new_string((string){.data = "string", .length = 6})));
push_nt(table, new_string((string){.data = "void", .length = 4}), get_builtin_type_tdef(new_string((string){.data = "void", .length = 4})));
push_nt(table, new_string((string){.data = "null_type", .length = 9}), get_builtin_type_tdef(new_string((string){.data = "null_type", .length = 9})));
push_nt(table, new_string((string){.data = "array", .length = 5}), get_builtin_type_tdef(new_string((string){.data = "array", .length = 5})));
push_nt(table, new_string((string){.data = "true", .length = 4}), nt_builtin_vardef(new_string((string){.data = "true", .length = 4}), new_string((string){.data = "boolean", .length = 7})));
push_nt(table, new_string((string){.data = "false", .length = 5}), nt_builtin_vardef(new_string((string){.data = "false", .length = 5}), new_string((string){.data = "boolean", .length = 7})));
push_nt(table, new_string((string){.data = "NULL", .length = 4}), nt_builtin_vardef(new_string((string){.data = "NULL", .length = 4}), new_string((string){.data = "null_type", .length = 9})));

}


struct gen{
file f;
nt table;
};
gen new_gen(string filename){
gen res;
{
struct gen __internal_tmp = {
.f = open_file(filename, WRITE_MODE),
.table = new_nt()};
res = allocate_compiler_persistent(sizeof(struct gen));
*res = __internal_tmp;
}
return res;

}


void kill_generator(gen g){
close_file(g->f);

}


void generate_type(gen g, ast a){
ast_type type = a->Data->data_type;
if (type->is_array)
pfile(g->f, new_string((string){.data = "__internal_dynamic_array_t", .length = 26}));
else
pfile(g->f, type->name->Lexeme);

}


void generate_gen_type_fun(gen g, ast_funcall funcall, string suffixe){
__internal_dynamic_array_t args = funcall->args;
ast arr_ast = ast_get_elem(args, 0);
string arr_name = arr_ast->Data->data_identifier->id->Lexeme;
nt_elem ref = get_ref(arr_name, g->table);
if (ref->Tag!=vdef)
{
print(new_string((string){.data = "Arrays must be declared as variables !\n", .length = 39}));
exit(1);

}
if (ref->var->type->arrays==0)
pfile(g->f, ref->var->type->base_type);
else
pfile(g->f, new_string((string){.data = "__internal_dynamic_array_t", .length = 26}));
pfile(g->f, suffixe);
pfile(g->f, new_string((string){.data = "(", .length = 1}));
for(int i =0; i <= (int)get_length(args)-1; i++){
if (i>0)
pfile(g->f, new_string((string){.data = ", ", .length = 2}));
generate_expression(g, ast_get_elem(args, i));

}
pfile(g->f, new_string((string){.data = ")", .length = 1}));

}


void generate_append(gen g, ast_funcall funcall){
generate_gen_type_fun(g, funcall, new_string((string){.data = "_push_array", .length = 11}));

}


void generate_get(gen g, ast_funcall funcall){
generate_gen_type_fun(g, funcall, new_string((string){.data = "_get_elem", .length = 9}));

}


void generate_set(gen g, ast_funcall funcall){
generate_gen_type_fun(g, funcall, new_string((string){.data = "_set_elem", .length = 9}));

}


void generate_pop(gen g, ast_funcall funcall){
generate_gen_type_fun(g, funcall, new_string((string){.data = "_pop_array", .length = 10}));

}


void generate_funcall(gen g, ast fun){
ast_funcall funcall = fun->Data->data_funcall;
if (str_eq(funcall->name->Lexeme, new_string((string){.data = "append", .length = 6})))
generate_append(g, funcall);
else
if (str_eq(funcall->name->Lexeme, new_string((string){.data = "get", .length = 3})))
generate_get(g, funcall);
else
if (str_eq(funcall->name->Lexeme, new_string((string){.data = "set", .length = 3})))
generate_set(g, funcall);
else
if (str_eq(funcall->name->Lexeme, new_string((string){.data = "pop", .length = 3})))
generate_pop(g, funcall);
else
{
pfile(g->f, funcall->name->Lexeme);
pfile(g->f, new_string((string){.data = "(", .length = 1}));
__internal_dynamic_array_t args = funcall->args;
for(int i =0; i <= (int)get_length(args)-1; i++){
if (i>0)
pfile(g->f, new_string((string){.data = ", ", .length = 2}));
generate_expression(g, ast_get_elem(args, i));

}
pfile(g->f, new_string((string){.data = ")", .length = 1}));

}

}


int get_lit_str_length(string s){
int length = 0;
for(int i =0; i <= (int)get_string_length(s)-1; i++){
if (get_nth_char(s, i)=='\\')
{
i = i+1;
char c = get_nth_char(s, i);
if (c=='n'||c=='t'||c=='\\'||c=='\"'||c=='\''||c=='r')
length = length+1;
else
length = length+2;

}
else
length = length+1;

}
return length;

}


void generate_op(gen g, ast expr){
ast_op op = expr->Data->data_op;
generate_expression(g, op->left);
if (op->op==TOK_EQUAL)
pfile(g->f, new_string((string){.data = "==", .length = 2}));
else
pfile(g->f, lexeme_of_type(op->op));
generate_expression(g, op->right);

}


void generate_if_statement(gen g, ast stmt){
ast_ifstmt ifstmt = stmt->Data->data_ifstmt;
pfile(g->f, new_string((string){.data = "if (", .length = 4}));
generate_expression(g, ifstmt->expr);
pfile(g->f, new_string((string){.data = ")\n", .length = 2}));
generate_statement(g, ifstmt->body);
if (ifstmt->elsestmt!=NULL)
{
pfile(g->f, new_string((string){.data = "else\n", .length = 5}));
generate_statement(g, ifstmt->elsestmt);

}

}


void generate_array_funcs(gen g, string type_name){
pfile(g->f, new_string((string){.data = "__internal_dynamic_array_t ", .length = 27}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "_make_array(void) {\n", .length = 20}));
pfile(g->f, new_string((string){.data = "return __internal_make_array(sizeof(", .length = 36}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "));\n", .length = 4}));
pfile(g->f, new_string((string){.data = "}\n\n", .length = 3}));
pfile(g->f, new_string((string){.data = " void ", .length = 6}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "_push_array(__internal_dynamic_array_t arr, ", .length = 44}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = " elem) {\n", .length = 9}));
pfile(g->f, new_string((string){.data = "  __internal_push_array(arr, &elem);\n", .length = 37}));
pfile(g->f, new_string((string){.data = "}\n\n", .length = 3}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "_pop_array(__internal_dynamic_array_t arr) {\n ", .length = 46}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = " *res = __internal_pop_array(arr);\n", .length = 35}));
pfile(g->f, new_string((string){.data = "  return *res;\n", .length = 15}));
pfile(g->f, new_string((string){.data = "}\n\n", .length = 3}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "_get_elem(__internal_dynamic_array_t arr, size_t index) {\n ", .length = 59}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = " *res = __internal_get_elem(arr, index);\n", .length = 41}));
pfile(g->f, new_string((string){.data = "  if (res == NULL){ printf(\"NULL ELEMENT IN ", .length = 44}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "_get_elem\"); exit(1);}", .length = 22}));
pfile(g->f, new_string((string){.data = "  return *res;\n", .length = 15}));
pfile(g->f, new_string((string){.data = "}\n\n", .length = 3}));
pfile(g->f, new_string((string){.data = "void ", .length = 5}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "_set_elem(__internal_dynamic_array_t arr, size_t index, ", .length = 56}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = " elem) {\n", .length = 9}));
pfile(g->f, new_string((string){.data = "  __internal_set_elem(arr, index, &elem);\n", .length = 42}));
pfile(g->f, new_string((string){.data = "}\n\n", .length = 3}));
pfile(g->f, new_string((string){.data = "void ", .length = 5}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "_insert(__internal_dynamic_array_t arr, size_t index, ", .length = 54}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = " elem) {\n", .length = 9}));
pfile(g->f, new_string((string){.data = "  __internal_insert(arr, index, &elem);\n", .length = 40}));
pfile(g->f, new_string((string){.data = "}\n\n", .length = 3}));

}


void generate_loop(gen g, ast loop_ast){
ast_loop l = loop_ast->Data->data_loop;
new_nt_scope(g->table);
nt_var var;
{
struct nt_var __internal_tmp = {
.type = get_builtin_type(new_string((string){.data = "int", .length = 3}))};
var = allocate_compiler_persistent(sizeof(struct nt_var));
*var = __internal_tmp;
}
nt_elem res;
{
struct nt_elem __internal_tmp = {
.Tag = vdef,
.name = l->variable->Lexeme,
.var = var};
res = allocate_compiler_persistent(sizeof(struct nt_elem));
*res = __internal_tmp;
}
push_nt(g->table, l->variable->Lexeme, res);
pfile(g->f, new_string((string){.data = "for(int ", .length = 8}));
pfile(g->f, l->variable->Lexeme);
pfile(g->f, new_string((string){.data = " =", .length = 2}));
generate_expression(g, l->start);
pfile(g->f, new_string((string){.data = "; ", .length = 2}));
pfile(g->f, l->variable->Lexeme);
pfile(g->f, new_string((string){.data = " <= (int)", .length = 9}));
generate_expression(g, l->end);
pfile(g->f, new_string((string){.data = "; ", .length = 2}));
pfile(g->f, l->variable->Lexeme);
pfile(g->f, new_string((string){.data = "++)", .length = 3}));
generate_statement(g, l->statement);
end_nt_scope(g->table);

}


void generate_sub_as_expression(gen g, ast expr){
ast_sub sub = expr->Data->data_sub;
__internal_dynamic_array_t path = sub->path;
for(int i =0; i <= (int)get_length(path)-1; i++){
token tok = token_get_elem(path, i);
pfile(g->f, tok->Lexeme);
pfile(g->f, new_string((string){.data = "->", .length = 2}));

}
generate_expression(g, sub->expr);

}


void generate_while_loop(gen g, ast l){
ast_while_loop while_loop = l->Data->data_while_loop;
pfile(g->f, new_string((string){.data = "while (", .length = 7}));
generate_expression(g, while_loop->condition);
pfile(g->f, new_string((string){.data = ")\n", .length = 2}));
generate_statement(g, while_loop->statement);

}


void generate_enum_tdef(gen g, ast expr){
ast_enum_tdef enum_tdef = expr->Data->data_enum_tdef;
pfile(g->f, new_string((string){.data = "enum ", .length = 5}));
pfile(g->f, enum_tdef->name->Lexeme);
pfile(g->f, new_string((string){.data = " {\n", .length = 3}));
__internal_dynamic_array_t items = enum_tdef->items;
for(int i =0; i <= (int)get_length(items)-1; i++){
if (i>0)
pfile(g->f, new_string((string){.data = ",\n", .length = 2}));
token tok = token_get_elem(items, i);
pfile(g->f, tok->Lexeme);

}
pfile(g->f, new_string((string){.data = "\n};\n", .length = 4}));

}


void generate_expression(gen g, ast expr){
if (expr->Tag==tag_literal)
{
token tok = expr->Data->data_literal->lit;
if (tok->Type!=TOK_STR_LIT)
pfile(g->f, tok->Lexeme);
else
{
pfile(g->f, new_string((string){.data = "new_string((string){.data = ", .length = 28}));
pfile(g->f, tok->Lexeme);
pfile(g->f, new_string((string){.data = ", .length = ", .length = 12}));
pfile(g->f, string_of_int(get_lit_str_length(tok->Lexeme)-2));
pfile(g->f, new_string((string){.data = "})", .length = 2}));

}

}
else
if (expr->Tag==tag_identifier)
pfile(g->f, expr->Data->data_identifier->id->Lexeme);
else
if (expr->Tag==tag_funcall)
generate_funcall(g, expr);
else
if (expr->Tag==tag_op)
generate_op(g, expr);
else
if (expr->Tag==tag_sub)
generate_sub_as_expression(g, expr);
else
{
print(new_string((string){.data = "Could not generate expression !\n", .length = 32}));
print_int(expr->Tag);
print(new_string((string){.data = "th tag is not implemented yet !\n", .length = 32}));
compiler_assert(false, new_string((string){.data = "TODO\n", .length = 5}));

}

}


void generate_assign(gen g, ast expr){
ast_assign assign = expr->Data->data_assign;
generate_expression(g, assign->target);
pfile(g->f, new_string((string){.data = " = ", .length = 3}));
generate_expression(g, assign->expr);
pfile(g->f, new_string((string){.data = ";\n", .length = 2}));

}


boolean is_builtin_typename(string name){
if (str_eq(name, new_string((string){.data = "int", .length = 3})))
return true;
if (str_eq(name, new_string((string){.data = "boolean", .length = 7})))
return true;
if (str_eq(name, new_string((string){.data = "string", .length = 6})))
return true;
if (str_eq(name, new_string((string){.data = "char", .length = 4})))
return true;
if (str_eq(name, new_string((string){.data = "void", .length = 4})))
return true;
return false;

}


void generate_vardef(gen g, ast var){
ast_vardef vardef = var->Data->data_vardef;
push_nt(g->table, vardef->name->Lexeme, get_nt_var(vardef));
string type_name = vardef->type->Data->data_type->name->Lexeme;
if (vardef->type->Data->data_type->is_array&&vardef->expr->Tag==tag_literal)
{
generate_type(g, vardef->type);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, vardef->name->Lexeme);
pfile(g->f, new_string((string){.data = " = ", .length = 3}));
compiler_assert(vardef->expr->Data->data_literal->lit->Type==TOK_ARR_DECL, new_string((string){.data = "Cannot declare arrays this way !\n", .length = 33}));
pfile(g->f, type_name);
pfile(g->f, new_string((string){.data = "_make_array();\n", .length = 15}));

}
else
if (is_builtin_typename(type_name)||vardef->type->Data->data_type->is_array)
{
generate_type(g, vardef->type);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, vardef->name->Lexeme);
pfile(g->f, new_string((string){.data = " = ", .length = 3}));
generate_expression(g, vardef->expr);
pfile(g->f, new_string((string){.data = ";\n", .length = 2}));

}
else
if (vardef->expr->Tag==tag_record_expr)
{
generate_type(g, vardef->type);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, vardef->name->Lexeme);
pfile(g->f, new_string((string){.data = ";\n{\nstruct ", .length = 11}));
generate_type(g, vardef->type);
pfile(g->f, new_string((string){.data = " __internal_tmp = {\n", .length = 20}));
ast_record_expr record = vardef->expr->Data->data_record_expr;
__internal_dynamic_array_t names = record->names;
__internal_dynamic_array_t exprs = record->exprs;
if (get_length(names)==0)
pfile(g->f, new_string((string){.data = "0", .length = 1}));
for(int i =0; i <= (int)get_length(names)-1; i++){
if (i>0)
pfile(g->f, new_string((string){.data = ",\n", .length = 2}));
token name = token_get_elem(names, i);
ast expr = ast_get_elem(exprs, i);
pfile(g->f, new_string((string){.data = ".", .length = 1}));
pfile(g->f, name->Lexeme);
pfile(g->f, new_string((string){.data = " = ", .length = 3}));
generate_expression(g, expr);

}
pfile(g->f, new_string((string){.data = "};\n", .length = 3}));
pfile(g->f, vardef->name->Lexeme);
pfile(g->f, new_string((string){.data = " = allocate_compiler_persistent(sizeof(struct ", .length = 46}));
generate_type(g, vardef->type);
pfile(g->f, new_string((string){.data = "));\n*", .length = 5}));
pfile(g->f, vardef->name->Lexeme);
pfile(g->f, new_string((string){.data = " = __internal_tmp;\n}\n", .length = 21}));

}
else
{
generate_type(g, vardef->type);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, vardef->name->Lexeme);
pfile(g->f, new_string((string){.data = " = ", .length = 3}));
generate_expression(g, vardef->expr);
pfile(g->f, new_string((string){.data = ";\n", .length = 2}));

}

}


void generate_return(gen g, ast ret_ast){
pfile(g->f, new_string((string){.data = "return ", .length = 7}));
ast expr = ret_ast->Data->data_ret->expr;
if (expr!=NULL)
generate_expression(g, expr);
pfile(g->f, new_string((string){.data = ";\n", .length = 2}));

}


void generate_statement(gen g, ast a){
ast_kind tag = a->Tag;
if (tag==tag_vardef)
generate_vardef(g, a);
else
if (tag==tag_ret)
generate_return(g, a);
else
if (tag==tag_compound)
generate_compound(g, a);
else
if (tag==tag_ifstmt)
generate_if_statement(g, a);
else
if (tag==tag_tdef)
generate_tdef(g, a);
else
if (tag==tag_enum_tdef)
generate_enum_tdef(g, a);
else
if (tag==tag_fundef)
generate_fundef(g, a);
else
if (tag==tag_loop)
generate_loop(g, a);
else
if (tag==tag_while_loop)
generate_while_loop(g, a);
else
if (tag==tag_assign)
generate_assign(g, a);
else
{
generate_expression(g, a);
pfile(g->f, new_string((string){.data = ";\n", .length = 2}));

}

}


void generate_tdef(gen g, ast a){
ast_tdef tdef = a->Data->data_tdef;
string name = tdef->name->Lexeme;
pfile(g->f, new_string((string){.data = "struct ", .length = 7}));
pfile(g->f, name);
pfile(g->f, new_string((string){.data = "{\n", .length = 2}));
compiler_assert(tdef->t!=TDEF_PRO, new_string((string){.data = "Product type definition not implemented yet\n", .length = 44}));
__internal_dynamic_array_t constructors = tdef->constructors;
for(int i =0; i <= (int)get_length(constructors)-1; i++){
ast cons_ast = ast_get_elem(constructors, i);
ast_cons cons = cons_ast->Data->data_cons;
ast_type type = cons->type->Data->data_type;
if (str_eq(new_string((string){.data = "void", .length = 4}), type->name->Lexeme)==false)
{
generate_type(g, cons->type);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, cons->name->Lexeme);
pfile(g->f, new_string((string){.data = ";\n", .length = 2}));

}

}
pfile(g->f, new_string((string){.data = "};\n", .length = 3}));

}


void generate_compound(gen g, ast expr){
pfile(g->f, new_string((string){.data = "{\n", .length = 2}));
ast_compound compound = expr->Data->data_compound;
new_nt_scope(g->table);
__internal_dynamic_array_t stmts = compound->stmts;
for(int i =0; i <= (int)get_length(stmts)-1; i++)generate_statement(g, ast_get_elem(stmts, i));
end_nt_scope(g->table);
pfile(g->f, new_string((string){.data = "\n}\n", .length = 3}));

}


void generate_fundef_proto(gen g, ast fun, boolean add){
ast_fundef fundef = fun->Data->data_fundef;
generate_type(g, fundef->ret_type);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, fundef->name->Lexeme);
pfile(g->f, new_string((string){.data = "(", .length = 1}));
__internal_dynamic_array_t args = fundef->args;
__internal_dynamic_array_t types = fundef->types;
for(int i =0; i <= (int)get_length(args)-1; i++){
token arg = token_get_elem(args, i);
ast type = ast_get_elem(types, i);
if (add)
{
nt_var elem_var;
{
struct nt_var __internal_tmp = {
.type = nt_type_of_ast(type)};
elem_var = allocate_compiler_persistent(sizeof(struct nt_var));
*elem_var = __internal_tmp;
}
nt_elem elem;
{
struct nt_elem __internal_tmp = {
.Tag = vdef,
.name = arg->Lexeme,
.var = elem_var};
elem = allocate_compiler_persistent(sizeof(struct nt_elem));
*elem = __internal_tmp;
}
push_nt(g->table, arg->Lexeme, elem);

}
if (i>0)
pfile(g->f, new_string((string){.data = ", ", .length = 2}));
generate_type(g, type);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, arg->Lexeme);

}
pfile(g->f, new_string((string){.data = ")", .length = 1}));

}


void generate_fundef(gen g, ast fun){
ast_fundef fundef = fun->Data->data_fundef;
new_nt_scope(g->table);
push_nt(g->table, fundef->name->Lexeme, get_nt_fun(fundef));
if (str_eq(fundef->name->Lexeme, new_string((string){.data = "main", .length = 4}))==false)
{
generate_fundef_proto(g, fun, true);
generate_compound(g, fundef->body);
pfile(g->f, new_string((string){.data = "\n\n", .length = 2}));

}
else
{
pfile(g->f, new_string((string){.data = "int main(int argc, char **argv) {\n", .length = 34}));
pfile(g->f, new_string((string){.data = "init_rocker(argc, argv);\n", .length = 25}));
generate_compound(g, fundef->body);
pfile(g->f, new_string((string){.data = "end_rocker();\n", .length = 14}));
pfile(g->f, new_string((string){.data = "return 0;\n", .length = 10}));
pfile(g->f, new_string((string){.data = "}\n\n", .length = 3}));

}
end_nt_scope(g->table);

}


void generate_forward_defs(gen g, ast program){
__internal_dynamic_array_t stmts = program->Data->data_program->prog;
for(int i =0; i <= (int)get_length(stmts)-1; i++){
ast stmt = ast_get_elem(stmts, i);
if (stmt->Tag==tag_tdef)
{
ast_tdef tdef = stmt->Data->data_tdef;
string name = tdef->name->Lexeme;
pfile(g->f, new_string((string){.data = "typedef struct ", .length = 15}));
pfile(g->f, name);
pfile(g->f, new_string((string){.data = "*", .length = 1}));
pfile(g->f, name);
pfile(g->f, new_string((string){.data = ";\n\n", .length = 3}));
generate_array_funcs(g, name);

}
else
if (stmt->Tag==tag_enum_tdef)
{
ast_enum_tdef enum_tdef = stmt->Data->data_enum_tdef;
string name = enum_tdef->name->Lexeme;
pfile(g->f, new_string((string){.data = "typedef enum ", .length = 13}));
pfile(g->f, name);
pfile(g->f, new_string((string){.data = " ", .length = 1}));
pfile(g->f, name);
pfile(g->f, new_string((string){.data = ";\n", .length = 2}));

}

}
for(int i =0; i <= (int)get_length(stmts)-1; i++){
ast stmt = ast_get_elem(stmts, i);
if (stmt->Tag==tag_fundef)
{
ast_fundef fundef = stmt->Data->data_fundef;
string name = fundef->name->Lexeme;
if (str_eq(name, new_string((string){.data = "main", .length = 4}))==false)
{
generate_fundef_proto(g, stmt, false);
pfile(g->f, new_string((string){.data = ";\n", .length = 2}));

}

}

}

}


void transpile(gen g, ast program){
setup_name_table(g->table);
__internal_dynamic_array_t stmts = program->Data->data_program->prog;
pfile(g->f, new_string((string){.data = "#include \"./src/generation/fundefs.h\"\n", .length = 38}));
pfile(g->f, new_string((string){.data = "#include \"./src/generation/fundefs_internal.h\"\n", .length = 47}));
pfile(g->f, new_string((string){.data = "#include \"./src/generation/typedefs.h\"\n", .length = 39}));
pfile(g->f, new_string((string){.data = "#include \"./RockerAllocator/alloc.h\"\n", .length = 37}));
generate_forward_defs(g, program);
for(int i =0; i <= (int)get_length(stmts)-1; i++){
generate_statement(g, ast_get_elem(stmts, i));

}

}


void type_check(ast prog){
implemented(new_string((string){.data = "type_check", .length = 10}));

}


void usage(string prog_name){
print(new_string((string){.data = "Usage:\n", .length = 7}));
print(new_string((string){.data = "\t", .length = 1}));
print(prog_name);
print(new_string((string){.data = " [flags] <input file> [output file]\n", .length = 36}));
print(new_string((string){.data = "Possible flags:\n", .length = 16}));
print(new_string((string){.data = "\t\'-t\' or \'--tmp\'      :\t Does not remove the temporary transpiled C files\n", .length = 74}));
print(new_string((string){.data = "\t\'-c\' or \'--transpile\':\t Only transpiles the Rocker to C but does not compile to a native executable\n", .length = 101}));
print(new_string((string){.data = "\t\'-l\' or \'--lexer\'    :\t Prints the tokens contained in the file and included files\n", .length = 84}));
print(new_string((string){.data = "\t\'-h\' or \'--help\'     :\t Displays this message\n", .length = 47}));
print(new_string((string){.data = "\t\'-v\' or \'--verbose\'  :\t Prints infos and commands ran by the compiler\n", .length = 71}));

}


int main(int argc, char **argv) {
init_rocker(argc, argv);
{
__internal_dynamic_array_t args = get_args();
string this_file = string_get_elem(args, 0);
if (get_length(args)<2)
{
print(new_string((string){.data = "[ERR]  Expected input !\n", .length = 24}));
usage(this_file);
exit(1);

}
string input = new_string((string){.data = "", .length = 0});
string output = new_string((string){.data = "", .length = 0});
string default_output = new_string((string){.data = "a.out", .length = 5});
boolean print_lexer = false;
boolean quiet = true;
boolean keep_tmp = false;
boolean transpile_only = false;
for(int i =1; i <= (int)get_length(args)-1; i++){
string arg = string_get_elem(args, i);
if (get_nth_char(arg, 0)=='-')
{
if (get_string_length(arg)==1)
{
print(new_string((string){.data = "[ERR]  Unexpected empty flag !\n", .length = 31}));
usage(this_file);
exit(1);

}
if (str_eq(arg, new_string((string){.data = "-l", .length = 2}))||str_eq(arg, new_string((string){.data = "--lexer", .length = 7})))
print_lexer = true;
else
if (str_eq(arg, new_string((string){.data = "-v", .length = 2}))||str_eq(arg, new_string((string){.data = "--verbose", .length = 9})))
quiet = false;
else
if (str_eq(arg, new_string((string){.data = "-h", .length = 2}))||str_eq(arg, new_string((string){.data = "--help", .length = 6})))
{
usage(this_file);
exit(0);

}
else
if (str_eq(arg, new_string((string){.data = "-t", .length = 2}))||str_eq(arg, new_string((string){.data = "--tmp", .length = 5})))
keep_tmp = true;
else
if (str_eq(arg, new_string((string){.data = "-c", .length = 2}))||str_eq(arg, new_string((string){.data = "--transpile", .length = 11})))
transpile_only = true;
else
{
print(new_string((string){.data = "[ERR]  Unknown flag \'", .length = 21}));
print(arg);
print(new_string((string){.data = "\'!\n", .length = 3}));
usage(this_file);
exit(1);

}

}
else
if (get_string_length(input)==0)
input = arg;
else
if (get_string_length(output)==0)
output = arg;
else
{
print(new_string((string){.data = "Unexpected argument: \'", .length = 22}));
print(arg);
print(new_string((string){.data = "\'!\n", .length = 3}));
usage(this_file);
exit(1);

}

}
if (get_string_length(input)==0)
{
print(new_string((string){.data = "[ERR]  Expected input !\n", .length = 24}));
usage(this_file);
exit(1);

}
if (get_string_length(output)==0)
output = default_output;
lexer l = new_lexer(input);
lex_program(l);
__internal_dynamic_array_t toks = l->Toks;
parser p = new_parser(toks);
parse_program(p);
if (print_lexer)
print_list_types(p->Toks);
string cout = concat_string(output, new_string((string){.data = ".c", .length = 2}));
gen g = new_gen(cout);
transpile(g, p->Prog);
kill_generator(g);
if (quiet==false)
print(new_string((string){.data = "[INFO] Transpiling to C successful\n", .length = 35}));
if (transpile_only==false)
{
string command = new_string((string){.data = "", .length = 0});
command = concat_string(command, new_string((string){.data = "clang-format ", .length = 13}));
command = concat_string(command, cout);
command = concat_string(command, new_string((string){.data = " -i", .length = 3}));
command = concat_string(command, new_string((string){.data = " && ", .length = 4}));
command = concat_string(command, new_string((string){.data = " gcc -Wall -g -o ", .length = 17}));
command = concat_string(command, output);
command = concat_string(command, new_string((string){.data = " ", .length = 1}));
command = concat_string(command, cout);
command = concat_string(command, new_string((string){.data = " src/generation/fundefs.c", .length = 25}));
command = concat_string(command, new_string((string){.data = " src/generation/fundefs_internal.c", .length = 34}));
command = concat_string(command, new_string((string){.data = " RockerAllocator/alloc.c", .length = 24}));
if (quiet==false)
{
print(new_string((string){.data = "[CMD]  ", .length = 7}));
print(command);
print(new_string((string){.data = "\n", .length = 1}));

}
system(string_to_cstr(command));
if (quiet==false)
print(new_string((string){.data = "[INFO] Compiling transpiled C file successful\n", .length = 46}));

}
if (keep_tmp==false&&transpile_only==false)
{
string remove_tmp = new_string((string){.data = "rm ", .length = 3});
remove_tmp = concat_string(remove_tmp, cout);
if (str_eq(cout, new_string((string){.data = "", .length = 0}))==false)
{
if (quiet==false)
{
print(new_string((string){.data = "[CMD]  ", .length = 7}));
print(remove_tmp);
print(new_string((string){.data = "\n", .length = 1}));
print(new_string((string){.data = "[INFO] Removing transpiled C file successful\n", .length = 45}));

}
system(string_to_cstr(remove_tmp));

}

}
if (quiet==false&&transpile_only==false)
print(new_string((string){.data = "[INFO] Rocker compiling successful\n", .length = 35}));

}
end_rocker();
return 0;
}

