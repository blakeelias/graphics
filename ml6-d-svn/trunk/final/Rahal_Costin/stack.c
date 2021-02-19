#include <stdio.h>
#include "stack.h"

void push() {
	struct node *new = (struct node *) malloc(sizeof(struct node));
	new->next = stack;
	new->m = new_matrix(4,4);
	copy_matrix(stack->m, new->m);
	stack = new;
}

void pop() {
  struct node *old = stack;
  stack = stack->next;
  free_matrix(old->m);
  free(old);
}

void init() {
  struct node *s = (struct node *) malloc(sizeof(struct node));
  s->m = new_matrix(4, 4);
  ident(s->m);
  s->next = NULL;
  stack = s;
}

void free_stack() {
	while (stack != NULL)
		pop();
}

void print_stack() {
	printf("\n");
	struct node *n = stack;
	while (n != NULL) {
		print_matrix(n->m);
		printf("\n");
		n = n->next;
	}
}
