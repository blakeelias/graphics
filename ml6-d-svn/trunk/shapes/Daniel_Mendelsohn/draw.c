#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"

//#define K 100

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point(struct matrix * points, double x, double y, double z) {
  points->lastcol++;
  if (points->lastcol >= points->cols) {
    grow_matrix(points, points->lastcol+1);
  }
  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;
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
  struct matrix *endpoints;
  if ((points->lastcol + 1) % 2 == 1)
    printf("Odd number of points, ignoring last point\n");
  int i;
  for (i = 0; i < points->lastcol+1; i+=2) {
    endpoints = points_in_bounds(points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1]);
    draw_line(endpoints->m[0][0], endpoints->m[1][0], endpoints->m[0][1], endpoints->m[1][1],s,c);
  }
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
aReturns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should call add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points,x0,y0,z0);
  add_point(points,x1,y1,z1);
}

/*======== int inBounds()=============
Inputs: double x0
        double y0
Returns: 1 if (x0,y0) is in bounds, 0 otherwise
===================================*/
int inBounds(double x0, double y0) {
  if (x0 >= 0 && y0 >= 0 && x0 <= XRES - 1 && y0 <= YRES - 1)
    return 1;
  return 0;
}

/*======= struct matrix *points_in_bounds() =======
Inputs: double X0
        double Y0
	double X1
	double Y1
Returns: 2 by 2 matrix with new x-values in first row and new y-values in second row
Takes in endpoints of our desired line and returns a matrix containing the endpoints of the segment
of the same line that falls within our screen
===============================================================*/
struct matrix *points_in_bounds (double X0, double Y0, double X1, double Y1) {
  struct matrix *endpoints = new_matrix(2,2);
  double x0,y0,x1,y1;

  endpoints->m[0][0] = -1;
  endpoints->m[1][0] = -1;
  endpoints->m[0][1] = -1;
  endpoints->m[1][1] = -1;

  if (X0 == X1) {
    if (Y0 < Y1) {
      x0 = X0;
      x1 = X1;
      y0 = Y0;
      y1 = Y1;
    }
    else {
      x0 = X1;
      x1 = X0;
      y0 = Y1;
      y1 = Y0;
    }
  }
  else {
    if (X0 < X1) {
      x0 = X0;
      x1 = X1;
      y0 = Y0;
      y1 = Y1;
    }
    else {
      x0 = X1;
      x1 = X0;
      y0 = Y1;
      y1 = Y0;
    }
  }

  if (inBounds(x0,y0) && inBounds(x1,y1)) {
    endpoints->m[0][0] = x0;
    endpoints->m[1][0] = y0;
    endpoints->m[0][1] = x1;
    endpoints->m[1][1] = y1;
    return endpoints;
  }

  if (inBounds(x0,y0) && !inBounds(x1,y1)) {
    endpoints->m[0][0] = x0;
    endpoints->m[1][0] = y0;
    if (x0 == x1) {
      endpoints->m[0][1] = x1;
      endpoints->m[1][1] = YRES-1;
    }
    else {
      if (y0 == y1) {
	endpoints->m[0][1] = XRES-1;
	endpoints->m[1][1] = y1;
      }
      else {
	double top, bottom, right, m;
	m = (y1- y0)/(x1-x0);
	top = x0 + ((YRES - 1 - y0)/m);
	bottom = x0 - (y0/m);
	right = m * (XRES - 1 - x0) + y0;
	if (right >= 0 && right <= YRES-1) {
	  endpoints->m[0][1] = XRES-1;
	  endpoints->m[1][1] = right;
	}
	else {
	  if (m > 0) {
	    endpoints->m[0][1] = top;
	    endpoints->m[1][1] = YRES-1;
	  }
	  else {
	    endpoints->m[0][1] = bottom;
	    endpoints->m[1][1] = 0;
	  }
	}
      }
    }
    return endpoints;
  }
  
