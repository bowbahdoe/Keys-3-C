CFLAGS = -std=c99 -c -fpic
all:
	gcc $(CFLAGS) key.c
	gcc $(CFLAGS) board.c
	gcc $(CFLAGS) main.c

	gcc main.o key.o board.o -o keys

PYTHON_INCLUDES = -I/usr/include/python2.7

python2:
	swig -python keys.i
	gcc $(CFLAGS) keys_wrap.c $(PYTHON_INCLUDES)
	gcc $(CFLAGS) key.c
	gcc $(CFLAGS) board.c

	ld -shared key.o keys_wrap.o board.o -o _keys.so
clean:
	rm board.o
	rm key.o
	rm main.o
	rm keys

clean_python2:
	rm keys_wrap.*
	rm board.o
	rm key.o
	rm keys.py*
	rm _keys.so
