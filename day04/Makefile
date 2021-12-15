CFLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -std=c17 -g
all : sol

sol: solution.c
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f part1 part2
