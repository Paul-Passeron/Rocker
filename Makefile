CC=gcc
CFLAGS= -Wall -Wextra -g
SRC=src/
BUILD=build/

DEP=$(BUILD)main.o $(BUILD)lexer.o $(BUILD)token.o $(BUILD)ast.o $(BUILD)parser.o $(BUILD)generator.o $(BUILD)name_table.o $(BUILD)compiler.o

all: clean main lines
main: $(DEP)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD)%.o: $(SRC)%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	rm -rf $(BUILD)*
	rm -rf main

lines:
	wc -l $$( find -name '*.[hc]' -o -name '*.rkr' -o -name '*.bnf') | tail -n 1