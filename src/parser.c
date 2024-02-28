#include "parser.h"
#include "../RockerAllocator/alloc.h"
#include "ast.h"
#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *includes[1024];
int includes_num = 0;

ast_t parse_expression(parser_t *p);
ast_t parse_type(parser_t *p);
ast_t parse_fundef(parser_t *p);
ast_t parse_var_def(parser_t *p);
ast_t parse_match(parser_t *p);
ast_t parse_loop(parser_t *p);
ast_t parse_compound(parser_t *p);
int is_sub(parser_t p);
ast_t parse_statement(parser_t *p);
ast_t parse_while_loop(parser_t *p);
ast_t parse_leaf(parser_t *p);

void print_error_prefix(parser_t p) {
  token_t tok = peek_token(p);
  printf("%s:%d:%d:", tok.filename, tok.line, tok.col);
}

token_type_t peek_type(parser_t p) { return p.tokens.data[p.cursor].type; }

token_t peek_token(parser_t p) { return p.tokens.data[p.cursor]; }

token_t consume_token(parser_t *p) {
  if (p->cursor < 0)
    return (token_t){0};
  return p->tokens.data[p->cursor++];
}

parser_t new_parser(token_array_t tokens) {
  parser_t res;
  res.cursor = 0;
  res.prog = NULL;
  res.tokens = tokens;
  return res;
}

void expect(parser_t p, token_type_t b) {
  token_type_t a = peek_type(p);
  if (a != b) {
    print_error_prefix(p);
    printf("Expected %s but got: %s\n", lexeme_of_type(b), lexeme_of_type(a));
    exit(1);
  }
}

int is_assign(parser_t p) {
  int scope = 0;
  token_type_t current = consume_token(&p).type;
  if (current == TOK_OPEN_BRACE || current == TOK_CLOSE_BRACE)
    return 0;
  while (scope >= 0 && current != TOK_BIG_ARROW) {
    if (current == TOK_OPEN_BRACE || current == TOK_OPEN_BRACE)
      scope++;
    else if (current == TOK_CLOSE_BRACE || current == TOK_CLOSE_BRACE)
      scope--;
    else if (current == TOK_COMMA)
      break;
    else if (current == TOK_SEMICOL)
      break;
    else if (current == TOK_COLON)
      break;
    else if (current == TOK_SMALL_ARROW)
      break;
    else if (current == TOK_LOOP)
      break;
    current = consume_token(&p).type;
  }
  return current == TOK_BIG_ARROW;
}

ast_t parse_assign(parser_t *p) {
  expect(*p, TOK_IDENTIFIER);
  ast_t target = parse_expression(p);
  expect(*p, TOK_BIG_ARROW);
  consume_token(p);
  ast_t expr = parse_expression(p);
  expect(*p, TOK_SEMICOL);
  consume_token(p);
  return new_ast(
      (node_t){assign, {.assign = {.expr = expr, .target = target}}});
}

ast_t parse_cons(parser_t *p) {
  // Name : type [,]
  token_t name = consume_token(p);
  expect(*p, TOK_COLON);
  consume_token(p);
  ast_t type = parse_type(p);
  if (peek_type(*p) == TOK_COMMA)
    consume_token(p);
  return new_ast((node_t){cons, {.cons = {name, type}}});
}

ast_t parse_tdef(parser_t *p) {
  tdef_type_t type = -1;
  if (peek_type(*p) == TOK_REC)
    type = TDEF_REC;
  else if (peek_type(*p) == TOK_PRO)
    type = TDEF_PRO;
  else
    expect(*p, TOK_REC); // Error reporting purposes
  consume_token(p);
  token_t name = consume_token(p);
  expect(*p, TOK_BIG_ARROW);
  consume_token(p);
  expect(*p, TOK_OPEN_BRACE);
  consume_token(p);
  ast_array_t conss = new_ast_array();
  while (peek_type(*p) != TOK_CLOSE_BRACE)
    push_ast_array(&conss, parse_cons(p));
  consume_token(p);
  return new_ast((node_t){tdef, {.tdef = {name, type, conss}}});
}

