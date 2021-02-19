#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
//#include "matrix.h"
#include "display.h"
#include "draw.h"

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
	grow_matrix(points, points->cols + 1);
	points->m[0][points->cols - 1] = x;
	points->m[1][points->cols - 1] = y;
	points->m[2][points->cols - 1] = z;
	points->m[3][points->cols - 1] = 1;
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
	int i = 0;
	while (i < points->cols){
		draw_line( points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1], s, c);
		i+= 2;
	}
}

/*======== void add_edge() ==========
 Inputs:   struct matrix * points
 int x0, int y0, int z0, int x1, int y1, int z1
 Returns: 
 add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
 should call add_point
 ====================*/
void add_edge( struct matrix * points, int x0, int y0, int z0, int x1, int y1, int z1) {
	add_point(points, x0, y0, z0);
	add_point(points, x1, y1, z1);
}


/*======== void draw_line() ==========
 Inputs:  int x0
 int y0
 int x1
 int y1
 screen s
 color c 
 Returns: 
 draws the line connecting (x0, y0) to (x1, y1) to screen s using color c
 ====================*/
//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
	
	int x, y, d, dx, dy;
	
	x = x0;
	y = y0;
	
	//swap points so we're always draing left to right
	if ( x0 > x1 ) {
		x = x1;
		y = y1;
		x1 = x0;
		y1 = y0;
	}
	
	//need to know dx and dy for this version
	dx = x1 - x;
	dy = y1 - y;
	
	//positive slope: Octants 1, 2 (5 and 6)
	if ( dy > 0 ) {
		
		//slope < 1: Octant 1 (5)
		if ( dx > dy ) {
			d = 2 * dy - dx;
			
			while ( x < x1 ) {
				plot(s, c, x, y);
				
				if ( d < 0 ) {
					x = x + 1;
					d = d + dy;
				}
				else {
					x = x + 1;
					y = y + 1;
					d = d + dy - dx;
				}
			}
		}
		
		//slope > 1: Octant 2 (6)
		else {
			d = dy - 2 * dx;
			while ( y < y1 ) {
				
				plot(s, c, x, y );
				if ( d > 0 ) {
					y = y + 1;
					d = d - dx;
				}
				else {
					y = y + 1;
					x = x + 1;
					d = d + dy - dx;
				}
			}
		}
	}
	
	//negative slope: Octants 7, 8 (3 and 4)
	else { 
		
		//slope > -1: Octant 8 (4)
		if ( dx > abs(dy) ) {
			d = 2 * dy + dx;
			
			while ( x < x1 ) {
				
				plot(s, c, x, y);
				
				if ( d > 0 ) {
					x = x + 1;
					d = d + dy;
				}
				else {
					x = x + 1;
					y = y - 1;
					d = d + dy + dx;
				}
			}
		}
		
		//slope < -1: Octant 7 (3)
		else {
			
			d = dy + 2 * dx;
			while ( y >= y1 ) {
				
				plot(s, c, x, y );
				if ( d < 0 ) {
					y = y - 1;
					d = d + dx;
				}
				else {
					y = y - 1;
					x = x + 1;
					d = d + dy + dx;
				}
			}
		}
	}
}

