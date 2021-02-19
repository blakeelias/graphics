CC=gcc
CCOPTS=-ggdb -Wall -c# -Wextra -pedantic
GTKC=`pkg-config --cflags gtk+-2.0`
SDLC=`pkg-config --cflags sdl`

LD=gcc
LDOPTS=-lm
GTKL=`pkg-config --libs   gtk+-2.0`
SDLL=`pkg-config --libs   sdl`

all : transform

transform : main.o controls.o darea.o matrix.o line.o signals.o
	$(LD) $(LDOPTS) $(GTKL) $(SDLL) \
	main.o controls.o darea.o matrix.o line.o signals.o -o transform


main.o : main.c controls.h darea.h constants.h
	$(CC) $(CCOPTS) \
	main.c -o main.o

controls.o : controls.c controls.h darea.h constants.h
	$(CC) $(CCOPTS) $(GTKC) \
	controls.c -o controls.o

darea.o : darea.c darea.h controls.h constants.h matrix.h
	$(CC) $(CCOPTS) $(SDLC) \
	darea.c -o darea.o

matrix.o : matrix.c matrix.h
	$(CC) $(CCOPTS) \
	matrix.c -o matrix.o

line.o : line.c line.h
	$(CC) $(CCOPTS) \
	line.c -o line.o

signals.o : signals.c signals.h
	$(CC) $(CCOPTS) \
	signals.c -o signals.o


force : clean all

clean :
	rm -rf transform *.o *~
