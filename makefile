CFLAGS = -std=c99 -Wall
MPFLAGS = -fopenmp
COMPILER = gcc
all:
	$(COMPILER) $(CFLAGS) game.c -D debug -o game



PYTHON2_INCLUDES = -I/usr/include/python2.7
PYTHON3_INCLUDES = -I/usr/include/python3
python2:
	swig -python keys.i
	gcc $(CFLAGS) keys_wrap.c $(PYTHON2_INCLUDES)
	gcc $(CFLAGS) key.c
	gcc $(CFLAGS) board.c
	gcc $(CFLAGS) gamestate.c
	ld -shared key.o keys_wrap.o board.o -o _keys.so
python3:
	swig -python keys.i
	gcc $(CFLAGS) keys_wrap.c $(PYTHON3_INCLUDES)
	gcc $(CFLAGS) key.c
	gcc $(CFLAGS) board.c
	gcc $(CFLAGS) gamestate.c
	ld -shared key.o keys_wrap.o board.o -o _keys.so

clean:
	rm game
	rm check_game

clean_python2:
	rm keys_wrap.*
	rm board.o
	rm key.o
	rm keys.py*
	rm _keys.so

TESTFLAGS = $(CFLAGS) 
tests:
	gcc $(TESTFLAGS) checks/check_game.c -lcheck --std=c99 -lm -lrt -o check_game

	
	