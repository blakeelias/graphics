#include "globals.h"
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

matrix *matrix_new(int cols, int rows){
	matrix *o;
	o = malloc(sizeof(matrix));
	o->ar = rows;
	o->ac = cols;
	o->nc = 0;
	o->m = malloc(cols * sizeof(matrix_t **));
	matrix_t *tmp;
	tmp = malloc(rows * cols * sizeof(matrix_t));
	int i;
	for(i = 0; i < cols; i++){
		o->m[i] = tmp + (i * rows);
	}
	return o;
}

/*
void matrix_col_resize(matrix *m, int cols){
	int oldcols;
	//oldcols = m->ac;
	m->ac = cols;
	matrix_t *tmp;
	debug_w("matrix_col_resize: new array size: %x", m->ar * cols * sizeof(matrix_t));
	tmp = m->m[0] = realloc(m->m[0], m->ar * cols * sizeof(matrix_t));
	m->m = realloc(m->m, cols * sizeof(matrix_t *));
	debug_w("matrix_col_resize: new array start: %x", (unsigned int)  tmp);
	for(oldcols = 1; oldcols < cols; oldcols++){
		//fprintf(stderr, "matrix_col_resize: pointer increment: %x\n", m->ar * sizeof(matrix_t));
		m->m[oldcols] = tmp + (oldcols * m->ar);
	}

	if(m->nc > m->ac){
		m->nc = m->ac;
	}
}
*/

void matrix_resize(matrix *m, int cols, int rows){
	matrix_t *tmp;
	tmp = m->m[0] = realloc(m->m[0], rows * cols * sizeof(matrix_t));
	m->m = realloc(m->m, cols * sizeof(matrix_t **));
	int i;
	for(i = 1; i < cols; i++){
		m->m[i] = tmp + (i * rows);
	}
	m->ar = rows;
	m->ac = cols;
	if(m->nc > m->ac){
		m->nc = m->ac;
	}
}

void matrix_free(matrix *m){
	free(m->m[0]);
	free(m->m);
	free(m);
}

void matrix_print(matrix *m){
	int i, j;
	printf("[\n  ar: %d, ac: %d, nc: %d.\n  [ ", m->ar, m->ac, m->nc);
	for(i = 0; i < m->ac; i++){
		printf("%11x ", (unsigned int) m->m[i]);
	}
	printf("]\n");
	for(i = 0; i < m->ar; i++){
		printf("  [ ");
		for(j = 0; j < m->ac; j++){
			printf("%11lf ", m->m[0][i + m->ar*j]);
		}
		printf("]\n");
	}
	printf("]\n");
}

void matrix_make_zero(matrix *m){
	int i;
	for(i = 0; i < m->ac * m->ar; i++){
		m->m[0][i] = 0;
	}
}

void matrix_make_ident(matrix *m){
	int i, j;
	for(i = 0; i < m->ac; i++){
		for(j = 0; j < m->ar; j++){
			if(i == j){
				m->m[i][j] = 1;
			} else {
				m->m[i][j] = 0;
			}
		}
	}
}

void matrix_scalar_mult(matrix *m, matrix_t multiple){
	int i, j;
	for(i = 0; i < m->ac; i++){
		for(j = 0; j < m->ar; j++){
			m->m[i][j] *= multiple;
		}
	}
}

void matrix_mult(matrix *a, matrix *b, matrix *o){
	int i, j, k;
	matrix_t tmp;
	matrix_t **ma, **mb, **mo;
	ma = a->m;
	mb = b->m;
	mo = o->m;
	for(i = 0; i < a->ar; i++){
		for(j = 0; j < b->ac; j++){
			tmp = ma[0][i] * mb[j][0];
			for(k = 1; k < a->ac; k++){
				tmp += ma[k][i] * mb[j][k];
			}
			mo[j][i] = tmp;
		}
	}			
}

