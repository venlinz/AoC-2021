CC=gcc
CFLAGS=-Werror -Wextra -Wall -Wconversion -pedantic -pedantic-errors
CXX=g++

part1: part1.c
	$(CC) $(CFLAGS) $^ -o $@

part2: part2.cpp
	$(CXX) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f part1 part2
