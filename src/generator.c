#include "generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int tmp_match_counter = 0;

FILE *f;

generator_t new_generator(parser_t p, char *filename)
{
    generator_t res;
    res.out = fopen(filename, "wb");
    if (res.out == NULL)
    {
        printf("Could not open file '%s'\n", filename);
        fflush(stdout);
    }
    f = res.out;
    res.program = p.prog;
    return res;
}

void kill_generator(generator_t g)
{
    fclose(g.out);
    kill_ast_array(g.program);
}
#ifdef GENERATOR_ASM

void generate_plus(void)
{
    // rax <- rax + rbx
    fprintf(f, "add rax, rbx\n");
}

void generate_minus(void)
{
    // rax <- rbx - rax
    fprintf(f, "sub rbx, rax\n");
    fprintf(f, "mov rax, rbx\n");
}

void generate_times(void)
{
    // rax <- rax + rbx
    fprintf(f, "mul rax, rbx\n");
}

void generate_div(void)
{
    fprintf(f, "mov rcx, rax\n");
    fprintf(f, "mov rax, rbx\n");
    fprintf(f, "mov rbx, rcx\n");
    fprintf(f, "cdq\n");
    fprintf(f, "mov rdx, 0\n");
    fprintf(f, "div rbx\n");
}

void generate_mod(void)
{
    fprintf(f, "mov rdx, 0\n");
    fprintf(f, "mov rcx, rax\n");
    fprintf(f, "mov rax, rbx\n");
    fprintf(f, "mov rbx, rcx\n");
    fprintf(f, "cdq\n");
    fprintf(f, "div rbx\n");
    fprintf(f, "mov rax, rdx\n");
}

void generate_rax_size(int n_bytes)
{
    switch (n_bytes)
    {
    case 1:
        fprintf(f, "byte al");
        break;
    case 2:
        fprintf(f, "word ax");
        break;
    case 4:
        fprintf(f, "dword eax");
        break;
    case 8:
        fprintf(f, "rax");
        break;
    default:
        printf("Rax size '%d' not supported\n", n_bytes);
        exit(1);
    }
}

#else

void generate_plus(void)
{
    fprintf(f, "+");
}

void generate_minus(void)
{
    fprintf(f, "-");
}

void generate_mult(void)
{
    fprintf(f, "*");
}

void generate_div(void)
{
    fprintf(f, "/");
}

void generate_mod(void)
{
    fprintf(f, "%c", '%');
}

void generate_grtr(void)
{
    fprintf(f, ">");
}

void generate_grtr_eq(void)
{
    fprintf(f, ">=");
}
void generate_lssr(void)
{
    fprintf(f, "<");
}
void generate_lssr_eq(void)
{
    fprintf(f, "<=");
}

void generate_function_sig(char *name, ast_t signature, token_array_t args)
{
    token_array_t types = signature->data.ast_type.chain;
    char *return_type = types.data[types.length - 1].lexeme;
    fprintf(f, "%s %s(", return_type, name);
    if (types.length == 1)
    {
        fprintf(f, "void)\n");
        return;
    }

    for (int i = 0; i < types.length - 1; i++)
    {
        char *s = types.data[i].lexeme;

        fprintf(f, "%s", s);
        if (strcmp(s, "void") != 0)
            fprintf(f, " %s", args.data[i].lexeme);
        // fprintf(f, " __arg%d ", i);
        if (i != types.length - 2)
        {
            fprintf(f, ", ");
        }
    }
    fprintf(f, ")");
}

void generate_semicolon(void)
{
    fprintf(f, ";\n");
}

void generate_rec_type(ast_t type_def)
{
    struct ast_type_def data = type_def->data.ast_type_def;
    fprintf(f, "typedef struct %s %s;\n", data.name.lexeme, data.name.lexeme);
    fprintf(f, "typedef struct %s {\n", data.name.lexeme);
    // Only support single types ie 'a as opposed to 'a -> 'b

    for (int i = 0; i < data.constructors.length; i++)
    {
        char *name = data.constructors.data[i]->data.ast_constructor.name.lexeme;
        char *type_name = data.constructors.data[i]->data.ast_constructor.signature->data.ast_type.chain.data[0].lexeme;
        fprintf(f, "    %s %s;\n", type_name, name);
    }
    fprintf(f, "} %s;\n\n", data.name.lexeme);
}

