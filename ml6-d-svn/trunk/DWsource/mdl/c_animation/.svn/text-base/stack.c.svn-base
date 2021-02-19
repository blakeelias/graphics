#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "stack.h"

struct stack * new_stack() {

  struct stack *s;
  struct matrix **m;
  struct matrix *i;
  s = (struct stack *)malloc(sizeof(struct stack));
  
  m = (struct matrix **)malloc(32 * sizeof(struct matrix *));
  i = new_matrix(4, 4);
  ident( i );

  s->top = 0;
  s->data = m;
  s->data[ s->top ] = i;

  return s;
}

void push( struct stack *s ) {

  struct matrix *m;
  m = new_matrix(4, 4);

  copy_matrix( s->data[ s->top ], m);

  s->top++;
  s->data[ s->top ] = m;  
}

void pop( struct stack * s) {

  free_matrix(s->data[s->top]);
  s->top--;
}

void free_stack( struct stack *s) {

  int i;
  for (i=0; i <= s->top; i++) {

    free_matrix(s->data[i]);
  }
  free(s->data);
  free(s);
}

void print_stack(struct stack *s) {

  int i;
  for (i=s->top; i >= 0; i--) {

    print_matrix(s->data[i]);
    printf("\n");
  }

}
