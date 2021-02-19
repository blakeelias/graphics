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
  screen s;
  struct matrix *P, *tmp, *A, *B, *C, *im, *nm;
   A = new_matrix(3,3);
   B = new_matrix(3,4);
   C = new_matrix(5,5);
   im = new_matrix(4,4);
   ident(im);
   nm = new_matrix(4, 6);
 
   P = new_matrix(4,1);
   P->m[0][0] = 2;
   P->m[1][0] = 2;
   P->m[2][0] = 3;
   P->m[3][0] = 1;

   tmp = make_translate(0.1,0.2,-10.5);
   print_matrix(tmp);
   matrix_mult(tmp,P);
   print_matrix(P);
  
  A->m[0][0] = 14;
  A->m[0][1] = 12;
  A->m[0][2] = 4;
  A->m[1][0] = 0;
  A->m[1][1] = -2;
  A->m[1][2] = -10;
  A->m[2][0] = 2;
  A->m[2][1] = 3;
  A->m[2][2] = -1;
  B->m[0][0] = 1;
  B->m[0][1] = 0;
  B->m[0][2] = -6;
  B->m[0][3] = 1;
  B->m[1][0] = 2;
  B->m[1][1] = 5;
  B->m[1][2] = 3;
  B->m[1][3] = 0;
  B->m[2][0] = -3;
  B->m[2][1] = 8;
  B->m[2][2] = 3;
  B->m[2][3] = 10;
  ident(C);

  printf("Matrix A:\n");
  print_matrix(A);
  printf("\n");

  printf("Scaling Matrix A by .5\n\n");
  scalar_mult(.5,A);

  printf("Matrix A:\n");
  print_matrix(A);
  printf("\n");

  printf("Matrix B:\n");
  print_matrix(B);
  printf("\n");

  printf("Multiplying Matrix A by Matrix B\n\n");
  matrix_mult(A,B);

  printf("Matrix B (product):\n");
  print_matrix(B);
  printf("\n");

  printf("Matrix C (the identity):\n");
  print_matrix(C);
  printf("\n");

  parse_file("script", im, nm, s);
  return 0;
}

void parse_file ( char * filename, 
	     struct matrix * transform, 
	     struct matrix * pm,
	     screen s) {
  FILE *f = fopen(filename, "r");
  // printf("OPEN SAYS ME\n");

  char line[256];
  color rgb;
  double add[6];
  rgb.red = 55;
  rgb.green = 55;
  rgb.blue = 55;
  struct matrix *temp;
  temp =  new_matrix(4,4);

  while(fscanf(f, "%s\n", line) != NULL){
    if(fscanf(f, "%s\n", line) == NULL){
      exit;
    }
     fgets(line, 256, f);
     printf("Hi\n");
     if(!(strcmp(line, "l\n"))){
      int i;
      for(i = 0; line[i] != NULL; i++){
	for(;line[i] == ' '; i++){
	  add[i++] = strtod(line + i, NULL);
	  for(;line[i] != ' ' && line[i] != NULL; i++);
	}
      }
      add_edge(pm, add[0], add[1], add[2], add[3], add[4], add[5]);
    }
    
    else if(!(strcmp(line, "i\n"))){
	ident(transform);
    }

    else if(!(strcmp(line, "s\n"))){
      temp = make_scale(add[0], add[1], add[2]);
      matrix_mult(temp, transform);
    }
    else if(!(strcmp(line, "t\n"))){
      temp = make_translate(add[0], add[1], add[2]);
      matrix_mult(temp, transform);
    }

    else if(!(strcmp(line, "x\n"))){
      temp = make_rotX(add[0]);
      matrix_mult(temp, transform);
    }

    else if(!(strcmp(line, "y\n"))){
      temp = make_rotY(add[0]);
      matrix_mult(temp, transform);
    }

    else if(!(strcmp(line, "z\n"))){
      temp = make_rotZ(add[0]);
      matrix_mult(temp, transform);
    }

    else if(!(strcmp(line, "a\n"))){
      matrix_mult(transform, pm);
    }

    else if(!(strcmp(line, "v\n"))){
      draw_lines(pm, s, rgb);
    }

    else if(!(strcmp(line, "g\n"))){
      save_extension(s, line);
    }

    else{
      printf("Unknown Command\n");
      break;
    }
  }
}
