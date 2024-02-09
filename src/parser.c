#include "parser.h"
#include "ast.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

token_t parser_peek(parser_t p)
{
    if (p.cursor >= p.tokens.length)
        return (token_t){0};
    return p.tokens.data[p.cursor];
}

token_type_t parser_peek_type(parser_t p)
{
    return parser_peek(p).type;
}

token_t parser_consume(parser_t *p)
{
    token_t res = parser_peek(*p);
    printf("Consumming token '%s'\n", res.lexeme);
    p->cursor++;
    return res;
}

void parser_consume_n(parser_t *p, int n)
{
    p->cursor += n;
}

int is_primary(parser_t p)
{
    token_type_t t = parser_peek_type(p);
    return t == TOK_OPEN_BRACE || t == TOK_OPEN_PAREN || t == TOK_IDENTIFIER || t == TOK_STR_LIT || t == TOK_CHR_LIT || t == TOK_NUM_LIT;
}

ast_t parse_primary(parser_t *p)
{
    // Either an identifier, a literal, or an expression between {} or ()

    // first case: identifier
    token_type_t type = parser_peek_type(*p);
    if (type == TOK_IDENTIFIER)
    {
        token_t iden = parser_consume(p);
        ast_t identifier = new_ast((node_t){
            ast_identifier, {.ast_identifier = {iden}}});
        if (is_primary(*p))
        {
            return new_ast((node_t){
                ast_curry, {.ast_curry = {.caller = identifier, .arg = parse_primary(p)}}});
        }
        return identifier;
    }
    else if (type == TOK_NUM_LIT || type == TOK_STR_LIT || type == TOK_CHR_LIT)
    {
        ast_t lit = new_ast((node_t){
            ast_literal, {.ast_literal = {parser_consume(p)}}});
        if (is_primary(*p))
        {
            return new_ast((node_t){
                ast_curry, {.ast_curry = {.caller = lit, .arg = parse_primary(p)}}});
        }
        return lit;
    }
    else if (type == TOK_OPEN_PAREN)
    {
        (void)parser_consume(p);
        ast_t res = parse_expression(p);
        type = parser_peek_type(*p);
        if (type != TOK_CLOSE_PAREN)
        {
            printf("TODO : Better error reporting\n");
            printf("Unclosed parenthesis !\n");
            exit(1);
        }
        (void)parser_consume(p);
        return res;
    }

    else if (type == TOK_OPEN_BRACE)
    {
        (void)parser_consume(p);
        ast_t res = parse_expression(p);
        type = parser_peek_type(*p);
        if (type != TOK_CLOSE_BRACE)
        {
            printf("TODO : Better error reporting\n");
            printf("Unclosed brace !\n");
            exit(1);
        }
        (void)parser_consume(p);
        return res;
    }
    return NULL;
}

// ast_t parse_funcall(parser_t *p)
// {
//     (void)p;
//     assert(0 && "TODO: parse function call !");
//     return NULL;
// }

ast_t parse_expression(parser_t *p)
{
    token_type_t a = parser_peek_type(*p);
    if (a == TOK_OPEN_BRACE)
    {
        (void)parser_consume(p);
        ast_t res = parse_expression(p);
        // we expect closing '}'
        if (parser_consume(p).type != TOK_CLOSE_BRACE)
        {
            printf("TODO: Unclosed brace\n");
            exit(1);
        }
        return res;
    }
    else if (a == TOK_OPEN_PAREN)
    {
        (void)parser_consume(p);
        ast_t res = parse_expression(p);
        // we expect closing ')'
        if (parser_consume(p).type != TOK_CLOSE_PAREN)
        {
            printf("TODO: Unclosed parenthesis\n");
            exit(1);
        }
        return res;
    }
    else if (a == TOK_LET)
    {
        // let expression followed by 'in' followed by another expression

        ast_t binding = parse_let_binding(p);
        // We expect 'in'
        if (parser_consume(p).type != TOK_IN)
        {
            printf("Expected in keyword to evaluate let binding as expression\n");
            exit(1);
        }
        // We parse the expression
        ast_t expr = parse_expression(p);
        return new_ast((node_t){
            ast_in, {.ast_in = {binding, expr}}});
    }
    return parse_expression_aux(p, -1);
}

