#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"


void render_curve( struct matrix *points, double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3, 
                   double x4, double y4, double step)
{
  struct matrix * bezier = make_bezier();
  struct matrix *xm = new_matrix(4,1);
  xm -> m[0][0] = x1;
  xm -> m[1][0] = x3;
  xm -> m[2][0] = x2-x1;
  xm -> m[3][0] = x4-x3;
  struct matrix *ym = new_matrix(4,1);
  ym -> m[0][0] = y1;
  ym -> m[1][0] = y3;
  ym -> m[2][0] = y2-y1;
  ym -> m[3][0] = y4-y3;
  matrix_mult(bezier,xm);
  matrix_mult(bezier,ym);
  double ax, bx, cx, dx;
  double ay, by, cy, dy; 
  ax = xm -> m[0][0];
  bx = xm -> m[1][0];
  cx = xm -> m[2][0];
  dx = xm -> m[3][0];
  ay = ym -> m[0][0];
  by = ym -> m[1][0];
  cy = ym -> m[2][0];
  dy = ym -> m[3][0];
  double t;
  for (t=0; t<=1; t = t+step)
    {
      add_edge(points, ax*pow(t, 3) + bx*pow(t,2) + cx * t +dx,ay*pow(t, 3) + by*pow(t,2) + cy * t +dy,0,ax*pow(t + step, 3) + bx*pow(t + step,2) + cx * (t+step) +dx,ay*pow(t+step, 3) + by*pow(t+step,2) + cy *( t+step) +dy,0);
    }
  free_matrix(xm);
  free_matrix(ym);
  free_matrix(bezier);
}

