CC=gcc
CFLAGS=-Werror -Wall -Wextra -pedantic
SRC=src/
BUILD=build/

DEP=$(BUILD)main.o $(BUILD)lexer.o $(BUILD)token.o

all: main
main: $(DEP)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD)%.o: $(SRC)%.c 
	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	rm -rf $(BUILD)*