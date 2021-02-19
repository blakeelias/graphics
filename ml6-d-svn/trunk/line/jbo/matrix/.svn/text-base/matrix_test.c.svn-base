#include <stdio.h>
#include "matrix.h"

int main() {
  int i,j;
  
  struct matrix *a = new_matrix(2, 2);
  for (i = 0; i < a->rows; i++) {
    for (j = 0; j < a->cols; j++) {
      a->m[i][j] = 2*i + j;
    }
  }
  print_matrix(a);
  printf("\n");
  
  struct matrix *b = new_matrix(2, 2);
  for (i = 0; i < b->rows; i++) {
    for (j = 0; j < b->cols; j++) {
      b->m[i][j] = 2*i + j + 4;
    }
  }
  print_matrix(b);
  printf("\n");
  
  scalar_mult(2., a);
  print_matrix(a);
  printf("\n");
  
  matrix_mult(a, b);
  print_matrix(b);
  printf("\n");
  
  ident(a);
  print_matrix(a);
  printf("\n");
  
  clear_matrix(b);
  print_matrix(b);
  printf("\n");
  
  copy_matrix(a, b);
  print_matrix(b);
  printf("\n");
  
  free_matrix(a);
  free_matrix(b);
  return 0;
}
