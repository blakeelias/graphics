all: test.o display.o draw.o matrix_skeleton.o
	gcc -o interesting_name_here test.o display.o draw.o matrix_skeleton.o

test.o: test.c ml6.h draw.h display.h matrix.h
	gcc -c test.c

display.o: display.c display.h ml6.h
	gcc -c display.c

draw.o: draw.c draw.h ml6.h display.h
	gcc -c draw.c

matrix_skeleton.o: matrix_skeleton.c matrix.h
	gcc -c matrix_skeleton.c
clean:
	rm *.o *~
