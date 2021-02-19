#ifndef DRAW_H
#define DRAW_H

#include "ml6.h"
#include "matrix.h"
#include "display.h"

void add_point(struct matrix * points, double x, double y, double z);
void draw_lines(struct matrix * points, screen s, color c);
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1);
void draw_line(int x0, int y0, int x1, int y1, screen s, color c);
struct matrix *points_in_bounds (double X0, double Y0, double X1, double Y1);
int inBounds (double x0, double y0);
struct matrix *make_sphere(double r, double x, double y, double z);//plots sphere with radius r, and center (x,y,z)
void make_sphere_points(struct matrix * points, double radius);
void make_edge_matrix(struct matrix * points, struct matrix * edges);
struct matrix *make_torus(double R, double r, double x, double y, double z);
void make_torus_points(struct matrix * points, double R, double r);
void make_torus_edges(struct matrix * points, struct matrix * edges);
struct matrix *make_circle(double r, double x, double y, double z);
//struct matrix *make_hermite(int numsteps, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
//struct matrix *make_bezier(int numsteps, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
//double cubic(double a, double b, double c, double d, double t);
//struct matrix *make_good_bezier(int numsteps, struct matrix *inputs);
//struct matrix *bezier_calc(double t, struct matrix *inputs);

#endif