void render_hcurve( struct matrix *points, double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3, 
                   double x4, double y4, double step) {

  struct matrix * hermite = make_hermite();
  struct matrix *xm = new_matrix(4,1);
  xm -> m[0][0] = x1;
  xm -> m[1][0] = x3;
  xm -> m[2][0] = x2-x1;
  xm -> m[3][0] = x4 - x3;
  struct matrix *ym = new_matrix(4,1);
  ym -> m[0][0] = y1;
  ym -> m[1][0] = y3;
  ym -> m[2][0] = y2-y1;
  ym -> m[3][0] = y4 - y3;
 
 
  matrix_mult(hermite,xm);
  matrix_mult(hermite,ym);
  
  double ax, bx, cx, dx;
  double ay, by, cy, dy;
  
  ax = xm -> m[0][0];
  bx = xm -> m[1][0];
  cx = xm -> m[2][0];
  dx = xm -> m[3][0];
  ay = ym -> m[0][0];
  by = ym -> m[1][0];
  cy = ym -> m[2][0];
  dy = ym -> m[3][0];
  
  double t;
  for (t=0; t<=1; t = t+step)
    {
      add_edge(points, ax*pow(t, 3) + bx*pow(t,2) + cx * t +dx,ay*pow(t, 3) + by*pow(t,2) + cy * t +dy,0,ax*pow(t + step, 3) + bx*pow(t + step,2) + cx * (t+step) +dx,ay*pow(t+step, 3) + by*pow(t+step,2) + cy *( t+step) +dy,0);
    }
  free_matrix(xm);
  free_matrix(ym);
  free_matrix(hermite);
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
void render_torus_mesh( struct matrix *points, double r, double r2,
			 double offx, double offy, double step) {
  double x = 1/step;
  double num_points = x * x;
  int n = x;
  int i,j;
  struct matrix *a = new_matrix(4,num_points);
  generate_torus_mesh(a, r, r2, offx, offy, step);
  for(i=0; i<n;i++)
    {for(j=0; j<n-1; j++)
	{add_edge(points,a->m[0][n*i+j],a->m[1][n*i+j], a->m[2][n*i+j], 
	  a->m[0][n*i+j+1],a->m[1][n*i+j+1], a->m[2][n*i+j+1]);
	}
  add_edge(points,a->m[0][n*i+j],a->m[1][n*i+j], a->m[2][n*i+j], a->m[0][n*i],a->m[1][n*i], a->m[2][n*i]);
  }
for(i=0; i<n; i++)
    {for(j=0; j<n-1; j++)
	{add_edge(points, a->m[0][i+j*n],a->m[1][i+j*n],a->m[2][i+j*n],a->m[0][i+(j+1)*n],a->m[1][i+(j+1)*n],a->m[2][i+(j+1)*n] );
	}
       add_edge(points, a->m[0][i+j*n],a->m[1][i+j*n],a->m[2][i+j*n],a->m[0][i],a->m[1][i],a->m[2][i] );
       }
 free_matrix(a);
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
void generate_torus_mesh( struct matrix *points, double r, double r2,
		     double offx, double offy, double step) {
  
  int i,j;
  double num_points = 1/step;
  for (i = 0; i < num_points; i++)
    {
      for(j=0; j< num_points; j++)
	{
	  add_point(points,r*cos(i*step*2*M_PI)+r2*cos(j*step*2*M_PI)*cos(i*step*2*M_PI)+offx ,r2*sin(j*step*2*M_PI)+offy ,-1*r*sin(i*step*2*M_PI)-r2*cos(j*step*2*M_PI)*sin(i*step*2*M_PI)  );
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
  double x = 1 / step;
  int i,j;
  double num_points = x * x;
  int n = x;
  struct matrix *temp_sphere = new_matrix(4,num_points);
  generate_sphere_mesh(temp_sphere, r, offx, offy, step);
  for(i=0; i<n/2;i++)
    {
      for(j=0; j<n-1; j++)
	{
	  add_edge(edges,temp_sphere->m[0][n*i+j],temp_sphere->m[1][n*i+j], temp_sphere->m[2][n*i+j], 
		   temp_sphere->m[0][n*i+j+1],temp_sphere->m[1][n*i+j+1], temp_sphere->m[2][n*i+j+1]);
	}
      add_edge(edges,temp_sphere->m[0][n*i+j],temp_sphere->m[1][n*i+j], temp_sphere->m[2][n*i+j], temp_sphere->m[0][n*i],temp_sphere->m[1][n*i], temp_sphere->m[2][n*i]);
    }
  for(i=0; i<n; i++)
    {
      for(j=0; j<n-1; j++)
	{add_edge(edges, temp_sphere->m[0][i+j*n],temp_sphere->m[1][i+j*n],temp_sphere->m[2][i+j*n],temp_sphere->m[0][i+(j+1)*n],temp_sphere->m[1][i+(j+1)*n],temp_sphere->m[2][i+(j+1)*n] );
	}
      add_edge(edges, temp_sphere->m[0][i+j*n],temp_sphere->m[1][i+j*n],temp_sphere->m[2][i+j*n],temp_sphere->m[0][i],temp_sphere->m[1][i],temp_sphere->m[2][i] );
    }
  free_matrix(temp_sphere);
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
  int i,j;
  double num_points = 1/step;
  for (i = 0; i < num_points; i++)
    {
      for(j=0; j< num_points; j++)
	{
	  add_point(points,r*cos(j*step*2*M_PI)*cos(i*step*2*M_PI)+offx ,r*sin(j*step*2*M_PI)+offy ,-1*r*cos(j*step*2*M_PI)*sin(i*step*2*M_PI) );
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

  struct matrix *a;
  int i;
  a = new_matrix(4,(int)1/step);
  generate_circle(a, r, offx, offy, step);
  for (i = 0; i < a->lastcol-1; i++) 
    add_edge(points, a->m[0][i], a->m[1][i], a->m[2][i], 
	     a->m[0][i+1], a->m[1][i+1], a->m[2][i+1]);
  add_edge(points, a->m[0][i], a->m[1][i], a->m[2][i], 
	   a->m[0][0], a->m[1][0], a->m[2][0]);
  free_matrix(a);
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

  double a, b, x, y;
  a = r + offx;
  b = offy;
  double i;
  for (i = step; i <= 1; i+= step) {
    x = r*cos(2*M_PI*i) + offx;
    y = r*sin(2*M_PI*i) + offy;
    add_point(points, a, b, 0);
    a = x;
    b = y;
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

  int i, j, tmp;

  //if x0 > x1, swap the points
  if (x0 > x1)
    {
      int tmp = x0;
      x0 = x1;
      x1 = tmp;
      tmp = y0;
      y0 = y1;
      y1 = tmp;
    }

  //Special cases

  //if m = 0 (horizontal line)
  if (y0 == y1)
    {
      for (i=0;(x0+i)<x1;i++)
	  plot(s, c, x0+i,y0);
    }

  //if m is undefined (vertical line)
  if (x0 == x1)
    {
      for (i=0;(y0+i)<y1;i++)
	  plot(s, c, x0,y0+i);
    }

  //Set up decision and calculation variables
  int d = 0; //decision factor lol
  int dx = x1 - x0; //delta x
  int dy = y1 - y0; //delta y

  //m = 1
  if (dx == dy)
    {
      for(i=0;(x0+i)<x1;i++)
	{
	  plot(s,c,x0+i,y0+i);
	}
      return;
    }
  
  //m = -1
  if (dx == -dy)
    {
      for(i=0;(x0+i)<x1;i++)
	{
	  plot(s,c,x0+i,y0-i);
	}
      return;
    }      

  //0<m<1
  if (dx > dy && dy > 0)
    {
      j=0;
      for(i=0;(x0+i)<x1;i++)
	{
	  plot(s,c,x0+i,y0+j);
	  if(d<0)
	    {
	      d=d+dy;
	    }
	  else
	    {
	      j++;
	      d=d+dy-dx;
	    }
	}
      return;
    }

  //-1<m<0
  if (dx > -dy && dy < 0 )
    {
      j=0;
      for(i=0;(x0+i)<x1;i++)
	{
	  plot(s,c,x0+i,y0-j);
	  if(d<0)
	    {
	      d=d-dy;
	    }
	  else
	    {
	      j++;
	      d=d-dy-dx;
	    }
	}
      return;
    }

  //m>1
  if (dy>dx)
    {
      i=0;
      for(j=0;(y0+j)<y1;j++)
	{
	  plot(s,c,x0+i,y0+j);
	  if(d<0)
	    {
	      d=d+dx;
	    }
	  else
	    {
	      i++;
	      d=d+dx-dy;
	    }
	}
      return;
    }

  //m<-1
  if(dx < -dy && dy < 0)
    {
      i=0;
      for(j=0;(y0-j)>y1;j++)
	{
	  plot(s,c,x0+i,y0-j);
	  if(d<0)
	    {
	      d=d+dx;
	    }
	  else
	    {
	      i++;
	      d=d+dx+dy;
	    }
	}
      return;
    }
  
}
