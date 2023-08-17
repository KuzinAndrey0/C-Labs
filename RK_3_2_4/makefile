PREFIX_SRC = ./src
PREFIX_OBJ = ./out
PREFIX_HEAD = ./inc

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -g

OBJ_NAMES = list_funcs.o
OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(OBJ_NAMES))

HEAD_NAMES = my_defines.h list_funcs.h
HEADERS = $(patsubst %,$(PREFIX_HEAD)/%,$(OBJ_HEAD))


app.exe: $(OBJS) ./out/main.o
	$(CC) -o app.exe $(OBJS) ./out/main.o

$(PREFIX_OBJ)/%.o: $(PREFIX_SRC)/%.c $(HEADERS)
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

./out/main.o: ./src/main.c
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $(PREFIX_SRC)/main.c -o $(PREFIX_OBJ)/main.o

.PHONY: clean

clean:
	rm -f *.exe
	rm -rf ./out
