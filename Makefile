# Electible Makefile
# SE 2XC3 Lab 7.2
# Team: Amanda Wu, Anshika Patel, Khushi Ved, Yasmine Abdelmalek

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
COVERAGE_FLAGS = --coverage -fprofile-arcs -ftest-coverage
LIBS = -lm

# Source files
SRC_FILES = src/data.c src/filter.c src/sort.c
TEST_FILES = tests/test.c

# Build the program
all:
	@mkdir -p bin
	$(CC) $(CFLAGS) -o bin/electible src/main.c $(SRC_FILES) src/ui.c $(LIBS)

# Run the program
run: all
	./bin/electible

# Build and run tests
test:
	@mkdir -p bin
	$(CC) $(CFLAGS) -o bin/test_electible $(TEST_FILES) $(SRC_FILES) $(LIBS)
	./bin/test_electible

# Build with coverage support
coverage:
	@mkdir -p bin coverage
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -o bin/test_coverage $(TEST_FILES) $(SRC_FILES) $(LIBS)
	cd bin && ./test_coverage
	@echo "Generating coverage data..."
	gcov -o bin $(SRC_FILES) 2>/dev/null || true
	@find . -name "*.gcov" -exec mv {} coverage/ \; 2>/dev/null || true
	@find . -name "*.gcda" -exec mv {} coverage/ \; 2>/dev/null || true
	@find . -name "*.gcno" -exec mv {} coverage/ \; 2>/dev/null || true
	@echo "Coverage files generated in coverage/ directory"

# Generate HTML coverage report (requires lcov)
coverage-html: coverage
	lcov --capture --directory coverage --output-file coverage/coverage.info 2>/dev/null || true
	genhtml coverage/coverage.info --output-directory coverage/html 2>/dev/null || true
	@echo "HTML coverage report generated in coverage/html/"

# Clean up compiled files
clean:
	rm -rf bin obj coverage *.gcov *.gcda *.gcno
	@find src -name "*.gcov" -o -name "*.gcda" -o -name "*.gcno" | xargs rm -f 2>/dev/null || true

# Rebuild everything
rebuild: clean all

.PHONY: all run test coverage coverage-html clean rebuild
