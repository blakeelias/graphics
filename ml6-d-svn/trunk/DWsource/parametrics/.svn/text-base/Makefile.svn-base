OBJECTS= main.o matrix.o display.o draw.o parametrics.o
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc

all: $(OBJECTS)
	$(CC)  $(CFLAGS) $(LDFLAGS) -o main $(OBJECTS)

main.o: main.c matrix.h display.h ml6.h draw.h parametrics.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

draw.o: draw.c draw.h ml6.h display.h matrix.h parametrics.h
	$(CC) $(CFLAGS) -c draw.c

display.o: display.c display.h ml6.h
	$(CC) $(CFLAGS) -c display.c

parametrics.o: parametrics.c parametrics.h
	$(CC) $(CFLAGS) -c parametrics.c

clean:
	rm $(OBJECTS)

