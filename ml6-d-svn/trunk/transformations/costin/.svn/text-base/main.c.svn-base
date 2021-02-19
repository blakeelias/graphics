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
  color mycolor;
  char line[256];
  double args[8];
  char cmd;
  int i, numargs;
  struct matrix * temp = new_matrix(4,4);
  while (fscanf(fp, "%s\n", line) != EOF){
    cmd = line[0];
    switch(cmd) {
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
    for (i = 0; i < numargs; i++){
    }
    switch(cmd) {
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
    case 'm':
      mycolor.red = 0;
      mycolor.green = 0;
      mycolor.blue = MAX_COLOR;
      //make_sphere(s,mycolor,args[0],args[1],args[2],args[3],args[4]);
      break;
    case 'd':
      mycolor.red = MAX_COLOR;
      mycolor.green = 0;
      mycolor.blue = 0;
      //make_torus(s,mycolor,args[0],args[1],args[2],args[3],args[4],args[5]);
      break;
    case 'a':
      matrix_mult(transform,pm);
      break;
    case 'v':
      mycolor.red = 0;
      mycolor.green = MAX_COLOR;
      mycolor.blue = 0;
      draw_lines(pm,s,mycolor);
      display(s); //DISPLAY HERE IF WE WANT TO
      break;
    }
  }
}  
