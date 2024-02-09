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
    // printf("Consumming token '%s'\n", res.lexeme);
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
    return t == TOK_OPEN_BRACE || t == TOK_OPEN_PAREN || t == TOK_IDENTIFIER || t == TOK_STR_LIT || t == TOK_CHR_LIT || t == TOK_NUM_LIT || t == TOK_WILDCARD;
}

ast_t parse_leaf(parser_t *p)
{
    token_t t = parser_consume(p);
    if (t.type == TOK_IDENTIFIER)
        return new_ast((node_t){
            ast_identifier, {.ast_identifier = {t}}});
    else if (t.type == TOK_NUM_LIT || t.type == TOK_STR_LIT || t.type == TOK_CHR_LIT)
        return new_ast((node_t){
            ast_literal, {.ast_literal = {t}}});
    printf("Expected leaf\n");
    exit(1);
}

ast_t parse_primary_aux(parser_t *p, int curry)
{
    token_type_t type = parser_peek_type(*p);

    if (type == TOK_IDENTIFIER || type == TOK_STR_LIT || type == TOK_CHR_LIT || type == TOK_NUM_LIT || type == TOK_WILDCARD)
    {

        ast_t tree = parse_leaf(p);
        while (is_primary(*p) && curry)
        {
            ast_t leaf;
            if (parser_peek_type(*p) != TOK_OPEN_PAREN && parser_peek_type(*p) != TOK_OPEN_BRACE)
                leaf = parse_primary_aux(p, 0);
            else
                leaf = parse_expression(p);
            tree = new_ast((node_t){
                ast_curry, {.ast_curry = {.caller = tree, .arg = leaf}}});
        }
        return tree;
    }

    else if (type == TOK_OPEN_PAREN)
    {
        (void)parser_consume(p);

        ast_t res = parse_expression(p);
        type = parser_peek_type(*p);
        if (type != TOK_CLOSE_PAREN)
        {
            printf("%s\n", parser_peek(*p).lexeme);
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
        while (type != TOK_CLOSE_BRACE)
        {
            ast_t r = parse_increasing_precedence(p, res, -1);
            type = parser_peek_type(*p);
            if (r == res)
                break;
            res = r;
        }
        (void)parser_consume(p);
        return res;
    }
    else
    {
        printf("Could not parse as a primary !\n");
        exit(1);
    }
}

ast_t parse_primary(parser_t *p)
{
    return parse_primary_aux(p, 1);
}

ast_t parse_match_case(parser_t *p)
{
    // We expect the first token to be '->'
    if (parser_consume(p).type != TOK_SMALL_ARROW)
    {
        printf("Expected '->' token for match case\n");
        exit(1);
    }
    // We expect an expression
    ast_t match_expr = parse_expression(p);
    // We expect ':'
    if (parser_consume(p).type != TOK_COLON)
    {
        printf("Expected ':' token for match case\n");
        exit(1);
    }
    // We expect the returned expression
    ast_t ret = parse_expression(p);
    return new_ast((node_t){
        ast_match_case, {.ast_match_case = {.expression = ret, .matcher = match_expr}}});
}

ast_t parse_match_expression(parser_t *p)
{
    // The fisrt token must be 'match'
    if (parser_consume(p).type != TOK_MATCH)
    {
        printf("Unreachable !\n");
        exit(1);
    }
    // Then we parse an expression
    ast_t matched = parse_expression(p);
    // Then we expect a =>
    if (parser_consume(p).type != TOK_BIG_ARROW)
    {
        printf("Must put '=>' following match expression\n");
        exit(1);
    }
    // Then a '{'
    if (parser_consume(p).type != TOK_OPEN_BRACE)
    {
        printf("Must put '{'...'}' to enclose match expression cases\n");
        exit(1);
    }
    ast_array_t cases;
    new_ast_array(&cases);
    while (parser_peek_type(*p) == TOK_SMALL_ARROW)
        ast_array_push(&cases, parse_match_case(p));
    // We expect a closing bracket

    if (parser_consume(p).type != TOK_CLOSE_BRACE)
    {
        printf("Unclosed brace in match expression\n");
        exit(1);
    }

    return new_ast((node_t){
        ast_match, {.ast_match = {.cases = cases, .to_match = matched}}});
}

ast_t parse_expression(parser_t *p)
{
    token_type_t a = parser_peek_type(*p);
    if (a == TOK_OPEN_BRACE)
    {
        (void)parser_consume(p);
        ast_t res = parse_expression(p);
        // we expect closing '}'
        while (parser_peek(*p).type != TOK_CLOSE_BRACE)
        {
            ast_t node = parse_increasing_precedence(p, res, -1);
            if (node == res)
                break;
            res = node;
        }
        (void)parser_consume(p);
        return res;
    }
    else if (a == TOK_OPEN_PAREN)
    {
        (void)parser_consume(p);
        ast_t res = parse_expression(p);
        // we expect closing ')'
        while (parser_peek(*p).type != TOK_CLOSE_PAREN)
        {
            ast_t node = parse_increasing_precedence(p, res, -1);
            if (node == res)
                break;
            res = node;
            // printf("TODO: Unclosed parenthesis\n");
            // exit(1);
        }
        (void)parser_consume(p);
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
    else if (a == TOK_MATCH)
    {
        return parse_match_expression(p);
    }
    return parse_expression_aux(p, -1);
}

ast_t parse_expression_aux(parser_t *p, int min_precedence)
{
    printf("Here\n");
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

int is_type_def(parser_t p)
{
    token_type_t t = parser_peek_type(p);
    return t == TOK_REC || t == TOK_PRO;
}

ast_t parse_val(parser_t *p)
{
    // Can be a let binding
    // Can be a primary (literal / function call (or cst))

    // Let's try to parse a let binding (function definition / variable basically)

    token_type_t t = parser_peek_type(*p);
    if (t == TOK_LET)
        return parse_let_binding(p);
    else if (is_primary(*p))
        return parse_primary(p);
    else if (is_type_def(*p))
        return parse_type_def(p);
    else
    {
        printf("%s\n", lexeme_of_type(t));
        printf("Could not parse as val\n");
        exit(1);
    }
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

ast_t parse_type_def(parser_t *p)
{
    // expect 'rec' or 'pro' keyword
    token_t t = parser_peek(*p);
    if (t.type == TOK_REC)
        return parse_rec_type(p);
    else if (t.type != TOK_PRO)
    {
        printf("Expected a valid type specifier, like 'rec' or 'pro'\n");
        exit(1);
    }
    return parse_pro_type(p);
}

ast_t parse_constructor(parser_t *p)
{
    // expect identifier
    token_t constructor_name = parser_consume(p);
    if (constructor_name.type != TOK_IDENTIFIER)
    {
        printf("Expected constructor name in type definition\n");
        exit(1);
    }
    // expect colon
    if (parser_consume(p).type != TOK_COLON)
    {
        printf("Expected ':' after constructor name in type definition\n");
        exit(1);
    }

    // expect type signature

    ast_t type_sig = parse_type_signature(p);

    return new_ast((node_t){
        ast_constructor, {.ast_constructor = {.name = constructor_name, .signature = type_sig}}});
}

ast_t parse_general_type(parser_t *p, int is_rec)
{
    // expect rec token
    // if (parser_consume(p).type != TOK_REC)
    // {
    //     printf("Expected 'rec' keyword in rec type definition\n");
    //     exit(1);
    // }
    (void)parser_consume(p);
    // We expect an identier, it's the name of the type
    token_t type_name = parser_consume(p);

    // We expect a big arrow
    if (parser_consume(p).type != TOK_BIG_ARROW)
    {
        printf("Expected '=>' in type definition");
        exit(1);
    }
    // We expect a '{'
    if (parser_consume(p).type != TOK_OPEN_BRACE)
    {
        printf("Expected '{' in type definition");
        exit(1);
    }
    ast_array_t constructors;
    new_ast_array(&constructors);
    // We expect at least one constructor
    ast_array_push(&constructors, parse_constructor(p));
    while (parser_peek_type(*p) == TOK_COMMA)
    {
        (void)parser_consume(p);
        if (parser_peek_type(*p) == TOK_COMMA)
        {
            (void)parser_consume(p);
            break;
        }
        ast_array_push(&constructors, parse_constructor(p));
    }
    // We expect '}'
    if (parser_consume(p).type != TOK_CLOSE_BRACE)
    {
        printf("Unclosed brace in type definition\n");
        exit(1);
    }
    return new_ast((node_t){
        ast_type_def, {.ast_type_def = {.name = type_name, .is_rec = is_rec, .constructors = constructors}}});
}

ast_t parse_rec_type(parser_t *p)
{
    return parse_general_type(p, 1);
}
ast_t parse_pro_type(parser_t *p)
{
    return parse_general_type(p, 0);
}