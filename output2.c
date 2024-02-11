#include <stdio.h>
typedef struct {
  char *s;
  int length;
} string;
void print(string s) {
  for (int i = 0; i < s.length; i++)
    putchar(s.s[i]);
}

typedef struct token_type_t token_type_t;
typedef struct token_type_t {
  enum tag_token_type_t {
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
    TOK_IN,
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_REC,
    TOK_PRO,
    TOK_MATCH,
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
  } tag_token_type_t;
  union data_token_type_t {
    int __typedef__;
  } data_token_type_t;
} token_type_t;

typedef struct token_t token_t;
typedef struct token_t {
  token_type_t type;
  string lexeme;
  int col;
  int line;
} token_t;

string lexeme_of_type(token_type_t t) {
  token_type_t _tmp_match1 = t;
  if (_tmp_match1.tag_token_type_t == TOK_IDENTIFIER) {
    return (string){.s = "<identifier>", .length = 12};
  } else if (_tmp_match1.tag_token_type_t == TOK_CHR_LIT) {
    return (string){.s = "<char literal>", .length = 14};
  } else if (_tmp_match1.tag_token_type_t == TOK_STR_LIT) {
    return (string){.s = "<string literal>", .length = 16};
  } else if (_tmp_match1.tag_token_type_t == TOK_NUM_LIT) {
    return (string){.s = "<numeric literal>", .length = 17};
  } else if (_tmp_match1.tag_token_type_t == TOK_LET) {
    return (string){.s = "let", .length = 3};
  } else if (_tmp_match1.tag_token_type_t == TOK_COLON) {
    return (string){.s = ":", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_COMMA) {
    return (string){.s = ",", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_SMALL_ARROW) {
    return (string){.s = "->", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_BIG_ARROW) {
    return (string){.s = "=>", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_OPEN_BRACE) {
    return (string){.s = "{", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_CLOSE_BRACE) {
    return (string){.s = "}", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_OPEN_PAREN) {
    return (string){.s = "(", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_CLOSE_PAREN) {
    return (string){.s = ")", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_IN) {
    return (string){.s = "in", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_IF) {
    return (string){.s = "if", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_THEN) {
    return (string){.s = "then", .length = 4};
  } else if (_tmp_match1.tag_token_type_t == TOK_ELSE) {
    return (string){.s = "else", .length = 4};
  } else if (_tmp_match1.tag_token_type_t == TOK_REC) {
    return (string){.s = "rec", .length = 3};
  } else if (_tmp_match1.tag_token_type_t == TOK_PRO) {
    return (string){.s = "pro", .length = 3};
  } else if (_tmp_match1.tag_token_type_t == TOK_MATCH) {
    return (string){.s = "match", .length = 5};
  } else if (_tmp_match1.tag_token_type_t == TOK_STAR) {
    return (string){.s = "*", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_MINUS) {
    return (string){.s = "-", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_PLUS) {
    return (string){.s = "+", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_DIV) {
    return (string){.s = "/", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_MODULO) {
    return (string){.s = "%", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_LOG_OR) {
    return (string){.s = "||", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_LOG_AND) {
    return (string){.s = "&&", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_BIT_OR) {
    return (string){.s = "|", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_BIT_XOR) {
    return (string){.s = "^", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_BIT_AND) {
    return (string){.s = "&", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_LSSR) {
    return (string){.s = "<", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_LSSR_EQ) {
    return (string){.s = "<=", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_GRTR) {
    return (string){.s = ">", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_GRTR_EQ) {
    return (string){.s = ">=", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_EQUAL) {
    return (string){.s = "=", .length = 1};
  } else if (_tmp_match1.tag_token_type_t == TOK_DIFF) {
    return (string){.s = "!=", .length = 2};
  } else if (_tmp_match1.tag_token_type_t == TOK_WILDCARD) {
    return (string){.s = "_", .length = 1};
  }
}
int main(void) {}
