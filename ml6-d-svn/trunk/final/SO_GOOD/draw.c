#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"

#define prontv printf

struct matrix *render_box(double x0, double y0, double z0, double lx, double ly, double lz) {
	
	double x1 = x0 + lx;
	double y1 = y0 + ly;
	double z1 = z0 + lz;
	
	struct matrix *m = new_matrix(4, 0);
	
	add_edge(m, x0, y0, z0, x1, y0, z0);
	add_edge(m, x0, y0, z1, x1, y0, z1);
	add_edge(m, x0, y1, z0, x1, y1, z0);
	add_edge(m, x0, y1, z1, x1, y1, z1);
	
	add_edge(m, x0, y0, z0, x0, y1, z0);
	add_edge(m, x1, y0, z0, x1, y1, z0);
	add_edge(m, x0, y0, z1, x0, y1, z1);
	add_edge(m, x1, y0, z1, x1, y1, z1);
	
	add_edge(m, x0, y0, z0, x0, y0, z1);
	add_edge(m, x1, y0, z0, x1, y0, z1);
	add_edge(m, x0, y1, z0, x0, y1, z1);
	add_edge(m, x1, y1, z0, x1, y1, z1);
	
	return m;	
}

void draw_sphere(struct matrix *points,
				 double x, double y, double r) {
	double phi, theta, step;
	int nsteps = 32;
	double xcor, ycor, zcor;
	
	struct matrix *sphere_points = new_matrix(4, 0);
	
	step = 2 * M_PI / nsteps;
	for (phi = 0; phi <= M_PI + step; phi += step) {
		for (theta = 0; theta < 2 * M_PI; theta += step) {
			xcor = r * cos(theta) * cos(phi) + x;
			ycor = r * sin(theta) + y;
			zcor = -r * cos(theta) * sin(phi);
			//add_point(sphere_points, xcor, ycor, zcor);
			add_point(points, xcor, ycor, zcor);
			add_point(points, xcor, ycor, zcor);
		}
	}
	
	//connect_dots(sphere_points, points, nsteps, nsteps/2);
}

void draw_torus(struct matrix *points,
				double x, double y, double R, double r) {
	double phi, theta, step;
	int nsteps = 32;
	double xcor, ycor, zcor;
	
	struct matrix *torus_points = new_matrix(4, 0);
	
	step = 2 * M_PI / nsteps;
	for (phi = 0; phi <= 2 * M_PI + step; phi += step) {
		for (theta = 0; theta < 2 * M_PI; theta += step) {
			xcor = r * cos(theta) * cos(phi) + R * cos(phi) + x;
			ycor = r * sin(theta) + y;
			zcor = -r * cos(theta) * sin(phi) - R * sin(phi);
			//add_point(torus_points, xcor, ycor, zcor);
			add_point(points, xcor, ycor, zcor);
			add_point(points, xcor, ycor, zcor);
		}
	}
	
	//connect_dots(torus_points, points, nsteps, nsteps);
}


void connect_dots(struct matrix *sphere_points, struct matrix *points, int nsteps_lat, int nsteps_lon) {
	int lon, lat;
	//printf("%d points\n", sphere_points->lastcol);
	for (lon = 0; lon < nsteps_lon; lon++) {
		for (lat = 0; lat < nsteps_lat - 1; lat++) {
			add_edge(points,
					 sphere_points->m[0][lon*nsteps_lat+lat], sphere_points->m[1][lon*nsteps_lat+lat], sphere_points->m[2][lon*nsteps_lat+lat],
					 sphere_points->m[0][lon*nsteps_lat+lat+1], sphere_points->m[1][lon*nsteps_lat+lat+1], sphere_points->m[2][lon*nsteps_lat+lat+1]);
		}
		add_edge(points,
				 sphere_points->m[0][lon*nsteps_lat+lat], sphere_points->m[1][lon*nsteps_lat+lat], sphere_points->m[2][lon*nsteps_lat+lat],
				 sphere_points->m[0][lon*nsteps_lat], sphere_points->m[1][lon*nsteps_lat], sphere_points->m[2][lon*nsteps_lat]);
	}
	
	for (lat = 0; lat < nsteps_lat; lat++) {
		for (lon = 0; lon < nsteps_lon; lon++) {
			add_edge(points,
					 sphere_points->m[0][lon*nsteps_lat+lat], sphere_points->m[1][lon*nsteps_lat+lat], sphere_points->m[2][lon*nsteps_lat+lat],
					 sphere_points->m[0][(lon+1)*nsteps_lat+lat], sphere_points->m[1][(lon+1)*nsteps_lat+lat], sphere_points->m[2][(lon+1)*nsteps_lat+lat]);
		}
	}
}

