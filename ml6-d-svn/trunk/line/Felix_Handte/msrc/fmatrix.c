#include "fmatrix.h"

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
		o->m[i] = tmp + (i * cols * sizeof(matrix_t));
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
