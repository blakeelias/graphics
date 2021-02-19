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
  for (i=0;i<m->rows;++i) 
    {
      for(j=0;j<m->cols;++j)
	printf("%f ",m->m[i][j]);
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
  int i,j;
  for(i=0;i<m->rows;++i)
    {
      for(j=0;j<m->cols;++j)
	{
	  if(i == j)
	    m->m[i][j] = 1;
	  else
	    m->m[i][j] = 0;
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
  int i,j;
  for(i=0;i<m->rows;++i)
    {
      for(j=0;j<m->cols;++j)
	{
	  m->m[i][j] = m->m[i][j] * x;
	}
    }
  return;
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
      for(x = 0; x < temp->cols; ++x)
	for(y = 0; y < temp->rows; ++y)
	  {
	    for(z = 0; z < i; ++z)
	      total += a->m[y][z] * b->m[z][x];
	    temp->m[y][x] = total;
	    total = 0;
	  }
      grow_matrix(b, temp->cols);
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
  int i,j;
  for(i = 0; i < a->rows; ++i)
    for(j = 0; j < a->cols; ++j)
      b->m[i][j] = a->m[i][j];
  return;
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/

struct matrix * make_translate(double x, double y, double z) {
  struct matrix *m = new_matrix(4,4);
  ident(m);
  m->m[0][3] = x;
  m->m[1][3] = y; 
  m->m[2][3] = z;
  return m;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y,double z) {
  struct matrix *m = new_matrix(4 , 4);
  ident(m);
  m->m[0][0] = x;
  m->m[1][1] = y;
  m->m[2][2] = z;
  return m;
}

inline double convert(double theta) {
  return M_PI * theta / 180;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  struct matrix *m = new_matrix(4,4);
  ident(m);
  double c = cos(convert(theta));
  double s = sin(convert(theta));
  m->m[1][1] = c;
  m->m[1][2] = -s;
  m->m[2][1] = s;
  m->m[2][2] = c;
  return m;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta
         char c 
Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  struct matrix *m = new_matrix(4,4);
  ident(m);
  double c = cos(convert(theta));
  double s = sin(convert(theta));
  m->m[0][0] = c;
  m->m[0][2] = s;
  m->m[2][0] = -s;
  m->m[2][2] = c;
  return m;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta
         char c 
Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  struct matrix *m = new_matrix(4,4);
  ident(m);
  double  c = cos(convert(theta));
  double s = sin(convert(theta));
  m->m[0][0] = c;
  m->m[0][1] = -s;
  m->m[1][0] = s;
  m->m[1][1] = c;
  return m;
}