void render_parametric(struct matrix * points, 
					   double func_x(double t),
					   double func_y(double t), double step) {
	
	double t = 0;
	double x0, y0, x1, y1;
	
	x0 = func_x(t);
	y0 = func_y(t);
	
	for (t=step; t <= 1.0; t+=step) {
		
		x1 = func_x(t);
		y1 = func_y(t);
		prontv("t: %lf\t x: %lf\t y: %lf\n", t, x1, y1);
		add_edge(points, x0, y0, 0, x1, y1, 0);
		
		x0 = x1;
		y0 = y1;
	}
	
	add_edge(points, x0, y0, 0, func_x(0), func_y(0), 0);
}



/*======== void add_point() ==========
 Inputs:   struct matrix * points
 int x
 int y
 int z 
 Returns: 
 adds point (x, y, z) to points and increment points.lastcol
 if points is full, should call grow on points
 ====================*/
void add_point( struct matrix * points, int x, int y, int z) {
	
	if ( points->lastcol == points->cols )
		grow_matrix(points, points->cols + 100);
	
	points->m[0][points->lastcol] = x;
	points->m[1][points->lastcol] = y;
	points->m[2][points->lastcol] = z;
	points->m[3][points->lastcol] = 1;
	
	points->lastcol++;
}


/*======== void draw_lines() ==========
 Inputs:   struct matrix * points
 screen s
 color c 
 Returns: 
 Go through points 2 at a time and call draw_line to add that line
 to the screen
 ====================*/
void draw_lines( struct matrix * points, screen s, color c) {
	
	int i;
	if ( points->lastcol < 2 ) {
		printf("Need at least 2 points to draw a line!\n");
		return;
	}
	
	for (i=0; i < points->lastcol - 1; i+=2) 
		draw_line(points->m[0][i], points->m[1][i], 
				  points->m[0][i+1], points->m[1][i+1], s, c);
    
    
}

/*======== void add_edge() ==========
 Inputs:   struct matrix * points
 int x0, int y0, int z0, int x1, int y1, int z1
 Returns: 
 add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
 should call add_point
 ====================*/
void add_edge( struct matrix * points, 
			  int x0, int y0, int z0, 
			  int x1, int y1, int z1) {
	
	add_point( points, x0, y0, z0);
	add_point( points, x1, y1, z1);
}

struct matrix* render_circle(double r, double x, double y, double t){
	struct matrix * helper;
	helper = new_matrix(4,0);
	double theta = 0;
	while (theta < 2 * M_PI){
		add_point(helper, r * cos(theta) + x, r * sin(theta) + y, 0);
		theta += t * 2 * M_PI;
	}
	return helper;
}

void generate_circle(struct matrix * pm, struct matrix * helper){
	int i = 2;
	while (i < helper->cols - 1){
		add_point(pm,
				  helper->m[0][i],
				  helper->m[1][i],
				  helper->m[2][i]);
		add_point(pm,
				  helper->m[0][i+1],
				  helper->m[1][i+1],
				  helper->m[2][i+1]);
		i++;
	}
	add_point(pm, helper->m[0][2], helper->m[1][2],helper->m[2][2]);
	add_point(pm, helper->m[0][helper->cols - 1], helper->m[1][helper->cols - 1], helper->m[2][helper->cols - 1]);
}


//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
	int octant = 1;
	
	if (x0 > x1) {
		octant = x1;
		x1 = x0;
		x0 = octant;
		octant = y1;
		y1 = y0;
		y0 = octant;
		octant = 1;
	}
	
	// slope >= 1, octant 2: reflect x and y, then reverse again when plotting
	if (y1-y0 >= x1-x0) {
		octant = x1;
		x1 = y1;
		y1 = octant;
		octant = x0;
		x0 = y0;
		y0 = octant;
		octant = 2;
	}
	
	// -1 < slope < 0, octant 8: negate y coordinates, reflect again when plotting
	else if (y1-y0 <= 0 && y1-y0 >= x0-x1) {
		y0 *= -1;
		y1 *= -1;
		octant = 8;
	}
	
	// slope < -1, octant 7: negate y coordinate then reflect x and y, undo when plotting
	else if (y1-y0 < x0-x1) {
		y0 *= -1;
		y1 *= -1;
		octant = x1;
		x1 = y1;
		y1 = octant;
		octant = x0;
		x0 = y0;
		y0 = octant;
		octant = 7;
	}
	
	int dy = y1-y0;
	int dx = x1-x0;
	int d = 2*dy - dx;
	for (; x0 <= x1; x0++) {
		if (octant == 2)
			plot(s, c, y0, x0);
		else if (octant == 1)
			plot(s, c, x0, y0);
		else if (octant == 8)
			plot(s, c, x0, -y0);
		else if (octant == 7)
			plot(s, c, y0, -x0);
		if (d >= 0) {
			y0++;
			d -= dx;
		}
		d += dy;
	}
}
