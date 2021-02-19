#ifndef STACK_H
#define STACK_H

struct stack {
  int top;
  struct matrix **data;
};

struct stack * new_stack();
void push( struct stack *s );
void pop(struct stack *s);

void free_stack( struct stack *);
void print_stack( struct stack *);

#endif
