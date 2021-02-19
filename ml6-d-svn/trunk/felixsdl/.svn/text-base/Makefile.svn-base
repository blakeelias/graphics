CC=gcc
CCOPTS=-g -Wall -c
UIC=`pkg-config --cflags sdl` `pkg-config --cflags gtk+-2.0`

LD=gcc
LDOPTS=
UIL=`pkg-config --libs   sdl` `pkg-config --libs   gtk+-2.0`

life : main.o ui.o
	$(LD) $(LDOPTS) $(UIL) main.o ui.o -o life

main.o : main.c ui.h
	$(CC) $(CCOPTS) main.c -o main.o

ui.o : ui.c ui.h
	$(CC) $(CCOPTS) $(UIC) ui.c -o ui.o


force : clean life

clean :
	rm -rf life *.o *~
