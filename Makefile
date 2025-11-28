# Electible Makefile
# SE 2XC3 Lab 7.2
# Team: Amanda Wu, Anshika Patel, Khushi Ved, Yasmine Abdelmalek

CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude
LIBS = -lm

# Build the program
all:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/electible src/main.c src/data.c src/filter.c src/sort.c src/ui.c $(LIBS)

# Run the program
run: all
	./bin/electible

# Build and run tests
test:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/test_electible tests/test.c src/data.c src/filter.c src/sort.c $(LIBS)
	./bin/test_electible

# Clean up compiled files
clean:
	rm -rf bin obj

# Rebuild everything
rebuild: clean all
