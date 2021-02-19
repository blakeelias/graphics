#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

void initWindow(){
	
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
		fprintf(stderr, "initWindow: SDL Fail: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE);
	if(screen == NULL){
		fprintf(stderr, "initWindow: Unable to set %dx%d video: %s\n", WIDTH, HEIGHT, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	clearScreen();
  atexit(SDL_Quit);
}


void drawPixel(unsigned char R, unsigned char G, unsigned char B, int x, int y){

  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    return;
    
	Uint32 color = 256 * 256 * R + 256 * G + B;
	
	if(screen->format->BytesPerPixel != 4) {
	  fprintf(stderr, "drawPixel: Not 32-bit color\n");
	  exit(EXIT_FAILURE);
  }
  
	Uint32 *bufp;
	bufp = (Uint32 *) screen->pixels + y*screen->pitch/4 + x;
	*bufp = color;
}

int getValue(int x, int y) {
  return *((Uint32 *) screen->pixels + y*screen->pitch/4 + x);
}

char getValueR(int x, int y) {
  return getValue(x, y) / (256 * 256);
}

char getValueG(int x, int y) {
  return (getValue(x, y) | (255 * 256)) / (256);
}

char getValueB(int x, int y) {
  return getValue(x, y) | (255);
}

void shadePixel(unsigned char R, unsigned char G, unsigned char B, int x, int y) {
  /*
  double newR = getValueR(x, y) + ((255 - getValueR(x, y)) * R / 255);
  double newG = getValueG(x, y) + ((255 - getValueG(x, y)) * G / 255);
  double newB = getValueB(x, y) + ((255 - getValueB(x, y)) * B / 255);
  */
  
  /*
  char newR, newG, newB;
  
  if (((int) R) + ((int) getValueR(x, y)) > 255)
    newR = 255;
  else
    newR = R + getValueR(x, y);
    
  if (((int) G) + ((int) getValueG(x, y)) > 255)
    newG = 255;
  else
    newG = G + getValueG(x, y);
    
  if (((int) B) + ((int) getValueB(x, y)) > 255)
    newB = 255;
  else
    newB = B + getValueB(x, y);
    
  drawPixel(newR, newG, newB, x, y);
  */
  drawPixel(R, G, B, x, y);
}

void clearScreen(void){
	int i, j;
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			drawPixel(0, 0, 0, j, i);
		}
	}
}


void updateScreen(void){
	SDL_UpdateRect(screen, 0, 0, WIDTH, HEIGHT);
}

