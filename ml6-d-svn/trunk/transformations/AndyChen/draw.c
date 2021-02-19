#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) { if (x0 > x1)
    {int temp = x0;
      x0=x1;
      x1=temp;
      temp = y0;
      y0 = y1;
      y1 = temp;
    }
  //horizontal lines
  if (y0 == y1)
    {int i;
      for (i = x0;i<=x1; i++)
	{plot(s,c,i,y0);}
      return;
    }
  //vertical
  if (x0 == x1)
    {int i;
      for (i = y0;i<=y1; i++)
	{plot(s,c,x0,i);}
      return;
    }
  //setup
  int dx = x1 - x0;
  int dy = y1-y0;
  int d = 2*dy - dx;

  // slope of 1
  if (dy == dx)
    {int i=0;
     while(i+x0 <= x1)
      {plot(s,c,i+x0,i+y0);
	i++;
      }
     return;
    }
  //slope -1
  if (dy == -1*dx)
    {int i=0;
      while(i+x0 <= x1)
	{plot(s,c,x0+i,y0-i);
	  i++;
	}
      return;
    }
  //positive slopes < 1
  if (dy < dx && dy >0)
    {int i = 0;
     int j = 0;
      while (i + x0 <= x1)
	{plot(s,c,x0+i,y0+j);
	  if (d<0)
	    {i++;
	     d = d + dy;
	    }
	  else
	    {i++;
	     j++;
	     d = d + dy - dx;
	    }
	}
    }

  // positive > 1
  if (dy > dx && dy >0)
    {int i = 0;
     int j = 0;
      while (j + y0 <= y1)
	{plot(s,c,x0+i,y0+j);
	  if (d<0)
	    {j++;
	     d = d + dx;
	    }
	  else
	    {i++;
	     j++;
	     d = d + dx - dy;
	    }
	}
    }
// negative > -1
 if (-dy < dx && dy <0)
    {int i = 0;
     int j = 0;
      while (i + x0 <= x1)
	{plot(s,c,x0+i,y0-j);
	  if (d<0)
	    {i++;
	     d = d - dy;
	    }
	  else
	    {i++;
	     j++;
	     d = d - dy - dx;
	    }
	}
    }
  // negative < -1
if (-dy > dx && dy <0)
    {int i = 0;
     int j = 0;
      while (y0-j >= y1)
	{plot(s,c,x0+i,y0-j);
	  if (d<0)
	    {j++;
	     d = d + dx;
	    }
	  else
	    {i++;
	     j++;
	     d = d + dx + dy;
	    }
	}
    }
}

