part1:
	gcc -g part1.c -o part1 -lm
part2:
	gcc -g part2.c -o part2 -lm
part3:
	gcc -g part3.c -o part3 -lm
clean:
	rm -f part1
	rm -f part2
	rm -f test
	rm -f part3
all:
	gcc -g part1.c -o part1 -lm
	gcc -g test.c -o test -lm
	gcc -g part2.c -o part2 -lm
	gcc -g part3.c -o part3 -lm
