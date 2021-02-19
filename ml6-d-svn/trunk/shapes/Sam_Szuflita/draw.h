#ifndef DRAW_H
#define DRAW_H

#include "matrix.h"

void add_point( struct matrix * points, int x, int y, int z);
void draw_lines( struct matrix * points, screen s, color c);
void add_edge( struct matrix * points, 
	       int x0, int y0, int z0, 
	       int x1, int y1, int z1);
void draw_line(int x0, int y0, int x1, int y1, screen s, color c);
struct matrix* render_circle(double r, double x, double y, double t);
void generate_circle(struct matrix * pm, struct matrix * helper);
struct matrix* render_sphere(double r, double offx, double offy);
void generate_sphere(struct matrix * pm, struct matrix * helper);
struct matrix * render_torus(double R, double r, double offx, double offy);
void generate_torus(struct matrix * pm, struct matrix * helper);
void generate_hermite(struct matrix * pm, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double p4x, double p4y);
void generate_bezier(struct matrix * pm, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double p4x, double p4y);
double cubic(double a, double b, double c, double d, double t);
#endif
