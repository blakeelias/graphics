#include <stdlib.h>
#include "globals.h"

void globals_init(void){
	screen_w = 512;
	screen_h = 384;
	screen_update = 1;
	debug = 1;
	
	max_shapes = 1024;
	universe = (struct shape **) malloc(max_shapes * sizeof(struct shape *));
	num_shapes = 0;
}
