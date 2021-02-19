#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"

void render_bes( struct matrix *points, double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3, 
                   double x4, double y4, double step) {
  struct matrix *b = make_bes();
  struct matrix *x = new_matrix(4,1);
  struct matrix *y = new_matrix(4,1);
  double t;
  double ax,bx,cx,dx;
  double ay,by,cy,dy;

  x->m[0][0] = x1;
  x->m[1][0] = x3;
  x->m[2][0] = 3*(x2-x1);
  x->m[3][0] = 3*(x4-x3);
  
  y->m[0][0] = y1;
  y->m[1][0] = y3;
  y->m[2][0] = 3*(y2-y1);
  y->m[3][0] = 3*(y4-y3);
  
  matrix_mult(b,x);
  matrix_mult(b,y);

  ax =  x->m[0][0];
  bx =  x->m[1][0];
  cx =  x->m[2][0];
  dx =  x->m[3][0];

  ay =  y->m[0][0];
  by =  y->m[1][0];
  cy =  y->m[2][0];
  dy =  y->m[3][0];
  
  for(t=0;t<=1;t+=step){
    add_edge(points,ax*pow(t,3)+bx*pow(t,2)+cx*t+dx,ay*pow(t,3)+by*pow(t,2)+cy*t+dy,0,ax*pow(t+step,3)+bx*pow(t+step,2)+cx*(t+step)+dx,ay*pow(t+step,3)+by*pow(t+step,2)+cy*(t+step)+dy,0);
  }
}
  
