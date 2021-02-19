#include "matrix.h"

struct node {
  struct node *next; struct matrix *m;
};

struct node *stack;
void push();
void pop();
void init();
void free_stack();
void print_stack();
