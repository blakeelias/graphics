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
	int i,h;
	for (i=0;i<m->rows;i++){
      	for(h=0;h<m->cols;h++){
	printf("%f ",m->m[i][h]);}
      printf("\n");
    }
  return;
}


/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {  
	int i,h;
  for(i=0;i<m->rows;i++)
    {
      for(h=0;h<m->cols;h++)
	{
	  if(i==h)
	    m->m[i][h] = 1;
	  else
	    m->m[i][h] = 0;
	}
    }
  return;
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
 	 if(a->cols != b->rows)
   	 {
     	 printf("cannot multiply\n");
    	  return;
   	 }
 	 else
  	  {
    	  int x,y,z;
    	  int i = a->cols;
    	  double total = 0;
     	 struct matrix *temp = new_matrix(a->rows, b->cols);
     	 for(x = 0;x<temp->cols;x++)
		for(y=0;y<temp->rows;y++)
		  {
	  	  for(z=0;z<i;z++)
	      total += a->m[y][x]*b->m[x][y];
	  	  temp->m[x][y] = total;
	 	 }
      	copy_matrix(temp,b);
     	 free_matrix(temp);
    	}
 	 return;
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
	int x,y;
	int a = a->rows;
	int aa = a->cols;
	for(x=0;x<a;x++)	{
		for(y=0;y<b;y++)			{
			b->b[x][y]=a->a[x][y];}
				}
return; 

}

