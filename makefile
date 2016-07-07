CFLAGS = -std=c99 -c -fpic -Wall
MPFLAGS = -fopenmp
COMPILER = gcc
all:
	$(COMPILER) $(CFLAGS) key.c
	$(COMPILER) $(CFLAGS) board.c
	$(COMPILER) $(CFLAGS) main.c
	$(COMPILER) $(CFLAGS) gamestate.c

	$(COMPILER) main.o key.o board.o gamestate.o -o keys

openmp:
	gcc $(CFLAGS) $(MPFLAGS) key.c
	gcc $(CFLAGS) $(MPFLAGS) board.c
	gcc $(CFLAGS) $(MPFLAGS) main.c

	gcc main.o key.o board.o $(MPFLAGS) -o keys

PYTHON2_INCLUDES = -I/usr/include/python2.7
PYTHON3_INCLUDES = -I/usr/include/python3
python2:
	swig -python keys.i
	gcc $(CFLAGS) keys_wrap.c $(PYTHON2_INCLUDES)
	gcc $(CFLAGS) key.c
	gcc $(CFLAGS) board.c

	ld -shared key.o keys_wrap.o board.o -o _keys.so
python3:
	swig -python keys.i
	gcc $(CFLAGS) keys_wrap.c $(PYTHON3_INCLUDES)
	gcc $(CFLAGS) key.c
	gcc $(CFLAGS) board.c

	ld -shared key.o keys_wrap.o board.o -o _keys.so
javascript:

	emcc main.c key.c board.c
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
