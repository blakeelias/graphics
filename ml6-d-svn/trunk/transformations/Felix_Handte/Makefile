CC=gcc
CCOPTS=-ggdb -Wall -c# -Wextra -pedantic
UIC=`pkg-config --cflags sdl` `pkg-config --cflags gtk+-2.0`

LD=gcc
LDOPTS=-lm
UIL=`pkg-config --libs   sdl` `pkg-config --libs   gtk+-2.0` #-lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lm -lcairo -lpng12 -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0

all : draw

draw : main.o ui.o controls.o line.o matrix.o
	$(LD) $(LDOPTS) $(UIL) main.o ui.o controls.o line.o matrix.o -o draw

main.o : main.c
	$(CC) $(CCOPTS) main.c -o main.o

line.o : line.c
	$(CC) $(CCOPTS) line.c -o line.o

matrix.o : matrix.c
	$(CC) $(CCOPTS) matrix.c -o matrix.o

ui.o : ui.c
	$(CC) $(CCOPTS) $(UIC) ui.c -o ui.o

controls.o : controls.c
	$(CC) $(CCOPTS) $(UIC) controls.c -o controls.o


force : clean all

clean :
	rm -rf draw *.o *~


main.c : main.h ui.h line.h
line.c : line.h
matrix.c : matrix.h
ui.c : ui.h
controls.c : controls.h
