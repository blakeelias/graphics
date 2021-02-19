#ifndef _FMATRIX_H
#define _FMATRIX_H

typedef double matrix_t;

// NOTE: Matrices are now indexed m->m[col][row] for efficiency.
struct matrix {
  matrix_t **m;
  int ar, ac;
  int     nc;
};

struct matrix 
    *matrix_new(int cols, int rows);
void matrix_free(struct matrix *m);
void matrix_col_resize(struct matrix *m, int cols);
void matrix_resize(struct matrix *m, int cols, int rows);
int matrix_addPoint(struct matrix *m, matrix_t *point); // JB
int matrix_concatenate(struct matrix *a, struct matrix *b); // JB
void matrix_print(struct matrix *m);
void matrix_ident(struct matrix *m);
void matrix_scalar_mult(struct matrix *m, matrix_t multiple);
void matrix_mult(struct matrix *a, struct matrix *b, struct matrix *o);
void matrix_mult_inplace(struct matrix *a, struct matrix *b);
void matrix_copy(struct matrix *i, struct matrix *o);

#endif
