#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "draw.h"
#include "geo.h"
#include "globals.h"
#include "matrix.h"
#include "screen.h"

color draw_shadeColor(color c, double shade) {
  color o;
  o.c.r *= shade;
  o.c.g *= shade;
  o.c.b *= shade;
  return o;
}

void draw_shapeList(struct shape **list, int num_shapes, color c) {
	int i;
	for(i = 0; i < num_shapes; i++) {
		debug_w("Drawing shape %d\n", i);
		matrix_print(list[i]->points);
		draw_all(list[i]->points, list[i]->edges, list[i]->numEdges, c);
	}
}

void draw_all(struct matrix *points, int *lines, int num_lines, color c) {
  draw_edges(points, lines, num_lines, c);
  draw_points(points, c);
}

void draw_points(struct matrix *points, color c) {
  int i;
  for (i = 0; i < points->nc; i++) {
    draw_point(points->m[i][0], points->m[i][1], c);
  }
}

void draw_edges(struct matrix *points, int *lines, int num_lines, color c) {
  int i;
  for (i = 0; i < num_lines; i++) {
    draw_edge(points->m[lines[2 * i]][0], points->m[lines[2 * i]][1], points->m[lines[2 * i + 1]][0], points->m[lines[2 * i + 1]][1], c); 
  }
}

void draw_point(double x, double y, color c) {
  /*
  int xL = (int) (x - 0.5);
  int xR = (int) (x + 0.5);
  
  int yU = (int) (y + 0.5);
  int yD = (int) (y - 0.5);
  
  double shade1 = (x - xR + 0.5) * (y - yU + 0.5);
  double shade2 = (xR - x + 0.5) * (y - yU + 0.5);
  double shade3 = (xR - x + 0.5) * (yU - y + 0.5);
  double shade4 = (x - xR + 0.5) * (yU - y + 0.5);
  
  screen_drawPixel(R * shade1, G * shade1, B * shade1, xR, yU);
  screen_drawPixel(R * shade2, G * shade2, B * shade2, xL, yU);
  screen_drawPixel(R * shade3, G * shade3, B * shade3, xL, yD);
  screen_drawPixel(R * shade4, G * shade4, B * shade4, xR, yD);
  */
  screen_drawPixel(c, floor(x), floor(y));
}

/*
void draw_edge(double x0, double y0, double x1, double y1, color c) {
  
  double slope = (double) (y1 - y0) / (x1 - x0);
  
  if (slope < 1 && slope > -1) {
    
    if (x1 < x0) {
      //printf("FLIP\n");
      draw_edge(x1, y1, x0, y0, c);
      return;
    }

    int x_curr = floor(x0 + 1);
    double y = y0 + (slope * (x_curr - x0 + 0.5));
    while (x_curr < ceil(x1 - 1)) {
      //double shade1 = y - floor(y - 0.5) - 0.5;
      //double shade2 = floor(y + 0.5) - y + 0.5;
      double shade1 = sqrt(y - floor(y - 0.5) - 0.5);
      double shade2 = sqrt(floor(y + 0.5) - y + 0.5);
      screen_drawPixel(draw_shadeColor(c, shade1), x_curr, (int) (y + 0.5));
      screen_drawPixel(draw_shadeColor(c, shade2), x_curr, (int) (y - 0.5));
      //screen_drawPixel(c, x_curr, (int) (y + 0.5));
      //screen_drawPixel(c, x_curr, (int) (y - 0.5));
      x_curr++;
      y += slope;
    }
    return;   
  }
  
  if (y1 < y0) {
    draw_edge(x1, y1, x0, y0, c);
    return;
  }
  
  int y_curr = floor(y0 + 1);
  double x = x0 + ((1/slope) * (y_curr - y0 + 0.5));
  while (y_curr < ceil(y1 - 1)) {
    //double shade1 = x - floor(x - 0.5) - 0.5;
    //double shade2 = floor(x + 0.5) - x + 0.5;
    double shade1 = sqrt(x - floor(x - 0.5) - 0.5);
    double shade2 = sqrt(floor(x + 0.5) - x + 0.5);
    screen_drawPixel(draw_shadeColor(c, shade1), (int) (x + 0.5), y_curr);
    screen_drawPixel(draw_shadeColor(c, shade2), (int) (x - 0.5), y_curr);
    //screen_drawPixel(c, (int) (x + 0.5), y_curr);
    //screen_drawPixel(c, (int) (x - 0.5), y_curr);
    y_curr++;
    x += 1/slope;
  }
}
*/

