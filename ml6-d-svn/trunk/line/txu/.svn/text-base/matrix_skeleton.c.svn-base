#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
  m->lastcol = 0;

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
newcols number of collumns
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
  int i,j;
  for(i=0;i<m->rows;i++)
    {
      for(j=0;j<m->cols;j++)
	  printf("%.2f ",m->m[i][j]);
      printf("\n");
    }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i,j;
  for(i=0;i<m->rows;i++)
    for(j=0;j<m->cols;j++)
      if(i==j)
	m->m[i][j]=1;
      else
	m->m[i][j]=0;
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i,j;
  for(i=0;i<m->rows;i++)
    for(j=0;j<m->cols;j++)
      m->m[i][j]*=x;
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  int c;
  if ((c=a->cols) != b->rows)
    return;
  struct matrix *product = new_matrix(a->rows, b->cols);

  int i,j,k;
  int sum;
  for(i=0; i < a->rows; i++){
    for(j=0; j < b->cols; j++){
      sum = 0;
      for(k=0; k<a->cols; k++){
        sum += a->m[i][k] * b->m[k][j];
      }
      product->m[i][j]=sum;
    }
  }
  product->cols=b->cols;
  copy_matrix(product,b);
  free_matrix(product);
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
  int i,j;
  b=new_matrix(a->rows,a->cols);
  for(i=0;i<a->rows;i++)
    for(j=0;j<a->cols;j++)
      b->m[i][j]=a->m[i][j];
}

void make_translate(int x, int y, int z, struct matrix *m){
  struct matrix *t = new_matrix(4,4);
  ident(t);
  t->m[0][3]=x;
  t->m[1][3]=y;
  t->m[1][3]=z;
  matrix_mult(t,m);
  free_matrix(t);
}

void make_scale(int x, int y, int z, struct matrix *m){
  struct matrix *s = new_matrix(4,4);
  ident(s);
  s->m[0][0]=x;
  s->m[1][1]=y;
  s->m[2][2]=z;
  matrix_mult(s,m);
  free_matrix(s);
}

void make_rotX(int deg, struct matrix *m){
  struct matrix *x = new_matrix(4,4);
  int rad = deg*M_PI/180;
  ident(x);
  x->m[1][1]=cos(rad);
  x->m[1][2]=-1*sin(rad);
  x->m[2][1]=sin(rad);
  x->m[2][2]=cos(rad);
  matrix_mult(x,m);
  free_matrix(x);
}

void make_rotY(int deg, struct matrix *m){
  struct matrix *y = new_matrix(4,4);
  int rad = deg*M_PI/180;
  ident(y);
  y->m[0][0]=cos(rad);
  y->m[0][2]=sin(rad);
  y->m[2][0]=-1*sin(rad);
  y->m[2][2]=cos(rad);
  matrix_mult(y,m);
  free_matrix(y);
}

void make_rotZ(int deg, struct matrix *m){
  struct matrix *z = new_matrix(4,4);
  int rad = deg*M_PI/180;
  ident(z);
  z->m[0][0]=cos(rad);
  z->m[0][1]=-1*sin(rad);
  z->m[1][0]=sin(rad);
  z->m[1][1]=cos(rad);
  matrix_mult(z,m);
  free_matrix(z);
}
