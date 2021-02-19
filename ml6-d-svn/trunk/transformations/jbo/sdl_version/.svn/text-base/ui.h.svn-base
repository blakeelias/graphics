#ifndef _UI_H
#define _UI_H

// User editable:

#define WINDOW_TITLE "Transformations"
#define WIDTH 512
#define HEIGHT 512

// Leave be:

#include "SDL.h"

#define DEPTH 32 // Total bits per pixel

SDL_Surface *screen;

void initWindow();
void drawPixel(unsigned char R, unsigned char G, unsigned char B, int x, int y);
int getValue(int x, int y);
char getValueR(int x, int y);
char getValueG(int x, int y);
char getValueB(int x, int y);
void shadePixel(unsigned char R, unsigned char G, unsigned char B, int x, int y);
void clearScreen(void);
void updateScreen(void);

#endif
