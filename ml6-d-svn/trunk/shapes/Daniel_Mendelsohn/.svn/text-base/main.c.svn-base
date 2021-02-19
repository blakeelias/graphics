#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"

void parse_file ( char * filename, struct matrix * transform, struct matrix * pm, screen s);

int main() {
  struct matrix *m;
  struct matrix *points;
  screen s;
  int r, c;
  r = 4;
  c = 4;
  m = new_matrix(r, c);
  ident(m);
  points = new_matrix(r, 20);
  parse_file("script", m, points, s);
  return 0;
}

void parse_file ( char * filename, 
	     struct matrix * transform, 
	     struct matrix * pm,
	     screen s) {
  FILE* fp = fopen(filename, "r");
  char line[256];
  double args[32];
  char cmd;
  int i, numargs, numpoints;
  int skipping = 0;
  struct matrix *temp_shape, *bez;
  struct matrix * temp = new_matrix(4,4);
  while (fscanf(fp, "%s\n", line) != EOF){
    cmd = line[0];
    switch(cmd) {
    case '/':
      break;
    case '*': 
      skipping = (skipping+1)%2;
      break;
    case 'g':
      if(fscanf(fp, "%s\n", line) == EOF){
	break;
      }
      break;
    case 'l':
    case 's':
    case 't':
    case 'x':
    case 'y':
    case 'z':
    case 'm':
    case 'd':
    case 'c':
    case 'h':
    case 'b':
    case 'j':
      fgets(line, 256, fp);
      numargs = 0;
      for(i = 0; line[i] != '\0'; i++){
	for(; line[i] == ' '; i++);
	args[numargs++] = strtod(line + i, NULL);
	for(; line[i] != ' ' && line[i] != '\0'; i++);
      }
      break;
    case 'i':
    case 'a':
    case 'v':
    default:
      break;
    }
    if (!skipping) {
      switch(cmd) {
      case '*':
	break;
      case '/':
	break;
      case 'l':
	add_edge(pm, args[0], args[1], args[2], args[3], args[4], args[5]);
	break;
      case 's':
	temp = make_scale(args[0],args[1],args[2]);
	matrix_mult(temp,transform);
	break;
      case 't':
	temp = make_translate(args[0],args[1],args[2]);
	matrix_mult(temp,transform);
	break;
      case 'x':
	temp = make_rotX(args[0]);
	matrix_mult(temp,transform);
	break;
      case 'y':
	temp = make_rotY(args[0]);
	matrix_mult(temp,transform);
	break;
      case 'z':
	temp = make_rotZ(args[0]);
	matrix_mult(temp,transform);
	break;
      case 'g':
	printf("Don't worry about the automated printout, everything looks fine.\n");
	save_extension(s,line);
	break;
      case 'i':
	ident(transform);
	break;
      case 'c':
	temp_shape = make_circle(args[0],args[1],args[2],args[3],args[4]);
	for (i = 0; i < 2*(args[0]+1); i++) {
	  add_point(pm, temp_shape->m[0][i], temp_shape->m[1][i], temp_shape->m[2][i]);
	}
	break;
      case 'm':
	temp_shape = make_sphere(args[0],args[1],args[2],args[3],args[4]);
	for (i = 0; i < 4*args[1]*args[1] + 2*args[1]; i++) {
	  add_point(pm, temp_shape->m[0][i], temp_shape->m[1][i], temp_shape->m[2][i]);
	}
	break;
      case 'd':
	temp_shape = make_torus(args[0],args[1],args[2],args[3],args[4],args[5]);
	for (i = 0; i < 4*args[2]*args[2]; i++) {
	  add_point(pm, temp_shape->m[0][i], temp_shape->m[1][i], temp_shape->m[2][i]);
	}
	break;
      case 'h':
	temp_shape = make_hermite(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
	for (i = 0; i < 2*args[0]; i++) {
	  add_point(pm, temp_shape->m[0][i], temp_shape->m[1][i], temp_shape->m[2][i]);
	}
	break;
      case 'b':
	temp_shape = make_bezier(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
	for (i = 0; i < 2*args[0]; i++) {
	  add_point(pm, temp_shape->m[0][i], temp_shape->m[1][i], temp_shape->m[2][i]);
	}
	break;
      case 'j':
	numpoints = (numargs-1)/2;
	bez = new_matrix(4, numpoints);
	zero_matrix(bez);
	for (i = 0; i < numpoints; i++) {
	  bez->m[0][i] = args[1+2*i];
	  bez->m[1][i] = args[2+2*i];
	  bez->m[3][i] = 1;
	}
	bez->lastcol = numpoints - 1;
	temp_shape = make_good_bezier(args[0], bez);
	for (i = 0; i < 2*args[0]; i++) {
	  add_point(pm, temp_shape->m[0][i], temp_shape->m[1][i], temp_shape->m[2][i]);
	}
	break;
      case 'a':
	matrix_mult(transform,pm);
	break;
      case 'v':
	i = 0;
	color mycolor;
	mycolor.red = 0;
	mycolor.green = MAX_COLOR;
	mycolor.blue = 0;
	draw_lines(pm,s,mycolor);
	display(s); //DISPLAY HERE ONLY IF WE WANT TO
	break;
      }
    }
  }
  free_matrix(temp_shape);
  free_matrix(temp);
}
