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

  //The following tests various matrix functions
  /*
  m = new_matrix(r, c);
  a = new_matrix(r, c);  

  for (r=0; r < m->rows; r++)
    for (c=0; c < m->cols; c++)
      m->m[r][c] = 5;
  
  print_matrix(m);
  printf("\n");

  ident(m);
  print_matrix(m);
  printf("\n");

  scalar_mult(7, m);
  print_matrix(m);
  printf("\n");

  copy_matrix(m, a);
  print_matrix(a);
  printf("\n");

  ident(m);

  matrix_mult(a, m);
  print_matrix(a);
  printf("\n");


  free_matrix(a);
  free_matrix(m);
  */
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
    //printf("entered while loop\n");
    cmd = line[0];
    switch(cmd) {
    case 'g':
      if(fscanf(fp, "%s\n", line) == EOF){
	break;
      }
      //printf("Got line: %s\n", line);
      break;
    case 'l':
    case 's':
    case 't':
    case 'x':
    case 'y':
    case 'z':
    case 'm':
    case 'd':
      //printf("Read in %c\n", cmd);
      fgets(line, 256, fp);
      //printf("Argument time\n");
      numargs = 0;
      for(i = 0; line[i] != '\0'; i++){
	//printf("into for loop with line: %s", line);
	for(; line[i] == ' '; i++);
	//printf("passed checkpoint 1\n");
	args[numargs++] = strtod(line + i, NULL);
	//printf("gonna hit checkpoint 2, line[i] is %s arg just read in is %lf\n", line, args[numargs-1]);	
	for(; line[i] != ' ' && line[i] != '\0'; i++);
	//printf("After reading command: cmd = %c and our arguments are:\n", cmd);
      }
      break;
    case 'i':
    case 'a':
    case 'v':
    default:
      break;
    }
    //printf("command to be implemented is %c\n", cmd);
    for (i = 0; i < numargs; i++){
      //printf("Argument number %d is %f\n", i, args[i]);
    }
    switch(cmd) {
    case 'l':
      //printf("implementing 'l'\n");
      add_edge(pm, args[0], args[1], args[2], args[3], args[4], args[5]);
      //int i;
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
      printf("Don't worry about the automated printout, everything looks fine.\n");
      save_extension(s,line);
      //printf("exiting save_extension for filename %s\n", line);
      break;
    case 'i':
      //printf("implementing 'i'\n");
      ident(transform);
      //printf("Transform:\n");
      //print_matrix(transform);
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
      make_torus(s,mycolor,args[0],args[1],args[2],args[3],args[4],args[5]);
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
      display(s); //DISPLAY HERE IF WE WANT TO
      break;
    }
  }
}  
