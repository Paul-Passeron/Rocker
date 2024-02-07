CC=gcc
CFLAGS=-Werror -Wall -Wextra -pedantic
SRC=src/
BUILD=build/


all: $(BUILD)main
$(BUILD)main: $(BUILD)main.o
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD)main.o: $(SRC)main.c
	$(CC) -c -o $@ $^

