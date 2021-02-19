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
  for (i = 0; i< m->rows; i++)
    {for (j=0; j<m->cols; j++)
	{printf("%15lf",m->m[i][j]);
	}
      printf("\n");
    }
  printf("\n");
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i,j;
  for (i = 0; i< m->rows; i++)
    {for (j=0; j<m->cols; j++)
	{if (i==j)
	    m->m[i][j] = 1;
	    
	 else
	    m->m[i][j] = 0;
	    
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
  int i,j;
  for (i = 0; i< m->rows; i++)
    {for (j=0; j<m->cols; j++)
	{m->m[i][j] = m->m[i][j]*x;
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
  printf("multiplying\n\n");
  struct matrix *c;
  c = new_matrix(b->rows, b->cols);
  
 
  int i,j,k,l; 
  int temp = 0;
  for (k=0; k<b->cols; k++){
    for (i = 0; i< a->rows; i++)
      {for (j=0; j<b->rows; j++)
	  {
	   
	    temp = temp + a->m[i][j] * b->m[j][k];
	   
	  }
	c->m[i][k] = temp;

	temp = 0;
      }
  }
  copy_matrix(c,b);
  free_matrix(c);
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
  int i, j;
  i = j = 0;
  while (i < a->rows){
    j = 0;
    while (j < a->cols){
      b->m[i][j] = a->m[i][j];
      j++;
    }
    i++;
  }

}

int main()
{struct matrix *A,*B,*C,*D;
  A = new_matrix(4,3);
  A->m[0][0] = 14;
  A->m[0][1] = 9;
  A->m[0][2] = 3;
  A->m[1][0] = 2;
  A->m[1][1] = 11;
  A->m[1][2] = 15;
  A->m[2][0] = 0;
  A->m[2][1] = 12;
  A->m[2][2] = 17;
  A->m[3][0] = 5;
  A->m[3][1] = 2; 
  A->m[3][2] = 3;
  print_matrix(A);
 
  D = new_matrix(3,3);
  ident(D);
  
  B = new_matrix(3,2);
  B->m[0][0]=12;
  B->m[0][1]=25;
  B->m[1][0]=9;
  B->m[1][1]=10;
  B->m[2][0]=8;
  B->m[2][1]=5;
  print_matrix(B);
  
   matrix_mult(D,B);
   print_matrix(B);

   // matrix_mult(A,B);
   // print_matrix(B);

  scalar_mult(4,A);
  scalar_mult(5,B);
  print_matrix(A);
  print_matrix(B);

  C = new_matrix(4,3);
  copy_matrix(A,C);
  print_matrix(C);
  
 
  
  return 0;
  


}
