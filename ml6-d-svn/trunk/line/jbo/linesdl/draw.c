#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "ui.h"

void add_point(struct matrix *points, int x, int y, int z) {
  grow_matrix(points, points->cols + 1);
  points->m[0][points->cols - 1] = x;
  points->m[1][points->cols - 1] = y;
  points->m[2][points->cols - 1] = z;
  points->m[3][points->cols - 1] = 1;
}

void draw_lines(struct matrix *points, unsigned char R, unsigned char G, unsigned char B) {
  int i = 1;
  while (i < points->cols) {
    draw_line(points->m[0][i-1], points->m[1][i-1], points->m[0][i], points->m[1][i], R, G, B);
    i += 2;
  }
}

void add_edge(struct matrix *points, int x0, int y0, int z0, int x1, int y1, int z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

void draw_line(int x0, int y0, int x1, int y1, unsigned char R, unsigned char G, unsigned char B) {

  if (x1 == x0 && y1 == y0) {
    drawPixel(R, G, B, x0, y0);
    return;
  }
  
  if (x1 < x0) {
    draw_line(x1, y1, x0, y0, R, G, B);
    return;
  }
  
  if (x1 == x0) {
    if (y1 > y0) {
      while (y0 <= y1) {
        drawPixel(R, G, B, x0, y0);
        y0++;
      }
      return;
    }
    while (y0 >= y1) {
      drawPixel(R, G, B, x0, y0);
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
        drawPixel(R, G, B, x0, y0);
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
      drawPixel(R, G, B, x0, y0);
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
      drawPixel(R, G, B, x0, y0);
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
    drawPixel(R, G, B, x0, y0);
    y0--;
    x_error += 1/slope;
  }
} 

