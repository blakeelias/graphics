#include "main.h"

#define WIDTH 1024
#define HEIGHT 512

int main(int argc, char *argv[]){
	initWindow(&argc, &argv, WIDTH, HEIGHT, "FelixDraw");
	initControls();
	while(1){
		doGtk();
	}
	return EXIT_SUCCESS;
}
