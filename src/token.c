#include "token.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static char *lexemes[TOK_COUNT] = {"", "", "", "", "let", ":", ",", "->", "=>", "{",
                                   "}", "(", ")", "in", "if", "then", "else", "rec", "pro", "match", "*", "+",
                                   "/", "%", "||", "&&", "|", "^", "&", "<", "<=", ">", ">=", "=", "!="};

char *lexeme_of_type(token_type_t t)
{
    assert(TOK_COUNT == 35 && "Exhaustive handling of token types in lexeme_of_type");

    switch (t)
    {
    case TOK_IDENTIFIER:
        return "<identifier>";
    case TOK_CHR_LIT:
        return "<char literal>";
    case TOK_STR_LIT:
        return "<string literal>";
    case TOK_NUM_LIT:
        return "<numeric literal>";
    case TOK_LET:
        return "let";
    case TOK_COLON:
        return ":";
    case TOK_COMMA:
        return ",";
    case TOK_SMALL_ARROW:
        return "->";
    case TOK_BIG_ARROW:
        return "=>";
    case TOK_OPEN_BRACE:
        return "{";
    case TOK_CLOSE_BRACE:
        return "}";
    case TOK_OPEN_PAREN:
        return "(";
    case TOK_CLOSE_PAREN:
        return ")";
    case TOK_IN:
        return "in";
    case TOK_IF:
        return "if";
    case TOK_THEN:
        return "then";
    case TOK_ELSE:
        return "else";
    case TOK_REC:
        return "rec";
    case TOK_PRO:
        return "pro";
    case TOK_MATCH:
        return "match";
    case TOK_STAR:
        return "*";
    case TOK_PLUS:
        return "+";
    case TOK_DIV:
        return "/";
    case TOK_MODULO:
        return "%";
    case TOK_LOG_OR:
        return "||";
    case TOK_LOG_AND:
        return "&&";
    case TOK_BIT_OR:
        return "|";
    case TOK_BIT_XOR:
        return "^";
    case TOK_BIT_AND:
        return "&";
    case TOK_LSSR:
        return "<";
    case TOK_LSSR_EQ:
        return "<=";
    case TOK_GRTR:
        return ">";
    case TOK_GRTR_EQ:
        return ">=";
    case TOK_EQUAL:
        return "=";
    case TOK_DIFF:
        return "!=";
    default:
        assert(0 && "Unreachable");
    }
}

token_type_t type_of_lexeme(char *s)
{
    assert(TOK_COUNT == 35 && "Exhaustive handling of token types in type_of_lexeme");
    for (int i = 4; i < TOK_COUNT; i++)
        if (strcmp(lexemes[i], s) == 0)
            return i;
    return TOK_COUNT;
}