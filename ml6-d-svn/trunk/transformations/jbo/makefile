main: main.c display.o draw.o matrix.o ml6.h
	gcc -lm -o transformator main.c display.o draw.o matrix.o

display.o: display.c display.h
	gcc -c display.c

draw.o: draw.c draw.h
	gcc -c draw.c
	
matrix.o: matrix.c matrix.h
	gcc -lm -c matrix.c
	
clean:
	rm display.o draw.o matrix.o
