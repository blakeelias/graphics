#include <stdio.h>

typedef struct
{
 double data[16];
 int rows;
 int cols;
} Matrix;

void initMatrix(Matrix* matrix, int rows, int cols)
{
 if ((rows > 4) || (cols > 4))
 {
  printf("What's the need for a matrix bigger than 4x4?\n");
  return;
 }

 int i;

 matrix->rows = rows;
 matrix->cols = cols;
 for (i = 0; i < 16; i++)
  matrix->data[i] = 0.0;
}

double* getMatrixCell(Matrix* m, int row, int col)
{
 if (row < 0) return NULL;
 if (col < 0) return NULL;
 if (row >= m->rows) return NULL;
 if (col >= m->cols) return NULL;

 return &m->data[(row * m->cols) + col];
}

void printMatrix(Matrix* m)
{
 int row, col;
 for (row = 0; row < m->rows; row++)
 {
  for (col = 0; col < m->cols; col++)
   printf("%f ", *getMatrixCell(m, row, col));

  printf("\n");
 }
}

int identityMatrix(Matrix* m)
{
 if (m->rows != m->cols)
  return -1;

 int row, col;
 for (row = 0; row < m->rows; row++)
 {
  for (col = 0; col < m->cols; col++)
  {
   if (row == col)
    *getMatrixCell(m, row, col) = 1.0;
   else
    *getMatrixCell(m, row, col) = 0.0;
  }
 }

 return 0;
}

void multiplyMatrix(Matrix* result, Matrix* m, double d)
{
 result->rows = m->rows;
 result->cols = m->cols;

 int i;
 for (i = 0; i < (m->rows * m->cols); i++)
  result->data[i] = m->data[i] * d;
}

int multiplyMatrices(Matrix* result, Matrix* m1, Matrix* m2)
{
 if (m1->cols != m2->rows)
  return -1;

 int limit = m1->cols;
 int row, col, i;

 result->rows = m1->rows;
 result->cols = m2->cols;

 for (row = 0; row < result->rows; row++)
 {
  for (col = 0; col < result->cols; col++)
  {
   double r = 0.0;
   for (i = 0; i < limit; i++)
   {
    r += (*getMatrixCell(m1, row, i)) * (*getMatrixCell(m2, i, col));
   }
   *getMatrixCell(result, row, col) = r;
  }
 }

 return 0;
}

void copyMatrix(Matrix* dst, const Matrix* src)
{
 *dst = *src;
}


int main(int argc, char** argv)
{
 Matrix m;

 initMatrix(&m, 3, 3);
 identityMatrix(&m);
 printMatrix(&m);

 printf("\n");

 initMatrix(&m, 4, 3);
 identityMatrix(&m);
 printMatrix(&m);
 return 0;
}
