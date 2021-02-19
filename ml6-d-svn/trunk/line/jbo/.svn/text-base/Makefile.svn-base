all: test.o display.o draw.o
	gcc -o hey_it_works test.o display.o draw.o

test.o: test.c ml6.h draw.h display.h
	gcc -c test.c

display.o: display.c display.h ml6.h
	gcc -c display.c

draw.o: draw.c draw.h ml6.h display.h
	gcc -c draw.c
clean:
	rm *.o *~
