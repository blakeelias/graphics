#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
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
