CC=gcc
CCOPTS=-ggdb -Wall -c# -Wextra -pedantic
GTKC=`pkg-config --cflags gtk+-2.0`
SDLC=`pkg-config --cflags sdl`

LD=gcc
LDOPTS=-lm
GTKL=`pkg-config --libs   gtk+-2.0`
SDLL=`pkg-config --libs   sdl`

all : transform

transform : main.o globals.o controls.o screen.o matrix.o line.o signals.o objects.o
	$(LD) $(LDOPTS) $(GTKL) $(SDLL) \
	main.o globals.o controls.o screen.o matrix.o line.o signals.o objects.o -o transform


main.o : main.c
	$(CC) $(CCOPTS) \
	main.c -o main.o

globals.o : globals.c
	$(CC) $(CCOPTS) \
	globals.c -o globals.o

controls.o : controls.c
	$(CC) $(CCOPTS) $(GTKC) \
	controls.c -o controls.o

screen.o : screen.c
	$(CC) $(CCOPTS) $(SDLC) \
	screen.c -o screen.o

matrix.o : matrix.c
	$(CC) $(CCOPTS) \
	matrix.c -o matrix.o

line.o : line.c
	$(CC) $(CCOPTS) \
	line.c -o line.o

signals.o : signals.c
	$(CC) $(CCOPTS) \
	signals.c -o signals.o

objects.o : objects.c
	$(CC) $(CCOPTS) \
	objects.c -o objects.o


force : clean all

clean :
	rm -rf transform *.o *~
