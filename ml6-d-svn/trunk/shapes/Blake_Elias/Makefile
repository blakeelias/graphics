all: main.o display.o draw.o matrix_skeleton.o parametrics.o splines.o
	gcc -o main -lm main.o display.o draw.o matrix_skeleton.o parametrics.o splines.o

main.o: main.c ml6.h draw.h display.h matrix.h
	gcc -c main.c

display.o: display.c display.h ml6.h
	gcc -c display.c

draw.o: draw.c draw.h ml6.h display.h
	gcc -c draw.c

matrix_skeleton.o : matrix.h matrix_skeleton.c
	gcc -c matrix_skeleton.c

parametrics.o : parametrics.h parametrics.c
	gcc -c parametrics.c

splines.o : splines.h splines.c
	gcc -c splines.c

clean :
	rm *.o *~ main
