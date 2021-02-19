#include "matrix.h"

struct node {
  struct node *nextnode; struct matrix *m;
};

struct node *stack;
void push();
void pop();
void init();
