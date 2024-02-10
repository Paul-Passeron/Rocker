#include "generator.h"

#include <stdio.h>

generator_t new_generator(parser_t p, char *filename)
{
    generator_t res;
    res.out = fopen(filename, "rb");
    res.program = p.prog;
    return res;
}

void kill_generator(generator_t g)
{
    fclose(g.out);
    kill_ast_array(g.program);
}