void matrix_mult_inplace(matrix *a, matrix *b){	
	//matrix_print(a);
	//matrix_print(b);
	int i, j, k;
	int orows = b->ar;
	matrix_t mt[a->ar * b->ac];
	matrix_t tmp;
	matrix_t **ma, **mb;
	ma = a->m;
	mb = b->m;
	for(i = 0; i < a->ar; i++){
		for(j = 0; j < b->ac; j++){
			tmp = ma[0][i] * mb[j][0];
			for(k = 1; k < a->ac; k++){
				tmp += ma[k][i] * mb[j][k];
			}
			mt[j * orows + i] = tmp;
		}
	}
	memcpy(*mb, mt, sizeof(mt)/*a->ar * b->ac * sizeof(matrix_t)*/);
	//matrix_print(a);
	//matrix_print(b);
}

void matrix_copy(matrix *i, matrix *o){
	if(i->ar != o->ar || i->ac != o->ac){
		matrix_resize(o, i->ac, i->ar);
	}
	memcpy(o->m[0], i->m[0], i->ar * i->ac * sizeof(matrix_t));
	/*
	int j;
	for (j = 0; j < i->ac; j++) {
		memcpy(o->m[j], i->m[j], i->ar * sizeof(matrix_t));
	}
	*/
}

void matrix_mult_int_power(matrix *a, matrix *b, int exp){
	int j;
	for (j = 0; j < exp; j++) {
		matrix_mult_inplace(a, b);
	}
}

/*======== void matrix_make_translate() ==========
Sets the matrix to a translation matrix created using x, y and z 
as the translation offsets.
Must be given a 4x4 matrix, or else behavior is undefined
====================*/
void matrix_make_translate(matrix *m, double x, double y, double z) {
  matrix_make_ident(m);
  m->m[3][0] = x;
  m->m[3][1] = y;
  m->m[3][2] = z;
}

/*======== void matrix_make_scale() ==========
Sets the matrix to a scale matrix created using x, y and z
as the scale factors
Must be given a 4x4 matrix, or else behavior is undefined
====================*/
void matrix_make_scale(matrix *m, double x, double y, double z) {
  matrix_make_ident(m);
  m->m[0][0] = x;
  m->m[1][1] = y;
  m->m[2][2] = z;
}

/*======== void matrix_make_rot_x() ==========
Sets the matrix to the rotation matrix created using theta as the 
angle of rotation (in radians) and X as the axis of rotation.
Must be given a 4x4 matrix, or else behavior is undefined
====================*/
void matrix_make_rot_x(matrix *m, double theta) {
  matrix_make_ident(m);
  m->m[1][1] = cos(theta * M_PI / 180);
  m->m[2][1] = -sin(theta * M_PI / 180);
  m->m[1][2] = sin(theta * M_PI / 180);
  m->m[2][2] = cos(theta * M_PI / 180);
}

/*======== void matrix_make_rot_y() ==========
Inputs:  double theta

Sets the matrix to the rotation matrix created using theta as the 
angle of rotation (in radians) and Y as the axis of rotation.
Must be given a 4x4 matrix, or else behavior is undefined
====================*/
void matrix_make_rot_y(matrix *m, double theta) {
  matrix_make_ident(m);
  m->m[0][0] = cos(theta * M_PI / 180);
  m->m[2][0] = sin(theta * M_PI / 180);
  m->m[0][2] = -sin(theta * M_PI / 180);
  m->m[2][2] = cos(theta * M_PI / 180);
}

/*======== void matrix_make_rot_z() ==========
Inputs:  double theta

Sets the matrix to the rotation matrix created using theta as the 
angle of rotation (in radians) and Z as the axis of rotation.
Must be given a 4x4 matrix, or else behavior is undefined
====================*/
void matrix_make_rot_z(matrix *m, double theta) {
  matrix_make_ident(m);
  m->m[0][0] = cos(theta * M_PI / 180);
  m->m[1][0] = -sin(theta * M_PI / 180);
  m->m[0][1] = sin(theta * M_PI / 180);
  m->m[1][1] = cos(theta * M_PI / 180);
}

