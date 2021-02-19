#ifndef SHAPES_H
#define SHAPES_H

void draw_sphere(struct matrix *points, double x, double y, double z, double r);
void draw_torus(struct matrix *points, double x, double y, double z, double R, double r);
void connect_dots_sphere(struct matrix *sphere_points, struct matrix *points, int nsteps_lat, int nsteps_lon);
void connect_dots_torus(struct matrix *sphere_points, struct matrix *points, int nsteps_lat, int nsteps_lon);
void render_parametric(struct matrix * points, 
		       double (*fucn_x)(double t),
		       double (*fucn_y)(double t), double);
void draw_box(struct matrix *points, double x1, double y1, double z1, double x2, double y2, double z2);

#endif
