#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  int x = x1>x0?x0:x1;
  if(x1 == x0)
    {
      int y = y1>y0?y0:y1;
      int ye = y1>y0?y1:y0;
      while(y<=ye)
	{
	  plot(s,c,x,y);
	  y++;
	}
      return;
    }
  double m = (y1-y0)/(x1-x0);
  double b = y0-(m*x0);
  while(x<=(x1>x0?x1:x0))
    {
      plot(s,c,x,(int)(m*x+b));
      x++;
    }
  
}

