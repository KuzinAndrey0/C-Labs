PREFIX_SRC = ./src
PREFIX_OBJ = ./out
PREFIX_HEAD = ./inc

.PHONY: clean

clean:
	rm -f *.exe
	rm -rf ./out

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -g3

OBJ_NAMES = file_funcs.o matrix_funcs.o
OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(OBJ_NAMES))

HEAD_NAMES = my_defines.h file_funcs.h matrix_funcs.h
HEADERS = $(patsubst %,$(PREFIX_HEAD)/%,$(OBJ_HEAD))


app.exe: $(OBJS) ./out/main.o
	$(CC) -o app.exe $(OBJS) ./out/main.o


$(PREFIX_OBJ)/%.o: $(PREFIX_SRC)/%.c $(HEADERS)
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

./out/main.o: ./src/main.c
	$(CC) $(CFLAGS) -c $(PREFIX_SRC)/main.c -o $(PREFIX_OBJ)/main.o

./out/unit_tests.o: ./unit_tests/unit_tests.c ./inc/unit_tests.h
	$(CC) $(CFLAGS) -c ./unit_tests/unit_tests.c -o $(PREFIX_OBJ)/unit_tests.o