void draw_edge(double x0f, double y0f, double x1f, double y1f, color c){
	int x0 = x0f;
	int y0 = y0f;
	int x1 = x1f;
	int y1 = y1f;
	
	int dx, dy, flip, tmp;
	dx = x1 - x0;
	dy = y1 - y0;
	if((flip = (abs(dy) > abs(dx)))){
		tmp = x0;
		x0  = y0;
		y0  = tmp;
		tmp = x1;
		x1  = y1;
		y1  = tmp;
		tmp = dx;
		dx  = dy;
		dy  = tmp;
	}
	if(x0 > x1){
		tmp = x0;
		x0  = x1;
		x1  = tmp;
		tmp = y0;
		y0  = y1;
		y1  = tmp;
	}
	color cc1, cc2, oc1, oc2;
	unsigned int ctmp;
	double slope, dtmp, intery, fracy;
	slope = (double) dy / dx;
	intery = y0 + slope;
	if(flip){
		pixel(y0, x0) = c.i;
		pixel(y1, x1) = c.i;
	} else {
		pixel(x0, y0) = c.i;
		pixel(x1, y1) = c.i;
	}
	double sqrtpfy, sqrtmfy;
	int i;
	for(i = x0 + 1; i < x1; i++){
		fracy = modf(intery, &dtmp);
		if(flip){
			oc1.i = pixel((int) dtmp    , i);
			oc2.i = pixel((int) dtmp + 1, i);
		} else {
			oc1.i = pixel(i, (int) dtmp);
			oc2.i = pixel(i, (int) dtmp + 1);
		}
		sqrtpfy = sqrt(      fracy);
		sqrtmfy = sqrt(1.0 - fracy);
		ctmp = (sqrtmfy * c.c.r) + (sqrtpfy * oc1.c.r); if(ctmp > MAX_COLOR){ cc1.c.r = MAX_COLOR; } else { cc1.c.r = ctmp; }
		ctmp = (sqrtmfy * c.c.g) + (sqrtpfy * oc1.c.g); if(ctmp > MAX_COLOR){ cc1.c.g = MAX_COLOR; } else { cc1.c.g = ctmp; }
		ctmp = (sqrtmfy * c.c.b) + (sqrtpfy * oc1.c.b); if(ctmp > MAX_COLOR){ cc1.c.b = MAX_COLOR; } else { cc1.c.b = ctmp; }
		ctmp = (sqrtpfy * c.c.r) + (sqrtmfy * oc1.c.r); if(ctmp > MAX_COLOR){ cc2.c.r = MAX_COLOR; } else { cc2.c.r = ctmp; }
		ctmp = (sqrtpfy * c.c.g) + (sqrtmfy * oc1.c.g); if(ctmp > MAX_COLOR){ cc2.c.g = MAX_COLOR; } else { cc2.c.g = ctmp; }
		ctmp = (sqrtpfy * c.c.b) + (sqrtmfy * oc1.c.b); if(ctmp > MAX_COLOR){ cc2.c.b = MAX_COLOR; } else { cc2.c.b = ctmp; }
		if(flip){
			pixel((int) dtmp    , i) = cc1.i;
			pixel((int) dtmp + 1, i) = cc2.i;
		} else {
			pixel(i, (int) dtmp    ) = cc1.i;
			pixel(i, (int) dtmp + 1) = cc2.i;
		}
		intery += slope;
	}
}
