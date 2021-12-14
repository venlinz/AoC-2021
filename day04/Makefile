CFLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -std=c17 -g
all : part1

part1: part1.c
	gcc -o part1 part1.c $(CFLAGS)

part2: part2.c
	gcc -o part2 part2.c $(CFLAGS)

.PHONY: clean
clean:
	rm -f part1 part2