void matrix_make_rot_zyx  (matrix *m, double psi, double theta, double phi) {

	double s0 = sin(phi *M_PI/180);
	double s1 = sin(theta *M_PI/180);
	double s2 = sin(psi *M_PI/180);
	double c0 = cos(phi *M_PI/180);
	double c1 = cos(theta *M_PI/180);
	double c2 = cos(psi *M_PI/180);
	
	m->m[0][0] = c0*c1;
	m->m[0][1] = s0*c1;
	m->m[0][2] = -s1;
	m->m[1][0] = c0*s1*s2 - s0*c2;
	m->m[1][1] = s0*s1*s2 + c0*c2;
	m->m[1][2] = c1*s2;
	m->m[2][0] = s0*s2 + c0*s1*c2;
	m->m[2][1] = s0*s1*c2 - c0*s2;
	m->m[2][2] = c1*c2;

}

void matrix_make_rot_xyz  (matrix *m, double psi, double theta, double phi) {

	double s0 = sin(phi *M_PI/180);
	double s1 = sin(theta *M_PI/180);
	double s2 = sin(psi *M_PI/180);
	double c0 = cos(phi *M_PI/180);
	double c1 = cos(theta *M_PI/180);
	double c2 = cos(psi *M_PI/180);
	
	m->m[0][0] = c1*c2;
	m->m[0][1] = s0*s1*c2 - c0*s2;
	m->m[0][2] = s0*s2 + c0*s1*c2;
	m->m[1][0] = c1*s2;
	m->m[1][1] = s0*s1*s2 + c0*c2;
	m->m[1][2] = c0*s1*s2 - s0*c2;
	m->m[2][0] = -s1;
	m->m[2][1] = s0*c1;
	m->m[2][2] = c0*c1;
	
}

void matrix_make_rot_aa(matrix *m, double u0, double u1, double u2, double theta) {
	
	double s = sin(theta *M_PI/180);
	double c = cos(theta *M_PI/180);

	m->m[2][0] = u0*u2*(1 - c) + u1*s;
	m->m[2][1] = u1*u2*(1 - c) - u0*s;
	m->m[2][2] = c + u2*u2*(1 - c);
	m->m[1][0] = u0*u1*(1 - c) - u2*s;
	m->m[1][1] = c + u1*u1*(1 - c);
	m->m[1][2] = u2*u1*(1 - c) + u0*s;
	m->m[0][0] = c + u0*u0*(1 - c);
	m->m[0][1] = u1*u0*(1 - c) + u2*s;
	m->m[0][2] = u2*u0*(1 - c) - u1*s;

}


/*======== void matrix_make_transform() ==========
Inputs:  doubles x, y, z, matrix *rot

Sets the matrix to the transformation defined by the three coordinates and the three angles.
Output = translate(x, y, z) * rot
====================*/

void matrix_make_transform(matrix *m, double x, double y, double z, matrix *rot) {

	m->m[0][0] = rot->m[0][0];
	m->m[0][1] = rot->m[0][1];
	m->m[0][2] = rot->m[0][2];
	m->m[0][3] = 0;
	m->m[1][0] = rot->m[1][0];
	m->m[1][1] = rot->m[1][1];
	m->m[1][2] = rot->m[1][2];
	m->m[1][3] = 0;
	m->m[2][0] = rot->m[2][0];
	m->m[2][1] = rot->m[2][1];
	m->m[2][2] = rot->m[2][2];
	m->m[2][3] = 0;
	m->m[3][0] = x;
	m->m[3][1] = y;
	m->m[3][2] = z;
	m->m[3][3] = 1;
}

