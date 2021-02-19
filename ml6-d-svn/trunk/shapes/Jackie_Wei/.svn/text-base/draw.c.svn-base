#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"


//Don't worry about this yet
void render_curve( struct matrix *points, double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3, 
                   double x4, double y4) {

  double t, xa, xb, xc, xd, ya, yb, yc, yd;
  struct matrix *xt = new_matrix(4,1);
  struct matrix *yt = new_matrix(4,1);
  struct matrix *hm = new_matrix(3, 8);
  xt->m[0][0] = x1;
  xt->m[1][0] = x3;
  xt->m[2][0] = x2 - x1;
  xt->m[3][0] = x4 - x3;
  yt->m[0][0] = y1;
  yt->m[1][0] = y3;
  yt->m[2][0] = y2 - y1;
  yt->m[3][0] = y4 - y3;

  matrix_mult(hm, xt);
  matrix_mult(hm, yt);

  xa =  xt->m[0][0];
  xb =  xt->m[1][0];
  xc =  xt->m[2][0];
  xd =  xt->m[3][0];
  ya =  yt->m[0][0];
  yb =  yt->m[1][0];
  yc =  yt->m[2][0];
  yd =  yt->m[3][0];

  double step = 0.05;

  for(t = 0; t<= 1; t += step){
    double u = t + step;
    double x = xa * (t*t*t) + xb * (t*t) + xc * t + xd;
    double y = ya * (t*t*t) + yb * (t*t) + yc * t + yd;
    double xx = xa * (u*u*u) + xb * (u*u) + xc * u + xd;
    double yy = ya * (u*u*u) + yb * (u*u) + yc *u + yd;
    add_edge(points, x, y, 0, xx, yy, 0);
  }
}

/*======== void render_torus_mesh() ==========
Inputs:   struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Calls generate_torus_mesh to get the points on the surface of a torus.
Calls add_edge to add the necesary lines to edges to draw a torus

03/21/11 12:45:10
jdyrlandweaver
====================*/    
void generate_torus_mesh( struct matrix *points, double r, double r2,
		     double offx, double offy) {

  double t, p, step;
  step = 0.05;
  for(p = 0; p <= 1; p += step){
    for(t = 0; t <= 1; t += step){
      double x = r2 * cos(2*M_PI*p) + r * cos(2*M_PI*t) * cos(2*M_PI*p) + offx;
      double y = r * sin(2*M_PI*t) + offy;
      double z = -1 * r2 * sin(2*M_PI*p) - r * cos(2*M_PI*t) * sin(2*M_PI*p);
      double xx = r2 * cos(2*M_PI*(p + step)) + r * cos(2*M_PI*t) * cos(2*M_PI*(p + step)) + offx;
      double yy = r * sin(2*M_PI*t) + offy;
      double zz = -1 * r2 * sin(2*M_PI*(p + step)) - r * cos(2*M_PI*t) * sin(2*M_PI*(p + step));
      double x1 = r2 * cos(2*M_PI*p) + r * cos(2*M_PI*(t + step)) * cos(2*M_PI*p) + offx;
      double y1 = r * sin(2*M_PI*(t + step)) + offy;
      double z1 = -1 * r2 * sin(2*M_PI*p) - r * cos(2*M_PI*(t + step)) * sin(2*M_PI*p);
      add_edge(points, x, y, z, xx, yy, zz);
      add_edge(points, x, y, z, x1, y1, z1);
    }
  }
}
    
/*======== void generate_torus_mesh() ==========
Inputs:   struct matrix *points
         double r
	 double r2
         double offx
         double offy
         double step 
Returns: 
Generates the points on the surface of the sphere
with circle radius r, offset radius r2
and center (offx, offy), stores them in points.

03/21/11 12:45:10
jdyrlandweaver
====================*/
void render_torus_mesh( struct matrix *points, double r, double r2,
			 double offx, double offy) {
  double t, p, step;
  step = 0.05;
  for(p = 0; p <= 1; p += step){
    for(t = 0; t <= 1; t += step){
      double x = r2 * cos(2*M_PI*p) + r * cos(2*M_PI*t) * cos(2*M_PI*p) + offx;
      double y = r * sin(2*M_PI*t) + offy;
      double z = -1 * r2 * sin(2*M_PI*p) - r * cos(2*M_PI*t) * sin(2*M_PI*p);
      add_point(points, x, y, z);
    }
  }
}

