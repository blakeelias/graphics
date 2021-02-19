#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  int i,n,p,y;
  double u,m,b,d;
  if(x0 > x1){
    i = x0;
    x0 = x1;
    x1 = i;
    i = y0;
    y0 = y1;
    y1 = i;
  }
  if(x0 == x1){
    for(n = y0; n <= y1; n++){
      plot(s,c,x0,n);
    }
  }
  if(y0 == y1){
    for(n = x0; n <= x1; n++){
      plot(s,c,n,y0);
    }
  }

  double dy = y1 - y0;
  double dx = x1 - x0;
  if(dx != 0){
    m = dy/dx;
  }
  else{
    m = 0;
  }
  b = (m * x0) + y0;
  d = dy - dx + (dx *b);

  if(m == 1){
    u = 0;
    while(u + x0 <= x1){
      plot(s,c,x0+u,y0+u);
      u++;
    }
  }

  if(m > 1 && dy > 0){
    u = 0;
    while(u + x0 <= x1){
      if(u == 0){
      plot(s,c,x0,y0);
      u++;
      }
      else{
	double x = (m*(x0+u) + b);
	plot(s,c,x0+u,y0+x);
	u++;
      }
    }
  }

if(m > 1 && dy < 0){
    u = 0;
    while(u + x0 <= x1){
      if(u == 0){
      plot(s,c,x0,y0);
      u++;
      }
      else{
	double x = (m*(x0+u) + b);
	plot(s,c,x0+u,y0-x);
	u++;
      }
    }
  }

  /* if(m > 1 && dy > 0){
    u = 0;
    y = 0;
    while(y + y0 <= y1){
      plot(s,c,x0+u,y0+y);
      if(d < 0){
	y++;
      }
      else{
	u++;
	y++;
      }
    }
  }
  
  if(m < 1 && dy > 0){
    u = 0;
    y = 0;
    while(u + x0 <= x1){
      plot(s,c,x0+u,y0+y);
      if(d < 0){
	u++;
      }
      else{
	u++;
	y++;
      }
    }
  }*/

  if(m == -1){
    u = 0;
    while(u + x0 <= x1){
      plot(s,c,x0+u,y0-u);
      u++;
    }
  }

  /* if(m < 1 && dy < 0){
    u = 0;
    y = 0;
    while(y + y0 <= y1){
      plot(s,c,x0+u,y0-y);
      if(d < 0){
	y++;
      }
      else{
	u++;
	y++;
      }
    }
  }

  if(m < 1 && dy > 0){
    u = 0;
    y = 0;
    while(u + x0 <= x1){
      plot(s,c,x0+u,y0-y);
      if(d < 0){
	u++;
      }
      else{
	u++;
	y++;
      }
    }
  }*/
}

