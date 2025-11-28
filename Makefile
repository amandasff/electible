# Electible Makefile
# SE 2XC3 Lab 7.2
# Team: Amanda Wu, Anshika Patel, Khushi Ved, Yasmine Abdelmalek

CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude
COVERAGE_FLAGS = --coverage -fprofile-arcs -ftest-coverage
LIBS = -lm

# Source files
SRC_FILES = src/data.c src/filter.c src/sort.c
TEST_FILES = tests/test.c

# Build the program
all:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/electible src/main.c $(SRC_FILES) src/ui.c $(LIBS)

# Run the program
run: all
	./bin/electible

# Build and run tests
test:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/test_electible $(TEST_FILES) $(SRC_FILES) $(LIBS)
	./bin/test_electible

# Build with coverage support
coverage:
	mkdir -p bin coverage
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -o bin/test_coverage $(TEST_FILES) $(SRC_FILES) $(LIBS)
	./bin/test_coverage
	gcov -o . $(SRC_FILES)
	mv *.gcov coverage/ 2>/dev/null || true
	mv *.gcda *.gcno coverage/ 2>/dev/null || true
	@echo "Coverage files generated in coverage/ directory"
	@echo "Run 'lcov' or check .gcov files for coverage details"

# Generate HTML coverage report (requires lcov)
coverage-html: coverage
	lcov --capture --directory . --output-file coverage/coverage.info
	genhtml coverage/coverage.info --output-directory coverage/html
	@echo "HTML coverage report generated in coverage/html/"

# Clean up compiled files
clean:
	rm -rf bin obj coverage *.gcov *.gcda *.gcno

# Rebuild everything
rebuild: clean all