ast_t parse_expression_aux(parser_t *p, int min_precedence)
{
    ast_t left = parse_primary(p);
    while (1)
    {
        ast_t node = parse_increasing_precedence(p, left, min_precedence);
        if (node == left)
            break;
        left = node;
    }
    return left;
}

ast_t parse_increasing_precedence(parser_t *p, ast_t left, int min_prec)
{
    token_t next = parser_peek(*p);
    if (!is_type_operator(next.type))
        return left;
    int next_prec = get_precedence(next.type);
    if (next_prec <= min_prec)
        return left;
    (void)parser_consume(p);
    ast_t right = parse_expression_aux(p, next_prec);
    return new_op_ast(left, next.type, right);
}

ast_t parse_type_signature(parser_t *p)
{
    // <identifier> ('->' <identifier>)

    token_array_t chain;
    new_token_array(&chain);
    // Expect an identifier
    token_t t = parser_peek(*p);
    if (t.type != TOK_IDENTIFIER)
    {
        printf("TODO: Expect at least on type name\n");
        exit(1);
    }
    token_array_push(&chain, t);
    (void)parser_consume(p);
    while (parser_peek_type(*p) == TOK_SMALL_ARROW)
    {
        parser_consume(p);
        // Expect an identifier
        t = parser_consume(p);
        if (t.type != TOK_IDENTIFIER)
        {
            printf("TODO: Expect at least on type name\n");
            exit(1);
        }
        token_array_push(&chain, t);
    }
    return new_ast((node_t){
        ast_type, {.ast_type = {.chain = chain}}});
}

ast_t parse_let_binding(parser_t *p)
{
    // Synatx of a let binding:
    // let <primary> : <type specification> => <expression>
    // OR
    // let () => <expression>

    // We expect 'let' keyword
    if (parser_consume(p).type != TOK_LET)
    {
        printf("Unreachable\n");
        exit(1);
    }
    ast_t primary = NULL;
    ast_t type_sig = NULL;

    if (parser_peek_type(*p) == TOK_IDENTIFIER)
    {
        primary = parse_primary(p);

        // We expect a colon ':' here

        if (parser_consume(p).type != TOK_COLON)
        {
            printf("TODO: Syntax Error: Expected type signature\n");
            exit(1);
        }

        type_sig = parse_type_signature(p);
        printf("Here\n");
        fflush(stdout);
    }
    else
    {
        // We must have a let()=>
        // We expect '('
        if (parser_consume(p).type != TOK_OPEN_PAREN)
        {
            printf("Expected Identifier or '()' in let binding\n");
            exit(1);
        }
        if (parser_consume(p).type != TOK_CLOSE_PAREN)
        {
            printf("Unclosed '(' in let binding\n");
            exit(1);
        }
    }

    // We expect a big arrow '=>' here

    token_t t = parser_consume(p);
    if (t.type != TOK_BIG_ARROW)
    {
        printf("TODO: Expect '=>' in let binding\n");
        exit(1);
    }

    ast_t expression = parse_primary(p);

    return new_ast((node_t){
        ast_let_binding, {.ast_let_binding = {.left = primary, .right = expression, .type_sig = type_sig}}});
}

ast_t parse_val(parser_t *p)
{
    // Can be a let binding
    // Can be a primary (literal / function call (or cst))

    // Let's try to parse a let binding (function definition / variable basically)

    token_type_t t = parser_peek_type(*p);
    if (t == TOK_LET)
        return parse_let_binding(p);
    else
        return parse_primary(p);
}

void parse_program(parser_t *p)
{
    while (parser_peek(*p).lexeme != NULL)
        ast_array_push(&p->prog, parse_val(p));
}

parser_t new_parser(token_array_t arr, char *filename)
{
    parser_t res;
    res.filename = filename;
    res.cursor = 0;
    new_ast_array(&res.prog);
    res.tokens = arr;
    return res;
}