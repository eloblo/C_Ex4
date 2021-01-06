all: frequency
frequency : frequency.o
	gcc -o frequency frequency.o
frequency.o: frequency.c
	gcc -Wall -g -c frequency.c
.PHONY: all clean
clean:
	rm -f *.o frequency
