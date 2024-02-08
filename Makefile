CC=gcc
CFLAGS=-Werror -Wall -Wextra -pedantic
SRC=src/
BUILD=build/

DEP=$(BUILD)main.o $(BUILD)lexer.o $(BUILD)token.o $(BUILD)ast.o

all: clean main lines
main: $(DEP)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD)%.o: $(SRC)%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	rm -rf $(BUILD)*

lines:
	wc -l $$( find -name '*.[hc]' -o -name '*.rkr' -o -name '*.bnf') | tail -n 1