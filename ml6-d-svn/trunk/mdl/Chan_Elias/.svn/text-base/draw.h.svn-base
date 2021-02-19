#include "matrix.h"

#ifndef DRAW_H
#define DRAW_H

void draw_sphere(struct matrix *points, double x, double y, double r);
void connect_dots(struct matrix *sphere_points, struct matrix *points, int nsteps_lat, int nsteps_lon);
void render_parametric(struct matrix * points, double (*fucn_x)(double t), double (*fucn_y)(double t), double);
void add_point( struct matrix * points, int x, int y, int z);
void add_polygon(struct matrix * points, int x0, int y0, int z0, int x1, int y1, int z1, int x2, int y2, int z2);
void draw_lines( struct matrix * points, screen s, color c);
void add_edge( struct matrix * points, int x0, int y0, int z0, int x1, int y1, int z1); 
void draw_line(int x0, int y0, int x1, int y1, screen s, color c);
void draw_box(struct matrix *points, double x1, double y1, double z1, double x2, double y2, double z2);
void draw_polygons(struct matrix * points, screen s, color c);
void shade_polygon(int x0, int y0, int x1, int y1, int x2, int y2, screen s, color c);
void shade_triangle(int x0, int y0, int x1, int y1, int x2, int y2, screen s, color c); 
void draw_vert(int y0, y1, x, screen s, color c);
#endif
