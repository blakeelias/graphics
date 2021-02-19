final: ui.o draw.o geo.o matrix.o main.c
	gcc -lm -lrt `pkg-config --libs --cflags sdl` -Wall main.c ui.o draw.o geo.o matrix.o -o shapes_n_stuff

ui.o: ui.c ui.h
	gcc `pkg-config --cflags sdl` -Wall -c ui.c -o ui.o
	
draw.o: draw.c draw.h
	gcc `pkg-config --cflags sdl` -Wall -c draw.c -o draw.o
	
geo.o: geo.c geo.h
	gcc -Wall -c geo.c
	
matrix.o: matrix.c matrix.h
	gcc -Wall -c matrix.c
	
clean:
	rm *.o
