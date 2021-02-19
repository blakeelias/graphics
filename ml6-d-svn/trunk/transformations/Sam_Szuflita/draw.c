#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
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
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
	
	if (x0 == x1 && y0 == y1){
		plot(s, c, x0, y0);
		return;
	}
	
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
			while ( y > y1 ) {
				
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

struct matrix* sphere_points(double offx, double offy, double r){
	struct matrix * points;
	points = new_matrix(4, 2);
	double t, u;
	for (t = 0; t < 2; t += .1){
		for (u = 0; u < 1; u += .1){
			//printf("u:%lf t:%lf\n sin:%lf", u, t, sin(60));
			add_point(points, r * cos(t * M_PI) * sin(u * M_PI) + offx, r * sin(t * M_PI) + offy, r * cos(u * M_PI) * sin(t * M_PI));
		}
	}
	//print_matrix(points);
	
	
	
	return points;
}
















