PNAME  := Line
CFLAGS := -O3 -Wall -o $(PNAME).exe $(PNAME).c

.PHONY: all clean normal linux win

all:
	@echo '"make normal" for standard executable'
	@echo '"make linux" for SDL with Linux'
	@echo '"make win" for SDL with Windows (MinGW)'

clean:
	rm -f $(PNAME).exe out.bmp

normal:
	gcc $(CFLAGS)

linux:
	gcc $(CFLAGS) -DUSE_SDL -lSDL

win:
	gcc $(CFLAGS) -DUSE_SDL -lmingw32 -lSDLmain -lSDL -mwindows
