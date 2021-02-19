#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "draw.h"
#include "matrix.h"
#include "ui.h"

void draw_all(struct matrix *points, int *lines, int num_lines, unsigned char R, unsigned char G, unsigned char B) {
  draw_edges(points, lines, num_lines, R, G, B);
  draw_points(points, R, G, B);
}

void draw_points(struct matrix *points, unsigned char R, unsigned char G, unsigned char B) {
  int i;
  for (i = 0; i < points->nextCol; i++) {
    draw_point(points->m[i][0], points->m[i][1], R, G, B);
  }
}

void draw_edges(struct matrix *points, int *lines, int num_lines, unsigned char R, unsigned char G, unsigned char B) {
  int i;
  for (i = 0; i < num_lines; i++) {
    draw_edge(points->m[lines[2 * i]][0], points->m[lines[2 * i]][1], points->m[lines[2 * i + 1]][0], points->m[lines[2 * i + 1]][1], R, G, B); 
  }
}

void draw_point(double x, double y, unsigned char R, unsigned char G, unsigned char B) {
  /*
  int xL = (int) (x - 0.5);
  int xR = (int) (x + 0.5);
  
  int yU = (int) (y + 0.5);
  int yD = (int) (y - 0.5);
  
  double shade1 = (x - xR + 0.5) * (y - yU + 0.5);
  double shade2 = (xR - x + 0.5) * (y - yU + 0.5);
  double shade3 = (xR - x + 0.5) * (yU - y + 0.5);
  double shade4 = (x - xR + 0.5) * (yU - y + 0.5);
  
  shadePixel(R * shade1, G * shade1, B * shade1, xR, yU);
  shadePixel(R * shade2, G * shade2, B * shade2, xL, yU);
  shadePixel(R * shade3, G * shade3, B * shade3, xL, yD);
  shadePixel(R * shade4, G * shade4, B * shade4, xR, yD);
  */
  shadePixel(R, G, B, floor(x), floor(y));
}

void draw_edge(double x0, double y0, double x1, double y1, unsigned char R, unsigned char G, unsigned char B) {
  
  double slope = (double) (y1 - y0) / (x1 - x0);
  
  if (slope < 1 && slope > -1) {
    
    if (x1 < x0) {
      //printf("FLIP\n");
      draw_edge(x1, y1, x0, y0, R, G, B);
      return;
    }

    int x_curr = floor(x0 + 1);
    double y = y0 + (slope * (x_curr - x0 + 0.5));
    while (x_curr < ceil(x1 - 1)) {
      //double shade1 = y - floor(y - 0.5) - 0.5;
      //double shade2 = floor(y + 0.5) - y + 0.5;
      double shade1 = sqrt(y - floor(y - 0.5) - 0.5);
      double shade2 = sqrt(floor(y + 0.5) - y + 0.5);
      shadePixel(R * shade1, G * shade1, B * shade1, x_curr, (int) (y + 0.5));
      shadePixel(R * shade2, G * shade2, B * shade2, x_curr, (int) (y - 0.5));
      x_curr++;
      y += slope;
    }
    return;   
  }
  
  if (y1 < y0) {
    draw_edge(x1, y1, x0, y0, R, G, B);
    return;
  }
  
  int y_curr = floor(y0 + 1);
  double x = x0 + ((1/slope) * (y_curr - y0 + 0.5));
  while (y_curr < ceil(y1 - 1)) {
    //double shade1 = x - floor(x - 0.5) - 0.5;
    //double shade2 = floor(x + 0.5) - x + 0.5;
    double shade1 = sqrt(x - floor(x - 0.5) - 0.5);
    double shade2 = sqrt(floor(x + 0.5) - x + 0.5);
    shadePixel(R * shade1, G * shade1, B * shade1, (int) (x + 0.5), y_curr);
    shadePixel(R * shade2, G * shade2, B * shade2, (int) (x - 0.5), y_curr);
    y_curr++;
    x += 1/slope;
  }
}
