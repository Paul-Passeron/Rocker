CC=gcc
CFLAGS=-Werror -Wall -Wextra -g -pedantic
SRC=src/
BUILD=build/

DEP=$(BUILD)main.o $(BUILD)lexer.o $(BUILD)token.o $(BUILD)alloc.o $(BUILD)ast.o $(BUILD)parser.o $(BUILD)generator.o $(BUILD)name_table.o

all: rocker lines
rocker: $(DEP)
	$(CC) $(CFLAGS) -o $@ $^
$(BUILD)%.o: RockerAllocator/%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c

$(BUILD)%.o: $(SRC)%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	rm -rf $(BUILD)*
	rm -rf rocker

lines:
	wc -l $$( find -name '*.[hc]' -o -name '*.rkr' ) | tail -n 1