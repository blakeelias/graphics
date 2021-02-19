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

  parse_file("test", m, points, s);
  //print_matrix(points);
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
  ident(transform);
  g.red = 0;
  g.green = 255;
  g.blue = 255;
  
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");
  
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    //printf(":%s:\n",line);
    char c;
    double x, y, z, x1, y1, z1, r, stepsize, x_off, y_off, large_r;
    double c_x1, c_y1, c_x2, c_y2, c_x3, c_y3, c_x4, c_y4;
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
    case 'c':
      fgets(line, 255, f);
      sscanf(line,"%lf %lf %lf %lf", &r,&x_off,&y_off,&stepsize);
      // printf("%lf %lf %lf %lf", r, x_off, y_off, stepsize);
      render_circle(pm,r,x_off,y_off,stepsize);
      //print_matrix(pm);
      break;
    case 'm':
      fgets(line, 255, f);
      sscanf(line, "%lf %lf %lf", &r, &x_off, &y_off);
      // printf("%lf %lf %lf %lf", r, x_off, y_off, stepsize);
      render_sphere_mesh(pm,r,x_off,y_off,.025);
      break;
    case 'd':
      fgets(line, 255, f);
      sscanf(line, "%lf %lf %lf %lf",&large_r, &r, &x_off, &y_off);
      // printf("%lf %lf %lf %lf", r, x_off, y_off, stepsize);
      render_torus_mesh(pm,large_r,r,x_off,y_off,.05);
      break;
    case 'h':
      fgets(line,255,f);
      sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf", &c_x1, &c_y1, &c_x2, &c_y2, &c_x3, &c_y3, &c_x4, &c_y4);
      render_hcurve(pm, c_x1, c_y1, c_x2, c_y2, c_x3, c_y3, c_x4, c_y4, .01);
      break;
case 'b':
      fgets(line,255,f);
      sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf", &c_x1, &c_y1, &c_x2, &c_y2, &c_x3, &c_y3, &c_x4, &c_y4);
      render_bcurve(pm, c_x1, c_y1, c_x2, c_y2, c_x3, c_y3, c_x4, c_y4, .01);
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
    case 'g':
      fgets(line, 255, f);
      //printf("end");
      // line[strlen(line)-1] = '\0';
      draw_lines(pm, s, g);
      //printf("end");
      save_extension(s, line);
      // printf("end");
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
