#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdio.h>

#include "geo.h" // JB
#include "matrix.h"

struct inputstate {
	struct matrix *p; // point list/matrix
	int *e;           // edge  list/matrix
	int mode;         // input mode
	int ms;           // mouse state 0 = normal, 1 = down, 2 = down move
	int lx, ly;       // last x and y;
	int cx, cy;       // current x and y;
};

struct inputstate is;

struct indivcolor {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
};

typedef union {
	struct indivcolor c;
	unsigned int i;
} color;

int screen_w;
int screen_h;
int screen_update;

int debug;

int busy;

void *pixel_array;
int   pixel_pitch;

struct shape **universe; // JB
int num_shapes;
int max_shapes;

#define pixel(X, Y) *((unsigned int *) (pixel_array + (((Y) * pixel_pitch + (X)) << 2)))

#define error_n(STR     ) fprintf(stderr, "\033[1m[%s:%s:%d]\033[m: " STR, __FILE__, __FUNCTION__, __LINE__             )
#define error_w(STR, ...) fprintf(stderr, "\033[1m[%s:%s:%d]\033[m: " STR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define debug_n(STR     ) if(debug){ error_n(STR             ); }
#define debug_w(STR, ...) if(debug){ error_w(STR, __VA_ARGS__); }

#define DEPTH 32
#define MAX_COLOR 255

#define MODE_ADDPT 1
#define MODE_DRAWL 2
#define MODE_SPHER 3
#define MODE_TRANS 4
#define MODE_SCALE 5
#define MODE_ROTAX 6
#define MODE_ROTAY 7
#define MODE_ROTAZ 8

#define ADDPT_NPTS 1
#define DRAWL_NPTS 2
#define SPHER_NPTS 2
#define TRANS_NPTS 3
#define SCALE_NPTS 3
#define ROTAT_NPTS 3

#define MOUSE_NORM 0
#define MOUSE_DOWN 1
#define MOUSE_DNMV 2

void globals_init(void);

#endif
