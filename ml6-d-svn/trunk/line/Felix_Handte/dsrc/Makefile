CCOPTS=-g -Wall

all : dwdraw

dwdraw : test.o display.o draw.o
	gcc $(CCOPTS) -lm -o dwdraw test.o display.o draw.o

test.o : test.c ml6.h draw.h display.h
	gcc $(CCOPTS) -c test.c -o test.o

display.o : display.c display.h ml6.h
	gcc $(CCOPTS) -c display.c -o display.o

draw.o : draw.c draw.h ml6.h display.h
	gcc $(CCOPTS) -c draw.c -o draw.o

clean :
	rm -f dwdraw *.o *~ 1.png

force : clean all
