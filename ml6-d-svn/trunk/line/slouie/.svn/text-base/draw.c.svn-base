#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  int d,dx,dy,x,y;
  double m;

  x=x0;
  y=y0;
  dx=x1-x0;
  dy=y1-y0;
  if(dx)
    m=(double)dy/dx;
  
  if(x0>x1)
    {
      draw_line(x1,y1,x0,y0,s,c);
      return;
    }

  while(dx==0 && y<y1) //bottom - up
    plot(s,c,x,y++);
  while(m==0 && x<x1) //left - right
    plot(s,c,x++,y);
  while(m==-1 && x<x1)
    plot(s,c,x++,y--);

  d=2*dy-dx;
  
  printf("endpt1(%d,%d), endpt2(%d,%d)\n",x0,y0,x1,y1);
  printf("dx=%d, dy=%d\n",dx,dy);
  printf("Slope is %f\n\n",m);

  while(x < x1)
    {
      plot(s,c,x,y);
      if (d<0)
	{
	  if(m > 0 && m < 1)
	    {
	      x++;
	      d=d+dy;
	    }
	  if(m > 1)
	    {
	      y++;
	      d=d+dy;
	    }
	  if(m < 0 && m > -1)
	    {
	      x++;
	      d=d-dy;
	    }
	  if(m < -1)
	    {
	      x++;
	      y--;
	      d=d-dy;
	    }
	  //d=d+dy;
	}
      else
	{
	  if(m > 0 && m <= 1)
	    {
	      y++;
	      x++;
	    }
	  if(m > 1)
	    {
	      x++;
	      y++;
	    }
	  if(m < 0 && m > -1)
	    {
	      y--;
	      x++;
	    }
	  if(m < -1)
	    y--;
	  d=d+dy-dx;
	}
    }
}

