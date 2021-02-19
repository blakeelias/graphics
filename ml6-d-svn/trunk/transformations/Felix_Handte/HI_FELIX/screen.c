#include "globals.h"
#include "screen.h"
#include "draw.h"
#include "controls.h"
#include "geo.h" // JB

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <SDL.h>

SDL_Surface *screen;
SDL_TimerID timer;
SDL_Event event;

void click(int x, int y, int button, int direction);
int points_suffice(void);
void draw_objects(void);
int point_add(struct matrix *m, matrix_t x, matrix_t y, matrix_t z);
void screen_clear(void);
void commit_object (void);

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
	
	is.p = matrix_new(1, 4);
	mode_change(0);
	//matrix_print(is.p);
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
		
		commit_object();
		mode_change(is.mode);
		draw_objects();
	} else {
		//draw_objects();
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
			error_n("Unrecognized click.\n");
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

////////// JB 
void commit_object (void){
	switch(is.mode){
		case MODE_ADDPT:
			universe[num_shapes] = geo_newShape(1, 0);
			geo_addPoint(universe[num_shapes], is.p->m[0]);
			num_shapes++;
			break;
		case MODE_DRAWL:
			universe[num_shapes] = geo_newShape(2, 1);
			geo_addLine(universe[num_shapes], is.p->m[0], is.p->m[1]);
			num_shapes++;
			break;
		case MODE_SPHER:
			break;
		case MODE_TRANS:
			break;
		case MODE_SCALE:
			break;
		case MODE_ROTAX:
		case MODE_ROTAY:
		case MODE_ROTAZ:
			break;
	debug_w("Number of shapes in universe: %d\n", num_shapes);
	}
}

void draw_objects(void){
	screen_clear();
	color c;
	c.c.r = 255;
	c.c.g = 255;
	c.c.b = 255;
	draw_shapeList(universe, num_shapes, c); // draws white, for now
	screen_update = 1;
}

int point_add(struct matrix *m, matrix_t x, matrix_t y, matrix_t z){
  /*
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
	*/
	matrix_t point[3];
	point[0] = x;
	point[1] = y;
	point[2] = z;
	return matrix_addPoint(m, point); // JB
}

void screen_clear(void){
	int i, j;
	for(i = 0; i < screen_w; i++){
		for(j = 0; j < screen_h; j++){
			pixel(i, j) = 0x00000000;
		}
	}
}

void screen_drawPixel(color c, int x, int y){

  if (x < 0 || x >= screen_w || y < 0 || y >= screen_h)
    return;
    
	//Uint32 color = 256 * 256 * R + 256 * G + B;
	
	if(screen->format->BytesPerPixel != 4) {
	  fprintf(stderr, "drawPixel: Not 32-bit color\n");
	  exit(EXIT_FAILURE);
  }
  
	Uint32 *bufp;
	bufp = (Uint32 *) screen->pixels + y*screen->pitch/4 + x;
	*bufp = (Uint32) c.i;
}
