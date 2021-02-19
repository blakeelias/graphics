#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"

/*======== void add_point() ==========
 Inputs:   struct matrix * points
 int x
 int y
 int z 
 Returns: 
 adds point (x, y, z) to points and increment points.lastcol
 if points is full, should call grow on points
 ====================*/
void add_point( struct matrix * points, int x, int y, int z) {
	grow_matrix(points, points->cols + 1);
	points->m[0][points->cols - 1] = x;
	points->m[1][points->cols - 1] = y;
	points->m[2][points->cols - 1] = z;
	points->m[3][points->cols - 1] = 1;
}


/*======== void draw_lines() ==========
 Inputs:   struct matrix * points
 screen s
 color c 
 Returns: 
 Go through points 2 at a time and call draw_line to add that line
 to the screen
 ====================*/
void draw_lines( struct matrix * points, screen s, color c) {
	int i = 0;
	while (i < points->cols){
		draw_line( points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1], s, c);
		i+= 2;
	}
}

/*======== void add_edge() ==========
 Inputs:   struct matrix * points
 int x0, int y0, int z0, int x1, int y1, int z1
 Returns: 
 add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
 should call add_point
 ====================*/
void add_edge( struct matrix * points, int x0, int y0, int z0, int x1, int y1, int z1) {
	add_point(points, x0, y0, z0);
	add_point(points, x1, y1, z1);
}


/*======== void draw_line() ==========
 Inputs:  int x0
 int y0
 int x1
 int y1
 screen s
 color c 
 Returns: 
 draws the line connecting (x0, y0) to (x1, y1) to screen s using color c
 ====================*/
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