void generate_function_pointer_type(ast_t signature, char *name)
{
    struct ast_type data = signature->data.ast_type;
    char *ret_type = data.chain.data[data.chain.length - 1].lexeme;
    fprintf(f, "%s (*%s)(", ret_type, name);
    for (int i = 0; i < data.chain.length - 1; i++)
    {
        char *type_name = data.chain.data[i].lexeme;
        fprintf(f, "%s", type_name);
        if (i != data.chain.length - 2)
            fprintf(f, ", ");
    }
    fprintf(f, ");\n");
}

void generate_function_pointer_decl(ast_t signature, char *name)
{
    struct ast_type data = signature->data.ast_type;
    char *ret_type = data.chain.data[data.chain.length - 1].lexeme;
    fprintf(f, "%s (*%s(", ret_type, name);
    for (int i = 0; i < data.chain.length - 1; i++)
    {
        char *type_name = data.chain.data[i].lexeme;
        fprintf(f, "%s", type_name);
        if (i != data.chain.length - 2)
            fprintf(f, ", ");
    }
    fprintf(f, "));\n");
}

void generate_pro_type(ast_t type_def)
{
    struct ast_type_def data = type_def->data.ast_type_def;
    // token_array_t type_sig = data.constructors.data[i]->data.ast_constructor.signature;
    char *name = data.name.lexeme;
    fprintf(f, "typedef struct %s %s;\n", data.name.lexeme, data.name.lexeme);
    fprintf(f, "typedef struct %s {\n", data.name.lexeme);
    fprintf(f, "   enum tag_%s\n    {\n", name);
    for (int i = 0; i < data.constructors.length; i++)
    {
        struct ast_constructor constructor = data.constructors.data[i]->data.ast_constructor;
        // We only need the name
        char *type_name = constructor.name.lexeme;
        fprintf(f, "         %s,\n", type_name);
    }
    fprintf(f, "    } tag_%s;\n", name);
    fprintf(f, "    union data_%s\n    {\n", name);
    fprintf(f, "         int __typedef__;\n");
    for (int i = 0; i < data.constructors.length; i++)
    {
        struct ast_constructor constructor = data.constructors.data[i]->data.ast_constructor;
        char *type_name = constructor.signature->data.ast_type.chain.data[0].lexeme;
        char *constructor_name = constructor.name.lexeme;

        if (constructor.signature->data.ast_type.chain.length == 1)
        {
            if (strcmp(type_name, "void") != 0)
                fprintf(f, "       %s %s;\n", type_name, constructor_name);
        }
        else
        {
            fprintf(f, "         ");
            generate_function_pointer_type(data.constructors.data[i]->data.ast_constructor.signature, constructor_name);
        }
        // else we don't need to do anything
    }
    fprintf(f, "    } data_%s;\n", name);
    fprintf(f, "} %s;\n\n", name);
}

void generate_prolog(void)
{
    fprintf(f, "#include <stdio.h>\n");
    fprintf(f, "typedef struct\n");
    fprintf(f, "{\n");
    fprintf(f, "    char *s;\n");
    fprintf(f, "    int length;\n");
    fprintf(f, "} string;\n");
    fprintf(f, "void print(string s)\n");
    fprintf(f, "{\n");
    fprintf(f, "    for (int i = 0; i < s.length; i++)\n");
    fprintf(f, "        putchar(s.s[i]);\n");
    fprintf(f, "}\n");
    fprintf(f, "\n");
}

void generate_string_literal(char *lit)
{
    fprintf(f, "(string) {.s = %s, .length = %ld}", lit, strlen(lit) - 2);
}

void generate_in(ast_t in)
{
    struct ast_in a = in->data.ast_in;
    ast_t first = a.first;
    ast_t second = a.second;
    if (second == NULL)
    {
        fprintf(f, "return ");
        generate_expression(first);
        fprintf(f, ";\n");
    }

    else if (second->tag == ast_identifier || second->tag == ast_literal || second->tag == ast_curry)
    {
        generate_expression(first);
        fprintf(f, "return ");
        generate_expression(second);
        fprintf(f, ";\n");
    }
    else
    {
        generate_expression(first);
        // fprintf(f, "return ");
        generate_expression(second);
    }
}

