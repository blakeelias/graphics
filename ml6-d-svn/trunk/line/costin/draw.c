#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  int i, j, tmp;

  //if x0 > x1, swap the points
  if (x0 > x1)
    {
      int tmp = x0;
      x0 = x1;
      x1 = tmp;
      tmp = y0;
      y0 = y1;
      y1 = tmp;
    }

  //Special cases

  //if m = 0 (horizontal line)
  if (y0 == y1)
    {
      for (i=0;(x0+i)<x1;i++)
	  plot(s, c, x0+i,y0);
    }

  //if m is undefined (vertical line)
  if (x0 == x1)
    {
      for (i=0;(y0+i)<y1;i++)
	  plot(s, c, x0,y0+i);
    }

  //Set up decision and calculation variables
  int d = 0; //decision factor lol
  int dx = x1 - x0; //delta x
  int dy = y1 - y0; //delta y

  //m = 1
  if (dx == dy)
    {
      for(i=0;(x0+i)<x1;i++)
	{
	  plot(s,c,x0+i,y0+i);
	}
      return;
    }
  
  //m = -1
  if (dx == -dy)
    {
      for(i=0;(x0+i)<x1;i++)
	{
	  plot(s,c,x0+i,y0-i);
	}
      return;
    }      

  //0<m<1
  if (dx > dy && dy > 0)
    {
      j=0;
      for(i=0;(x0+i)<x1;i++)
	{
	  plot(s,c,x0+i,y0+j);
	  if(d<0)
	    {
	      d=d+dy;
	    }
	  else
	    {
	      j++;
	      d=d+dy-dx;
	    }
	}
      return;
    }

  //-1<m<0
  if (dx > -dy && dy < 0 )
    {
      j=0;
      for(i=0;(x0+i)<x1;i++)
	{
	  plot(s,c,x0+i,y0-j);
	  if(d<0)
	    {
	      d=d-dy;
	    }
	  else
	    {
	      j++;
	      d=d-dy-dx;
	    }
	}
      return;
    }

  //m>1
  if (dy>dx)
    {
      i=0;
      for(j=0;(y0+j)<y1;j++)
	{
	  plot(s,c,x0+i,y0+j);
	  if(d<0)
	    {
	      d=d+dx;
	    }
	  else
	    {
	      i++;
	      d=d+dx-dy;
	    }
	}
      return;
    }

  //m<-1
  if(dx < -dy && dy < 0)
    {
      i=0;
      for(j=0;(y0-j)>y1;j++)
	{
	  plot(s,c,x0+i,y0-j);
	  if(d<0)
	    {
	      d=d+dx;
	    }
	  else
	    {
	      i++;
	      d=d+dx+dy;
	    }
	}
      return;
    }
  
}
