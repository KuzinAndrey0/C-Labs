PREFIX_SRC = ./src
PREFIX_OBJ = ./out
PREFIX_HEAD = ./inc
PREFIX_LIBS = ./libs

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra

OBJ_NAMES =
OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(OBJ_NAMES))

HEAD_NAMES = 
HEADERS = $(patsubst %,$(PREFIX_HEAD)/%,$(HEAD_NAMES))

CHECK_OBJ_NAMES = check_cmpfunc.o check_key.o check_mysort.o
CHECK_OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(CHECK_OBJ_NAMES))



app.exe: $(OBJS) ./out/main.o
	mkdir -p $(PREFIX_OBJ)
	$(CC) -o app.exe $(OBJS) ./out/main.o


unit_tests.exe: $(OBJS) $(CHECK_OBJS) ./out/unit_tests.o $(STATS) $(DYNS)
	$(CC) -o $@ $(OBJS) $(CHECK_OBJS) ./out/unit_tests.o $(STATS) $(DYNS) -lcheck -lpthread -lrt -lm -ldl
#	$(CC) -o $@ $(OBJS) $(CHECK_OBJS) ./out/unit_tests.o -lcheck -lpthread -lrt -lm -lsubunit
# gcc -std=c99 -Wall -Werror main.c -L. -larr -o test.exe


my_module.so: $(PREFIX_SRC)/my_module.c $(HEADERS)
	$(CC) $(CFLAGS) -fPIC -c $(PREFIX_SRC)/my_module.c -o $(PREFIX_OBJ)/my_module.o
	$(CC) -o $(PREFIX_LIBS)/my_module.so -shared $(PREFIX_OBJ)/my_module.o	



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