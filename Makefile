CC=gcc
CFLAGS=-Werror -Wall -Wextra -g
SRC=src/
BUILD=src/

DEP=$(BUILD)main.c $(BUILD)lexer.c $(BUILD)token.c $(BUILD)ast.c $(BUILD)parser.c $(BUILD)generator.c $(BUILD)name_table.c $(BUILD)compiler.c
# DEP=$(BUILD)main.o $(BUILD)lexer.o $(BUILD)token.o $(BUILD)ast.o $(BUILD)parser.o $(BUILD)generator.o $(BUILD)name_table.o $(BUILD)compiler.o

all: clean main lines
main: 
	$(CC) $(CFLAGS) -o $@ $^ $(DEP)

# $(BUILD)%.o: $(SRC)%.c 
# 	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	rm -rf main

lines:
	wc -l $$( find -name '*.[hc]' -o -name '*.rkr' -o -name '*.bnf') | tail -n 1