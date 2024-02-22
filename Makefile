CC=clang
CFLAGS=-Werror -Wall -Wextra -g -pedantic
SRC=src/
BUILD=build/

DEP=$(BUILD)main.o $(BUILD)lexer.o $(BUILD)token.o $(BUILD)alloc.o $(BUILD)ast.o $(BUILD)parser.o $(BUILD)generator.o $(BUILD)typechecker.o $(BUILD)name_table.o

all: clean main lines
main: $(DEP)
	$(CC) $(CFLAGS) -o $@ $^
$(BUILD)%.o: RockerAllocator/%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c

$(BUILD)%.o: $(SRC)%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	rm -rf $(BUILD)*
	rm -rf main

lines:
	wc -l $$( find -name '*.[hc]' -o -name '*.rkr' -o -name '*.bnf') | tail -n 1