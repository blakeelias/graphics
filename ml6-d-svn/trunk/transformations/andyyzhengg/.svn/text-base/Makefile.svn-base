OBJECTS= test.o matrix_skeleton.o display.o draw.o
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc

all: $(OBJECTS)
	$(CC)  $(CFLAGS) $(LDFLAGS) -o main $(OBJECTS)

test.o: test.c matrix.h display.h ml6.h draw.h
	$(CC) $(CFLAGS) -c test.c

matrix_skeleton.o: matrix_skeleton.c matrix.h
	$(CC) $(CFLAGS) -c matrix_skeleton.c

draw.o: draw.c draw.h ml6.h display.h matrix.h
	$(CC) $(CFLAGS) -c draw.c

display.o: display.c display.h ml6.h
	$(CC) $(CFLAGS) -c display.c

clean:
	rm $(OBJECTS)