ast_t parse_ret(parser_t *p) {
  expect(*p, TOK_RETURN);
  consume_token(p);
  if (peek_type(*p) == TOK_SEMICOL) {
    consume_token(p);
    return new_ast((node_t){ret, {.ret = {NULL}}});
  }
  ast_t expr = parse_expression(p);
  expect(*p, TOK_SEMICOL);
  consume_token(p);
  return new_ast((node_t){ret, {.ret = {expr}}});
}

ast_t parse_literal(parser_t *p) {
  return new_ast((node_t){literal, {.literal = {.lit = consume_token(p)}}});
}

ast_t parse_sub(parser_t *p) {
  token_array_t path = new_token_array();
  token_array_push(&path, consume_token(p));
  while (peek_type(*p) == TOK_SUB) {
    consume_token(p);
    if (is_sub(*p))
      token_array_push(&path, consume_token(p));
    else
      break;
  }
  ast_t expr = parse_expression(p);
  return new_ast((node_t){sub, {.sub = {.expr = expr, .path = path}}});
}

ast_t parse_if(parser_t *p) {
  consume_token(p);
  ast_t condition = parse_expression(p);
  expect(*p, TOK_THEN);
  consume_token(p);
  ast_t body = parse_statement(p);
  ast_t else_body = NULL;
  if (peek_type(*p) == TOK_ELSE) {
    consume_token(p);
    else_body = parse_statement(p);
  }
  return new_ast((node_t){ifstmt,
                          {.ifstmt = {
                               .body = body,
                               .elsestmt = else_body,
                               .expression = condition,
                           }}});
}

ast_t parse_enum(parser_t *p) {
  expect(*p, TOK_ENUM);
  consume_token(p);
  expect(*p, TOK_IDENTIFIER);
  token_t name = consume_token(p);
  expect(*p, TOK_BIG_ARROW);
  consume_token(p);
  expect(*p, TOK_OPEN_BRACE);
  consume_token(p);
  token_array_t elems = new_token_array();
  while (peek_type(*p) != TOK_CLOSE_BRACE) {
    expect(*p, TOK_IDENTIFIER);
    token_array_push(&elems, consume_token(p));
    if (peek_type(*p) != TOK_COMMA)
      break;
    consume_token(p);
  }
  expect(*p, TOK_CLOSE_BRACE);
  consume_token(p);
  return new_ast((node_t){enum_tdef, {.enum_tdef = {name, elems}}});
}

ast_t parse_statement(parser_t *p) {
  token_type_t a = peek_type(*p);
  if (a == TOK_IF)
    return parse_if(p);
  else if (a == TOK_ENUM)
    return parse_enum(p);
  else if (a == TOK_PRO || a == TOK_REC)
    return parse_tdef(p);
  else if (a == TOK_WHILE)
    return parse_while_loop(p);
  else if (is_assign(*p))
    return parse_assign(p);
  else if (a == TOK_LOOP)
    return parse_loop(p);
  else if (a == TOK_LET) {
    parser_t p2 = *p;
    consume_token(&p2);
    consume_token(&p2);
    if (peek_type(p2) == TOK_OPEN_PAREN) // function def
      return parse_fundef(p);
    else // var def
    {
      ast_t vdef = parse_var_def(p);
      return vdef;
    }
  } else if (a == TOK_RETURN) {
    return parse_ret(p);
  } else if (a == TOK_MATCH)
    return parse_match(p);
  else if (a == TOK_OPEN_BRACE) {
    return parse_compound(p);
  } else {
    ast_t expr = parse_expression(p);
    expect(*p, TOK_SEMICOL);
    consume_token(p);
    return expr;
  }
  return NULL;
}

ast_t parse_matchcase(parser_t *p) {
  ast_t expr = parse_expression(p);
  expect(*p, TOK_SMALL_ARROW);
  ast_t stmt = parse_statement(p);
  return new_ast(
      (node_t){matchcase, {.matchcase = {.body = stmt, .expr = expr}}});
}

