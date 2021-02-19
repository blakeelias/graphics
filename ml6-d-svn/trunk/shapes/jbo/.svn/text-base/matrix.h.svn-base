#ifndef MATRIX_H
#define MATRIX_H

struct matrix {
  double **m;
  int cols;
  int rows;
  int nextCol;
} matrix;

struct matrix *matrix_newMatrix(int cols, int rows);
void matrix_freeMatrix(struct matrix *m);
//int matrix_grow(struct matrix *m, int newcols);
int matrix_addPointFromCoords(struct matrix *m, double x, double y, double z);
int matrix_addPoint(struct matrix *m, double *point);
int matrix_concatenate(struct matrix *a, struct matrix *b);
struct matrix *matrix_merge(struct matrix *a, struct matrix *b);
void matrix_print(struct matrix *m);
void matrix_scalarMult(double x, struct matrix *m);
void matrix_matrixMult(struct matrix *a, struct matrix *b);
void matrix_copy(struct matrix *a, struct matrix *b);
void matrix_ident(struct matrix *m);
void matrix_clear(struct matrix *m);
struct matrix *matrix_makeTranslate(double x, double y, double z);
struct matrix *matrix_makeScale(double x, double y, double z);
struct matrix *matrix_makeRotX(double theta);
struct matrix *matrix_makeRotY(double theta);
struct matrix *matrix_makeRotZ(double theta);

#endif
