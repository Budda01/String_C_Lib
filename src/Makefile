CFLAGS = gcc -Wall -Werror -Wextra -std=c11
L = -lcheck
UNI_F = -lsubunit -lm -lrt -lpthread
SYSTEM_NAME = $(shell uname -s)
GCOV = -fprofile-arcs -ftest-coverage

ifeq ($(SYSTEM_NAME), Darwin)
	OPEN_CMD = open
endif

ifeq ($(SYSTEM_NAME), Linux)
	OPEN_CMD = xdg-open
endif

all: s21_string.a

test: s21_string.a
	checkmk clean_mode=1 check.check > test_s21_string.c
	make style
ifeq ($(SYSTEM_NAME), Darwin)
	$(CFLAGS) test_s21_string.c s21_string.a -o test $(L) -lm
endif
ifeq ($(SYSTEM_NAME), Linux)
	$(CFLAGS) test_s21_string.c s21_string.a -o test $(L) $(UNI_F)
endif
	./test
	make clean

gcov_report: style s21_string.a
	checkmk clean_mode=1 check.check > test_s21_string.c
	make style
ifeq ($(SYSTEM_NAME), Darwin)
	$(CFLAGS) $(GCOV) test_s21_string.c s21*.c s21_string.a -o test $(L)
endif
ifeq ($(SYSTEM_NAME), Linux)
	$(CFLAGS) $(GCOV) test_s21_string.c s21*.c s21_string.a -o test $(L) $(UNI_F)
endif
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_CMD) ./report/index.html

s21_string.a: clean
	$(CFLAGS) -c s21_*.c
	ar rc s21_string.a *.o
	ranlib s21_string.a

style:
	clang-format -style=Google -i *.c *.h

clean:
	rm -rf *.a *.o test *.gcda *.gcno *.info report *.out test_s21_string.c


.PHONY: all clean test s21_string.a gcov_report style