//Don't worry about this yet
void render_curve( struct matrix *points, double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3, 
                   double x4, double y4, double step) {
  struct matrix *h = make_hermite();
  struct matrix *x = new_matrix(4,1);
  struct matrix *y = new_matrix(4,1);
  double t;
  double ax,bx,cx,dx;
  double ay,by,cy,dy;

  x->m[0][0] = x1;
  x->m[1][0] = x3;
  x->m[2][0] = x2-x1;
  x->m[3][0] = x4-x3;

  y->m[0][0] = y1;
  y->m[1][0] = y3;
  y->m[2][0] = y2-y1;
  y->m[3][0] = y4-y3;

  matrix_mult(h,x);
  matrix_mult(h,y);

  ax =  x->m[0][0];
  bx =  x->m[1][0];
  cx =  x->m[2][0];
  dx =  x->m[3][0];

  ay =  y->m[0][0];
  by =  y->m[1][0];
  cy =  y->m[2][0];
  dy =  y->m[3][0];

  for(t=0;t<=1;t+=step){
    add_edge(points,ax*pow(t,3)+bx*pow(t,2)+cx*t+dx,ay*pow(t,3)+by*pow(t,2)+cy*t+dy,0,ax*pow(t+step,3)+bx*pow(t+step,2)+cx*(t+step)+dx,ay*pow(t+step,3)+by*pow(t+step,2)+cy*(t+step)+dy,0);
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
		     double offx, double offy, double step) {
  double phi,theta;
  for(phi=0;phi<=1;phi+=step){
    for(theta=0;theta<=1;theta+=step){
      add_edge(points,(r+r2*cos(2*M_PI*phi))*cos(2*M_PI*theta),(r+r2*cos(2*M_PI*phi))*sin(2*M_PI*theta),r2*sin(2*M_PI*phi),(r+r2*cos(2*M_PI*(phi+step)))*cos(2*M_PI*theta),(r+r2*cos(2*M_PI*(phi+step)))*sin(2*M_PI*theta),r2*sin(2*M_PI*(phi+step)));
      add_edge(points,(r+r2*cos(2*M_PI*phi))*cos(2*M_PI*theta),(r+r2*cos(2*M_PI*phi))*sin(2*M_PI*theta),r2*sin(2*M_PI*phi),(r+r2*cos(2*M_PI*phi))*cos(2*M_PI*(theta+step)),(r+r2*cos(2*M_PI*phi))*sin(2*M_PI*(theta+step)),r2*sin(2*M_PI*phi));
    }
  }
  struct matrix *t = make_translate(offx,offy,0);
  matrix_mult(t,points);
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
  double phi,theta;
  for(phi=0;phi<=1;phi+=step){
    for(theta=0;theta<=1;theta+=step){
      add_edge(points,(r+r2*cos(2*M_PI*phi))*cos(2*M_PI*theta)+offx,(r+r2*cos(2*M_PI*phi))*sin(2*M_PI*theta)+offy,r2*sin(2*M_PI*phi),(r+r2*cos(2*M_PI*(phi+step)))*cos(2*M_PI*theta)+offx,(r+r2*cos(2*M_PI*(phi+step)))*sin(2*M_PI*theta)+offy,r2*sin(2*M_PI*(phi+step)));
      add_edge(points,(r+r2*cos(2*M_PI*phi))*cos(2*M_PI*theta)+offx,(r+r2*cos(2*M_PI*phi))*sin(2*M_PI*theta)+offy,r2*sin(2*M_PI*phi),(r+r2*cos(2*M_PI*phi))*cos(2*M_PI*(theta+step))+offx,(r+r2*cos(2*M_PI*phi))*sin(2*M_PI*(theta+step))+offy,r2*sin(2*M_PI*phi));
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
  double theta,phi;
  for(phi = 0; phi<=1;phi+=step)
    {
      for(theta = 0; theta<=1; theta+=step)
	{
	  add_edge(edges,r*sin(M_PI*phi)*cos(2*M_PI*theta)+offx,r*sin(M_PI*phi)*sin(2*M_PI*theta)+offy,r*cos(M_PI*phi),r*sin(M_PI*(phi+step))*cos(2*M_PI*(theta))+offx,r*sin(M_PI*(phi+step))*sin(2*M_PI*theta)+offy,r*cos(M_PI*(phi+step)));
	  add_edge(edges,r*sin(M_PI*phi)*cos(2*M_PI*theta)+offx,r*sin(M_PI*phi)*sin(2*M_PI*theta)+offy,r*cos(M_PI*phi),r*sin(M_PI*(phi))*cos(2*M_PI*(theta+step))+offx,r*sin(M_PI*(phi))*sin(2*M_PI*(theta+step))+offy,r*cos(M_PI*(phi)));
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
void generate_sphere_mesh( struct matrix *edges, double r, 
			   double offx, double offy, double step) {
  double theta,phi;
  for(phi = 0; phi<=1;phi+=step)
    {
      for(theta = 0; theta<=1; theta+=step)
	{
	  add_edge(edges,r*sin(M_PI*phi)*cos(2*M_PI*theta),r*sin(M_PI*phi)*sin(2*M_PI*theta),r*cos(M_PI*phi),r*sin(M_PI*(phi+step))*cos(2*M_PI*(theta)),r*sin(M_PI*(phi+step))*sin(2*M_PI*theta),r*cos(M_PI*(phi+step)));
	  add_edge(edges,r*sin(M_PI*phi)*cos(2*M_PI*theta),r*sin(M_PI*phi)*sin(2*M_PI*theta),r*cos(M_PI*phi),r*sin(M_PI*(phi))*cos(2*M_PI*(theta+step)),r*sin(M_PI*(phi))*sin(2*M_PI*(theta+step)),r*cos(M_PI*(phi)));
	}
    }
  struct matrix *t = make_translate(offx,offy,0);
  matrix_mult(t,edges);
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
  for(t = 0; t<=1; t+=step)
    add_edge(points, r*cos(2*M_PI*t)+offx,r*sin(2*M_PI*t)+offy,0,r*cos(2*M_PI*(t+step))+offx,r*sin(2*M_PI*(t+step))+offy,0);

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
  int i;
  for( i = 0; i <= 1; i+=step)
    add_point(points, r * cos(2 * M_PI * i) + offx, r * sin(2 * M_PI * i) + offy, 0);
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

