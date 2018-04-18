part1:
	gcc -g part1.c -o part1 -lm
clean:
	rm -f part1
all:
	gcc -g part1.c -o part1 -lm
	gcc -g cse320_functions.h
	gcc -g test.c -o test -lm