  if (inBounds(x1,y1) && !inBounds(x0,y0)) {
    endpoints->m[0][1] = x1;
    endpoints->m[1][1] = y1;
    if (x0 == x1) {
      endpoints->m[0][0] = x0;
      endpoints->m[1][0] = 0;
    }
    else {
      if (y0 == y1) {
	endpoints->m[0][0] = 0;
	endpoints->m[1][0] = y0;
      }
      else {
	double top, bottom, left, m;
	m = (y1- y0)/(x1-x0);
	top = x0 + ((YRES - 1 - y0)/m);
	bottom = x0 - (y0/m);
	left = y0 - m * x0;
	if (left >= 0 && left <= YRES-1) {
	  endpoints->m[0][0] = 0;
	  endpoints->m[1][0] = left;
	}
	else {
	  if (m < 0) {
	    endpoints->m[0][0] = top;
	    endpoints->m[1][0] = YRES-1;
	  }
	  else {
	    endpoints->m[0][0] = bottom;
	    endpoints->m[1][0] = 0;
	  }
	}
      }
    }
    return endpoints;
  }
  
  if (x1 >= 0 && x0 <= XRES-1 && ((y0 > 0) || (y1 > 0)) && ((y0 < YRES-1) || (y1 < YRES-1))) {
    if (x0 == x1) {
      endpoints->m[0][0] = x0;
      endpoints->m[1][0] = 0;
      endpoints->m[0][1] = x1;
      endpoints->m[1][1] = YRES-1;
    }
    else {
      if (y0 == y1) {
	endpoints->m[0][0] = 0;
	endpoints->m[1][0] = y0;
	endpoints->m[0][1] = XRES-1;
	endpoints->m[1][1] = y1;
      }
      else {
	double left,right,top,bottom, m;
	m = (y1-y0) / (x1-x0);
	//printf("Slope of line is %f\n", m);

	left = y0 - m * x0;
	if (left >= 0 && left <= YRES-1) {
	  if (endpoints->m[0][0] == -1) {
	    endpoints->m[0][0] = 0;
	    endpoints->m[1][0] = left;
	  }
	  else {
	    endpoints->m[0][1] = 0;
	    endpoints->m[1][1] = left;
	  }
	}
	
	right = m * (XRES - 1 - x0) + y0;
	if (right >= 0 && right <= YRES-1) {
	  if (endpoints->m[0][0] == -1) {
	    endpoints->m[0][0] = XRES-1;
	    endpoints->m[1][0] = right;
	  }
	  else {
	    endpoints->m[0][1] = XRES-1;
	    endpoints->m[1][1] = right;
	  }
	}
	
	bottom = x0 - (y0/m);
	if (bottom >= 0 && bottom <= XRES-1) {
	  if (endpoints->m[0][0] == -1) {
	    endpoints->m[0][0] = bottom;
	    endpoints->m[1][0] = 0;
	  }
	  else {
	    endpoints->m[0][1] = bottom;
	    endpoints->m[1][1] = 0;
	  }
	}
	
	top = x0 + ((YRES - 1 - y0)/m);
	if (top >= 0 && top <= XRES-1) {
	  if (endpoints->m[0][0] == -1) {
	    endpoints->m[0][0] = top;
	    endpoints->m[1][0] = YRES-1;
	  }
	  else {
	    endpoints->m[0][1] = top;
	    endpoints->m[1][1] = YRES-1;
	  }
	} 
      }
    }
  }
  if (endpoints->m[1][1] == -1) {
    endpoints->m[0][0] = 0;
    endpoints->m[1][0] = 0;
    endpoints->m[0][1] = 0;
    endpoints->m[1][1] = 0;
  }
  return endpoints;
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
void draw_line(int X0, int Y0, int X1, int Y1, screen s, color c) {
  int x0,x1,y0,y1,x,y;
  double m,d;
  if (X0 < X1) {
    x0 = X0;
    y0 = Y0;
    x1 = X1;
    y1 = Y1;
  }
  else {
    x0 = X1;
    y0 = Y1;
    x1 = X0;
    y1 = Y0;
  }
  if (x0 == x1) {
    y = y0;
    if (y0 < y1) {
      while (y <= y1) {
	plot(s,c,x0,y);
	y++;
      }
    }
    else {
      while (y >= y1) {
	plot(s,c,x0,y);
	y--;
      }
    }
  }
  else {
    m = ((double)y1 - (double)y0) / ((double)x1 - (double)x0);
    d = 0;
    x = x0;
    y = y0;
    if (m >= 0 && m <=1) {
      while (x <= x1) {
	if (d <= .5) {
	  plot(s,c,x,y);
	}
	else {
	  y++;
	  d--;
	  plot(s,c,x,y);
	}
	x++;
	d = d + m;
      }
    }
    else {
      if (m < 0 && m >= -1) {
	while (x <= x1) {
	  if (d >= -.5)
	    plot(s,c,x,y);
	  else {
	    y--;
	    d++;
	    plot(s,c,x,y);
	  }
	  x++;
	  d = d + m;
	}
      }
      else {
	if (m >1) {
	  while (y <= y1) {
	    if (d <= .5)
	      plot(s,c,x,y);
	    else {
	      x++;
	      d--;
	      plot(s,c,x,y);
	    }
	    y++;
	    d = d + (1/m);
	  }
	}
	else {
	  while (y >= y1) {
	    if (d <= .5)
	      plot(s,c,x,y);
	    else {
	      x++;
	      d--;
	      plot(s,c,x,y);
	    }
	    y--;
	    d = d - (1/m);
	  }
	}
      }
    }
  }
}

struct matrix *make_sphere(double r, int numsteps, double x, double y, double z) {//plots sphere with radius r, and center (x,y,z)
  struct matrix *points = new_matrix(4, numsteps*numsteps);
  struct matrix *edges = new_matrix(4, 4*numsteps*numsteps);
  make_sphere_points(points,r,numsteps);
  make_edge_matrix(points,edges,numsteps);
  struct matrix *trans = make_translate(x,y,z);
  matrix_mult(trans,edges);
  return edges;
}

void make_sphere_points(struct matrix * points, double radius, int numsteps) {
  double theta_incr = M_PI/numsteps;
  double phi_incr = 2*M_PI/numsteps;
  double r = radius;
  int i,j;
  for (i = 0; i < numsteps; i++) {
    for (j = 0; j < numsteps; j++) {
      add_point(points, r*cos(i*theta_incr-(M_PI/2))*cos(j*phi_incr), r*sin(i*theta_incr-(M_PI/2)), r*cos(i*theta_incr-(M_PI/2))*sin(j*phi_incr));
    }
  }
  add_point(points,0,r,0);
}

void make_edge_matrix(struct matrix * points, struct matrix * edges, int numsteps) {
  int i, e;
  int n = numsteps*numsteps;
  for (i = 0; i < numsteps*numsteps; i++) {
    e = numsteps*(i/numsteps)+(i+1)%numsteps;
    add_edge(edges, points->m[0][i], points->m[1][i], points->m[2][i], points->m[0][e], points->m[1][e], points->m[2][e]);
    e = (i+numsteps);
    if (e < numsteps*numsteps)
      add_edge(edges, points->m[0][i], points->m[1][i], points->m[2][i], points->m[0][e], points->m[1][e], points->m[2][e]);
  }
  for (i = numsteps*(numsteps-1); i < numsteps*numsteps; i++){
    add_edge(edges, points->m[0][i], points->m[1][i], points->m[2][i], points->m[0][n], points->m[1][n], points->m[2][n]);
  }
}

struct matrix * make_torus(double R, double r, int numsteps, double x, double y, double z){
  struct matrix *points = new_matrix(4, numsteps*numsteps);
  struct matrix *edges = new_matrix(4, 4*numsteps*numsteps);
  make_torus_points(points,R,r,numsteps);
  make_torus_edges(points,edges,numsteps);
  struct matrix *trans = make_translate(x,y,z);
  matrix_mult(trans,edges);
  return edges;
}

void make_torus_points(struct matrix * points, double R, double r, int numsteps){
  double theta_incr = 2*M_PI/numsteps;
  double phi_incr = 2*M_PI/numsteps;
  int i,j;
  for (i = 0; i < numsteps; i++) {
    for (j = 0; j < numsteps; j++) {
      add_point(points, R*cos(j*phi_incr) + r*cos(i*theta_incr)*cos(j*phi_incr), r*sin(i*theta_incr),  R*sin(j*phi_incr) + r*cos(i*theta_incr)*sin(j*phi_incr));
    }
  }
}

void make_torus_edges(struct matrix * points, struct matrix * edges, int numsteps){
  int i, e;
  int n = numsteps*numsteps;
  for (i = 0; i < n; i++) {
    e = numsteps*(i/numsteps)+(i+1)%numsteps;
    add_edge(edges, points->m[0][i], points->m[1][i], points->m[2][i], points->m[0][e], points->m[1][e], points->m[2][e]);
    e = (i+numsteps)%n;
    add_edge(edges, points->m[0][i], points->m[1][i], points->m[2][i], points->m[0][e], points->m[1][e], points->m[2][e]);
  }
}

struct matrix * make_circle(int numsteps, double r, double x, double y, double z) {
  int i;
  double incr = 2*M_PI/numsteps;
  struct matrix *circ = new_matrix(4,1);
  for (i = 0; i < numsteps+1; i++){
    add_edge(circ, r*cos(i*incr)+x, r*sin(i*incr)+y, z, r*cos((i+1)*incr)+x, r*sin((i+1)*incr)+y, z);
  }
  return circ;
}

struct matrix *make_hermite(int numsteps, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  double ax, bx, cx, dx, ay, by, cy, dy, mx1, my1, mx2, my2, incr;
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
  
  incr = 1/(double)numsteps;
  int i;
  //printf("Our coefficients are: ax = %f, bx = %f, cx = %f, dx = %f, ay = %f, by = %f, cy = %f, dy = %f\n", ax,bx,cx,dx,ay,by,cy,dy);
  for (i = 0; i < numsteps; i++) {
    add_edge(edges, cubic(ax,bx,cx,dx,i*incr), cubic(ay,by,cy,dy,i*incr), 0, cubic(ax,bx,cx,dx,(i+1)*incr), cubic(ay,by,cy,dy,(i+1)*incr), 0);
  }
  return edges;
}

struct matrix *make_bezier(int numsteps, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
double ax, bx, cx, dx, ay, by, cy, dy, incr;
  struct matrix *H = new_matrix(4,4);
  struct matrix *temp = new_matrix(4,1);
  struct matrix *edges = new_matrix(4,2*numsteps);
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
  
  incr = 1/(double)numsteps;
  int i;
  for (i = 0; i < numsteps; i++) {
    add_edge(edges, cubic(ax,bx,cx,dx,i*incr), cubic(ay,by,cy,dy,i*incr), 0, cubic(ax,bx,cx,dx,(i+1)*incr), cubic(ay,by,cy,dy,(i+1)*incr), 0);
  }
  return edges;
}

double cubic(double a, double b, double c, double d, double t) {
  double result = a*t*t*t + b*t*t + c*t + d;
  return result;
}

struct matrix *make_good_bezier(int numsteps, struct matrix *inputs) {
  struct matrix *edges = new_matrix(4, 2*numsteps);
  struct matrix *temp1, *temp2;
  double incr = 1/((double) numsteps);
  int i;
  for (i = 0; i < numsteps; i++) {
    temp1 = bezier_calc(i*incr, inputs);
    temp2 = bezier_calc((i+1)*incr, inputs);
    add_edge(edges, temp1->m[0][0], temp1->m[1][0], 0, temp2->m[0][0], temp2->m[1][0], 0);
  }
  free_matrix(temp1);
  free_matrix(temp2);
  return edges;
}
struct matrix *bezier_calc(double t, struct matrix *inputs) {
  int length = inputs->lastcol + 1;
  struct matrix *temp1 = new_matrix(4,length);
  copy_matrix(inputs, temp1);
  struct matrix *temp2 = new_matrix(4,length-1);
  int i;
  int j;
  for (i = length; i > 1; i--) {
    if ((length-i) % 2 == 0) {
      for (j = 0; j < i-1; j++) {
	temp2->m[0][j] = (1-t)*temp1->m[0][j] + t*temp1->m[0][j+1];
	temp2->m[1][j] = (1-t)*temp1->m[1][j] + t*temp1->m[1][j+1];
      }
    }
    else {
      for (j = 0; j < i-1; j++) {
	temp1->m[0][j] = (1-t)*temp2->m[0][j] + t*temp2->m[0][j+1];
	temp1->m[1][j] = (1-t)*temp2->m[1][j] + t*temp2->m[1][j+1];
      }
    }
  }
  if (length%2 == 0) {
    return temp2;
    free_matrix(temp1);
  }
  else {
    return temp1;
    free_matrix(temp2);
  }
}
