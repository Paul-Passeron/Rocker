CC=gcc
CFLAGS=-Werror -Wall -Wextra -g -pedantic
SRC=src/
# BUILD=build/

# DEP=$(BUILD)bootstrap.o $(BUILD)lexer.o $(BUILD)token.o $(BUILD)alloc.o $(BUILD)ast.o $(BUILD)parser.o $(BUILD)generator.o $(BUILD)name_table.o $(BUILD)stringview.o

all:  clean_rocker lines rocker


create_build:
	mkdir build
# bootstrap: $(DEP)
# 	$(CC) $(CFLAGS) -o $@ $^
# $(BUILD)%.o: RockerAllocator/%.c 
# 	$(CC) $(CFLAGS) -o $@ $^ -c

# $(BUILD)%.o: $(SRC)%.c 
# 	$(CC) $(CFLAGS) -o $@ $^ -c
# $(BUILD)bootstrap.o: $(SRC)main.c
# 	$(CC) $(CFLAGS) -o $@ $^ -c

rocker:
	./bootstrapper/bootstrap RockerSRC/main.rkr $@
	./rocker RockerSRC/main.rkr tmp_rocker
	mv tmp_rocker rocker
clean:
	rm -rf $(BUILD)*
	rm -rf rocker

clean_rocker:
	@rm -rf rocker

lines:
	@echo "C:"
	@wc -l $$( find -wholename './src/*.[hc]' -not -path "./src/generation" ) | tail -n 1
	@echo "Rocker:"
	@wc -l $$( find  -wholename './RockerSRC/*.rkr') | tail -n 1
	@echo "C dependencies:"
	@wc -l $$( find -wholename './RockerAllocator/*.[hc]' -o  -wholename './src/generation/*.[hc]'  ) | tail -n 1
	@echo "Total:"
	@wc -l $$( find -wholename './src/*.[hc]' -o  -wholename './RockerSRC/*.rkr' -o -wholename './RockerAllocator/*.[hc]') | tail -n 1