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
  int i,n;
  for(i = 0; i < m->rows; i++){
    for(n = 0; n < m->cols; n++){
      printf("%f ", m->m[i][n]);
    }
    printf("\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i,n;
  for(i = 0; i < m->rows; i++){
    for(n = 0; n < m->cols; n++){
      if(i == n)
	m->m[i][n] = 1;
      else
	m->m[i][n] = 0;
    }
  }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i,n;
  for(i = 0; i < m->rows; i++){
    for(n = 0; n < m-> cols; n++){
      m->m[i][n] = m->m[i][n] * x;
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
  int acol = a->cols;
  int arow = a->rows;
  int bcol = b->cols;
  int brow = b->rows;
  int i,n,y;
  int p = 0;
  int x = 0;

  for(i = 0; i < arow; i++){
    y = b->m[p][x];
    b->m[p][x] = 0;
    for(n = 0; i < acol; i++){
      b->m[p][x] = (b->m[p][x] += y * a->m[i][n]);
    }
    if(p < brow)
      p++;
    else{
      x++;
      p = 0;
    }
  }
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
  int i,n;
  for(i = 0; i < a->rows; i++){
    for(n = 0; i < a->cols; i++){
      b->m[i][n] = a->m[i][n];
    }
  }
}