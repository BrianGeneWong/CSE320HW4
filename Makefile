part1:
	gcc -g part1.c -o part1 -lm
part2:
	gcc -g part2.c -o part2 -lm
part2ec:
	gcc -g part2ec.c -o part2ec -lm
part3:
	gcc -g part3.c -o part3 -lm
clean:
	rm -f part1
	rm -f part2
	rm -f test
	rm -f part3
	rm -f part2ec
all:
	gcc -g part1.c -o part1 -lm
	gcc -g test.c -o test -lm
	gcc -g part2.c -o part2 -lm
	gcc -g part3.c -o part3 -lm
	gcc -g part2ec.c -o part2ec -lpthread -lm -lrt
