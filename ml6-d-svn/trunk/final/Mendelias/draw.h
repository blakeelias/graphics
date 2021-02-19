#include "matrix.h"

#ifndef DRAW_H
#define DRAW_H

void add_point( struct matrix * points, int x, int y, int z);
void draw_lines( struct matrix * points, screen s, color c);
void add_edge( struct matrix * points, 
	       int x0, int y0, int z0, 
	       int x1, int y1, int z1);

void draw_line(int x0, int y0, double z0,
	       //double nx0, double ny0, double nz0,
	       int x1, int y1, double z1,
	       //double nx1, double ny1, double nz1,
	       screen s, color c);

void draw_polygons(struct matrix *points, screen s, color c[NUM_COLORS]);
void add_polygon(struct matrix *points,
		 int x0, int y0, int z0,
		 int x1, int y1, int z1,
		 int x2, int y2, int z2);
#endif
