#include "globals.h"
#include "screen.h"
#include "line.h"
#include "controls.h"
#include "objects.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <SDL.h>

SDL_Surface *screen;
SDL_TimerID timer;
SDL_Event event;

void click(int x, int y, int button, int direction);

void screen_init(void){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
		error_w("initwindow: SDL Fail: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_SetVideoMode(screen_w, screen_h, DEPTH, SDL_SWSURFACE);
	if(screen == NULL){
		error_w("initwindow: Unable to set %dx%d video: %s\n", screen_w, screen_h, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	pixel_array = screen->pixels;
	pixel_pitch = screen->pitch >> 2;
	
	atexit(SDL_Quit);
	
	is.o = object_new();
	mode_change(0);
}

void screen_main(void){
	screen_update = 0;
	if(SDL_PollEvent(&event)){
		busy = 1;
		switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				debug_n("Click\n");
				click(event.button.x, event.button.y, event.button.button, event.type);
				is.lx = event.button.x;
				is.ly = event.button.y;
				break;
			case SDL_MOUSEMOTION:
				if(is.ms == MOUSE_DOWN){
					is.ms = MOUSE_DNMV;
				}
				is.cx = event.button.x;
				is.cy = event.button.y;
				break;
			case SDL_ACTIVEEVENT:
				break;
			case SDL_QUIT:
				raise(SIGQUIT);
				break;
			case SDL_KEYDOWN:
				debug_w("Key Down: %d\n", event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				debug_w("Key Up  : %d\n", event.key.keysym.sym);
				break;
			default:
				debug_w("Unrecognized event: %d.\n", event.type);
				break;
		}
	}
	if(points_suffice()){
		debug_n("The number of points has been found sufficient.\n");
		
		//object_commit();
		mode_change(is.mode);
		objects_draw();
	} else {
		objects_draw();
		//draw_temp_object();
	}
	if(screen_update){
		SDL_UpdateRect(screen, 0, 0, screen_w, screen_h);
		screen_update = 0;
	}
}

void click(int x, int y, int button, int direction){
	switch(button){
		case SDL_BUTTON_LEFT:
			switch(direction){
				case SDL_MOUSEBUTTONDOWN:
					switch(is.ms){
						case MOUSE_NORM:
							is.ms = MOUSE_DOWN;
							break;
						case MOUSE_DOWN:
							error_n("Wat. SDL_MOUSEBUTTONDOWN event while button is down.\n");
							raise(SIGABRT);
							break;
						case MOUSE_DNMV:
							error_n("Wat. SDL_MOUSEBUTTONDOWN event while button is down.\n");
							raise(SIGABRT);
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch(is.ms){
						case MOUSE_NORM:
							error_n("Wat. SDL_MOUSEBUTTONUP event while button is up.\n");
							raise(SIGABRT);
							break;
						case MOUSE_DOWN:
							point_add(is.o, x, y, 0);
							is.ms = MOUSE_NORM;
							break;
						case MOUSE_DNMV:
							point_add(is.o, is.lx, is.ly, 0);
							point_add(is.o, x, y, 0);
							is.ms = MOUSE_NORM;
							break;
					}
					break;
			}
			break;
		case SDL_BUTTON_RIGHT:
			switch(direction){
				case SDL_MOUSEBUTTONDOWN:
					
					break;
				case SDL_MOUSEBUTTONUP:
					
					break;
			}
			break;
		default:
			error_n("Unrecognized click.\n");
			break;
	}
}

void screen_clear(void){
	int i, j;
	for(i = 0; i < screen_w; i++){
		for(j = 0; j < screen_h; j++){
			pixel(i, j) = 0x00000000;
		}
	}
}
