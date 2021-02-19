#all : matrix

all: test.o display.o draw.o
	gcc -o mkimg test.o display.o draw.o

test.o: test.c ml6.h draw.h display.h
	gcc -c test.c

display.o: display.c display.h ml6.h
	gcc -c display.c

draw.o: draw.c draw.h ml6.h display.h
	gcc -c draw.c

matrix : matrix.h matrix_skeleton.c
	gcc -o matrix matrix_skeleton.c

clean :
	rm *.o *~ mkimg matrix
