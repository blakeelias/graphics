#ifndef STACK_H
#define STACK_H

#include "matrix.h"

//need another field: a pointer to top matrix
//name that field top and rename the int counter to something else
struct stack {
  struct matrix *m[1000];
  int top;
};

struct stack *s;
void new_stack();
void push();
struct matrix *pop();

#endif
