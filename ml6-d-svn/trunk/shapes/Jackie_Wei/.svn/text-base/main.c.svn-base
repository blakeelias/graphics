#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"

void parse_file ( char * filename, 
		  struct matrix * transform, 
		  struct matrix * pm,
		  screen s);

int main() {

  struct matrix *m;
  struct matrix *points;
  screen s;

  int r, c;
  r = 4;
  c = 4;

  m = new_matrix(r, c);
  points = new_matrix(r, 20);

  parse_file("stdin", m, points, s);

  free_matrix(points);
  free_matrix(m);

  return 0;
}

void parse_file ( char * filename, 
	     struct matrix * transform, 
	     struct matrix * pm,
	     screen s) {

  FILE *f;
  char line[256];
  struct matrix * tmp;
  double angle;
  color g;

  g.red = 0;
  g.green = 255;
  g.blue = 255;
  
  clear_screen(s);

   if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
    else
    f = fopen(filename, "script");
  
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    //printf(":%s:\n",line);
    char c;
    double x, y, z, x1, y1, z1, r, x2, x3, x4, y2, y3, y4;
    int mode;

    c = line[0];

    switch (c) {
    case 'l':
      //      printf("LINE!\n");
      fgets(line, 255, f);
      //      printf("\t%s", line);
      //line[strlen(line)-1]='\0';
      sscanf(line, "%lf %lf %lf %lf %lf %lf", &x, &y, &z, &x1, &y1, &z1);
      add_edge(pm, x, y, z, x1, y1, z1);
      // printf( "%lf %lf %lf %lf %lf %lf\n", x, y, z, x1, y1, z1);
      break;
     case 's':
      //printf("SCALE\n");
      fgets(line, 255, f);
      //line[strlen(line)-1]='\0';      
      sscanf(line, "%lf %lf %lf", &x, &y, &z);
      tmp = make_scale(x, y, z);
      matrix_mult(tmp, transform);
      //print_matrix(transform);
      break;
    case 't':
      //printf("TRANSLATE\n");
      fgets(line, 255, f);
      //      line[strlen(line)-1]='\0';      
      sscanf(line, "%lf %lf %lf", &x, &y, &z);
      tmp = make_translate(x, y, z);
      matrix_mult(tmp, transform);
      //print_matrix(transform);
      break;
    case 'x':
      //printf("ROTATE!\n");
      fgets(line, 255, f);
      sscanf(line, "%lf", &angle);
      angle = angle * (M_PI / 180);
      tmp = make_rotX( angle);
      matrix_mult(tmp, transform);
      break;
    case 'y':
      //printf("ROTATE!\n");
      fgets(line, 255, f);
      sscanf(line, "%lf", &angle);
      angle = angle * (M_PI / 180);
      tmp = make_rotY( angle);
      matrix_mult(tmp, transform);
      break;
    case 'z':
      //printf("ROTATE!\n");
      fgets(line, 255, f);
      sscanf(line, "%lf", &angle);
      angle = angle * (M_PI / 180);
      tmp = make_rotZ( angle);
      matrix_mult(tmp, transform);
      break;
    case 'i':
      ident(transform);
      break;
    case 'a':
      //printf("APPLY!\n");
      //print_matrix( transform );
      //      print_matrix(pm);
      matrix_mult(transform, pm);
      break;
    case 'v':
      //printf("VIEW\n");
      clear_screen(s);
      draw_lines(pm, s, g);
      display(s);
      break;
    case 'r':
      clear_screen(s);
      clear_matrix(pm);
      break;
    case 'c':
      fgets(line, 255, f);
      sscanf(line,"%lf %lf %lf %lf", &r, &x, &y, &z);
      //generate_circle(pm, r, x, y, z);
      render_circle(pm, r, x, y, z);
      break;
    case 'm':
      fgets(line, 255, f);
      sscanf(line,"%lf %lf %lf", &r, &x, &y);
      //generate_sphere_mesh(pm, r, x, y);
      render_sphere_mesh(pm, r, x, y);
      break;
    case 'd':
      fgets(line, 255, f);
      sscanf(line, "%lf %lf %lf %lf", &r, &z, &x, &y);
      generate_torus_mesh(pm, r, z ,x, y);
      //render_torus_mesh(pm, r, z, x, y);
      break;
    case 'h':
      fgets(line, 255, f);
      sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
      render_curve(pm, x1, y1, x2, y2, x3, y3, x4, y4);
      break;
    case 'g':
      fgets(line, 255, f);
      // line[strlen(line)-1] = '\0';
      draw_lines(pm, s, g);
      save_extension(s, line);
      break;
    case 'q':
      return;
    default:
      printf("Invalid command: %s:\n", line);
      break;
    }
  }

  free_matrix(tmp);
  fclose(f);
  //printf("END PARSE\n");
}  
