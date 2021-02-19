final: ui.o draw.o matrix.o main.c
	gcc -lm -lrt `pkg-config --libs --cflags sdl` -Wall main.c ui.o draw.o matrix.o -o spinny

ui.o: ui.c ui.h
	gcc `pkg-config --cflags sdl` -Wall -c ui.c -o ui.o
	
draw.o: draw.c draw.h
	gcc `pkg-config --cflags sdl` -Wall -c draw.c -o draw.o
	
matrix.o: matrix.c matrix.h
	gcc -Wall -c matrix.c
	
clean:
	rm *.o
