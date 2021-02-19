#include "matrix.h"

#ifndef DRAW_H
#define DRAW_H

struct matrix *render_box(double x0, double y0, double z0, double lx, double ly, double lz);
void draw_torus(struct matrix *points, double x, double y, double R, double r);
void draw_sphere(struct matrix *points, double x, double y, double r);
void connect_dots(struct matrix *sphere_points, struct matrix *points, int nsteps_lat, int nsteps_lon);
void render_parametric(struct matrix * points, 
					   double (*fucn_x)(double t),
					   double (*fucn_y)(double t), double);
void add_point( struct matrix * points, int x, int y, int z);
void draw_lines( struct matrix * points, screen s, color c);
void add_edge( struct matrix * points, 
			  int x0, int y0, int z0, 
			  int x1, int y1, int z1);
void draw_line(int x0, int y0, int x1, int y1, screen s, color c);
void draw_box(struct matrix *points, double x1, double y1, double z1, double x2, double y2, double z2);
struct matrix* render_circle(double r, double x, double y, double t);
void generate_circle(struct matrix * pm, struct matrix * helper);
#endif
