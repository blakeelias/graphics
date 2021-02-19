#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

/*int f(x,y,dx,dy,c)
{
return ( (dy * x)+(-1 * dx * y) +c);
}*/

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

/*
if(x1<x0)
{
int xtemp=x1;
x1=x0;
x0=xtemp;
}if(y1<y0)
{
int ytemp=y1;
y1=y0;
y0=ytemp;
}*/

//double m = (y1-y0)/(x1-x0);
int dy = (y1 - y0);
int dx = (x1 - x0);

double d= 2*dy-dx;

int x=x0;
int y=y0;

if (dx==0) //vertical test
{
 if(y1<y0)
 {
 int ytemp=y1;
 y1=y0;
 y0=ytemp;
 }
 int x=x0;
int y=y0;
 while (y <= y1)
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      y++;
	//y++;//supposedly off
      d = d + dy;
     }
     else
     {
      //x++; //just in case, horoz. case
      y++;
      d = d + dy - dx;
     }
   }

}

else if (dy==0) //horozontal test
{
 if(x1<x0)
 {
 int xtemp=x1;
 x1=x0;
 x0=xtemp;
 
 int ytemp=y1;
 y1=y0;
 y0=ytemp;
 }
 int x=x0;
int y=y0;
 while (x <= x1)
   {
    plot(s,c,x,y);
    if (d <= 0)
     {
      x++;
	//y++;//supposedly off
      d = d + dy;
     }
     else
     {
      //y++; //just in case, horoz. case
      x++;
      d = d + dy - dx;
     }
   }
}

else if ((dy/dx > 0) && (dy/dx <=1)) //octant 2 E, NE
{
 if(x1<x0)
 {
 int xtemp=x1;
 x1=x0;
 x0=xtemp;
 
 int ytemp=y1;
 y1=y0;
 y0=ytemp;
 }
 int x=x0;
int y=y0;
d= 2 *dy-dx;
//printf("x:%d y:%d dy/dx%f\n", dx, dy,(double) dy/dx);
 while (x <= x1)
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      x++;
	//y++;//supposedly off
      d = d + dy;
	//printf("+xonly \n");
     }
     else
     {
      y++; //just in case, horoz. case
      x++;
      d = d + dy - dx;
	//printf("+x+y  \n");
     }
   }
}
else if (dy/dx < 0 && dy/dx >= -1) //octant 3,7 E, SE
{
 if(x1<x0)
 {
 int xtemp=x1;
 x1=x0;
 x0=xtemp;
 
 int ytemp=y1;
 y1=y0;
 y0=ytemp;
 }
  int x=x0;
int y=y0;
// printf("%f\n",(double)dy/dx);
 while (x <= x1)
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      x++;
      y--;//supposedly off
      d = d + dy;
     }
     else
     {
      //y--; //just in case, horoz. case
      x++;
      d = d + dy - dx;
     }
   }
}
else if(dy/dx>1) //octant 1 N, NE
{
 if(y1<y0)
 {
 int xtemp=x1;
 x1=x0;
 x0=xtemp;
 
 int ytemp=y1;
 y1=y0;
 y0=ytemp;
 }
  int x=x0;
int y=y0;
 printf("%f\n",(double)dy/dx);
 while (y <= y1)
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      x++;
      y++;//supposedly off
      d = d + dy;
     }
     else
     {
      //x++; //just in case, horoz. case
      y++;
      d = d + dy - dx;
     }
   }
}
else if(((dy/dx)<-1)) //octant 4 S, SE
{
 if(y1>y0)
 {
 int xtemp=x1;
 x1=x0;
 x0=xtemp;
 
 int ytemp=y1;
 y1=y0;
 y0=ytemp;
 }
  int x=x0;
int y=y0;
 printf("%f\n",(double)dy/dx);
 while (y >= y1)
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      //x--;
      y--;//supposedly off
      d = d + dy;
     }
     else
     {
      x--; //just in case, horoz. case
      y--;
      d = d + dy - dx;
     }
   }
}


/*	
if(dx!=0)//test to see if not vertical
 {

 if( (dy/dx)< .5 && (dy/dx)>=0) //quad 2/6, testing E, NE
  { while (x <= x1)
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      x++;
	//y++;//supposedly off
      d = d + dy;
     }
     else
     {
      y++;
      x++;
      d = d + dy - dx;
     }
   }
  }
  if( (dy/dx)> -.5 && (dy/dx)<0)//quad 3/7, testing E,SE
  { while (x <= x1)
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      x++;
      y--;//supposedly on
      d = d + dy;
     }
     else
     {
      //y--;
      x++;
      d = d + dy - dx;
     }
   }
  }



 } 

 else if(dx==0 ||dx*dy>0)//(dx*dy>=0) //vert. lines or testing quad 1/5, N,Ne
	{
	while (y <= y1)
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      y++;
      //x++;//supposedly on
      d = d + dy;
     }
     else
     {
      y++;
      x++; 
      d = d + dy - dx;
     }
   }


	}
	else 
	{
	while (y <= y1)  //last case, testing quads 4/8 S,Se
   {
    plot(s,c,x,y);
    if (d < 0)
     {
      y--;
      d = d + dy;
     }
     else
     {
      y--;
      x++;
      d = d + dy - dx;
     }
   }


	}*/
}

