#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  int octant = 1;
  
  if (x0 > x1) {
    octant = x1;
    x1 = x0;
    x0 = octant;
    octant = y1;
    y1 = y0;
    y0 = octant;
    octant = 1;
  }

  // slope >= 1, octant 2: reflect x and y, then reverse again when plotting
  if (y1-y0 >= x1-x0) {
    octant = x1;
    x1 = y1;
    y1 = octant;
    octant = x0;
    x0 = y0;
    y0 = octant;
    octant = 2;
  }

  // -1 < slope < 0, octant 8: negate y coordinates, reflect again when plotting
  else if (y1-y0 <= 0 && y1-y0 >= x0-x1) {
    y0 *= -1;
    y1 *= -1;
    octant = 8;
  }

  // slope < -1, octant 7: negate y coordinate then reflect x and y, undo when plotting
  else if (y1-y0 < x0-x1) {
    y0 *= -1;
    y1 *= -1;
    octant = x1;
    x1 = y1;
    y1 = octant;
    octant = x0;
    x0 = y0;
    y0 = octant;
    octant = 7;
  }

  int dy = y1-y0;
  int dx = x1-x0;
  int d = 2*dy - dx;
  for (; x0 <= x1; x0++) {
    if (octant == 2)
      plot(s, c, y0, x0);
    else if (octant == 1)
      plot(s, c, x0, y0);
    else if (octant == 8)
      plot(s, c, x0, -y0);
    else if (octant == 7)
      plot(s, c, y0, -x0);
    if (d >= 0) {
      y0++;
      d -= dx;
    }
    d += dy;
  }
}
