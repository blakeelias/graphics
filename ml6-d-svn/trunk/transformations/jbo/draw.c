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
void add_point(struct matrix *points, int x, int y, int z) {
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
void draw_lines(struct matrix *points, screen s, color c) {
  int i = 1;
  while (i < points->cols) {
    draw_line(points->m[0][i-1], points->m[1][i-1], points->m[0][i], points->m[1][i], s, c);
    i += 2;
  }
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should call add_point
====================*/
void add_edge(struct matrix *points, int x0, int y0, int z0, int x1, int y1, int z1) {
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

  if (x1 == x0 && y1 == y0) {
    plot(s, c, x0, y0);
    return;
  }
  
  if (x1 < x0) {
    draw_line(x1, y1, x0, y0, s, c);
    return;
  }
  
  if (x1 == x0) {
    if (y1 > y0) {
      while (y0 <= y1) {
        plot(s, c, x0, y0);
        y0++;
      }
      return;
    }
    while (y0 >= y1) {
      plot(s, c, x0, y0);
      y0--;
    }
    return;
  }
  
  double slope = (double) (y1 - y0) / (x1 - x0);
  
  if (y1 > y0) {
  
    if (slope < 1) {
    
      // Octant 1
      double y_error = 0;
      while (x0 <= x1) {
        if (y_error > .5) {
          y0++;
          y_error--;
        }
        plot(s, c, x0, y0);
        x0++;
        y_error += slope;
      }
      return;   
    }
    
    // Octant 2
    double x_error = 0;
    while (y0 <= y1) {
      if (x_error > .5) {
        x0++;
        x_error--;
      }
      plot(s, c, x0, y0);
      y0++;
      x_error += 1/slope;
    }
    return;
  }
  
  if (slope > -1) {
  
    // Octant 8
    double y_error = 0;
    while (x0 <= x1) {
      if (y_error < -.5) {
        y0--;
        y_error++;
      }
      plot(s, c, x0, y0);
      x0++;
      y_error += slope;
    }
    return;   
  }
  
  // Octant 7
  double x_error = 0;
  while (y0 >= y1) {
    if (x_error < .5) {
      x0++;
      x_error++;
    }
    plot(s, c, x0, y0);
    y0--;
    x_error += 1/slope;
  }
} 