ast_t parse_match(parser_t *p) {
  expect(*p, TOK_MATCH);
  consume_token(p);
  ast_t to_match = parse_expression(p);
  expect(*p, TOK_BIG_ARROW);
  consume_token(p);
  expect(*p, TOK_OPEN_BRACE);
  consume_token(p);
  ast_array_t cases = new_ast_array();
  while (peek_type(*p) == TOK_SMALL_ARROW) {
    consume_token(p);
    push_ast_array(&cases, parse_matchcase(p));
  }
  expect(*p, TOK_CLOSE_BRACE);
  consume_token(p);
  return new_ast(
      (node_t){match, {.match = {.cases = cases, .expr = to_match}}});
}

ast_t parse_loop(parser_t *p) {
  expect(*p, TOK_LOOP);
  consume_token(p);
  expect(*p, TOK_IDENTIFIER);
  token_t var_name = consume_token(p);
  expect(*p, TOK_COLON);
  consume_token(p);
  ast_t begin = parse_expression(p);
  expect(*p, TOK_SMALL_ARROW);
  consume_token(p);
  ast_t end = parse_expression(p);
  expect(*p, TOK_BIG_ARROW);
  consume_token(p);
  ast_t stmt = parse_statement(p);
  return new_ast((node_t){loop, {.loop = {var_name, begin, end, stmt}}});
}

ast_t parse_while_loop(parser_t *p) {
  expect(*p, TOK_WHILE);
  consume_token(p);
  ast_t condition = parse_expression(p);
  expect(*p, TOK_DO);
  consume_token(p);
  ast_t statement = parse_statement(p);
  return new_ast((node_t){
      while_loop,
      {.while_loop = {.statement = statement, .condition = condition}}});
}

ast_t parse_record_expression(parser_t *p) {
  token_array_t names = new_token_array();
  ast_array_t exprs = new_ast_array();
  while (peek_type(*p) != TOK_CLOSE_BRACE) {
    expect(*p, TOK_IDENTIFIER);
    token_t cons_name = consume_token(p);
    token_array_push(&names, cons_name);
    expect(*p, TOK_BIG_ARROW);
    consume_token(p);
    ast_t expr = parse_expression(p);
    push_ast_array(&exprs, expr);
    if (peek_type(*p) != TOK_COMMA) {
      break;
    }
    consume_token(p);
  }
  return new_ast(
      (node_t){record_expr, {.record_expr = {.exprs = exprs, .names = names}}});
}

ast_t parse_var_def(parser_t *p) {
  expect(*p, TOK_LET);
  consume_token(p);
  token_t id = consume_token(p);

  expect(*p, TOK_COLON);
  consume_token(p);

  ast_t type = parse_type(p);

  expect(*p, TOK_BIG_ARROW);
  consume_token(p);

  ast_t expr = NULL;
  int is_rec = 0;
  if (peek_type(*p) == TOK_OPEN_BRACE) {
    // We have a Record variable declaration !!
    is_rec = 1;
    consume_token(p);
    expr = parse_record_expression(p);
    expect(*p, TOK_CLOSE_BRACE);
    consume_token(p);
  } else if (peek_type(*p) == TOK_ARR_DECL) {
    expr = new_ast((node_t){literal, {.literal = {consume_token(p)}}});

  } else
    expr = parse_expression(p);
  expect(*p, TOK_SEMICOL);
  consume_token(p);
  return new_ast((node_t){
      vardef,
      {.vardef = {.expr = expr, .name = id, .type = type, .is_rec = is_rec}}});
}

ast_t parse_type(parser_t *p) {
  expect(*p, TOK_IDENTIFIER);
  token_t name = consume_token(p);
  int is_array = 0;
  if (peek_type(*p) == TOK_ARR_DECL) {
    consume_token(p);
    is_array = 1;
  }
  return new_ast((node_t){type, {.type = {name, is_array}}});
}

