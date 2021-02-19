#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *matrix_newMatrix() --------------
Inputs: int cols 
Returns: 

The matrix struct contains an array of double arrays: m[cols][rows], or m[points][coords].
It also contains the integer "cols", which keeps track of the number of columns.
*/
struct matrix *matrix_newMatrix(int cols, int rows) {

  struct matrix *m = (struct matrix *) malloc(sizeof(struct matrix));
  m->cols = cols;
  m->rows = rows;
  m->nextCol = 0;
  double *temp = (double *) calloc(cols * rows, sizeof(double));
  m->m = (double **) calloc(cols, sizeof(double *));
  int i;
  for (i = 0; i < cols; i++) {
    m->m[i] = temp + rows*i;
  }
  return m;
}


/*-------------- void matrix_free() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual columns
2. free array holding column pointers
3. free actual matrix
*/
void matrix_free(struct matrix *m) {

  int i;
  for (i = 0; i < m->cols; i++) {
    free(m->m[i]);
  }
  free(m->m);
  free(m);
}

//////////////////////////////////////////////
/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of columns
====================*/
/*
int matrix_grow(struct matrix *m, int newcols) {

  int i;
  m = realloc(m, newcols * m->rows * sizeof(double)
  for (i = 0; i < m->rows; i++) {
    m->m[i] = realloc(m->m[i], newcols * sizeof(double));
  }
  m->cols = newcols;
}
*/////////////////////////////////////////////



/*======== int matrix_addPointFromCoords() ==========
Inputs:  struct matrix *m
         double x, y, z
Returns: The new number of points in the matrix, or 0 on failure (matrix already full).

Writes the given coordinates to the nextCol column of the given matrix.
Increments, and returns, nextCol.
====================*/
int matrix_addPointFromCoords(struct matrix *m, double x, double y, double z) {
  //printf("adding point\n");
  //printf("%d %d %d\n", m->rows, m->cols, m->nextCol);
  
  if (m->nextCol == m->cols) {
    return 0;
  }
  m->m[m->nextCol][0] = x;
  m->m[m->nextCol][1] = y;
  m->m[m->nextCol][2] = z;
  m->m[m->nextCol][3] = 1;
  m->nextCol++;
  //matrix_print(m);
  return m->nextCol;
}

/*======== int matrix_addPoint() ==========
Inputs:  struct matrix *m
         double *point 
Returns: The new number of points in the matrix, or 0 on failure (matrix already full).

Writes the given vector to the nextCol column of the given matrix.
Increments, and returns, nextCol.
====================*/
int matrix_addPoint(struct matrix *m, double *point) {
  if (m->nextCol == m->cols) {
    return 0;
  }
  m->m[m->nextCol][0] = point[0];
  m->m[m->nextCol][1] = point[1];
  m->m[m->nextCol][2] = point[2];
  m->m[m->nextCol][3] = 1;
  m->nextCol++;
  return m->nextCol;
}

/*======== int matrix_concatenate() ==========
Inputs:  struct matrix *a
         struct matrix *b
Returns: The new number of points in the matrix, or 0 on failure (not enough space in matrix a).

Merges together the two matrices into matrix a.
Adjusts, and returns, a->nextCol.
====================*/
int matrix_concatenate(struct matrix *a, struct matrix *b) {
  int i;
  for (i = 0; i < b->nextCol; i++) {
    if (!matrix_addPoint(a, b->m[i]))
      return 0;
  }
  return a->nextCol;
}

/*-------------- void matrix_print() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void matrix_print(struct matrix *m) {
  int i, j;
  for (i = 0; i < m->rows; i++) {
    for (j = 0; j <= m->nextCol; j++) {
      printf("%lf ", m->m[j][i]);
    }
    printf("\n");
  }
}


/*-------------- void matrix_scalarMult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void matrix_scalarMult(double x, struct matrix *m) {
  int i,j;
  for (i = 0; i < m->rows; i++) {
    for (j = 0; j < m->cols; j++) {
      m->m[i][j] *= x;
    }
  }
}


/*-------------- void matrix_matrixMult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 
a*b -> b
Assumes a->rows == a->cols == b->rows
e.g. a is a 4x4 transformation matrix, and b is an nx4 point matrix
*/
void matrix_matrixMult(struct matrix *a, struct matrix *b) {
  double buf[b->rows];
  int i,j,k;
  for (i = 0; i < b->cols; i++) {
      
    for (j = 0; j < a->rows; j++) {
      buf[j] = 0;
      for (k = 0; k < a->cols; k++) {
        buf[j] += a->m[k][j] * b->m[i][k];
      }
    }
    
    for (j = 0; j < a->rows; j++) {
      b->m[i][j] = buf[j];
    }
  }
}


/*-------------- void matrix_copy() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void matrix_copy(struct matrix *a, struct matrix *b) {
  int i,j;
  for (i = 0; i < b->rows; i++) {
    for (j = 0; j < b->cols; j++) {
      b->m[i][j] = a->m[i][j];
    }
  }
}


/*-------------- void matrix_ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void matrix_ident(struct matrix *m) {
  int i, j;
  for (i = 0; i < m->rows; i++) {
    for (j = 0; j < m->cols; j++) {
      if (i == j)
        m->m[i][j] = 1.;
      else
        m->m[i][j] = 0.;
    }
  } 
}


/*-------------- void matrix_clear() --------------
Inputs:  struct matrix *m
Returns: 

turn m into a zero matrix
*/
void matrix_clear(struct matrix *m) {
  int i,j;
  for (i = 0; i < m->rows; i++) {
    for (j = 0; j < m->cols; j++) {
      m->m[i][j] = 0.;
    }
  }
}

/*======== struct matrix *matrix_makeTranslate() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix *matrix_makeTranslate(double x, double y, double z) {
  struct matrix *m = matrix_newMatrix(4, 4);
  matrix_ident(m);
  m->m[3][0] = x;
  m->m[3][1] = y;
  m->m[3][2] = z;
  return m;
}

/*======== struct matrix *matrix_makeScale() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix *matrix_makeScale(double x, double y, double z) {
  struct matrix *m = matrix_newMatrix(4, 4);
  matrix_ident(m);
  m->m[0][0] = x;
  m->m[1][1] = y;
  m->m[2][2] = z;
  return m;
}

/*======== struct matrix *matrix_makeRotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix *matrix_makeRotX(double theta) {
  struct matrix *m = matrix_newMatrix(4, 4);
  matrix_ident(m);
  m->m[1][1] = cos(theta * M_PI / 180);
  m->m[2][1] = -sin(theta * M_PI / 180);
  m->m[1][2] = sin(theta * M_PI / 180);
  m->m[2][2] = cos(theta * M_PI / 180);
  return m;
}

/*======== struct matrix *matrix_makeRotY() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix *matrix_makeRotY(double theta) {
  struct matrix *m = matrix_newMatrix(4, 4);
  matrix_ident(m);
  m->m[0][0] = cos(theta * M_PI / 180);
  m->m[2][0] = -sin(theta * M_PI / 180);
  m->m[0][2] = sin(theta * M_PI / 180);
  m->m[2][2] = cos(theta * M_PI / 180);
  return m;
}

/*======== struct matrix *matrix_makeRotZ() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix *matrix_makeRotZ(double theta) {
  struct matrix *m = matrix_newMatrix(4, 4);
  matrix_ident(m);
  m->m[0][0] = cos(theta * M_PI / 180);
  m->m[1][0] = -sin(theta * M_PI / 180);
  m->m[0][1] = sin(theta * M_PI / 180);
  m->m[1][1] = cos(theta * M_PI / 180);
  return m;
}
