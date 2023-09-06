#!/bin/bash
FLAGS=-Wall -Wextra -Werror
CC=gcc
FUNC_FILES_C=*.c
FUNC_FILES_O=*.o
CHECKFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LIBNAME=s21_math.a
GLFLAGS=--coverage

all: s21_math.a

build_object_files:
	$(CC) $(FLAGS) $(GCOVFLAGS) $(GLFLAGS) -c $(FUNC_FILES_C)

build_library:
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

s21_math.a:
	$(CC) $(FLAGS) -c $(FUNC_FILES_C)
	make build_library
	rm -rf *.o

test: s21_math.a
	$(CC) $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) s21_math_test.c -L. s21_math.a  -o s21_test
	make start_tests

start_tests:
	./s21_test

gcov_report: clean build_object_files build_library test
	lcov -o tests.info -c -d .
	genhtml -o report tests.info
	open report/index.html


style:
	clang-format -n -style=google *.c *.h

clean:
	rm -rf *.a *.o *.info *.gcda *.gcno s21_test report

rebuild:
	make clean
	make