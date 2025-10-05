CC = gcc
CCFLAGS = -c -Wall -Werror -Wextra -std=c11
#CFLAGS=$(shell pkg-config --cflags check)
CFLAGS=-I/usr/include
#LIBS = $(shell pkg-config --libs check)
LIBS = -lcheck -lm -lsubunit
SOURCE = $(wildcard CORE/s21_*.c)
OBJECTS = $(SOURCE: CORE/%.c=OBJ/%.o)
OBJECT = TESTS/asd.o s21_string.a

all: s21_string.a

s21_string.a: $(OBJECTS)
	ar rc s21_string.a $^
	ranlib s21_string.a

OBJ/%.o: CORE/%.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $< -o $@

test: TESTS/asd.o s21_string.check
	$(CC) -o test $^ $(LIBS)
	./test

s21_string.check: $(SOURCE)
	$(CC) $(CCFLAGS) $(CFLAGS) $(SOURCE) 
	ar rc s21_string.check s21_*.o
	ranlib s21_string.check

TESTS/asd.o: TESTS/asd.c
	$(CC) $(CFLAGS) -c $^ -o $@

TESTS/asd.c:
	checkmk clean_mode=1 TESTS/asd.check > $@

gcov_report: TESTS/asd.c $(SOURCE)
	$(CC) --coverage $(SOURCE) $< -o s21_test $(CFLAGS) $(LIBS)
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

rebuild: clean all 

clang:
ifeq ("","$(wildcard ./clang-format)") 
	cp ../materials/linters/.clang-format .clang-format
endif
	clang-format -n CORE/*.c *.h
	-rm -rf .clang-format

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf s21_test
	-rm -rf s21_string.check
	-rm -rf TESTS/*.o TESTS/asd.c