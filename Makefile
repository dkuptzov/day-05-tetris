CC := gcc
#CFLAGS1=-Wall -Wextra -Werror -std=c11
CFLAGS=-Wall -Wextra -Werror -std=c11 -I/opt/homebrew/Cellar/check/0.15.2/include/ -D_THREAD_SAFE
LDFLAGS=-L/opt/homebrew/Cellar/check/0.15.2/lib
TEST_FLAGS=-lcheck -lm -pthread
GREP=s21_brick.c
#GREP=s21_decimal.c s21_arithmetic.c s21_comparison.c s21_conversion.c s21_other_functions.c
QUEST1=brick
LN=-lncurses

SRC=$(wildcard ./*.c)
OBJ=$(SRC:.c=.o)

UNAME=$(shell uname -s)

#ifeq ($(UNAME), Linux)
#	TEST_FLAGS=-lcheck -lm -lrt -lpthread -lsubunit
#endif

#ifeq ($(UNAME), Darwin)
#	TEST_FLAGS=-lcheck
#endif

all: clean s21_matrix.a

brick: $(GREP)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(QUEST1) $(LN)

s21_matrix.a: $(OBJ)
	ar rcs $@ $^
	ranlib $@

test: s21_matrix.a
	$(CC) $(CFLAGS) $(LDFLAGS) ./tests/*.c s21_matrix.a $(TEST_FLAGS) -o $@
	./$@

gcov_report: clean
	$(CC) $(CFLAGS) $(LDFLAGS) --coverage ./tests/*.c ./*.c $(TEST_FLAGS) -o gcov_test
	./gcov_test
	lcov -t "gcov_test" -c -d . -o gcov_test.info
	genhtml -o report gcov_test.info
	rm -f *.gcda *.gcno gcov_test.info gcov_test
	open report/index.html
#	firefox report/index.html 

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n --style=file *.c *.h tests/*.c tests/*.h
	clang-format -i --style=file *.c *.h tests/*.c tests/*.h
	rm ./.clang-format

clean:
	rm -f $(OBJ) s21_matrix.a test gcov_test *.gcda *.gcno *.info
	rm -rf report