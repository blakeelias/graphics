#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"


void render_bcurve( struct matrix *points, double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3, 
                   double x4, double y4, double step)
{
struct matrix * bezier = new_matrix(4,4);
  bezier -> m[0][0] = -1;
  bezier -> m[1][0] = -3;
 bezier -> m[2][0] = -3;
  bezier -> m[3][0] = 1;
  bezier -> m[0][1] = 3;
  bezier -> m[1][1] = -6;
  bezier -> m[2][1] = 3;
  bezier -> m[3][1] = 0;
  bezier -> m[0][2] = -3;
  bezier -> m[1][2] = 3;
  bezier -> m[2][2] = 0;
  bezier -> m[3][2] = 0;
  bezier -> m[0][3] = 1;
  bezier -> m[1][3] = 0;
  bezier -> m[2][3] = 0;
  bezier -> m[3][3] = 0;

struct matrix *x_matrix = new_matrix(4,1);
  x_matrix -> m[0][0] = x1;
  x_matrix -> m[1][0] = x3;
  x_matrix -> m[2][0] = 3*(x2-x1);
  x_matrix -> m[3][0] = 3*(x4 - x3);
 struct matrix *y_matrix = new_matrix(4,1);
  y_matrix -> m[0][0] = y1;
  y_matrix -> m[1][0] = y3;
  y_matrix -> m[2][0] = 3*(y2-y1);
  y_matrix -> m[3][0] = 3*(y4 - y3);
 
 
  matrix_mult(bezier,x_matrix);
  matrix_mult(bezier,y_matrix);
  
  double a_x, b_x, c_x, d_x;
  double a_y, b_y, c_y, d_y;
  
  a_x = x_matrix -> m[0][0];
  b_x = x_matrix -> m[1][0];
  c_x = x_matrix -> m[2][0];
  d_x = x_matrix -> m[3][0];
  a_y = y_matrix -> m[0][0];
  b_y = y_matrix -> m[1][0];
  c_y = y_matrix -> m[2][0];
  d_y = y_matrix -> m[3][0];
  
  double t;
  for (t=0; t<=1; t = t+step)
    {add_edge(points, a_x*pow(t, 3) + b_x*pow(t,2) + c_x * t +d_x,a_y*pow(t, 3) + b_y*pow(t,2) + c_y * t +d_y,0,a_x*pow(t + step, 3) + b_x*pow(t + step,2) + c_x * (t+step) +d_x,a_y*pow(t+step, 3) + b_y*pow(t+step,2) + c_y *( t+step) +d_y,0);
    }
 
}
//Don't worry about this yet
void render_hcurve( struct matrix *points, double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3, 
                   double x4, double y4, double step) {

struct matrix * hermite = new_matrix(4,4);
  hermite -> m[0][0] = 2;
  hermite -> m[1][0] = -3;
  hermite -> m[2][0] = 0;
  hermite -> m[3][0] = 1;
  hermite -> m[0][1] = -2;
  hermite -> m[1][1] = 3;
  hermite -> m[2][1] = 0;
  hermite -> m[3][1] = 0;
  hermite -> m[0][2] = 1;
  hermite -> m[1][2] = -2;
  hermite -> m[2][2] = 1;
  hermite -> m[3][2] = 0;
  hermite -> m[0][3] = 1;
  hermite -> m[1][3] = 1;
  hermite -> m[2][3] = 0;
  hermite -> m[3][3] = 0;
 
 struct matrix *x_matrix = new_matrix(4,1);
  x_matrix -> m[0][0] = x1;
  x_matrix -> m[1][0] = x3;
  x_matrix -> m[2][0] = x2-x1;
  x_matrix -> m[3][0] = x4 - x3;
 struct matrix *y_matrix = new_matrix(4,1);
  y_matrix -> m[0][0] = y1;
  y_matrix -> m[1][0] = y3;
  y_matrix -> m[2][0] = y2-y1;
  y_matrix -> m[3][0] = y4 - y3;
 
 
  matrix_mult(hermite,x_matrix);
  matrix_mult(hermite,y_matrix);
  
  double a_x, b_x, c_x, d_x;
  double a_y, b_y, c_y, d_y;
  
  a_x = x_matrix -> m[0][0];
  b_x = x_matrix -> m[1][0];
  c_x = x_matrix -> m[2][0];
  d_x = x_matrix -> m[3][0];
  a_y = y_matrix -> m[0][0];
  b_y = y_matrix -> m[1][0];
  c_y = y_matrix -> m[2][0];
  d_y = y_matrix -> m[3][0];
  
  double t;
  for (t=0; t<=1; t = t+step)
    {add_edge(points, a_x*pow(t, 3) + b_x*pow(t,2) + c_x * t +d_x,a_y*pow(t, 3) + b_y*pow(t,2) + c_y * t +d_y,0,a_x*pow(t + step, 3) + b_x*pow(t + step,2) + c_x * (t+step) +d_x,a_y*pow(t+step, 3) + b_y*pow(t+step,2) + c_y *( t+step) +d_y,0);
    }
  //print_matrix(points);
  
  
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
 
int i,j;
  double num_points = 1/step;
  for (i = 0; i < num_points; i++)
    {for(j=0; j< num_points; j++)
	{add_point(points,r*cos(i*step*2*M_PI)+r2*cos(j*step*2*M_PI)*cos(i*step*2*M_PI)+offx ,r2*sin(j*step*2*M_PI)+offy ,-1*r*sin(i*step*2*M_PI)-r2*cos(j*step*2*M_PI)*sin(i*step*2*M_PI)  );
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
			 double offx, double offy, double step) {
  // printf("%lf %lf %lf %lf %lf", r, r2, offx, offy, step);
  double x = 1/step;
  double num_points = x * x;
  int n = x;
  int i,j;
  struct matrix *temp_torus = new_matrix(4,num_points);
  generate_torus_mesh(temp_torus, r, r2, offx, offy, step);
  //for (i=0;i<num_points;i++)
  //{add_edge(points, temp_torus -> m[0][i],temp_torus -> m[1][i],temp_torus -> m[2][i],temp_torus -> m[0][i],temp_torus -> m[1][i],temp_torus -> m[2][i]);}
  for(i=0; i<n;i++)
    {for(j=0; j<n-1; j++)
	{add_edge(points,temp_torus->m[0][n*i+j],temp_torus->m[1][n*i+j], temp_torus->m[2][n*i+j], 
	  temp_torus->m[0][n*i+j+1],temp_torus->m[1][n*i+j+1], temp_torus->m[2][n*i+j+1]);
	}
  add_edge(points,temp_torus->m[0][n*i+j],temp_torus->m[1][n*i+j], temp_torus->m[2][n*i+j], temp_torus->m[0][n*i],temp_torus->m[1][n*i], temp_torus->m[2][n*i]);
  }
for(i=0; i<n; i++)
    {for(j=0; j<n-1; j++)
	{add_edge(points, temp_torus->m[0][i+j*n],temp_torus->m[1][i+j*n],temp_torus->m[2][i+j*n],temp_torus->m[0][i+(j+1)*n],temp_torus->m[1][i+(j+1)*n],temp_torus->m[2][i+(j+1)*n] );
	}
       add_edge(points, temp_torus->m[0][i+j*n],temp_torus->m[1][i+j*n],temp_torus->m[2][i+j*n],temp_torus->m[0][i],temp_torus->m[1][i],temp_torus->m[2][i] );
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
  double x = 1 / step;
  int i,j;
  double num_points = x * x;
  //printf("%lf", num_points);
  int n = x;
  struct matrix *temp_sphere = new_matrix(4,num_points);
  generate_sphere_mesh(temp_sphere, r, offx, offy, step);
  for(i=0; i<n/2;i++)
    {for(j=0; j<n-1; j++)
	{add_edge(edges,temp_sphere->m[0][n*i+j],temp_sphere->m[1][n*i+j], temp_sphere->m[2][n*i+j], 
	  temp_sphere->m[0][n*i+j+1],temp_sphere->m[1][n*i+j+1], temp_sphere->m[2][n*i+j+1]);
	}
  add_edge(edges,temp_sphere->m[0][n*i+j],temp_sphere->m[1][n*i+j], temp_sphere->m[2][n*i+j], temp_sphere->m[0][n*i],temp_sphere->m[1][n*i], temp_sphere->m[2][n*i]);
    }
  for(i=0; i<n; i++)
    {for(j=0; j<n-1; j++)
	{add_edge(edges, temp_sphere->m[0][i+j*n],temp_sphere->m[1][i+j*n],temp_sphere->m[2][i+j*n],temp_sphere->m[0][i+(j+1)*n],temp_sphere->m[1][i+(j+1)*n],temp_sphere->m[2][i+(j+1)*n] );
	}
       add_edge(edges, temp_sphere->m[0][i+j*n],temp_sphere->m[1][i+j*n],temp_sphere->m[2][i+j*n],temp_sphere->m[0][i],temp_sphere->m[1][i],temp_sphere->m[2][i] );
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
  //double theta = 0;
  //double phi = 0;
  int i,j;
  double num_points = 1/step;
  for (i = 0; i < num_points; i++)
    {for(j=0; j< num_points; j++)
	{add_point(points,r*cos(j*step*2*M_PI)*cos(i*step*2*M_PI)+offx ,r*sin(j*step*2*M_PI)+offy ,-1*r*cos(j*step*2*M_PI)*sin(i*step*2*M_PI) );
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
 
  double num_points = 1 / step;
  // printf("%lf\n", num_points);
  struct matrix *temp_circle = new_matrix(4,num_points);
  generate_circle(temp_circle, r,offx, offy, step);
  //print_matrix(temp_circle);
  int i;
  for(i=0; i<temp_circle->cols-1; i++)
    {add_edge
(points,temp_circle->m[0][i],temp_circle->m[1][i], temp_circle->m[2][i], 
temp_circle->m[0][i+1],temp_circle->m[1][i+1], temp_circle->m[2][i+1]);
    }
  add_edge(points,temp_circle->m[0][temp_circle->cols-1],temp_circle->m[1][temp_circle->cols-1], temp_circle->m[2][temp_circle->cols-1], temp_circle->m[0][0],temp_circle->m[1][0], temp_circle->m[2][0]);
  //print_matrix(points);
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
  // printf("%lf %lf %lf %lf", r, offx, offy, step);
  //print_matrix(points);
  int i = 0;
  double angle_counter=0;
  
  for(i=0; i<points->cols; i++)
    {add_point(points, r*cos(2*angle_counter*M_PI) + offx,r*sin(2*angle_counter*M_PI) + offy,0);
      angle_counter = angle_counter + step;
      
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

