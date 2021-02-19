#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrix_stack.h"

void matrix_stack_init(struct matrix *m) {
  struct stack_element *e = calloc(sizeof(struct stack_element), 1);
  e->m = m;
  e->prev = NULL;
  matrix_stack.first = e;
  matrix_stack.last = e;
}

void matrix_stack_push(struct matrix *m) {
  struct stack_element *e = calloc(sizeof(struct stack_element), 1);
  e->m = m;
  e->prev = matrix_stack.last;
  matrix_stack.last = e;
}

struct matrix *matrix_stack_pop() {
  struct stack_element *e = matrix_stack.last;
  struct matrix *m = e->m;
  matrix_stack.last = e->prev;
  free(e);
  return m;
}

void matrix_stack_flush() {
  if(matrix_stack.last!=matrix_stack.first){
  struct stack_element *e = matrix_stack.last;
  matrix_stack.last = e->prev;
  free(e);
  matrix_stack_flush();
  return; 
  }
}

/*void main() {
  struct matrix *a = new_matrix(4, 4);
  a->m[0][0] = a->m[0][1] = a->m[0][2] = a->m[0][3] = a->m[1][0] = a->m[1][1] = a->m[1][2] = a->m[1][3] = a->m[2][0] = a->m[2][1] = a->m[2][2] = a->m[2][3] = a->m[3][0] = a->m[3][1] = a->m[3][2] = a->m[3][3] = 1;
  //print_matrix(a);

  struct matrix *b = new_matrix(4, 4);
  b->m[0][0] = b->m[0][1] = b->m[0][2] = b->m[0][3] = b->m[1][0] = b->m[1][1] = b->m[1][2] = b->m[1][3] = b->m[2][0] = b->m[2][1] = b->m[2][2] = b->m[2][3] = b->m[3][0] = b->m[3][1] = b->m[3][2] = b->m[3][3] = 2;
  //print_matrix(b);

  matrix_stack_init(a);
  matrix_stack_push(b);
  print_matrix(matrix_stack_pop());
  print_matrix(matrix_stack_pop());
}
*/