struct matrix* render_circle(double r, double x, double y, double t){
	struct matrix * helper;
	helper = new_matrix(4,2);
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

struct matrix* render_sphere(double r, double offx, double offy){
	struct matrix * helper;
	helper = new_matrix(4, 0);
	double t, u;
	for (t = 0; t < 2; t += .05){
		for (u = 0; u < 1; u += .05){
			add_point(helper, r * cos(t * M_PI) * cos(u * M_PI) + offx, r * sin(t * M_PI) + offy, -1 * r * sin(u * M_PI) * cos(t * M_PI));
		}
	}
	//print_matrix(helper);
	//printf("number of cols %i\n", helper->cols);
	
	
	return helper;
}

void generate_sphere(struct matrix * pm, struct matrix * helper){
	//take care of longitude
	int i = 2;
	int j = 0;
	while (j < 40){
		while (i < 21){
			//printf("i: %i j: %i\n", i, j);
			add_point(pm,
					  helper->m[0][20*j + i],
					  helper->m[1][20*j + i],
					  helper->m[2][20*j + i]);
			add_point(pm,
					  helper->m[0][20*j + i+1],
					  helper->m[1][20*j + i+1],
					  helper->m[2][20*j + i+1]);
			i++;
		}
		
		/*		add_point(pm,
		 helper->m[0][20*j+2],
		 helper->m[1][20*j+2],
		 helper->m[2][20*j+2]);
		 add_point(pm,
		 helper->m[0][21*j+2],
		 helper->m[1][21*j+2],
		 helper->m[2][21*j+2]);*/
		i = 2;
		j++;
	}
	
	
	
	i = 2;
	j = 0;
	while (i < 780){
		//printf("i: %i x: %lf y: %lf z: %lf\n", i, helper->m[0][i], helper->m[1][i], helper->m[2][i]);
		add_point(pm,
				  helper->m[0][i],
				  helper->m[1][i],
				  helper->m[2][i]);
		add_point(pm,
				  helper->m[0][i+20],
				  helper->m[1][i+20],
				  helper->m[2][i+20]);
		i++;
	}
	//printf("here we are\n");
}

struct matrix * render_torus(double R, double r, double offx, double offy){
	struct matrix* helper;
	helper = new_matrix(4,2);
	double t, u;
	
