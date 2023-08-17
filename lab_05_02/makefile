PREFIX_SRC = ./src
PREFIX_OBJ = ./out
PREFIX_HEAD = ./inc

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra
LFLAGS = 
ifeq ($(mode), debug)
	CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -g -fprofile-arcs -ftest-coverage
	LFLAGS = -fprofile-arcs -ftest-coverage
endif

OBJ_NAMES = dynamic_data.o queue_funcs.o #file_funcs.o matrix_funcs.o matrix_math.o
OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(OBJ_NAMES))

HEAD_NAMES = dynamic_data.h my_defines.h queue_funcs.h
HEADERS = $(patsubst %,$(PREFIX_HEAD)/%,$(OBJ_HEAD))

CHECK_OBJ_NAMES = #check_pop_front.o check_insert.o check_sort.o #check_matrix_addition.o check_matrix_multiplication.o check_calc_determinant.o
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
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $(PREFIX_SRC)/main.c -o $(PREFIX_OBJ)/main.o

./out/unit_tests.o: ./unit_tests/unit_tests.c ./inc/unit_tests.h
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c ./unit_tests/unit_tests.c -o $(PREFIX_OBJ)/unit_tests.o

.PHONY: clean

clean:
	rm -f *.exe
	rm -rf ./out
