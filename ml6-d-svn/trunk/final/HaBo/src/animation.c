#include <math.h>
#include <stdint.h>
#include <time.h> // should be redundant
#include <SDL/SDL.h>

#include "animation.h"
#include "matrix.h"
#include "objects.h"

void animation_update_subtree(node *n, double time_interval);
struct timespec diff(struct timespec *start, struct timespec *end);
double game_clock;
int frame_count;

void animation_init() {
	//time_last_update = 0;
	rot_temp = matrix_new(4, 4);
	clock_gettime(CLOCK_REALTIME, &time_last_update);
	game_clock = 0;
	frame_count = 0;
}

void animation_update_scene(node *scene) {
	clock_gettime(CLOCK_REALTIME, &time_current);
	struct timespec time_diff;
	time_diff = diff(&time_last_update, &time_current);
	
	double time_interval;
	time_interval = time_diff.tv_sec + time_diff.tv_nsec / 1000000000.;
	
	game_clock += time_interval;
	frame_count++;
	d_debug_w(D_FRAME_RATE, "Framerate = %lf", frame_count / game_clock); //1. / time_interval);
	
	animation_update_subtree(scene, time_interval);

	time_last_update = time_current;	

	//debug_w("%lf", 1000./time_interval);
}

void animation_update_subtree(node *n, double time_interval) {
	if(n->type == NODE_TFORM){
		
		n->n.k->  pos[0] += n->n.k-> d_pos[0] * time_interval;
		n->n.k->  pos[1] += n->n.k-> d_pos[1] * time_interval;
		n->n.k->  pos[2] += n->n.k-> d_pos[2] * time_interval;
		n->n.k->d_pos[0] += n->n.k->dd_pos[0] * time_interval;
		n->n.k->d_pos[1] += n->n.k->dd_pos[1] * time_interval;
		n->n.k->d_pos[2] += n->n.k->dd_pos[2] * time_interval;
		
		/*
		static matrix *dd_rot = NULL;
		if (dd_rot == NULL) {
			dd_rot = matrix_new(3, 3);
		}
		
		matrix_make_rot_aa(dd_rot,
		                   n->n.k->dd_rot_v[0], n->n.k->dd_rot_v[1], n->n.k->dd_rot_v[2],
		                   n->n.k->dd_rot_a * time_interval);
		matrix_mult_inplace(dd_rot, n->n.k->d_rot);
		matrix_mult_inplace(n->n.k->d_rot, n->n.k->rot);
		*/
		
		static matrix *dd_int;
		if (dd_int == NULL)
			dd_int = matrix_new(3, 3);
		static matrix *d_int;
		if (d_int == NULL)
			d_int = matrix_new(3, 3);

		//debug_n("");
		//matrix_print(n->n.k->dd_rot);
		matrix_interpolate(n->n.k->dd_rot, dd_int, time_interval);
		//matrix_print(dd_int);
		matrix_mult_inplace(dd_int, n->n.k->d_rot);
		matrix_interpolate(n->n.k->d_rot, d_int, time_interval);
		matrix_mult_inplace(d_int, n->n.k->rot);
		//debug_w("%lf", game_clock);
	}
	
	int i;
	for (i = 0; i < n->nchild; i++)
		animation_update_subtree(n->child[i], time_interval);		
}

struct timespec diff(struct timespec *start, struct timespec *end){
	struct timespec temp;
	if(end->tv_nsec < start->tv_nsec){
		temp.tv_sec = end->tv_sec - start->tv_sec - 1;
		temp.tv_nsec = 1000000000 + end->tv_nsec - start->tv_nsec;
	} else {
		temp.tv_sec = end->tv_sec - start->tv_sec;
		temp.tv_nsec = end->tv_nsec - start->tv_nsec;
	}
	return temp;
}
