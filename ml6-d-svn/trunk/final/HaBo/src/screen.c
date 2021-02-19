#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <SDL/SDL.h>

#include "aircraft.h"
#include "animation.h"
#include "globals.h"
#include "render.h"
#include "screen.h"
#include "stack.h"

SDL_Surface *screen;
SDL_TimerID timer;
SDL_Event event;

void click(int x, int y, int button, int direction);
void process_user_input();
void recalculate_kinematics(node *subtree);

void screen_init(void){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
		error_w("initwindow: SDL Fail: %s.", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_SetVideoMode(screen_w, screen_h, DEPTH, SDL_SWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL){
		error_w("initwindow: Unable to set %dx%d video: %s.", screen_w, screen_h, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	zbuffer = malloc(screen_w * screen_h * sizeof(double));
	
	pixel_array = screen->pixels;
	pixel_pitch = screen->pitch >> 2;
	
	stack_init();
	
	atexit(SDL_Quit);
}

void screen_toggle_fullscreen(void){
	SDL_WM_ToggleFullScreen(screen);
}

void screen_main(void){

			/*/////////////////////////////
				debug_n("FREEING SCENE");
				scene_free(root_node);
				debug_n("FREEING STACK");
				stack_free();
				debug_n("RAISING SIGABRT");
				raise(SIGABRT);
			/////////////////////////////*/
	
	if(SDL_PollEvent(&event)){
		//busy = 1;
		switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				d_debug_n(D_INPUT, "Click.");
				click(event.button.x, event.button.y, event.button.button, event.type);
				break;
			case SDL_MOUSEMOTION:
				break;
			case SDL_ACTIVEEVENT:
				break;
			case SDL_KEYDOWN:
				d_debug_w(D_INPUT, "Key Down: %d.", event.key.keysym.sym);
				keys[event.key.keysym.sym] = 1;
				break;
			case SDL_KEYUP:
				d_debug_w(D_INPUT, "Key Up: %d.", event.key.keysym.sym);
				keys[event.key.keysym.sym] = 0;
				break;
				
			/////
			case SDL_QUIT:
				//debug_n("FREEING SCENE");
				//scene_free(root_node);
				//debug_n("FREEING STACK");
				//stack_free();
				//debug_n("RAISING SIGABRT");
				raise(SIGABRT);
				break;
			/////
				
			default:
				d_debug_w(D_INPUT, "Unrecognized event: %d.", event.type);
				break;
		}	
	}
	
	process_user_input();
	recalculate_kinematics(root_node);
	animation_update_scene(root_node);
	screen_clear();
	//debug_n("Rendering scene\n");
	render_scene(root_node, cam_node);
	screen_refresh();

}

void process_user_input() {
	switch (usrctl_node->type) {
		case NODE_OBJ:
			switch (usrctl_node->n.o->type) {
				case OBJ_AIRCRAFT:
					aircraft_user_control();
					break;
			}
		break;
	}
}

void recalculate_kinematics(node *subtree) {
	if (subtree->type == NODE_OBJ) {
		switch (subtree->n.o->type) {
			case OBJ_AIRCRAFT:
				aircraft_update(subtree);
				break;
			case OBJ_CAMERA:
				// stuff goes here
				break;
		}
	}
	int i;
	for (i = 0; i < subtree->nchild; i++)
		recalculate_kinematics(subtree->child[i]);
}

void click(int x, int y, int button, int direction){
	switch(button){
		case SDL_BUTTON_LEFT:
			switch(direction){
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_MOUSEBUTTONUP:
					break;
			}
			break;
		case SDL_BUTTON_RIGHT:
			switch(direction){
				case SDL_MOUSEBUTTONDOWN:
					screen_toggle_fullscreen();
					break;
				case SDL_MOUSEBUTTONUP:
					
					break;
			}
			break;
		default:
			error_n("Unrecognized click.");
			break;
	}
}

void screen_clear(void){
	memset(pixel_array, 0x00, screen_w * screen_h * 4);
	//int i, j;
	//for(i = 0; i < screen_w; i++){
	//	for(j = 0; j < screen_h; j++){
	//		pixel(i, j) = 0x00000000;
	//	}
	//}
}

void screen_refresh(void){
	SDL_UpdateRect(screen, 0, 0, screen_w, screen_h);
}
