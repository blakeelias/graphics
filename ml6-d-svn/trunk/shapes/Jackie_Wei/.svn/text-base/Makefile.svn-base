OBJECTS= main.o matrix.o display.o draw.o
CFLAGS=-Wall 
LDFLAGS=-lm 
CC=gcc

all: $(OBJECTS)
	$(CC)  $(CFLAGS) $(LDFLAGS) -o main $(OBJECTS)

main.o: main.c matrix.h display.h ml6.h draw.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

draw.o: draw.c draw.h ml6.h display.h matrix.h
	$(CC) $(CFLAGS) -c draw.c

display.o: display.c display.h ml6.h
	$(CC) $(CFLAGS) -c display.c

clean:
	rm $(OBJECTS)

