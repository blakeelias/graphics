#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "draw.h"
#include "ui.h"

void blackScreen();

int main(int argc, char **argv) {

  // Seed rand() with current nanosecond time
  struct timespec *tp;
  clock_gettime(CLOCK_REALTIME, tp);
  srand(tp->tv_nsec);
  
  initWindow(NULL, NULL);
  blackScreen();
  
  while (1) {
    drawLine(rand() % 512, rand() % 512, rand() % 512, rand() % 512, (unsigned int) rand(), (unsigned int) rand(), (unsigned int) rand());
    updateScreen();
    doGtk();
    usleep(500000);
  }
  
  return 0;
}

void blackScreen() {
	int i, j;
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			drawPixel(0, 0, 0, j, i);
		}
	}
}
