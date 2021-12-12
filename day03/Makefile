CFLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -std=c17 -g
all :

part1: Part1.java
	javac Part1.java
	echo "use 'java Part1' to run"

part2: part2.c
	gcc -o part2 part2.c $(CFLAGS)

.PHONY: clean
clean:
	rm -f Part1.class part2
