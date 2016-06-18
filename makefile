CFLAGS = -std=c99 -fpic
all:
	gcc $(CFLAGS) -c key.c
	gcc $(CFLAGS) -c board.c
	gcc -shared -o libkeys.so

clean:
	rm board.o
	rm key.o
	rm keys
