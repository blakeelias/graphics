#include <stdio.h>
#include "stack.h"

void stack_push(matrix *m) {
	struct stack_item *new = (struct stack_item *) malloc(sizeof(struct stack_item));
	new->next = stack;
	new->m = matrix_new(4, 4);
	//print_matrix(stack->m);
	//print_matrix(new->m);
	matrix_copy(stack->m, new->m);
	matrix_mult_inplace(new->m, m);
	matrix_copy(m, new->m);
	stack = new;
}

void stack_pop() {
	struct stack_item *old = stack;
	stack = stack->next;
	matrix_free(old->m);
	free(old);
}

void stack_init() {
	struct stack_item *s = (struct stack_item *) malloc(sizeof(struct stack_item));
	s->m = matrix_new(4, 4);
	matrix_make_ident(s->m);
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
		matrix_print(n->m);
		printf("\n");
		n = n->next;
	}
}
	
