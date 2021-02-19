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
	int i, j;
	i = j = 0;
	while (i < m->rows){
		j = 0;
		while (j < m->cols){
			printf("%f ", m->m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

/*-------------- void ident() --------------
 Inputs:  struct matrix *m <-- assumes m is a square matrix
 Returns: 
 
 turns m in to an identity matrix
 */
void ident(struct matrix *m) {
	int i, j;
	i = j = 0;
	while (i < m->rows){
		j = 0;
		while (j < m->cols){
			if (i == j)
				m->m[i][j] = 1;
			else
				m->m[i][j] = 0;
			j++;
		}
		i++;
	}
}


/*-------------- void scalar_mult() --------------
 Inputs:  double x
 struct matrix *m 
 Returns: 
 
 multiply each element of m by x
 */
void scalar_mult(double x, struct matrix *m) {
	int i, j;
	i = j = 0;
	while (i < m->rows){
		j = 0;
		while (j < m->cols){
			m->m[i][j] *= x;
			j++;
		}
		i++;
	}
}


/*-------------- void matrix_mult() --------------
 Inputs:  struct matrix *a
 struct matrix *b 
 Returns: 
 
 a*b -> b
 */
void matrix_mult(struct matrix *a, struct matrix *b) {
	struct matrix *temp;
	temp = new_matrix(b->rows, b->cols);
	
	int i, j, k, sum;
	i = j = k = sum = 0;
	while (i < b->rows){
		j = 0;
		while (j < b-> cols){
			sum = k = 0;
			while (k < b->rows && k < b->cols){
				sum += a->m[i][k] * b->m[k][j];
				k++;
			}
			temp->m[i][j] = sum;
			j++;
		}
		i++;
	}
	printf("temp:\n");
	print_matrix(temp);
	printf("\n\n");
	
	copy_matrix(temp, b);
	free_matrix(temp);
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

int main(){
	struct matrix *iseverywhere, *isasystem;
	
	iseverywhere = new_matrix(3,3);
	isasystem = new_matrix(3,3);
	
	int i, j;
	i = j = 0;
	while ( i < iseverywhere->rows){
		j = 0;
		while( j < iseverywhere-> cols){
			iseverywhere->m[i][j] = i + j + 2;
			isasystem->m[i][j] = i * j + 3;
			j++;
		}
		i++;
	}
	
	print_matrix(iseverywhere);
	printf("\n");
	print_matrix(isasystem);
	printf("\n");
	
	matrix_mult(iseverywhere, isasystem);
	printf("\n");
	print_matrix(isasystem);
	exit(0);
}