ast_t parse_compound(parser_t *p) {
  expect(*p, TOK_OPEN_BRACE);
  consume_token(p);
  ast_array_t stmts = new_ast_array();
  while (peek_type(*p) != TOK_CLOSE_BRACE)
    push_ast_array(&stmts, parse_statement(p));
  expect(*p, TOK_CLOSE_BRACE);
  consume_token(p);
  return new_ast((node_t){compound, {.compound = {stmts}}});
}

ast_t parse_fundef(parser_t *p) {
  expect(*p, TOK_LET);
  consume_token(p);
  token_t id = consume_token(p);
  expect(*p, TOK_OPEN_PAREN);
  consume_token(p);
  token_array_t args = new_token_array();
  ast_array_t types = new_ast_array();
  while (peek_type(*p) != TOK_CLOSE_PAREN) {
    expect(*p, TOK_IDENTIFIER);
    token_t arg = consume_token(p);
    token_array_push(&args, arg);

    expect(*p, TOK_COLON);
    consume_token(p);
    ast_t type = parse_type(p);
    push_ast_array(&types, type);

    if (peek_type(*p) != TOK_COMMA)
      break;
    consume_token(p);
  }

  expect(*p, TOK_CLOSE_PAREN);
  consume_token(p);

  expect(*p, TOK_COLON);
  consume_token(p);

  ast_t type = parse_type(p);

  expect(*p, TOK_BIG_ARROW);
  consume_token(p);

  ast_t body = parse_compound(p);
  return new_ast((node_t){fundef,
                          {.fundef = {.args = args,
                                      .body = body,
                                      .name = id,
                                      .types = types,
                                      .ret_type = type}}});
}

int is_primary(parser_t p) {
  token_type_t t = peek_type(p);
  return t == TOK_OPEN_BRACE || t == TOK_OPEN_PAREN || t == TOK_IDENTIFIER ||
         t == TOK_STR_LIT || t == TOK_CHR_LIT || t == TOK_NUM_LIT ||
         t == TOK_WILDCARD || t == TOK_ARR_DECL;
}

int is_funcall(parser_t p) {
  return consume_token(&p).type == TOK_IDENTIFIER &&
         peek_type(p) == TOK_OPEN_PAREN;
}

ast_t parse_funcall(parser_t *p) {
  token_t id = consume_token(p);
  expect(*p, TOK_OPEN_PAREN);
  consume_token(p);
  ast_array_t args = new_ast_array();
  while (peek_type(*p) != TOK_CLOSE_PAREN) {
    push_ast_array(&args, parse_expression(p));
    if (peek_type(*p) != TOK_COMMA)
      break;
    consume_token(p);
  }

  expect(*p, TOK_CLOSE_PAREN);
  consume_token(p);
  return new_ast((node_t){funcall, {.funcall = {id, args}}});
}

ast_t parse_leaf(parser_t *p) {
  token_t t = consume_token(p);
  if (is_funcall(*p))
    return parse_funcall(p);
  if (t.type == TOK_IDENTIFIER)
    return new_ast((node_t){identifier, {.identifier = {t}}});
  else if (t.type == TOK_NUM_LIT || t.type == TOK_STR_LIT ||
           t.type == TOK_CHR_LIT || t.type == TOK_WILDCARD ||
           t.type == TOK_ARR_DECL)
    return new_ast((node_t){literal, {.literal = {t}}});
  printf("Expected leaf\n");
  exit(1);
  return NULL; // For TCC
}

int is_sub(parser_t p) {
  if (consume_token(&p).type != TOK_IDENTIFIER)
    return 0;
  if (consume_token(&p).type != TOK_SUB)
    return 0;
  return 1;
}

