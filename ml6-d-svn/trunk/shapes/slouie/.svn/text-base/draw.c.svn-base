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
                   double x4, double y4, double step) {
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
		     double offx, double offy, double step) {
  double x,y,z;
  double n=1/step;
  int i,j;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      {
	x=r*cos(j*step*2*M_PI)*cos(i*step*2*M_PI)+r2*cos(i*step*2*M_PI)+offx;
	y=r*sin(j*step*2*M_PI)+offy;
	z=-1*r*cos(j*step*2*M_PI)*sin(i*step*2*M_PI)-r2*sin(i*step*2*M_PI);
	add_point(points,x,y,z);
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
			 double offx, double offy, double step) {
  int i,j;
  int n = 1/step;
  struct matrix * tor = new_matrix(4,n*n);
  generate_torus_mesh(tor,r,r2,offx,offy,step);
  for(i=0;i<n;++i)
    {
      for(j=0;j<n-1;j++)
	{
	
	  add_edge(points,tor->m[0][n*i+j],tor->m[1][n*i+j],
		   tor->m[2][n*i+j],tor->m[0][n*i+j+1],
		   tor->m[1][n*i+j+1],tor->m[2][n*i+j+1]);
	  
       
	  add_edge(points,tor->m[0][n*i+j],tor->m[1][n*i+j],
		   tor->m[2][n*i+j],tor->m[0][n*(i+1)+j],
		   tor->m[1][n*(i+1)+j],tor->m[2][n*(i+1)+j]); 
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
void render_sphere_mesh( struct matrix *edges, double r, 
			 double offx, double offy, double step) {
  
  int i,j;
  int n = 1/step;
  struct matrix * circ = new_matrix(4,n*n);
  generate_sphere_mesh(circ,r,offx,offy,step);
  for(i=0;i<n/2;++i)
    {
      for(j=0;j<n-1;j++)
	{
	  //longitude
	  add_edge(edges,circ->m[0][n*i+j],circ->m[1][n*i+j],
		   circ->m[2][n*i+j],circ->m[0][n*i+j+1],
		   circ->m[1][n*i+j+1],circ->m[2][n*i+j+1]);
	  
	  //latitude
	  add_edge(edges,circ->m[0][n*i+j],circ->m[1][n*i+j],
		   circ->m[2][n*i+j],circ->m[0][n*(i+1)+j],
		   circ->m[1][n*(i+1)+j],circ->m[2][n*(i+1)+j]); 
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
			   double offx, double offy, double step) {
  
  double x,y,z;
  double n=1/step;
  int i,j;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      {
	x=r*cos(j*step*2*M_PI)*cos(i*step*2*M_PI)+offx;
	y=r*sin(j*step*2*M_PI)+offy;
	z=-1*r*cos(j*step*2*M_PI)*sin(i*step*2*M_PI);
	add_point(points,x,y,z);
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
  double i;
  for(i=0;i<=1;i+=step)
    add_edge(points, r * cos(2*M_PI*i)+offx, r * sin(2*M_PI*i)+offy, 0,
	     r * cos(2*M_PI*(i+step)) + offx, r * sin(2*M_PI*(i+step))+offy, 0);
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
  double i,x,y;
  for (i=0;i<1.0;i+=step)
    {
      x=r*cos(step * 2 * M_PI) + offx;
      y=r*sin(step * 2 * M_PI) + offy;
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