/*======== void render_sphere_mesh() ==========
Inputs:   struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Calls generate_sphere_mesh to get the points on the surface of a sphere.
Calls add_edge to add the necesary lines to edges to draw a sphere

03/21/11 12:45:10
jdyrlandweaver
====================*/    
void render_sphere_mesh( struct matrix *points, double r, 
			 double offx, double offy) {
  double t, p, step;
  step = 0.05;
  for(p = 0; p <= 1; p += step){
    for(t = 0; t <= 1; t += step){
      double x = r * cos(2*M_PI*t) * cos(M_PI*p) + offx;
      double y = r * sin(2*M_PI*t) + offy;
      double z = -1 * r * sin(2*M_PI*t) * cos(2*M_PI*t);
      double xx = r * cos(2*M_PI*(t + step)) * cos(M_PI*p) + offx;
      double yy = r * sin(2*M_PI*(t + step)) + offy;
      double zz = -1 * r * sin(2*M_PI*(t + step)) * cos(2*M_PI*(t + step));
      double x1 = r * cos(2*M_PI*t) * cos(M_PI*(p + step)) + offx;
      double y1 = r * sin(2*M_PI*t) + offy;
      double z1 = -1 * r * sin(2*M_PI*t) * cos(2*M_PI*t);
      add_edge(points, x, y, z, xx, yy, zz);
      add_edge(points, x, y, z, x1, y1, z1);
    }
  }
}
    
/*======== void generate_sphere_mesh() ==========
Inputs:   struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Generates the points on the surface of the sphere
with radius r and center (offx, offy), stores them in points.

03/21/11 12:45:10
jdyrlandweaver
====================*/
void generate_sphere_mesh( struct matrix *points, double r, 
			   double offx, double offy) {
  double t, p;
  for(p = 0; p <= 1; p += .05){
    for(t = 0; t <= 1; t += .05){
      double x = r * cos(2*M_PI*t) * cos(M_PI*p) + offx;
      double y = r * sin(2*M_PI*t) + offy;
      double z = -1 * r * sin(2*M_PI*t) * cos(2*M_PI*t);
      add_point(points, x, y, z);
    }
  }
}

/*======== void render_circle() ==========
Inputs:   struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Uses generate_circle to create the points necessary for a circle.
Calls add_edge to create the lines necessary from the given points
03/15/10 19:37:43
jonalf
====================*/
void render_circle( struct matrix *points, double r, 
		    double offx, double offy, double step) {
  double t;
  for(t = 0; t <= 1; t += step){
    double x = r * cos(2*M_PI*t) + offx;
    double y = r * sin(2*M_PI*t) + offy;
    double xx = r * cos(2*M_PI*(t + step)) + offx;
    double yy = r * sin(2*M_PI*(t + step)) + offy;
    add_edge(points, x, y, 0, xx, yy, 0);
  }
} 
	     

/*======== void  generate_circle() ==========
Inputs:  struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Generates the points required for a circle 

03/15/10 19:11:13
jonalf
====================*/
void  generate_circle(struct matrix *points, double r, 
		    double offx, double offy, double step) {

  double t;
  for(t = 0; t <= 1; t += step){
    double x = r * cos(2*M_PI*t) + offx;
    double y = r * sin(2*M_PI*t) + offy;
    add_point(points, x, y, 0);
  }
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
void add_point( struct matrix * points, double x, double y, double z) {

  if ( points->lastcol == points->cols )
    grow_matrix(points, points->lastcol + 100);

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
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {

  add_point( points, x0, y0, z0);
  add_point( points, x1, y1, z1);
}

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

