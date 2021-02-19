#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "constants.h"
#include "controls.h"
#include "darea.h"
#include "signals.h"

int width;
int height;

int main(int argc, char *argv[]){
	debug = 1;
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	setsighandling();
	initDArea(width, height);
	initControls(&argc, &argv);
	while(1){
		busy = 0;
		doGtk();
		doSDL();
		if(!busy){
			usleep(10000);
		}
	}
	fprintf(stderr, "Waaaaah?!?\n");
	return EXIT_FAILURE;
}
