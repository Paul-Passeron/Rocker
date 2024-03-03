CC=gcc
CFLAGS=-Werror -Wall -Wextra -g -pedantic
SRC=src/
BUILD=build/

DEP=$(BUILD)bootstrap.o $(BUILD)lexer.o $(BUILD)token.o $(BUILD)alloc.o $(BUILD)ast.o $(BUILD)parser.o $(BUILD)generator.o $(BUILD)name_table.o $(BUILD)stringview.o

all:  clean_rocker lines bootstrap rocker


create_build:
	mkdir build
bootstrap: $(DEP)
	$(CC) $(CFLAGS) -o $@ $^
$(BUILD)%.o: RockerAllocator/%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c

$(BUILD)%.o: $(SRC)%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c
$(BUILD)bootstrap.o: $(SRC)main.c
	$(CC) $(CFLAGS) -o $@ $^ -c

rocker:
	./bootstrap RockerSRC/main.rkr $@
	./rocker RockerSRC/main.rkr tmp_rocker
	mv tmp_rocker rocker
clean:
	rm -rf $(BUILD)*
	rm -rf rocker
clean_rocker:
	rm -rf rocker

lines:
	@echo "C:"
	@wc -l $$( find -name '*.[hc]'  ) | tail -n 1
	@echo "Rocker:"
	@wc -l $$( find  -name '*.rkr' ) | tail -n 1
	@echo "Total:"
	@wc -l $$( find -name '*.[hc]' -o -name '*.rkr' ) | tail -n 1