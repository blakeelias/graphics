#ifndef _FMATRIX_H
#define _FMATRIX_H

typedef double matrix_t;

struct matrix {
  matrix_t **m;
  int rows, cols;
};

struct matrix *matrix_new(int rows, int cols);
void matrix_free(struct matrix *m);
void matrix_resize(struct matrix *m, int rows, int cols);
void matrix_print(struct matrix *m);
void matrix_ident(struct matrix *m);
void matrix_scalar_mult(struct matrix *m, matrix_t multiple);
void matrix_mult(struct matrix *a, struct matrix *b, struct matrix *o);
void matrix_mult_inplace(struct matrix *a, struct matrix *b);
void matrix_copy(struct matrix *i, struct matrix *o);

#endif
