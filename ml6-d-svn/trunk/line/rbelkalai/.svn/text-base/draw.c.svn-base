#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here.
void draw_line(int x0, int y0, int x1, int y1, screen s, color c)
{
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

