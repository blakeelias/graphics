#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "parametrics.h"

double line_x( double t ) {

  return 1 * (1 - t) + 212 * t;
}

double line_y( double t ) {

  return 54 * (1 - t) + 90 * t;
}

double circle_x( double t ) {

  return circle_radius * cos( 2 * M_PI * t) + circle_x_cor;
}

double circle_y( double t ) {

  return circle_radius * sin( 2 * M_PI * t) + circle_y_cor;
}


double square_x(double t) {

  double x;
  if ( t <= .25 )
    x = 50;
  else if ( t <= .5 ) {
    t = t * 4 - 1;
    x = 50 * (1 - t) + 100 * t;
  }
  else if ( t<= .75 ) 
    x = 100;
  else {
    t = t * 4 - 3;
    x = 100 * (1 - t) + 50 * t;
  }

  return x;
}

 double square_y(double t) {

  double y;
  if ( t <= .25 ) {
    t = t * 4;
    y = 50 * (1 - t) + 100 * t;
  }
  else if ( t <= .5 ) 
    y = 100;
  else if ( t<= .75 ) {
    t = t * 4 - 2;
    y = 100 * (1 - t) + 50 * t;
  }
  else 
    y = 50;

  return y;
}

double squarex(double t)
{
  double x;
  if (t>=0 && t<.25)
    x=4.0*t;
  else if (t>=.25 && t<.5)
    x=1.0;
  else if (t>=.5 && t<.75)
    x = 3.0-4.0*t;
  else
    x = 0;

  return 150+50*x;
}

double barty(double t)
{
  double y;
  if (t>=0 && t<.25)
    y=0;
  else if (t>=.25 && t<.5)
    y=4.0*t-1.0;
  else if (t>=.5 && t<.75)
    {
      y=3*sin(30*2*M_PI*t);
      y = y / 50;
      y=y+1;
    }
  else
    {
      y=1.0-4*(t-0.75);
    }
  return 150+50*y;
}
