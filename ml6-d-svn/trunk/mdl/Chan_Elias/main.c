#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "parametrics.h"
#include "splines.h"

void parse_file ( char * filename, 
		  struct matrix * transform, 
		  struct matrix * pm,
		  screen s);

int main() {

  struct matrix *transformation;
  struct matrix *points;
  screen s;
  color c;
  c.red = 0;
  c.green = 0;
  c.blue = 255;

  transformation = new_matrix(4, 4);
  ident(transformation);
  points = new_matrix(4, 1);
  points->lastcol = 0;
  
  //  render_parametric(points, circle_x, circle_y, 0.01);
  // draw_lines(points, s, c);

  parse_file("script", transformation, points, s);

  return 0;
}

void parse_file ( char * filename, 
	     struct matrix * transform, 
	     struct matrix * pm,
	     screen s) {
  FILE *in = fopen(filename, "r");
  char *command = calloc(256, sizeof(char));
  double args[10];
  struct matrix *new_transform;
  color c;
  c.red = 0;
  c.green = 0;
  c.blue = 255;
  int i, j;
  while ((i=fscanf(in, "%s\n", command)) && i != EOF) {
    printf("%s\n", command);
    switch (command[0]) {
    case 'l':
      fscanf(in, "%lf %lf %lf %lf %lf %lf", args, args+1, args+2, args+3, args+4, args+5);
      add_edge(pm, args[0], args[1], args[2], args[3], args[4], args[5]);
      break;
    case 'c':
      fscanf(in, "%lf %lf %lf %lf", args, args+1, args+2, args+3);
      circle_radius = args[0];
      circle_x_cor = args[1];
      circle_y_cor = args[2];
      render_parametric(pm, circle_x, circle_y, args[3]);
      break;
    case 'm':
      fscanf(in, "%lf %lf %lf", args, args+1, args+2);
      draw_sphere(pm, args[1], args[2], args[0]);
      break;
    case 'd':
      fscanf(in, "%lf %lf %lf %lf", args, args+1, args+2, args+3);
      draw_torus(pm, args[2], args[3], args[0], args[1]);
      break;
    case 'h':
      fscanf(in, "%lf %lf %lf %lf %lf %lf %lf %lf",
	     args, args+1, args+2, args+3, args+4, args+5, args+6, args+7);
      draw_hermite(pm, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
      break;
    case 'b':
      fscanf(in, "%lf %lf %lf %lf %lf %lf %lf %lf",
	     args, args+1, args+2, args+3, args+4, args+5, args+6, args+7);
      draw_bezier(pm, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
      break;

    case 'i':
      ident(transform);
      break;
    case 's':
      fscanf(in, "%lf %lf %lf", args, args+1, args+2);
      new_transform = make_scale(args[0], args[1], args[2]);
      matrix_mult(new_transform, transform);
      free_matrix(new_transform);
      break;
    case 't':
      fscanf(in, "%lf %lf %lf", args, args+1, args+2);
      new_transform = make_translate(args[0], args[1], args[2]);
      matrix_mult(new_transform, transform);
      free_matrix(new_transform);
      break;
    case 'x':
      fscanf(in, "%lf", args);
      new_transform = make_rotX(args[0]);
      matrix_mult(new_transform, transform);
      free_matrix(new_transform);
      break;
    case 'y':
      fscanf(in, "%lf", args);
      new_transform = make_rotY(args[0]);
      matrix_mult(new_transform, transform);
      free_matrix(new_transform);
      break;
    case 'z':
      fscanf(in, "%lf", args);
      new_transform = make_rotZ(args[0]);
      matrix_mult(new_transform, transform);
      free_matrix(new_transform);
      break;
    case 'a':
      matrix_mult(transform, pm);
      break;
    case 'v':
      draw_lines(pm, s, c);
      display(s);
      break;
    case 'g':
      fscanf(in, "%s\n", command);
      printf("%s\n", command);
      save_ppm(s, command);
      break;
    }
  }
}
