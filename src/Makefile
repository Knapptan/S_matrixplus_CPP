CFLAGS = -Wall -Werror -Wextra -std=c++17
LIB_NAME=s21_matrix_oop.a

all: clean s21_matrix_oop.a gcov_report

.PHONY: $(LIB_NAME)
$(LIB_NAME):
	$(CC) $(CFLAGS) -c s21_matrix_oop.cc -g
	ar -rcs $@ *.o
	ranlib $@
	rm -rf *.o

clean:
	@rm -rf *report *.o *.a *.gcda *.gcno *.info *.out *.txt tests

s21_matrix_oop.a:
	@g++ $(CFLAGS) -c s21_matrix_oop.cc
	@ar rc s21_matrix_oop.a s21_matrix_oop.o
	@ranlib s21_matrix_oop.a
	@rm s21_matrix_oop.o

test:
	@g++ $(CFLAGS) tests.cc s21_matrix_oop.cc -lgtest -pthread -o tests.out
	@./tests.out

gcov_report:
	@g++ --coverage $(CFLAGS) tests.cc s21_matrix_oop.cc -o tests -lstdc++ -lm -lgtest
	@./tests
	# @lcov -t "info" -o tests.info -c -d .
	# @lcov -t "tests" -o tests.info -c -d '/usr/*' '*gtest*' '*CMakeFiles*' '*s21_matrix_oop.h*' '*tests.cc*' --output-file gcovreport.info
	@geninfo --ignore-errors inconsistent --output-filename tests.info --test-name tests --memory 0 s21_matrix_oop.gcda
	@genhtml --ignore-errors inconsistent -o report tests.info
	@open report/index.html

rebuild: all

format:
	find . -type f -name "*.cc" -exec clang-format -style=Google -i {} \;
	find . -type f -name "*.h" -exec clang-format -style=Google -i {} \;

format_check:
	find . -type f -name "*.cc" -exec clang-format -style=Google -n {} \;
	find . -type f -name "*.h" -exec clang-format -style=Google -n {} \;
