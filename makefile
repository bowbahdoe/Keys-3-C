CFLAGS = -std=c99
all:
	gcc $(CFLAGS) -c key.c
	gcc $(CFLAGS) -c board.c
	gcc $(CFLAGS) -c main.c

	gcc main.o key.o board.o -o keys

clean:
	rm board.o
	rm key.o
	rm keys
