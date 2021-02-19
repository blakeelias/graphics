#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"

/*
NB: accd the SVN logs, Daniel Mendelsohn overwrote the base source with a completely working copy of the code, and I cannot find where I left my other copies of the base.
I will still try to add as much of my own code as possible, but I am not going out of my way to break existing code and remake it.
*/


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
  //printf("Made it into parse file\n");
  FILE* fp = fopen(filename, "r");
  //printf("Fopen success\n");
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
     fscanf(fp, "%s\n", line);
	break;
    case 'z':
      fgets(line, 256, fp);
      numargs = 0;
      for(i = 0; line[i] != '\0'; i++){
	for(; line[i] == ' '; i++);
	args[numargs++] = strtod(line + i, NULL);	
	for(; line[i] != ' ' && line[i] != '\0'; i++);
      }
      break;
    default:
      break;
    }
    for (i = 0; i < numargs; i++){
    }
    switch(cmd) {
    case 'l':
      //printf("implementing 'l'\n");
      add_edge(pm, args[0], args[1], args[2], args[3], args[4], args[5]);
      int i;
      //for (i = 0; i < 6; i++)
      //printf("%f, \n", args[i]);
      //print_matrix(pm);
      break; //do I need to do this?
    case 's':
      //printf("implementing 's'\n");
      temp = make_scale(args[0],args[1],args[2]);
      matrix_mult(temp,transform);
      //printf("Transform:\n");
      //print_matrix(transform);
      break;
    case 't':
      //printf("implementing 't'\n");
      temp = make_translate(args[0],args[1],args[2]);
      matrix_mult(temp,transform);
      //printf("Transform:\n");
      //print_matrix(transform);
      break;
    case 'x':
      //printf("implementing 'x'\n");
      temp = make_rotX(args[0]);
      matrix_mult(temp,transform);
      //printf("Transform:\n");
      //print_matrix(transform);
      break;
    case 'y':
      //printf("implementing 'y'\n");
      temp = make_rotY(args[0]);
      //printf("Rotation Y by %f radians yields the temp matrix:\n", args[0]);
      //print_matrix(temp);
      matrix_mult(temp,transform);
      //printf("Transform:\n");
      //print_matrix(transform);
      break;
    case 'z':
      //printf("implementing 'z'\n");
      temp = make_rotZ(args[0]);
      matrix_mult(temp,transform);
      //printf("Transform:\n");
      //print_matrix(transform);
      break;
    case 'g':
      //printf("implementing 'g'\n");
      //printf("entering save_extension for filename %s\n", line);
      printf("Apparently switching case g is supposed to dump crap?\n");
      save_extension(s,line);
      //printf("exiting save_extension for filename %s\n", line);
      break;
    case 'i':
      //printf("implementing 'i'\n");
      ident(transform);
      //printf("Transform:\n");
      //print_matrix(transform);
      break;
    case 'a':
      //printf("implementing 'a'\n");
      //print_matrix(transform);
      matrix_mult(transform,pm);
      //print_matrix(pm);
      break;
    case 'v':
      //printf("implementing 'v'\n");
      mycolor.red = 0;
      mycolor.green = MAX_COLOR;
      mycolor.blue = 0;
      //printf("calling draw_lines\n");
      draw_lines(pm,s,mycolor);
      //printf("called draw_lines\n");
      //display(s);
      break;
    }
  }
}  