	for (t = 0; t < 2; t += .05){
		for (u = 0; u < 2; u += .05){
			add_point(helper,
					  R * cos(t * M_PI) + r * cos(u * M_PI) * cos(t * M_PI) + offx,
					  r * sin(u * M_PI) + offy,
					  -R * sin(t * M_PI) - r * cos(u * M_PI) * sin(t * M_PI));
		}
	}
	return helper;
}

void generate_torus(struct matrix * pm, struct matrix * helper){
	int i = 2;
	int j = 0;
	
	//take care of small circles
	
	while (j < 40){
		while (i < 41){
			add_point(pm,
					  helper->m[0][40 * j + i],
					  helper->m[1][40 * j + i],
					  helper->m[2][40 * j + i]);
			add_point(pm,
					  helper->m[0][40 * j + i+1],
					  helper->m[1][40 * j + i+1],
					  helper->m[2][40 * j + i+1]);
			i++;
		}
		i = 2;
		add_point(pm,
				  helper->m[0][40 * j + 2],
				  helper->m[1][40 * j + 2],
				  helper->m[2][40 * j + 2]);
		add_point(pm,
				  helper->m[0][40 * j + 41],
				  helper->m[1][40 * j + 41],
				  helper->m[2][40 * j + 41]);
		j++;
	}
	//take care of large circles
	i = 2;
	while (i < 40 * 39 + 2){
		add_point(pm,
				  helper->m[0][i],
				  helper->m[1][i],
				  helper->m[2][i]);
		add_point(pm,
				  helper->m[0][i+40],
				  helper->m[1][i+40],
				  helper->m[2][i+40]);
		i++;
	}
	i = 2;
	while (i < 42){
		add_point(pm,
				  helper->m[0][i],
				  helper->m[1][i],
				  helper->m[2][i]);
		add_point(pm,
				  helper->m[0][i + 39 * 40],
				  helper->m[1][i + 39 * 40],
				  helper->m[2][i + 39 * 40]);
		
		i++;
	}
}

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

void generate_box(struct matrix *pm, struct matrix *helper) {
	int i;
	for (i = 0; i < 24; i++) {
		add_point(pm, helper->m[0][i], helper->m[1][i], helper->m[2][i]);
	}
}

/*
void generate_hermite(struct matrix * pm, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double p4x, double p4y){
	double ax, bx, cx, dx, ay, by, cy, dy;
	struct matrix * assistant = new_matrix(4,4);
	//prepare inverted matrix
	assistant->m[0][0] = 2;
	assistant->m[1][0] = -3;
	assistant->m[2][0] = 0;
	assistant->m[3][0] = 1;
	assistant->m[0][1] = -2;
	assistant->m[1][1] = 3;
	assistant->m[2][1] = 0;
	assistant->m[3][1] = 0;
	assistant->m[0][2] = 1;
	assistant->m[1][2] = -2;
	assistant->m[2][2] = 1;
	assistant->m[3][2] = 0;
	assistant->m[0][3] = 1;
	assistant->m[1][3] = -1;
	assistant->m[2][3] = 0;
	assistant->m[3][3] = 0;
	//print_matrix(assistant);
	
	//find a,b,c,d for x-coordinates
	struct matrix * holder = new_matrix(4,1);
	holder->m[0][0] = p1x;
	holder->m[1][0] = p3x;
	holder->m[2][0] = p2x - p1x;
	holder->m[3][0] = p4x - p3x;
	
	print_matrix(holder);
	matrix_mult(assistant, holder);
	print_matrix(holder);
	
	ax = holder->m[0][0];
	bx = holder->m[1][0];
	cx = holder->m[2][0];
	dx = holder->m[3][0];
	
	printf("ax: %lf bx: %lf cx: %lf dx: %lf\n", ax, bx, cx, dx);
	
	//find a,b,c,d for y-coordinates
	holder->m[0][0] = p1y;
	holder->m[1][0] = p3y;
	holder->m[2][0] = p2y - p1y;
	holder->m[3][0] = p4y - p3y;
	
	matrix_mult(assistant, holder);
	
	ay = holder->m[0][0];
	by = holder->m[1][0];
	cy = holder->m[2][0];
	dy = holder->m[3][0];
	
	printf("ay: %lf by: %lf cy: %lf dy: %lf\n", ay, by, cy, dy);
	
	double t = 0;
	//add points
	while (t < 1){
		//printf("x: %lf y: %lf\n", ax * t * t * t + bx * t * t + cx * t + dx, ay * t * t * t + by * t * t + cy * t + dy);
		add_point(pm,
				  ax * t * t * t + bx * t * t + cx * t + dx,
				  ay * t * t * t + by * t * t + cy * t + dy,
				  0);
		t+= .05;
		add_point(pm,
				  ax * t * t * t + bx * t * t + cx * t + dx,
				  ay * t * t * t + by * t * t + cy * t + dy,
				  0);
		
	}
}

*/

/*
void *make_hermite(struct matrix* pm, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	double ax, bx, cx, dx, ay, by, cy, dy, mx1, my1, mx2, my2;
	mx1 = (x2 - x1);
	my1 = (y2 - y1);
	mx2 = (x4 - x3);
	my2 = (y4 - y3);
	struct matrix *H = new_matrix(4,4);
	struct matrix *temp = new_matrix(4,1);
	struct matrix *edges = new_matrix(4,2*numsteps);
	H->m[0][0] = 2;
	H->m[0][1] = -2;
	H->m[0][2] = 1;
	H->m[0][3] = 1;
	H->m[1][0] = -3;
	H->m[1][1] = 3;
	H->m[1][2] = -2;
	H->m[1][3] = -1;
	H->m[2][0] = 0;
	H->m[2][1] = 0;
	H->m[2][2] = 1;
	H->m[2][3] = 0;
	H->m[3][0] = 1;
	H->m[3][1] = 0;
	H->m[3][2] = 0;
	H->m[3][3] = 0;
	temp->m[0][0] = x1;
	temp->m[1][0] = x3;
	temp->m[2][0] = mx1;
	temp->m[3][0] = mx2;
	matrix_mult(H,temp);
	ax = temp->m[0][0];
	bx = temp->m[1][0];
	cx = temp->m[2][0];
	dx = temp->m[3][0];
	temp->m[0][0] = y1;
	temp->m[1][0] = y3;
	temp->m[2][0] = my1;
	temp->m[3][0] = my2;
	matrix_mult(H,temp);
	ay = temp->m[0][0];
	by = temp->m[1][0];
	cy = temp->m[2][0];
	dy = temp->m[3][0];
	
	double t = .01;
	int i;
	//printf("Our coefficients are: ax = %f, bx = %f, cx = %f, dx = %f, ay = %f, by = %f, cy = %f, dy = %f\n", ax,bx,cx,dx,ay,by,cy,dy);
	for (i = 0; i < numsteps; i++) {
		add_edge(pm, cubic(ax,bx,cx,dx,i*t), cubic(ay,by,cy,dy,i*t), 0, cubic(ax,bx,cx,dx,(i+1)*t), cubic(ay,by,cy,dy,(i+1)*t), 0);
	}
	return edges;
}

double cubic(double a, double b, double c, double d, double t) {
	double result = a*t*t*t + b*t*t + c*t + d;
	return result;
}

void generate_hermite(struct matrix* pm, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	double ax, bx, cx, dx, ay, by, cy, dy, mx1, my1, mx2, my2;
	mx1 = (x2 - x1);
	my1 = (y2 - y1);
	mx2 = (x4 - x3);
	my2 = (y4 - y3);
	struct matrix *H = new_matrix(4,4);
	struct matrix *temp = new_matrix(4,1);
	//struct matrix *edges = new_matrix(4,2);
	H->m[0][0] = 2;
	H->m[0][1] = -2;
	H->m[0][2] = 1;
	H->m[0][3] = 1;
	H->m[1][0] = -3;
	H->m[1][1] = 3;
	H->m[1][2] = -2;
	H->m[1][3] = -1;
	H->m[2][0] = 0;
	H->m[2][1] = 0;
	H->m[2][2] = 1;
	H->m[2][3] = 0;
	H->m[3][0] = 1;
	H->m[3][1] = 0;
	H->m[3][2] = 0;
	H->m[3][3] = 0;
	temp->m[0][0] = x1;
	temp->m[1][0] = x3;
	temp->m[2][0] = mx1;
	temp->m[3][0] = mx2;
	matrix_mult(H,temp);
	ax = temp->m[0][0];
	bx = temp->m[1][0];
	cx = temp->m[2][0];
	dx = temp->m[3][0];
	temp->m[0][0] = y1;
	temp->m[1][0] = y3;
	temp->m[2][0] = my1;
	temp->m[3][0] = my2;
	matrix_mult(H,temp);
	ay = temp->m[0][0];
	by = temp->m[1][0];
	cy = temp->m[2][0];
	dy = temp->m[3][0];
	
	double t = .01;
	int i;
	//printf("Our coefficients are: ax = %f, bx = %f, cx = %f, dx = %f, ay = %f, by = %f, cy = %f, dy = %f\n", ax,bx,cx,dx,ay,by,cy,dy);
	for (i = 0; i < 100; i++) {
		add_edge(pm, cubic(ax,bx,cx,dx,i*t), cubic(ay,by,cy,dy,i*t), 0, cubic(ax,bx,cx,dx,(i+1)*t), cubic(ay,by,cy,dy,(i+1)*t), 0);
	}
	//return edges;
}

void generate_bezier(struct matrix* pm, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	double ax, bx, cx, dx, ay, by, cy, dy;
	struct matrix *H = new_matrix(4,4);
	struct matrix *temp = new_matrix(4,1);
	H->m[0][0] = -1;
	H->m[0][1] = 3;
	H->m[0][2] = -3;
	H->m[0][3] = 1;
	H->m[1][0] = 3;
	H->m[1][1] = -6;
	H->m[1][2] = 3;
	H->m[1][3] = 0;
	H->m[2][0] = -3;
	H->m[2][1] = 3;
	H->m[2][2] = 0;
	H->m[2][3] = 0;
	H->m[3][0] = 1;
	H->m[3][1] = 0;
	H->m[3][2] = 0;
	H->m[3][3] = 0;
	temp->m[0][0] = x1;
	temp->m[1][0] = x2;
	temp->m[2][0] = x3;
	temp->m[3][0] = x4;
	matrix_mult(H,temp);
	ax = temp->m[0][0];
	bx = temp->m[1][0];
	cx = temp->m[2][0];
	dx = temp->m[3][0];
	temp->m[0][0] = y1;
	temp->m[1][0] = y2;
	temp->m[2][0] = y3;
	temp->m[3][0] = y4;
	matrix_mult(H,temp);
	ay = temp->m[0][0];
	by = temp->m[1][0];
	cy = temp->m[2][0];
	dy = temp->m[3][0];
	
	double t = .01;
	int i;
	for (i = 0; i < 100; i++) {
		add_edge(pm, cubic(ax,bx,cx,dx,i*t), cubic(ay,by,cy,dy,i*t), 0, cubic(ax,bx,cx,dx,(i+1)*t), cubic(ay,by,cy,dy,(i+1)*t), 0);
	}
}

double cubic(double a, double b, double c, double d, double t) {
	double result = a*t*t*t + b*t*t + c*t + d;
	return result;
}
*/

