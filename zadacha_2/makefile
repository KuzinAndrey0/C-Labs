PREFIX_SRC = ./src
PREFIX_OBJ = ./out
PREFIX_HEAD = ./inc
PREFIX_LIBS = ./libs

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -g3

OBJ_NAMES =
OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(OBJ_NAMES))

HEAD_NAMES = my_defines.h
HEADERS = $(patsubst %,$(PREFIX_HEAD)/%,$(HEAD_NAMES))

STAT_NAMES = arr_lib_stat.a
STATS = $(patsubst %,$(PREFIX_LIBS)/%,$(STAT_NAMES))

CHECK_OBJ_NAMES = check_cmpfunc.o check_key.o check_mysort.o
CHECK_OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(CHECK_OBJ_NAMES))

DYN_NAMES = arr_lib_dyn_1.so arr_lib_dyn_2.so
DYNS = $(patsubst %,$(PREFIX_LIBS)/%,$(DYN_NAMES))

app.exe: $(OBJS) ./out/main.o
	mkdir -p $(PREFIX_OBJ)
	$(CC) -o app.exe $(OBJS) ./out/main.o


unit_tests.exe: $(OBJS) $(CHECK_OBJS) ./out/unit_tests.o $(STATS) $(DYNS)
	$(CC) -o $@ $(OBJS) $(CHECK_OBJS) ./out/unit_tests.o $(STATS) $(DYNS) -lcheck -lpthread -lrt -lm -ldl

$(PREFIX_OBJ)/check_%.o: ./unit_tests/check_%.c $(HEADERS)
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(PREFIX_OBJ)/%.o: $(PREFIX_SRC)/%.c $(HEADERS)
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


$(PREFIX_LIBS)/arr_lib_dyn_1.so: $(PREFIX_SRC)/arr_lib_dyn_1.c $(HEADERS)
	$(CC) $(CFLAGS) -fPIC -c $(PREFIX_SRC)/arr_lib_dyn_1.c -o $(PREFIX_OBJ)/arr_lib_dyn_1.o
	$(CC) -o $(PREFIX_LIBS)/arr_lib_dyn_1.so -shared $(PREFIX_OBJ)/arr_lib_dyn_1.o

$(PREFIX_LIBS)/arr_lib_dyn_2.so: $(PREFIX_SRC)/arr_lib_dyn_2.c $(HEADERS)
	$(CC) $(CFLAGS) -fPIC -c $(PREFIX_SRC)/arr_lib_dyn_2.c -o $(PREFIX_OBJ)/arr_lib_dyn_2.o
	$(CC) -o $(PREFIX_LIBS)/arr_lib_dyn_2.so -shared $(PREFIX_OBJ)/arr_lib_dyn_2.o	

$(PREFIX_LIBS)/arr_lib_stat.a: $(PREFIX_SRC)/arr_lib_stat.c $(HEADERS)
	mkdir -p $(PREFIX_LIBS)
	mkdir -p $(PREFIX_OBJ)
	gcc -std=c99 -Wall -Werror -c $(PREFIX_SRC)/arr_lib_stat.c -o $(PREFIX_OBJ)/arr_lib_stat.o
	ar rc $(PREFIX_LIBS)/arr_lib_stat.a $(PREFIX_OBJ)/arr_lib_stat.o
	ranlib $(PREFIX_LIBS)/arr_lib_stat.a


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