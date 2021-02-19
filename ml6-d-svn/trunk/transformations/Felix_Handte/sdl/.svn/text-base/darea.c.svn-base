#include "darea.h"
#include "controls.h"
#include "constants.h"
#include "line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "SDL.h"

#define DEPTH 32

SDL_Surface *screen;
SDL_TimerID timer;
SDL_Event event;

int width, height;

void initDArea(int tmp_width, int tmp_height){
	error_n("Noo!\n");
	error_w("Noo! %d\n", 10);
	exit(0);
	width = tmp_width;
	height = tmp_height;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
		fprintf(stderr, "initwindow: SDL Fail: %s\n", SDL_GetError());
		raise(SIGABRT);
	}
	screen = SDL_SetVideoMode(width, height, DEPTH, SDL_SWSURFACE);
	if(screen == NULL){
		fprintf(stderr, "initwindow: Unable to set %dx%d video: %s\n", width, height, SDL_GetError());
		raise(SIGABRT);
	}
	
	pa = screen->pixels;
	pixpitch = screen->pitch / 4;
	
	atexit(SDL_Quit);
	
	is.p = matrix_new(1, 4);
	mode_change(0);
	//matrix_print(is.p);
}

void doSDL(void){
	need_update = 0;
	if(SDL_PollEvent(&event)){
		busy = 1;
		switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				fprintf(stderr, "Click\n");
				click(event.button.x, event.button.y, event.button.button, event.type);
				is.lx = event.button.x;
				is.ly = event.button.y;
				break;
			case SDL_MOUSEMOTION:
				//fprintf(stderr, "Mouse motion: (%3d, %3d)\n", event.button.x, event.button.y);
				//point_add(is.p, event.button.x, event.button.y, 0);
				if(is.ms == MOUSE_DOWN){
					is.ms = MOUSE_DNMV;
				}
				is.cx = event.button.x;
				is.cy = event.button.y;
				break;
			// Catch mouse leaving / entering the window.
			case SDL_ACTIVEEVENT:
				//fprintf(stderr, "Active Event, gain focus?: %d", event.active.gain);
				break;
			case SDL_QUIT:
				raise(SIGQUIT);
				break;
			case SDL_KEYDOWN:
				fprintf(stderr, "Key Down: %d\n", event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				fprintf(stderr, "Key Up  : %d\n", event.key.keysym.sym);
				break;
			default:
				printf("Unrecognized event: %d.\n", event.type);
				break;
		}
	}
	if(points_suffice()){
		printf("Woo!\n");
		//commit_object();
		mode_change(is.mode);
		draw_objects();
	} else {
		draw_objects();
		//draw_temp_object();
	}
	if(need_update){
		SDL_UpdateRect(screen, 0, 0, width, height);
		need_update = 0;
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
							fprintf(stderr, "Wat. SDL_MOUSEBUTTONDOWN event while button is down.\n");
							raise(SIGABRT);
							break;
						case MOUSE_DNMV:
							fprintf(stderr, "Wat. SDL_MOUSEBUTTONDOWN event while button is down.\n");
							raise(SIGABRT);
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch(is.ms){
						case MOUSE_NORM:
							fprintf(stderr, "Wat. SDL_MOUSEBUTTONUP event while button is up.\n");
							raise(SIGABRT);
							break;
						case MOUSE_DOWN:
							point_add(is.p, x, y, 0);
							is.ms = MOUSE_NORM;
							break;
						case MOUSE_DNMV:
							point_add(is.p, is.lx, is.ly, 0);
							point_add(is.p, x, y, 0);
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
			fprintf(stderr, "darea.c: click: Unrecognized click.\n");
			break;
	}
}

int points_suffice(void){
	switch(is.mode){
		case MODE_ADDPT:
			return is.p->nc >= ADDPT_NPTS;
			break;
		case MODE_DRAWL:
			return is.p->nc >= DRAWL_NPTS;
			break;
		case MODE_SPHER:
			return is.p->nc >= SPHER_NPTS;
			break;
		case MODE_TRANS:
			return is.p->nc >= TRANS_NPTS;
			break;
		case MODE_SCALE:
			return is.p->nc >= SCALE_NPTS;
			break;
		case MODE_ROTAX:
		case MODE_ROTAY:
		case MODE_ROTAZ:
			return is.p->nc >= ROTAT_NPTS;
			break;
	}
	return 0;
}

void draw_objects(void){
	clear_screen();
	draw_line_aa(100, 125,  50, 250, (color) (unsigned int) 0x7fff7f);
	draw_line_aa(125, 125, 150, 250, (color) (unsigned int) 0x3f3f3f);
	draw_line_aa(100,  10, 200,  10, (color) (unsigned int) 0x1f1f1f);
	need_update = 1;
}

int point_add(struct matrix *m, matrix_t x, matrix_t y, matrix_t z){
	matrix_print(m);
	if(m->ac <= m->nc){
		matrix_col_resize(m, m->ac + 1);
	}
	m->m[m->nc][0] = x;
	m->m[m->nc][1] = y;
	m->m[m->nc][2] = z;
	m->m[m->nc][3] = 1;
	matrix_print(m);
	return m->nc++;
}

void clear_screen(void){
	int i, j;
	for(i = 0; i < width; i++){
		for(j = 0; j < height; j++){
			pixel(i, j) = 0x00000000;
		}
	}
}
