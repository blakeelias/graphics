#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix *matrix_new(int cols, int rows){
	struct matrix *o;
	o = malloc(sizeof(struct matrix));
	o->ar = rows;
	o->ac = cols;
	o->nc = 0;
	o->m = malloc(cols * sizeof(matrix_t **));
	matrix_t *tmp;
	tmp = malloc(rows * cols * sizeof(matrix_t));
	int i;
	for(i = 0; i < cols; i++){
		o->m[i] = tmp + (i * rows * sizeof(matrix_t));
	}
	return o;
}

void matrix_col_resize(struct matrix *m, int cols){
	int oldcols;
	oldcols = m->ac;
	m->ac = cols;
	matrix_t *tmp;
	tmp = m->m[0] = realloc(m->m[0], m->ar * cols * sizeof(matrix_t **));
	m->m = realloc(m->m, cols * sizeof(matrix_t *));
	for(; oldcols < cols; oldcols++){
		m->m[oldcols] = tmp + (oldcols * m->ar * sizeof(matrix_t));
	}
}

void matrix_resize(struct matrix *m, int cols, int rows){
	m->ar = rows;
	m->ac = cols;
	matrix_t *tmp;
	tmp = m->m[0] = realloc(m->m[0], rows * cols * sizeof(matrix_t **));
	m->m = realloc(m->m, cols * sizeof(matrix_t *));
	int i;
	for(i = 1; i < cols; i++){
		m->m[i] = tmp + (i * rows * sizeof(matrix_t));
	}
}

void matrix_free(struct matrix *m){
	free(m->m[0]);
	free(m->m);
	free(m);
}

void matrix_print(struct matrix *m){
	int i, j;
	for(i = 0; i < m->ar; i++){
		for(j = 0; j < m->ac - 1; j++){
			printf("%lf ", m->m[j][i]);
		}
		printf("%lf\n", m->m[j][i]);
	}
}

void matrix_ident(struct matrix *m){
	int i, j;
	for(i = 0; i < m->ac; i++){
		for(j = 0; j < m->ar; j++){
			if(i == j){
				m->m[i][j] = 1;
			} else {
				m->m[i][j] = 0;
			}
		}
	}
}

void matrix_scalar_mult(struct matrix *m, matrix_t multiple){
	int i, j;
	for(i = 0; i < m->ac; i++){
		for(j = 0; j < m->ar; j++){
			m->m[i][j] *= multiple;
		}
	}
}

void matrix_mult(struct matrix *a, struct matrix *b, struct matrix *o){
	int i, j, k;
	matrix_t tmp;
	matrix_t **ma, **mb, **mo;
	ma = a->m;
	mb = b->m;
	mo = o->m;
	for(i = 0; i < a->ar; i++){
		for(j = 0; j < b->ac; j++){
			tmp = ma[0][i] * ma[j][0];
			for(k = 1; k < a->ac; k++){
				tmp += ma[k][i] * ma[j][k];
			}
			mo[i][j] = tmp;
		}
	}			
}

void matrix_mult_inplace(struct matrix *a, struct matrix *b){
	int i, j, k;
	int orows = b->ar;
	matrix_t mt[a->ar * b->ar];
	matrix_t tmp;
	matrix_t **ma, **mb;
	ma = a->m;
	mb = b->m;
	for(i = 0; i < a->ar; i++){
		for(j = 0; j < b->ac; j++){
			tmp = ma[0][i] * ma[j][0];
			for(k = 1; k < a->ac; k++){
				tmp += ma[k][i] * ma[j][k];
			}
			mt[j * orows + i] = tmp;
		}
	}
	memcpy(mt, *mb, a->ar * b->ar * sizeof(matrix_t));
}

void matrix_copy(struct matrix *i, struct matrix *o){
	if(i->ar != o->ar || i->ac != o->ac){
		matrix_resize(o, i->ac, i->ar);
	}
	memcpy(i->m[0], o->m[0], i->ar * i->ac * sizeof(matrix_t));
}

/*

struct matrix *matrix_new(int rows, int cols){
	struct matrix *o;
	o = malloc(sizeof(struct matrix));
	o->rows = rows;
	o->cols = cols;
	o->m = malloc(rows * sizeof(matrix_t **));
	matrix_t *tmp;
	tmp = malloc(rows * cols * sizeof(matrix_t));
	int i;
	for(i = 0; i < rows; i++){
		o->m[i] = tmp + (i * cols * sizeof(matrix_t));
	}
	return o;
}

void matrix_free(struct matrix *m){
	free(m->m[0]);
	free(m->m);
	free(m);
}

void matrix_resize(struct matrix *m, int rows, int cols){
	m->rows = rows;
	m->cols = cols;
	matrix_t *tmp;
	tmp = m->m[0] = realloc(m->m[0], rows * cols * sizeof(matrix_t **));
	m->m = realloc(m->m, rows * sizeof(matrix_t *));
	int i;
	for(i = 1; i < rows; i++){
		m->m[i] = tmp + (i * cols * sizeof(matrix_t));
	}
}

void matrix_print(struct matrix *m){
	int i, j;
	for(i = 0; i < m->rows; i++){
		for(j = 0; j < m->cols - 1; j++){
			printf("%lf ", m->m[i][j]);
		}
		printf("%lf\n", m->m[i][j]);
	}
}

void matrix_ident(struct matrix *m){
	int i, j;
	for(i = 0; i < m->rows; i++){
		for(j = 0; j < m->cols; j++){
			if(i == j){
				m->m[i][j] = 1;
			} else {
				m->m[i][j] = 0;
			}
		}
	}
}

void matrix_scalar_mult(struct matrix *m, matrix_t multiple){
	int i, j;
	for(i = 0; i < m->rows; i++){
		for(j = 0; j < m->cols; j++){
			m->m[i][j] *= multiple;
		}
	}
}

void matrix_mult(struct matrix *a, struct matrix *b, struct matrix *o){
	int i, j, k;
	matrix_t tmp;
	matrix_t **ma, **mb, **mo;
	ma = a->m;
	mb = b->m;
	mo = o->m;
	for(i = 0; i < a->rows; i++){
		for(j = 0; j < b->cols; j++){
			tmp = ma[i][0] * ma[0][j];
			for(k = 1; k < a->cols; k++){
				tmp += ma[i][k] * ma[k][j];
			}
			mo[j][i] = tmp;
		}
	}			
}

void matrix_mult_inplace(struct matrix *a, struct matrix *b){
	int i, j, k;
	int ocols = b->cols;
	matrix_t mt[a->rows * b->rows];
	matrix_t tmp;
	matrix_t **ma, **mb;
	ma = a->m;
	mb = b->m;
	for(i = 0; i < a->rows; i++){
		for(j = 0; j < b->cols; j++){
			tmp = ma[i][0] * ma[0][j];
			for(k = 1; k < a->cols; k++){
				tmp += ma[i][k] * ma[k][j];
			}
			mt[j * ocols + i] = tmp;
		}
	}
	memcpy(mt, *mb, a->rows * b->rows * sizeof(matrix_t));
}

void matrix_copy(struct matrix *i, struct matrix *o){
	if(i->rows != o->rows || i->cols != o->cols){
		matrix_resize(o, i->rows, i->cols);
	}
	memcpy(i->m[0], o->m[0], i->rows * i->cols * sizeof(matrix_t));
}

*/
