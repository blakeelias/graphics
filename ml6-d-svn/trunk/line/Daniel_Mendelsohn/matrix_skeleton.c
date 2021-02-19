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
  int i,j;
  for (i = 0; i < m->rows; i++) {
    for (j = 0; j < m->cols; j++)
      printf("%f ", m->m[i][j]);
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
  for (i = 0; i < m->rows; i++) {
    for (j = 0; j < m->cols; j++)
      m->m[i][j] = 0;
  }
  for (i = 0; i < m->rows; i++)
    m->m[i][i] = 1;
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i,j;
  for (i = 0; i < m->rows; i++) {
    for (j = 0; j < m->cols; j++)
      m->m[i][j] *= x;
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
struct matrix *matrix_mult(struct matrix *a, struct matrix *b) {
  struct matrix *temp;
  temp = new_matrix(a->rows, b->cols);
  int i,j,k,entry;
  for (i = 0; i < temp->rows; i++) {
    for (j = 0; j < temp->cols; j++) {
      entry = 0;
      for (k = 0; k < a->cols; k++)
	entry += (a->m[i][k] * b->m[k][j]);
      temp->m[i][j] = entry;
    }
  }
  b = new_matrix(a->rows, b->cols);
  for (i = 0; i < b->rows; i++) {
    for (j = 0; j < b-> cols; j++)
      b->m[i][j] = temp->m[i][j];
  }

  /*
  printf("Test print of temp in matrix_mult:\n");
  print_matrix(temp);
  printf("\n");*/

  //printf("calling copy\n");
  b = copy_matrix(temp,b);
  //printf("First entry in B right after exiting copy_matrix: %f\n", b->m[0][0]);
  free_matrix(temp);
  //printf("First entry in B right after freeing temp: %f\n", b->m[0][0]);
  return b;
  }


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
struct matrix *copy_matrix(struct matrix *a, struct matrix *b) {
  int i,j;
  b = new_matrix(a->rows, a->cols);
  for (i = 0; i < a->rows; i++) {
    for (j = 0; j < a-> cols; j++) {
      b->m[i][j] = a->m[i][j];
    }
  }
  //printf("First entry in B right before exiting copy_matrix: %f\n", b->m[0][0]);
  return b;
}

int main(){
  struct matrix *A,*B,*C, *AA;
  A = new_matrix(2,3);
  B = new_matrix(3,4);
  C = new_matrix(5,5);
  A->m[0][0] = 14;
  A->m[0][1] = 12;
  A->m[0][2] = 4;
  A->m[1][0] = 0;
  A->m[1][1] = -2;
  A->m[1][2] = -10;
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
  B = matrix_mult(A,B);

  printf("Matrix B (product):\n");
  print_matrix(B);
  printf("\n");

  printf("Matrix C (the identity):\n");
  print_matrix(C);
  printf("\n");
}