ast_t parse_primary(parser_t *p) {
  token_type_t type = peek_type(*p);
  if (is_funcall(*p)) {
    return parse_funcall(p);
  } else if (is_sub(*p)) {
    return parse_sub(p);
  } else if (type == TOK_STR_LIT || type == TOK_CHR_LIT ||
             type == TOK_NUM_LIT || type == TOK_WILDCARD ||
             type == TOK_IDENTIFIER || type == TOK_ARR_DECL) {
    return parse_leaf(p);
  } else if (type == TOK_OPEN_PAREN) {
    (void)consume_token(p);
    ast_t res = parse_expression(p);
    type = peek_type(*p);

    if (type != TOK_CLOSE_PAREN) {
      printf("%s\n", peek_token(*p).lexeme);
      printf("TODO : Better error reporting\n");
      printf("Unclosed parenthesis !\n");
      exit(1);
    }
    (void)consume_token(p);
    return res;
  } else if (type == TOK_OPEN_BRACE) {
    return parse_record_expression(p);
  } else {
    printf("Pb : %s\n", lexeme_of_type(type));
    printf("Could not parse as a primary !\n");
    exit(1);
  }
  return NULL; // For TCC
}

ast_t parse_increasing_precedence(parser_t *p, ast_t left, int min_prec);

ast_t parse_expression_aux(parser_t *p, int min_precedence);

ast_t parse_expression(parser_t *p) {
  token_type_t a = peek_type(*p);

  if (a == TOK_OPEN_PAREN) {
    consume_token(p);
    ast_t res = parse_expression(p);
    expect(*p, TOK_CLOSE_PAREN);
    consume_token(p);
    return res;
  } else if (a == TOK_OPEN_BRACE) {
    consume_token(p);
    return parse_record_expression(p);
  }
  return parse_expression_aux(p, -1); // for TCC
}

ast_t parse_expression_aux(parser_t *p, int min_precedence) {
  ast_t left = parse_primary(p);
  while (1) {
    ast_t node = parse_increasing_precedence(p, left, min_precedence);
    if (node == left)
      break;
    left = node;
  }
  return left;
}

ast_t parse_increasing_precedence(parser_t *p, ast_t left, int min_prec) {
  token_t next = peek_token(*p);
  if (!is_type_operator(next.type))
    return left;
  int next_prec = get_precedence(next.type);
  if (next_prec < min_prec)
    return left;
  (void)consume_token(p);
  ast_t right = parse_expression_aux(p, next_prec);
  return new_ast((node_t){op, {.op = {next.type, left, right}}});
}

int has_been_included(char *filename) {
  for (int i = 0; i < includes_num; i++)
    if (strcmp(filename, includes[i]) == 0)
      return 1;
  return 0;
}

void parse_program(parser_t *p) {
  ast_array_t prog = new_ast_array();
  while (p->cursor < p->tokens.length) {
    if (peek_type(*p) == TOK_INCLUDE) {
      consume_token(p);
      expect(*p, TOK_STR_LIT);
      char *filename = consume_token(p).lexeme;
      char *buffer = allocate_compiler_persistent(strlen(filename) - 1);
      memcpy(buffer, filename + 1, strlen(filename) - 2);
      buffer[strlen(filename) - 1] = 0;
      char *abs_path_tmp = realpath(buffer, NULL);
      char *abs_path = allocate_compiler_persistent(strlen(abs_path_tmp + 1));
      memcpy(abs_path, abs_path_tmp, strlen(abs_path_tmp) + 1);
      free(abs_path_tmp);
      if (!has_been_included(abs_path)) {
        if (includes_num >= 1024) {
          printf("Include limit reached !\n");
          exit(1);
        }
        includes[includes_num++] = abs_path;

        lexer_t l = new_lexer(buffer);
        token_array_t toks = lex_program(&l);
        token_array_t new_toks = new_token_array();
        for (int i = 0; i < p->cursor; i++)
          token_array_push(&new_toks, p->tokens.data[i]);
        for (int i = 0; i < toks.length; i++)
          token_array_push(&new_toks, toks.data[i]);
        for (int i = p->cursor; i < p->tokens.length; i++)
          token_array_push(&new_toks, p->tokens.data[i]);
        p->tokens = new_toks;
      }
      continue;
    }
    push_ast_array(&prog, parse_statement(p));
  }
  p->prog = new_ast((node_t){program, {.program = {prog}}});
}
