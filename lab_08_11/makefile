PREFIX_SRC = ./src
PREFIX_OBJ = ./out
PREFIX_HEAD = ./inc

.PHONY: clean

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -g3
LFLAGS = 
ifeq ($(mode), debug)
	CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -g -fprofile-arcs -ftest-coverage
	LFLAGS = -fprofile-arcs -ftest-coverage
endif

OBJ_NAMES = dynamic_data.o graph_funcs.o
OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(OBJ_NAMES))

HEAD_NAMES = my_defines.h dynamic_data.h graph_funcs.h
HEADERS = $(patsubst %,$(PREFIX_HEAD)/%,$(OBJ_HEAD))

CHECK_OBJ_NAMES =
CHECK_OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(CHECK_OBJ_NAMES))


app.exe: $(OBJS) ./out/main.o
	$(CC) $(LFLAGS) -o app.exe $(OBJS) ./out/main.o


unit_tests.exe: $(OBJS) $(CHECK_OBJS) ./out/unit_tests.o
	$(CC) -o $@ $(OBJS) $(CHECK_OBJS) ./out/unit_tests.o -lcheck -lpthread -lrt -lm
#	$(CC) -o $@ $(OBJS) $(CHECK_OBJS) ./out/unit_tests.o -lcheck -lpthread -lrt -lm -lsubunit


$(PREFIX_OBJ)/check_%.o: ./unit_tests/check_%.c $(HEADERS)
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(PREFIX_OBJ)/%.o: $(PREFIX_SRC)/%.c $(HEADERS)
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

./out/main.o: ./src/main.c
	$(CC) $(CFLAGS) -c $(PREFIX_SRC)/main.c -o $(PREFIX_OBJ)/main.o

./out/unit_tests.o: ./unit_tests/unit_tests.c ./inc/unit_tests.h
	$(CC) $(CFLAGS) -c ./unit_tests/unit_tests.c -o $(PREFIX_OBJ)/unit_tests.o

clean:
	rm -f *.exe
	rm -rf ./out