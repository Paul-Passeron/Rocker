#include "generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void generate_function_sig(char *name, ast_t signature)
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
            fprintf(f, " __arg%d ", i);
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

#endif