#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "matrix.h"

//Tested on a couple test cases (see `main' below)
// UNINTERGRATED into cmd_parser.c

struct stack_element {
  struct matrix *m;
  struct stack_element *prev;
};

struct matrix_stack {
  struct stack_element *first;
  struct stack_element *last;
} matrix_stack;

void matrix_stack_init(struct matrix *m);

void matrix_stack_push(struct matrix *m);

struct matrix *matrix_stack_pop();

void matrix_stack_flush();
