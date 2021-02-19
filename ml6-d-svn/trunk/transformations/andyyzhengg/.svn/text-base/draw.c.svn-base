#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "matrix.h"
#include "draw.h"

void add_point(struct matrix* m, int x, int y, int z)
{
  if(m->lastcol == 0)
    {
       m->m[0][0] = x;
       m->m[1][0] = y;
       m->m[2][0] = z;
       m->m[3][0] = 1;
       m->lastcol = 1;
    }
  else
    {
      int cols = m->cols+1;
      grow_matrix(m , cols);
      m->m[0][cols - 1] = x;
      m->m[1][cols - 1] = y;
      m->m[2][cols - 1] = z;
      m->m[3][cols - 1] = 1;
    }
}
void draw_lines(struct matrix *points, screen s, color c)
{
  int end = points->cols;
  int i = 0;
  int x0,y0,z0,x1,y1,z1;
  while(i < end)
    {
      x0 = points->m[0][i];
      y0 = points->m[1][i];
      z0 = points->m[2][i];
      x1 = points->m[0][i+1];
      y1 = points->m[1][i+1];
      z1 = points->m[2][i+1];
      if(end-1 == i)
	  break;
      if(x0 < 0 || x0 > 300 || x1 <0 || x1 > 300 || y0 < 0 || y0 > 300 || y1 < 0 || y1 > 300)
	{
	  i += 2;
	  continue;
	}
      draw_line(x0, y0, x1, y1, s, c);
      i += 2;
    }
}
void add_edge( struct matrix *m, int x0, int y0, int z0, int x1, int y1, int z1)
{
  add_point(m , x0,y0,z0);
  add_point(m, x1,y1,z1);
}
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
  int d, dy, dx, i, x, y;
  dx = x1 - x0; // always positive
  dy = y1 - y0;
  
  // vertical lines
  if(dx == 0)
    {
      while(y0 <= y1)
	{
	  plot(s,c,x0,y0);
	  ++y0;
	}
      return;
    }
  
  // horizontal lines
  if(dy == 0)
    {
      while(x0 <= x1)
	{
	  plot(s,c,x0,y0);
	  ++x0;
      }
      return;
    }

  //lines that are: -1 <= m <= 1
  if(abs(dy) <= abs(dx))
    {
      if(x0 > x1)
	{
	  draw_line(x1, y1, x0, y0, s, c);
	  return;
	}
      
      if (dy < 0)
	{
	  i = -1;
	  dy = -dy;
	}
      else
	{
	  i = 1;
	}
      
      d = 2 * dy - dx;
      y = y0;

      for(x = x0; x <= x1; ++x)
	{
	  plot(s, c, x, y);
	  if(d <= 0)
	    {
	      d += dy;
	    }
	else
	  {
	    y += i;
	    d += dy - dx;
	  }
	}
      return;
    }
  else // all other lines
    {
      if(y0 > y1)
	{
	  draw_line(x1, y1, x0, y0, s, c);
	  return;
	}
      
      if (dx < 0)
	{
	  i = -1;
	  dx = -dx;
	}
      else
	{
	  i = 1;
	}
      
      d = 2 * dx - dy;
      x = x0;

      for(y = y0; y <= y1; ++y)
	{
	  plot(s, c, x, y);
	  if(d <= 0)
	    {
	      d += dx;
	    }
	else
	  {
	    x += i;
	    d += dx - dy;
	  }
	}
      return;
    }
}
*/ 
