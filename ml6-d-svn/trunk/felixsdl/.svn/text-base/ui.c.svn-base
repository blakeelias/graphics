#include "ui.h"

#include <stdlib.h>
#include <unistd.h>
#include "SDL.h"
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

GtkWidget *window;
SDL_Surface *screen;

int width, height;
char *window_title;

static gint exit_window(GtkWidget *widget, gpointer user_data);

void initWindow(int *argc, char ***argv, int arg_width, int arg_height, char *arg_window_title){
	width = arg_width;
	height = arg_height;
	window_title = arg_window_title;
	gtk_init(argc, argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), window_title);
	g_signal_connect(window, "destroy", G_CALLBACK(exit_window), NULL);
	gtk_widget_set_size_request(window, width, height);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
	
	gtk_widget_realize(window); //           Required to get a valid X window ID
	gtk_main_iteration(); // Apparently also required to get a valid X window ID
	
	char SDL_windowid[32]; // Hack to put SDL in a GTK window
	sprintf(SDL_windowid,"SDL_WINDOWID=%ld", GDK_WINDOW_XWINDOW(window->window));
	putenv(SDL_windowid);
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf(stderr, "initwindow: SDL Fail: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(width, height, DEPTH, SDL_SWSURFACE);
	if(screen == NULL){
		fprintf(stderr, "initwindow: Unable to set %dx%d video: %s\n", width, height, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	clearScreen(); // Initialize array to white.
	
	gtk_widget_show_all(window);
	doGtk();
}

void drawPixel(/*SDL_Surface *screen, */unsigned char R, unsigned char G, unsigned char B, int x, int y){
	//Uint32 color = SDL_MapRGB(screen->format, R, G, B);
	//printf("%x\n", color);
	Uint32 color = 256 * 256 * R + 256 * G + B;
	drawPixelInt(color, x, y);
}

void drawPixelInt(unsigned int color, int x, int y){
	//if(SDL_MUSTLOCK(screen)){
	//	if(SDL_LockSurface(screen) < 0){
	//		return;
	//	}
	//}
	switch(screen->format->BytesPerPixel){
		case 1: /* Assuming 8-bpp */
			{
			Uint8 *bufp;
			bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
			*bufp = color;
			}
			break;
		case 2: /* Probably 15-bpp or 16-bpp */
			{
			Uint16 *bufp;
			bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
			*bufp = color;
			}
			break;
		case 3: /* Slow 24-bpp mode, usually not used */
			{
			Uint8 *bufp;
			bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
			*(bufp+screen->format->Rshift/8) = color & 0x00ff0000;
			*(bufp+screen->format->Gshift/8) = color & 0x0000ff00;
			*(bufp+screen->format->Bshift/8) = color & 0x000000ff;
			}
			break;
		case 4: /* Probably 32-bpp */
			{
			Uint32 *bufp;
			bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
			*bufp = color;
			}
			break;
	}
	//if(SDL_MUSTLOCK(screen)){
	//	SDL_UnlockSurface(screen);
	//}
}

void clearScreen(void){
	int i, j;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			drawPixel(255, 255, 255, j, i);
		}
	}
}

void updateScreen(void){
	SDL_UpdateRect(screen, 0, 0, width, height);
}

void updateScreenRect(int x, int y, int w, int h){
	SDL_UpdateRect(screen, x, y, w, h);
}

void doGtk(void){
	while(gtk_events_pending()){
		gtk_main_iteration();
	}
}

static gint exit_window(GtkWidget *widget, gpointer user_data){
	raise(SIGQUIT);
	return 0;
}
