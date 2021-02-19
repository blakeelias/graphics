#ifndef DRAW_H
#define DRAW_H

void generate_torus_mesh( struct matrix *points, double r1, double r2,
		     double offx, double offy, double step);
void render_torus_mesh( struct matrix *points, double r, double r2,
			double offx, double offy, double step);
void render_sphere_mesh( struct matrix *points, double r,
			 double offx, double offy, double step);
void generate_sphere_mesh( struct matrix *points, double r,
			   double offx, double offy, double step);
void render_circle( struct matrix *points, double r, 
		    double offx, double offy, double step);
void generate_circle(struct matrix *points, double r, 
		    double offx, double offy, double step);
void add_point( struct matrix * points, double x, double y, double z);
void draw_lines( struct matrix * points, screen s, color c);
void add_edge( struct matrix * points, 
	       int x0, int y0, int z0, 
	       int x1, int y1, int z1);
void draw_line(int x0, int y0, int x1, int y1, screen s, color c);
void render_curve( struct matrix *points, double x1, double y1, 
		   double x2, double y2, 
		   double x3, double y3, 
		   double x4, double y4, double step);
void render_hcurve( struct matrix *points, double x1, double y1, 
		   double x2, double y2, 
		   double x3, double y3, 
		   double x4, double y4, double step);
#endif
