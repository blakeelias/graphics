#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "matrix.h"

int main()
{//printf("d");
  new_stack();
  // struct matrix *m = new_matrix(4,4);
  //ident(m);
  //s->m[0] = m;
  //print_matrix(s->m[0]);
   push();
   //print_matrix(s->m[0]);  
   //print_matrix(s->m[1]);
 struct matrix *m = pop();
 print_matrix(m);
 print_matrix(s->m[0]);
 print_matrix(s->m[1]);
 matrix_mult(make_scale(2,3,4),s->m[0]);
 push();
 push();
 print_matrix(s->m[0]);
print_matrix(s->m[1]);
print_matrix(s->m[2]);
  //print_matrix(m);
return 0;
}
