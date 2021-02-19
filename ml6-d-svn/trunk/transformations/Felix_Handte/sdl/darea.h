#ifndef _DAREA_H
#define _DAREA_H

#include "matrix.h"

void initDArea(int tmp_width, int tmp_height);
void doSDL(void);
void click(int x, int y, int button, int direction);
int points_suffice(void);
int point_add(struct matrix *m, matrix_t x, matrix_t y, matrix_t z);
void draw_objects(void);
void clear_screen(void);

int need_update;

struct inputstate {
	struct matrix *p; //pointmatrix
	int mode; // input mode
	int ms; // mouse state 0 = normal, 1 = down, 2 = down move
	int lx, ly; // last x and y;
	int cx, cy; // current x and y;
} is;

void *pa; // pixel array
int pixpitch;

#define pixel(X, Y) *((unsigned int *) (pa + (((Y) * pixpitch + (X)) << 2)))

#define error_n(STR)      fprintf(stderr, "[%s:%s:%d]: " STR, __FILE__, __FUNCTION__, __LINE__)
#define error_w(STR, ...) fprintf(stderr, "[%s:%s:%d]: " STR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#endif
