#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "matrix.h"

void new_stack()
{//printf("daf");
  s = (struct stack *)malloc(sizeof(struct stack));
  s->top = 1;
  struct matrix *m = new_matrix(4,4);
  ident(m);
  s->m[0] = m;
}

void push()
{
  int x =s->top;
   struct matrix *m = new_matrix(4,4);
   copy_matrix(s->m[x-1], m);
  s->m[x]=m;
  s->top=s->top+1;
  // print_matrix(s->m[s->top-1]);
  // printf("adfads");
}

struct matrix * pop()
{//print_matrix(s->m[s->top]);
  //printf("%d", s->top);
  // int x = s->top;
  s->top = s-> top -1;
  //print_matrix(s->m[s->top-1]);
  return s->m[s->top];
}

void move(double x, double y, double z)
{
  struct matrix *tran = make_translate(x,y,z);
  matrix_mult(tran,s->m[s->top-1]);
  free_matrix(tran);
  // print_matrix(s->m[s->top-1]);
}


