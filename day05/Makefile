CFLAGS =-Wall -Wextra -Werror -pedantic -pedantic-errors -std=c17 -g
LIBS=-lm
all : out

out: solution.c
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f out