void matrix_make_tform_inv(matrix *m, double x, double y, double z, matrix *rot) {

	m->m[0][0] = rot->m[0][0];
	m->m[0][1] = rot->m[1][0];
	m->m[0][2] = rot->m[2][0];
	m->m[0][3] = 0;
	m->m[1][0] = rot->m[0][1];
	m->m[1][1] = rot->m[1][1];
	m->m[1][2] = rot->m[2][1];
	m->m[1][3] = 0;
	m->m[2][0] = rot->m[0][2];
	m->m[2][1] = rot->m[1][2];
	m->m[2][2] = rot->m[2][2];
	m->m[2][3] = 0;
	m->m[3][0] = -x*(m->m[0][0]) - y*(m->m[1][0]) - z*(m->m[2][0]);
	m->m[3][1] = -x*(m->m[0][1]) - y*(m->m[1][1]) - z*(m->m[2][1]);
	m->m[3][2] = -x*(m->m[0][2]) - y*(m->m[1][2]) - z*(m->m[2][2]);
	m->m[3][3] = 1;

}

void matrix_interpolate(matrix *i, matrix *o, double scale) {
	double a = acos((i->m[0][0] + i->m[1][1] + i->m[2][2] - 1) / 2);
	//debug_w("%lf", a*180/M_PI);
	double temp = 2 * sin(a);
	double e1 = 0, e2 = 0, e3 = 0;
	if (temp != 0) {
		e1 = (i->m[1][2] - i->m[2][1])/temp;
		e2 = (i->m[2][0] - i->m[0][2])/temp;
		e3 = (i->m[0][1] - i->m[1][0])/temp;
	}
	matrix_make_rot_aa(o, e1, e2, e3, a * scale *180/M_PI);
}

/*
void matrix_make_transform(matrix *m, double x, double y, double z, double phi, double theta, double psi) {
	
	//static matrix *temp = NULL;
	//if(temp == NULL){
		//temp = matrix_new(4, 4);
	//}
	//matrix_make_rot_x(m, phi);
	//matrix_make_rot_y(temp, theta);
	//matrix_mult_inplace(temp, m);
	//matrix_make_rot_z(temp, psi);
	//matrix_mult_inplace(temp, m);
	//matrix_make_translate(temp, x, y, z);
	//matrix_mult_inplace(temp, m);
	//matrix_free(temp);
	
	
	double s0 = sin(phi *M_PI/180);
	double s1 = sin(theta *M_PI/180);
	double s2 = sin(psi *M_PI/180);
	double c0 = cos(phi *M_PI/180);
	double c1 = cos(theta *M_PI/180);
	double c2 = cos(psi *M_PI/180);
	
	m->m[0][0] = c0*c1;
	m->m[0][1] = s0*c1;
	m->m[0][2] = -s1;
	m->m[0][3] = 0;
	m->m[1][0] = c0*s1*s2 - s0*c2;
	m->m[1][1] = s0*s1*s2 + c0*c2;
	m->m[1][2] = c1*s2;
	m->m[1][3] = 0;
	m->m[2][0] = s0*s2 + c0*s1*c2;
	m->m[2][1] = s0*s1*c2 - c0*s2;
	m->m[2][2] = c1*c2;
	m->m[2][3] = 0;
	m->m[3][0] = x;
	m->m[3][1] = y;
	m->m[3][2] = z;
	m->m[3][3] = 1;
	
}

void matrix_make_tform_inv(matrix *m, double x, double y, double z, double phi, double theta, double psi) {
	
	//static matrix *temp = NULL;
	//if(temp == NULL){
		//temp = matrix_new(4, 4);
	//}
	//matrix_make_translate(m, -x, -y, -z);
	//matrix_make_rot_z(temp, -psi);
	//matrix_mult_inplace(temp, m);
	//matrix_make_rot_y(temp, -theta);
	//matrix_mult_inplace(temp, m);
	//matrix_make_rot_x(temp, -phi);
	//matrix_mult_inplace(temp, m);
	//matrix_free(temp);
	
	
	double s0 = sin(phi *M_PI/180);
	double s1 = sin(theta *M_PI/180);
	double s2 = sin(psi *M_PI/180);
	double c0 = cos(phi *M_PI/180);
	double c1 = cos(theta *M_PI/180);
	double c2 = cos(psi *M_PI/180);
	
	m->m[0][0] = c1*c2;
	m->m[0][1] = s0*s1*c2 - c0*s2;
	m->m[0][2] = s0*s2 + c0*s1*c2;
	m->m[0][3] = 0;
	m->m[1][0] = c1*s2;
	m->m[1][1] = s0*s1*s2 + c0*c2;
	m->m[1][2] = c0*s1*s2 - s0*c2;
	m->m[1][3] = 0;
	m->m[2][0] = -s1;
	m->m[2][1] = s0*c1;
	m->m[2][2] = c0*c1;
	m->m[2][3] = 0;
	m->m[3][0] = -x*(m->m[0][0]) - y*(m->m[1][0]) - z*(m->m[2][0]);
	m->m[3][1] = -x*(m->m[0][1]) - y*(m->m[1][1]) - z*(m->m[2][1]);
	m->m[3][2] = -x*(m->m[0][2]) - y*(m->m[1][2]) - z*(m->m[2][2]);
	m->m[3][3] = 1;
	
}
*/


