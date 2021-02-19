#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "stack.h"

struct node * push(struct node *stack){
  struct matrix *mtrx = new_matrix(4,4);
  copy_matrix(stack->m,mtrx);
  struct node *newstack = calloc(sizeof(struct node), 1);
  newstack->m = mtrx;
  newstack->nextnode = stack;
  return newstack;
}

struct node * pop(struct node *stack){
  struct node *tempstack = stack->nextnode;
  free_matrix(stack->m);
  free(stack);
  return tempstack;
}

struct node * init() {
  struct node *stack = calloc(sizeof(struct node), 1);
  struct matrix *mtrx = new_matrix(4,4);
  ident(mtrx);
  stack->m = mtrx;
  return stack;
}

void print_stack(struct node *stack){
  struct node *tempstack = stack;
  while (tempstack) {
    printf("This matrix:\n");
    print_matrix(tempstack->m);
    tempstack = tempstack->nextnode;
    //printf("Next matrix:\n");
    //print_matrix(tempstack->m);
  }
  free(tempstack);
}
