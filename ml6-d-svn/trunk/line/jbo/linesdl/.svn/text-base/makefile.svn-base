final: ui.o draw.o main.c
	gcc `pkg-config --libs   sdl` `pkg-config --libs   gtk+-2.0` main.c ui.o draw.o -o lines

ui.o: ui.c ui.h
	gcc `pkg-config --cflags sdl` `pkg-config --cflags gtk+-2.0` -c ui.c -o ui.o
	
draw.o: draw.c draw.h
	gcc -c draw.c -o draw.o
	
clean:
	rm draw.o ui.o
