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
void add_point(struct matrix * points, double x, double y, double z) {
  points->lastcol++;
  //printf("adding point %f,%f,%f,1 to column %d\n", x,y,z,points->lastcol);
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
  //printf("Matrix into draw_lines is:\n");
  //print_matrix(points);
  if ((points->lastcol + 1) % 2 == 1)
    printf("Odd number of points, ignoring last point\n");
  // int pairs = (points->lastcol +1) / 2;
  int i;
  //printf("Right before draw_line, our point matrix is:\n");
  //print_matrix(points);
  for (i = 0; i < points->lastcol+1; i+=2) {
    //printf("Inputs into points_in_bounds: (%f, %f) to (%f, %f)\n",points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1]);
    endpoints = points_in_bounds(points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1]);
    //printf("Result matrix from points_in_bounds:\n");
    //print_matrix(endpoints);
    //printf("Drawing line (%f, %f) to (%f, %f)\n", points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i + 1]);
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
  
      
  
  
  /*endpoints->m[0][0] = -1;
  endpoints->m[0][1] = -1;
  endpoints->m[1][0] = -1;
  endpoints->m[1][1] = -1;

  double left,right,top,bottom, m;
  //int firstedge, secondedge;

  m = (y1-y0) / (x1-x0);
  printf("Slope of line is %f\n", m);

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

  if (endpoints->m[0][0] == -1) {
    endpoints->m[0][0] = 0;
    endpoints->m[1][0] = 0;
  }

  if (endpoints->m[0][1] == -1) {
    endpoints->m[0][1] = endpoints->m[0][0];
    endpoints->m[1][1] = endpoints->m[1][0];
  } 
  return endpoints;*/
  



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
  //printf("Drawing line from (%d, %d) to (%d, %d)\n", X0, Y0, X1, Y1);
  int x0,x1,y0,y1,x,y;
  double m,d;
  if (X0 < X1) {
    //printf("Points in right order\n");
    x0 = X0;
    y0 = Y0;
    x1 = X1;
    y1 = Y1;
  }
  else {
    //printf("Points in wrong order\n");
    x0 = X1;
    y0 = Y1;
    x1 = X0;
    y1 = Y0;
  }
  //printf("Current values: x0 is %d, x1 is %d, y0 is %d, y1 is %d\n", x0, x1, y0, y1);
  if (x0 == x1) {
    //printf("Entered vertical line routine\n");
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
    //printf("Our slope is %f\n", m);
    d = 0;
    x = x0;
    y = y0;
    if (m >= 0 && m <=1) {
      //printf("Made it to octant 1 routine\n");
      while (x <= x1) {
	if (d <= .5) {
	  plot(s,c,x,y);
	  //printf("Just plotted %d, %d\n", x,y);
	}
	else {
	  y++;
	  d--;
	  plot(s,c,x,y);
	  //printf("Just plotted %d, %d\n", x,y);
	}
	x++;
	d = d + m;
      }
      //printf("Our final y in octant 1 line is %d\n", y);
    }
    else {
      if (m < 0 && m >= -1) {
	//printf("Made it to octant 8 routine\n"); //test more here
	//printf("x is %d, x0 is %d, x1 is %d, y is %d, y0 is %d, y1 is %d, m is %f, d is %f\n",x,x0,x1,y,y0,y1,m,d);
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
	  //printf("Made it to octant 2 routine\n");
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
	  //printf("Made it to octant 7 routine\n");
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

/*void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

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
    }*/

void make_sphere(screen s, color c, double r, int numsteps, double x, double y, double z) {//plots sphere with radius r, and center (x,y,z)
  struct matrix *points = new_matrix(4, numsteps*numsteps);
  struct matrix *edges = new_matrix(4, 4*numsteps*numsteps);

  make_sphere_points(points,r,numsteps);
  make_edge_matrix(points,edges,numsteps);
  
  struct matrix *trans = make_translate(x,y,z);
  
  matrix_mult(trans,edges);
  draw_lines(edges,s,c);
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
  //print_matrix(points);
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

void make_torus(screen s, color c, double R, double r, int numsteps, double x, double y, double z){
  struct matrix *points = new_matrix(4, numsteps*numsteps);
  struct matrix *edges = new_matrix(4, 4*numsteps*numsteps);

  make_torus_points(points,R,r,numsteps);
  make_torus_edges(points,edges,numsteps);
  
  struct matrix *trans = make_translate(x,y,z);
  struct matrix *rotateX = make_rotX(90);

  matrix_mult(rotateX, edges);
  matrix_mult(trans,edges);
  draw_lines(edges,s,c);
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
  //print_matrix(points);
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
