#ifndef _FMATRIX_H
#define _FMATRIX_H

typedef double matrix_t;

// NOTE: Matrices are now indexed m->m[col][row] for efficiency.
typedef struct _matrix {
  matrix_t **m;
  int ar; // Number of rows allocated
  int ac; // Number of columns allocated
  int nc; // If used as a point matrix, number of columns currently storing points
} matrix;

matrix *matrix_new      (int cols, int rows);
void matrix_free        (matrix *m);
//void matrix_col_resize  (matrix *m, int cols);
void matrix_resize      (matrix *m, int cols, int rows);
void matrix_print       (matrix *m);

void matrix_copy          (matrix *i, matrix *o);
void matrix_scalar_mult   (matrix *m, matrix_t multiple);
void matrix_mult          (matrix *a, matrix *b, matrix *o);
void matrix_mult_inplace  (matrix *a, matrix *b); // b <- a*b
void matrix_mult_int_power(matrix *a, matrix *b, int exp); /* b <- (a^e)*b
Used in animation_update_scene().
Is there a more efficient algorithm than repeated multiplication? */

void matrix_make_zero     (matrix *m);
void matrix_make_ident    (matrix *m);
// The following assume matrices are 4-by-4 unless otherwise indicated
void matrix_make_translate(matrix *m, double x, double y, double z);
void matrix_make_scale    (matrix *m, double x, double y, double z);
void matrix_make_rot_x    (matrix *m, double theta);
void matrix_make_rot_y    (matrix *m, double theta);
void matrix_make_rot_z    (matrix *m, double theta);
void matrix_make_rot_zyx  (matrix *m, double phi, double theta, double psi); // 3-by-3
void matrix_make_rot_xyz  (matrix *m, double phi, double theta, double psi); // 3-by-3
void matrix_make_rot_aa   (matrix *m, double u0, double u1, double u2, double theta); // 3-by-3 (axis-angle -> rotation matrix)
//void matrix_make_transform(matrix *m, double x, double y, double z, double phi, double theta, double psi); // see note on convention, in obj_kinematics struct definition
//void matrix_make_tform_inv(matrix *m, double x, double y, double z, double phi, double theta, double psi);
void matrix_make_transform(matrix *m, double x, double y, double z, matrix *rot);
void matrix_make_tform_inv(matrix *m, double x, double y, double z, matrix *rot);

void matrix_interpolate(matrix *i, matrix *o, double scale); // 3-by-3

int matrix_addpoint                  (matrix *m, double *point);
int matrix_addpoint_resize           (matrix *m, double *point);
int matrix_addpoint_fromcoords       (matrix *m, double x, double y, double z);
int matrix_addpoint_fromcoords_resize(matrix *m, double x, double y, double z);
int matrix_cat                       (matrix *a, matrix *b);
int matrix_cat_resize                (matrix *a, matrix *b);

/*
Might need this:
void matrix_invert      (matrix *i, matrix *o);
*/


#endif
