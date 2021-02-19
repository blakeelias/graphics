#include "ui.h"

#include <stdlib.h>
#include <unistd.h>
#include "SDL.h"
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

GtkWidget *window;
SDL_Surface *screen;

static gint exit_window(GtkWidget *widget, gpointer user_data);

void initWindow(int *argc, char ***argv){
	gtk_init(argc, argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), WINDOW_TITLE);
	g_signal_connect(window, "destroy", G_CALLBACK(exit_window), NULL);
	gtk_widget_set_size_request(window, WIDTH, HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
	
	gtk_widget_realize(window); //           Required to get a valid X window ID
	gtk_main_iteration(); // Apparently also required to get a valid X window ID
	
	char SDL_windowid[32];
	sprintf(SDL_windowid,"SDL_WINDOWID=%ld", GDK_WINDOW_XWINDOW(window->window));
	putenv(SDL_windowid);
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf(stderr, "initwindow: SDL Fail: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE);
	if(screen == NULL){
		fprintf(stderr, "initwindow: Unable to set %dx%d video: %s\n", WIDTH, HEIGHT, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	clearScreen();
	
	gtk_widget_show_all(window);
	gtk_main_iteration();
}

void drawPixel(/*SDL_Surface *screen, */unsigned char R, unsigned char G, unsigned char B, int x, int y){
	//Uint32 color = SDL_MapRGB(screen->format, R, G, B);
	//printf("%x\n", color);
	//if(SDL_MUSTLOCK(screen)){
	//	if(SDL_LockSurface(screen) < 0){
	//		return;
	//	}
	//}
	Uint32 color = 256 * 256 * R + 256 * G + B;
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
			*(bufp+screen->format->Rshift/8) = R;
			*(bufp+screen->format->Gshift/8) = G;
			*(bufp+screen->format->Bshift/8) = B;
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
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			drawPixel(255, 255, 255, j, i);
		}
	}
}

void updateScreen(void){
	SDL_UpdateRect(screen, 0, 0, WIDTH, HEIGHT);
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
