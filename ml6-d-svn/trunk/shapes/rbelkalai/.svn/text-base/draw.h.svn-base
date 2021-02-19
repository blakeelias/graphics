#ifndef DRAW_H
#define DRAW_H

void add_point( struct matrix * points, double x, double y, double z);
void draw_lines( struct matrix * points, screen s, color c);
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1);
void draw_line(int x0, int y0, int x1, int y1, screen s, color c);
struct matrix *points_in_bounds (double X0, double Y0, double X1, double Y1);
int inBounds (double x0, double y0);
void make_sphere(screen s, color c, double r, int numsteps, double x, double y, double z);//plots sphere with radius r, and center (x,y,z)
void make_sphere_points(struct matrix * points, double radius, int numsteps);
void make_edge_matrix(struct matrix * points, struct matrix * edges, int numsteps);
void make_torus(screen s, color c, double R, double r, int numsteps, double x, double y, double z);
void make_torus_points(struct matrix * points, double R, double r, int numsteps);
void make_torus_edges(struct matrix * points, struct matrix * edges, int numsteps);
#endif