/*======== int matrix_addpoint() ==========
Returns: The new number of points in the matrix, or 0 on failure (matrix already full).

Writes the given ordered triple to column m->nc of matrix *m.
Increments, and returns, m->nc.
====================*/
int matrix_addpoint(matrix *m, matrix_t *point) {
  if (m->nc == m->ac) {
    return 0;
  }
  memcpy(m->m[m->nc], point, 3 * sizeof(matrix_t));
  m->m[m->nc][3] = 1;
  m->nc++;
  return m->nc;
}

/*======== int matrix_addpoint_resize() ==========
Like matrix_addpoint, but resizes matrix m if necessary
====================*/
int matrix_addpoint_resize(matrix *m, matrix_t *point) {
  if (m->nc == m->ac) {
    matrix_resize(m, m->nc + 1, m->ar);
  }
  return matrix_addpoint(m, point);
}

/*======== int matrix_addpoint_fromcoords() ==========
Returns: The new number of points in the matrix, or 0 on failure (matrix already full).

Writes the given coordinates to column m->nc of matrix *m.
Increments, and returns, m->nc.
====================*/
int matrix_addpoint_fromcoords(matrix *m, double x, double y, double z) {
  if (m->nc >= m->ac) {
    return 0;
  }
  m->m[m->nc][0] = x;
  m->m[m->nc][1] = y;
  m->m[m->nc][2] = z;
  m->m[m->nc][3] = 1;
  m->nc++;
  return m->nc;
}

/*======== int matrix_addpoint_fromcoords_resize() ==========
Like matrix_addpoint_fromcoords, but resizes matrix m if necessary
====================*/
int matrix_addpoint_fromcoords_resize(matrix *m, double x, double y, double z) {
  if (m->nc == m->ac) {
    matrix_resize(m, m->nc + 1, m->ar);
  }
  return matrix_addpoint_fromcoords(m, x, y, z);
}

/*======== int matrix_cat() ==========
Merges together the two (point) matrices into matrix a.
Assumes a and b have the same number of rows.
Adjusts, and returns, a->nc.

Returns: The new number of points in the matrix, or 0 on failure (not enough space in matrix a).
====================*/
int matrix_cat(matrix *a, matrix *b) {
	if (a->nc + b->nc > a->ac)
		return 0;
  memcpy(a->m[a->nc], b->m[0], b->ar * b->nc * sizeof(matrix_t));
  return a->nc;
}

/*======== int matrix_cat_resize() ==========
Like matrix_cat, but resizes matrix a if necessary.
====================*/
int matrix_cat_resize(matrix *a, matrix *b) {
	if (a->nc + b->nc > a->ac)
		matrix_resize(a, a->nc + b->nc, a->ar);
  return matrix_cat(a, b);
}

// need matrix_invert();
