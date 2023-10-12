LIB_NAME=s21_matrix_oop.a

CC=g++
CC_FLAGS=-Wall -Werror -Wextra -std=c++17
FILES=s21_matrix_oop.cc
TEST_FILES=tests.cc
GCOV_FLAGS=-coverage -fprofile-arcs -ftest-coverage 
LGTEST_FLAGS = -lgtest -lgtest_main -pthread
ifeq ($(OS), Linux)
  OPEN=xdg-open
else
  OPEN=open
endif

all: gcov_report

clean:
	rm -f *.o
	rm -f *.a
	rm -f tests
	rm -f *info*
	rm -f *.gc*
	rm -rf report
	rm -f s21_matrix_oop.a

test:
	g++ -o $(CC_FLAGS) tests $(TEST_FILES) $(FILES) $(LGTEST_FLAGS) -g
	./tests

.PHONY: $(LIB_NAME)
$(LIB_NAME):
	$(CC) $(CC_FLAGS) -c $(FILES) -g
	ar -rcs $@ *.o
	ranlib $@
	rm -rf *.o

gcov_report: $(LIB_NAME) 
	$(CC) $(CC_FLAGS) $(FILES) $(TEST_FILES) $(LGTEST_FLAGS) $(GCOV_FLAGS)  -o info
	./info
	lcov -t "info" -o gcovreport.info -c -d .
	lcov --remove gcovreport.info '/usr/*' '*gtest*' '*CMakeFiles*' '*s21_matrix_oop.h*' '*tests.cc*' --output-file gcovreport.info
	genhtml -o report gcovreport.info
	$(OPEN) report/index.html

format:
	find . -type f -name "*.cc" -exec clang-format -style=Google -i {} \;
	find . -type f -name "*.h" -exec clang-format -style=Google -i {} \;

format_check:
	find . -type f -name "*.cc" -exec clang-format -style=Google -n {} \;
	find . -type f -name "*.h" -exec clang-format -style=Google -n {} \;