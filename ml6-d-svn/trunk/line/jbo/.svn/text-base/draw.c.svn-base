#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  if (x1 < x0) {
    draw_line(x1, y1, x0, y0, s, c);
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

