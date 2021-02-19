#include <stdio.h>
#include "stack.h"

void stack_push() {
	struct stack_item *new = (struct stack_item *) malloc(sizeof(struct stack_item));
	new->next = stack;
	new->m = new_matrix(4, 4);
	//print_matrix(stack->m);
	//print_matrix(new->m);
	copy_matrix(stack->m, new->m);
	stack = new;
}

void stack_pop() {
	struct stack_item *old = stack;
	stack = stack->next;
	free_matrix(old->m);
	free(old);
}

void stack_init() {
	struct stack_item *s = (struct stack_item *) malloc(sizeof(struct stack_item));
	s->m = new_matrix(4, 4);
	ident(s->m);
	s->next = NULL;
	stack = s;
}

void stack_free() {
	while (stack != NULL)
		stack_pop();
}

void stack_print() {
	printf("\n");
	struct stack_item *n = stack;
	while (n != NULL) {
		print_matrix(n->m);
		printf("\n");
		n = n->next;
	}
}
	
