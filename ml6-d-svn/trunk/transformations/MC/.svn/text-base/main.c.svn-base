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
  struct matrix *a;
  struct matrix *points;
  screen s;

  int r, c;
  r = 4;
  c = 4;

  m = new_matrix(r, c);
  ident(m);
  //print_matrix(m);
  points = new_matrix(r, 20);

  parse_file("script", m, points, s);

  //The following tests various matrix functions
  /*
  m = new_matrix(r, c);
  a = new_matrix(r, c);  
  //print_matrix(m);
  //printf("\n");
  //print_matrix(a);
  //printf("\n");

  for (r=0; r < m->rows; r++)
    for (c=0; c < m->cols; c++)
      m->m[r][c] = 5;


  //printf("\n");
  //print_matrix(m);
  ident(a);
  print_matrix(m);
  printf("\n");
  scalar_mult(7, m);
  matrix_mult(a, m);
  print_matrix(m);
  printf("\n");

  //copy_matrix(m, a);
  print_matrix(a);
  printf("\n");

  ident(m);

  matrix_mult(a, m);
  print_matrix(m);
  printf("\n");


  free_matrix(a);
  free_matrix(m);
*/  
  return 0;

}

void parse_file ( char * filename, struct matrix * tf, struct matrix * pt, screen s) {

FILE* f = fopen(filename, "r");

char * buf=calloc(256,sizeof(char));
int chr=1;
char * tmpp;
int p;
double d[6];
struct matrix * tmp=new_matrix(4,4);

color G;
	G.red = 0;
	G.green = MAX_COLOR;
	G.blue = 0;

while(1){
buf=calloc(256,sizeof(char));
if(fgets(buf,256,f)==NULL){break;}
if(chr){
switch(buf[0]){
//listxyzavg

case 'l':
//fprintf(stderr,"TESTING L\n");
 fgets(buf,256,f);
 p=0;
// fprintf(stderr,"FGETS PASS\n");

  
  tmpp=strtok(buf," ");
  while(tmpp!=NULL){
    d[p]=atof(tmpp);
    tmpp=strtok (NULL," ");
    p++;
  }
 add_edge(pt, d[0], d[1], d[2], d[3], d[4], d[5]);
 break;

case 'i':
 ident(tf);
 break;

case 's':
 fprintf(stderr,"TESTING S");
 fgets(buf,256,f);
 p=0;
  tmpp=strtok(buf," ");
  while(tmpp!=NULL){
    d[p]=atof(tmpp);
    tmpp=strtok (NULL," ");
    p++;
  }
 tmp=make_scale(d[0], d[1], d[2]);
 matrix_mult(tmp,tf);
 break;

case 't':  fgets(buf,256,f);
 p=0;
 tmpp=strtok(buf," ");
  while(tmpp!=NULL){
    d[p]=atof(tmpp);
    tmpp=strtok (NULL," ");
    p++;
  }
 tmp=make_translate(d[0], d[1], d[2]);
 matrix_mult(tmp,tf);
 break;

case 'x':
 fgets(buf,256,f);
 tmp=make_rotX(atof(buf));
 matrix_mult(tmp,tf);
 break;

case 'y': 
 fgets(buf,256,f);
 tmp=make_rotY(atof(buf));
 matrix_mult(tmp,tf);
 break;

case 'z':
 fgets(buf,256,f);
 tf=make_rotZ(atof(buf));
 matrix_mult(tmp,tf);
 break;

case 'a':
 matrix_mult(tf, pt);
 break;

case 'v':   
 //fprintf(stderr,"TESTING V");
 draw_lines(pt,s,G);
 display(s);
 break;

case 'g': 
 save_extension(s,buf);
 break;

default: break;

}}
free(buf);
}
	
}
