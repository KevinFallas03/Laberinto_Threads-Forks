CC=gcc
CFLAGS=-lpthread

default=all

all:
	$(CC) main.c -o program.exe $(CFLAGS)
	./program.exe
	rm -f ./program.exe

clean: 
	rm -f ./program.exe

debug:
	$(CC) -g -o program main.c $(CFLAGS)
	gdb program