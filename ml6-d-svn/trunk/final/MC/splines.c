#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"
#include "splines.h"

struct matrix *coefficients;
double P1_x, P2_x;


double hermite_y(double t) {
  return (coefficients->m[0][0] * t*t*t +
    coefficients->m[1][0] * t*t +
    coefficients->m[2][0] * t +
    coefficients->m[3][0]);
}

double hermite_x(double t) {
  return P1_x + t*(P2_x-P1_x);
}

void draw_bezier(struct matrix * pm, double P1_x, double P1_y, double P2_x, double P2_y, double P3_x, double P3_y, double P4_x, double P4_y) {
  //draw_hermite(pm, P1_x, P1_y, P3_x, P3_y, 3*(P2_x - P1_x), 3*(P2_y - P1_y), 3*(P4_x - P3_x), 3*(P4_y - P3_y));

  /*struct matrix *B = new_matrix(4, 4);

  B->m[0][0] = -1;
  B->m[1][0] = 3;
  B->m[2][0] = -3;
  B->m[3][0] = 1;
  B->m[0][1] = 3;
  B->m[1][1] = -6;
  B->m[2][1] = 3;
  B->m[3][1] = 0;
  B->m[0][2] = -3;
  B->m[1][2] = 3;
  B->m[2][2] = 0;
  B->m[3][2] = 0;
  B->m[0][3] = 1;
  B->m[1][3] = 0;
  B->m[2][3] = 0;
  B->m[3][3] = 0;
	
  draw_spline(pm, P1_x, P1_y, P2_x, P2_y, P3_x, P3_y, P4_x, P4_y, B);*/

  double t, h1, h2, h3, h4, x, y;
  x = P1_x;
  y = P1_y;
  for (t = 0; t <= 1; t+=0.05) {
    add_point(pm, x, y, 0);
    h1 = -1*t*t*t + 3*t*t -3*t + 1;
    h2 = 3*t*t*t - 6*t*t + 3*t;
    h3 = -3*t*t*t + 3*t*t;
    h4 = t*t*t;
    x = h1*P1_x + h2*P3_x + h3*(P2_x-P1_x) + h4*(P4_x-P3_x);
    y = h1*P1_y + h2*P3_y + h3*(P2_y-P1_y) + h4*(P4_y-P3_y);
    add_point(pm, x, y, 0);
  }

}


void draw_hermite(struct matrix * pm, double P1_x, double P1_y, double P2_x, double P2_y, double P3_x, double P3_y, double P4_x, double P4_y) {
  double t, h1, h2, h3, h4, x, y;
  x = P1_x;
  y = P1_y;
  for (t = 0; t <= 1; t+=0.05) {
    add_point(pm, x, y, 0);
    h1 = 2*t*t*t - 3*t*t + 1;
    h2 = -2*t*t*t + 3*t*t;
    h3 = t*t*t - 2*t*t + t;
    h4 = t*t*t - t*t;
    x = h1*P1_x + h2*P3_x + h3*(P2_x-P1_x) + h4*(P4_x-P3_x);
    y = h1*P1_y + h2*P3_y + h3*(P2_y-P1_y) + h4*(P4_y-P3_y);
    add_point(pm, x, y, 0);
  }
}

void draw_spline(struct matrix * pm, double P1_x, double P1_y, double P2_x, double P2_y, double P3_x, double P3_y, double P4_x, double P4_y, struct matrix * M){
	double ax, bx, cx, dx, ay, by, cy, dy;
	
	//calculate coefficients for the cubic function, X
	struct matrix *P = new_matrix(4,1);
	P->m[0][0] = P1_x;
	P->m[1][0] = P3_x;
	P->m[2][0] = P2_x - P1_x;
	P->m[3][0] = P4_x - P3_x;
	
	matrix_mult(M, P);
	
	ax = P->m[0][0];
	bx = P->m[1][0];
	cx = P->m[2][0];
	dx = P->m[3][0];
	
	//find coefficients for y cubic
	P->m[0][0] = P1_y;
	P->m[1][0] = P3_y;
	P->m[2][0] = P2_y - P1_y;
	P->m[3][0] = P4_y - P3_y;
	
	matrix_mult(M, P);
	
	ay = P->m[0][0];
	by = P->m[1][0];
	cy = P->m[2][0];
	dy = P->m[3][0];
	
	double t = 0;
	//add points
	while (t < 1){
	  add_point(pm,
		    ax * t * t * t + bx * t * t + cx * t + dx,
		    ay * t * t * t + by * t * t + cy * t + dy,
		    0);
	  t+= .05;
	  add_point(pm,
		    ax * t * t * t + bx * t * t + cx * t + dx,
		    ay * t * t * t + by * t * t + cy * t + dy,
		    0);	  
	}
}
