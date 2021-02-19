#include "globals.h"
#include "signals.h"
#include "screen.h"
#include "controls.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	signals_set_handlers();
	globals_init();
	//args_parse(argc, argv);
	screen_init();
	controls_init(&argc, &argv);
	while(1){
		busy = 0;
		controls_main();
		screen_main();
		if(!busy){
			usleep(10000);
		}
	}
	error_n("...?");
	return EXIT_FAILURE;
}
