#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define R2D 180.0/M_PI
#define D2R M_PI/180.0
#include "matrix.h"


/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/

struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = cols;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of columns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
    }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
int xx=m->rows;
int yy=m->cols;
int x;
int y;


for(x=0;x<xx;++x){
	printf("\n");
	for(y=0;y<yy;++y){
		printf("|%f|",m->m[x][y]); 
	}
}

}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
fprintf(stderr,"calling IDENT\n");
int xx=m->rows;
int yy=m->cols;
int x;
int y;


for(x=0;x<xx;++x){
	//printf("\n");
	for(y=0;y<yy;++y){
		m->m[x][y]=0;		
	}
}

for(x=0;x<xx;++x){m->m[x][x]=1;}
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double xd, struct matrix *m) {
//fprintf(stderr,"calling SCALAR\n");
int xx=m->rows;
int yy=m->cols;
int x;
int y;


for(x=0;x<xx;++x){
	for(y=0;y<yy;++y){
		m->m[x][y]=m->m[x][y]*xd;
			
	}
}

}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/

void matrix_mult(struct matrix *a, struct matrix *b) {
//fprintf(stderr,"calling DOTMULT\n");

struct matrix * f;
f=new_matrix(a->rows,b->cols);
//fprintf(stderr,"A:(%d,%d) \nB:(%d,%d)\nF:(%d,%d)",a->rows,a->cols,b->rows,b->cols,f->rows,f->cols);
int x;
int y;
int z;
//fprintf(stderr,"MULTIPLYING");
for(y=0;y<(f->cols);++y){
	for(x=0;x<(f->rows);++x){
		f->m[x][y]=0;
		for(z=0;z<(a->cols);++z){	
			//fprintf(stderr,"X:%d Y:%d Z:%d \n",x,y,z);	
			f->m[x][y]=f->m[x][y]+((a->m[x][z])*(b->m[z][y]));
		}
	}
}
//fprintf(stderr,"FREEING");
copy_matrix(f,b);
free_matrix(f);
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
//fprintf(stderr,"calling MATCOP\n");
int xx=a->rows;
int yy=a->cols;
int x;
int y;


for(x=0;x<xx;++x){
	for(y=0;y<yy;++y){
		b->m[x][y]=a->m[x][y];
	}
}

}

/*======== struct matrix * make_translate() ==========
Inputs:  double x
         double y
         double z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
  struct matrix *a;
  a = new_matrix(4,4);
  ident(a);
  a->m[0][3] = x;
  a->m[1][3] = y;
  a->m[2][3] = z;
  return a;
}

/*======== struct matrix * make_scale() ==========
Inputs:  double x
         double y
         double z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
  struct matrix *a;
  a = new_matrix(4,4);
  ident(a);
  a->m[0][0] = x;
  a->m[1][1] = y;
  a->m[2][2] = z;
  return a;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  struct matrix *a;
  a = new_matrix(4,4);
  ident(a);
  a->m[1][1] = cos(theta * D2R);
  a->m[2][1] = -1 * sin(theta * D2R);
  a->m[1][2] = sin(theta * D2R);
  a->m[2][2] = cos(theta * D2R);
  return a;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta
         char c 
Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  struct matrix *a;
  a = new_matrix(4,4);
  ident(a);
  a->m[0][0] = cos(theta * D2R);
  a->m[2][0] = sin(theta * D2R);
  a->m[0][2] = -1 * sin(theta * D2R);
  a->m[2][2] = cos(theta * D2R);
  return a;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta
         char c 
Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  struct matrix *a;
  a = new_matrix(4,4);
  ident(a);
  a->m[0][0] = cos(theta * D2R);
  a->m[1][0] = -1 * sin(theta * D2R);
  a->m[0][1] = sin(theta * D2R);
  a->m[1][1] = cos(theta * D2R);
  return a;
}

