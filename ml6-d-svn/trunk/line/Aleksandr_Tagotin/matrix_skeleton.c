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
int i=0;
int j=0;
for(;i<m->rows;i++)
 {
	for(;j<m->cols;j++)
	{
	printf("%d",m[i][j]);
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
int k= m->rows;
int i=0;
int j=0;
int c=0;
for (;i<m->rows;i++)
	{
	for(;j< m->cols;j++)
	 {
	  if(i==c&&j==c)
		{m[i][j]=1;}
	else {m[i][j]=0;}
	 }		
	c++;	
	}
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
int i=0;
int j=0;
 for(;i<m->rows;i++)
 {
  for(;j<m->cols;j++)
   {
	m[i][j]*=x;
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
int i=0;
int j=0;
int a=0;
int b=0;
int c= a->cols;
int k=0;
int sum=0;
matrix m = new_matrix(a->rows, b->cols);
for (;i<a->rows;i++)
 {
  for(;j<b->cols;j++)
  {
   sum=0;
   a=i;
   b=j;
   for(k=0;k<c;k++)
    {
     sum+=a[a][k]*b[b][k];
     k++;
     
    }

   
   m[i][j]=sum;
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
int i=0;
int j=0;

for(;i<m->rows;i++)
{
 for(;j<m->cols;j++)
 {
  b[i][j]=a[i][j];
 }
}

}

