#include <stdio.h>
#include <stdlib.h>

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
  points->lastcol++;
  if (points->lastcol >= points->cols) {
    grow_matrix(points, points->lastcol+1);
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
  if ((points->lastcol + 1) % 2 == 1)
    printf("Odd number of points, ignoring last point\n");
  int pairs = (points->lastcol +1) / 2;
  int i;
  for (i = 0; i < pairs; i++)
    draw_line(points->m[0][2*pairs],points->m[1][2*pairs],points->[0][2*pairs+1],points->m[1][2*pairs+1],s,c);
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
aReturns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should call add_point
====================*/
void add_edge( struct matrix * points, 
	       int x0, int y0, int z0, 
	       int x1, int y1, int z1) {
  add_point(points,x0,y0,z0);
  add_point(points,x1,y1,z1);
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
  //printf("We made it to draw_line\n");
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
	if (d <= .5)
	  plot(s,c,x,y);
	else {
	  y++;
	  d--;
	  plot(s,c,x,y);
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
}