void generate_curry(ast_t curr)
{
    struct ast_curry curry = curr->data.ast_curry;
    if (curry.arg == NULL)
    {
        generate_expression(curry.caller);
        return;
    }
    if (curry.caller->tag == ast_identifier)
    {
        fprintf(f, "%s", curry.caller->data.ast_identifier.id.lexeme);
        if (curry.arg != NULL)
        {
            fprintf(f, "(");
            generate_expression(curry.arg);
            fprintf(f, ")");
        }
    }
}

void generate_expression(ast_t expr)
{
    if (expr->tag == ast_literal)
    {
        token_t t = expr->data.ast_literal.literal;
        if (t.type == TOK_STR_LIT)
        {
            generate_string_literal(t.lexeme);
            // generate_semicolon();
        }
        else if (t.type != TOK_WILDCARD)

            fprintf(f, "%s", t.lexeme);
    }

    else if (expr->tag == ast_let_binding)
    {
        generate_let_binding(expr);
    }
    else if (expr->tag == ast_in)
    {
        generate_in(expr);
    }
    else if (expr->tag == ast_curry)
    {
        // assert(0 && "TODO: Curry support");
        generate_curry(expr);
    }
    else if (expr->tag == ast_identifier)
    {
        fprintf(f, "%s", expr->data.ast_identifier.id.lexeme);
    }
    else if (expr->tag == ast_match)
    {
        // very very temporary
        token_array_t chain;
        new_token_array(&chain);
        token_t t = {.col = -1, .line = -1, .lexeme = "int", .type = TOK_IDENTIFIER};
        token_array_push(&chain, t);
        ast_t type = new_ast((node_t){
            ast_type, {.ast_type = {.chain = chain}}});
        generate_match(expr, type);
    }
}

void generate_match_aux(ast_t match, ast_t type)
{
    struct ast_match data = match->data.ast_match;
    // Expect expression to match of type type is defined in
    // _tmp_match_i where i is the value within tmp_match_counter
    char var_name[15];
    sprintf(var_name, "_tmp_match%d", tmp_match_counter);
    printf("Here\n");
    // For the moment only trying to match enum tags
    char *type_name = type->data.ast_type.chain.data[0].lexeme;
    if (strcmp(type_name, "int") == 0)
    {
        for (int i = 0; i < data.cases.length; i++)
        {
            fprintf(f, "%s if (%s == ", i > 0 ? "else" : "", var_name);
            ast_t matcher = data.cases.data[i]->data.ast_match_case.matcher;
            ast_t expr = data.cases.data[i]->data.ast_match_case.expression;
            generate_expression(matcher);
            fprintf(f, ")\n{");
            fprintf(f, "return ");
            generate_expression(expr);
            fprintf(f, "}\n");
        }
    }
    else
    {
        for (int i = 0; i < data.cases.length; i++)
        {

            fprintf(f, "%s if (%s.tag_%s == ", i > 0 ? "else" : "", var_name, type_name);
            struct ast_match_case matcher = data.cases.data[i]->data.ast_match_case;
            if (matcher.matcher->tag == ast_identifier)
            {
                fprintf(f, "%s", matcher.matcher->data.ast_identifier.id.lexeme);
            }
            fprintf(f, ")\n{");

            // Temporary
            fprintf(f, "return ");

            generate_expression(matcher.expression);
            fprintf(f, ";\n");
            fprintf(f, "}\n");
        }
    }
}

void generate_match(ast_t match_ast, ast_t type)
{
    struct ast_match match = match_ast->data.ast_match;
    tmp_match_counter++;
    // match.to_match
    fprintf(f, "    %s _tmp_match%d = ", type->data.ast_type.chain.data[0].lexeme, tmp_match_counter);
    generate_expression(match.to_match);
    fprintf(f, ";\n");

    generate_match_aux(match_ast, type);
}

void generate_let_binding(ast_t bind)
{

    struct ast_let_binding binding = bind->data.ast_let_binding;
    if (!binding.is_void)
    {
        // Check if it is a function or a variable
        if (binding.type_sig->data.ast_type.chain.length > 1)
        {
            generate_function_sig(binding.name.lexeme, binding.type_sig, binding.args);
            fprintf(f, "{\n");
            generate_expression(binding.right);
            fprintf(f, "\n}\n");
        }
        else
        {
            fprintf(f, "%s %s=", binding.type_sig->data.ast_type.chain.data[0].lexeme, binding.name.lexeme);
            generate_expression(binding.right);
            generate_semicolon();
        }
    }
    else
    {
        generate_expression(binding.right);
        generate_semicolon();
    }
}

#endif