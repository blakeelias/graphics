#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "globals.h"
#include "animation.h"
#include "camera.h"
#include "objects.h"
#include "signals.h"
#include "screen.h"
#include "scene.h"
#include "ver.h"
#include "world.h"

void print_welcome(void);

int main(int argc, char *argv[]){
	globals_init();
	signals_init();
	print_welcome();
	screen_init();
	animation_init();
	world_init();
	scene_print(root_node);
	while(1){
		screen_main();
	}
	error_n("...?");
	return EXIT_FAILURE;
}

void print_welcome(void){
	if(dodebug(D_WELCOME)){
		fprintf(stderr, "%s, V%s, compiled on %s at %s, PID %u.\n  %s SegFaults since build 664.\n  %s failed makes since build 843.\n", PROGRAM_NAME, PROGRAM_VER_BUILD, __DATE__, __TIME__, getpid(), SEGFAULT_COUNT, FAILEDMAKES_COUNT);
	}
}
