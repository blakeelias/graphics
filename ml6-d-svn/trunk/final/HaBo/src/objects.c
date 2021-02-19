#include "aircraft.h"
#include "camera.h"
#include "objects.h"


#include <stdlib.h>


object *object_new(int type, int num_points, int num_edges, int num_faces) {
	object *o = (object *) malloc(sizeof(object));
	o->type = type;
	o->g = obj_geometry_new(num_points, num_edges, num_faces);
	obj_fields_attach(type, &(o->f));
	o->flags = 0;
	return o;
}

void object_free(object *o) {
	//debug_w("freeing obj_geometry at ptr %d", (int) o->g);
	obj_geometry_free(o->g);
	//debug_n("freed");
	//debug_w("freeing obj_fields at ptr %d", (int) o->f);
	obj_fields_free(o->type, o->f);
	//debug_n("freed");
	//debug_w("freeing obj struct at ptr %d", (int) o);
	free(o);
	//debug_n("freed");
	//fprintf(stderr, "\n");
}



obj_geometry *obj_geometry_new(int num_points, int num_edges, int num_faces) {
	if (num_points == 0)
		return NULL;
	obj_geometry *geo = (obj_geometry *) malloc(sizeof(obj_geometry));
	geo->p  = matrix_new(num_points, 4);
	geo->tp = matrix_new(num_points, 4);
	geo->pp = matrix_new(num_points, 4);
	geo->fp = matrix_new(num_points, 4);
	geo->e = (int *) malloc((2*num_edges) * sizeof(int));
	geo->e[0] = 0;
	if (num_edges > 0)
		geo->max_edges = num_edges;
	else
		geo->max_edges = 0;
	geo->num_edges = 0;
	geo->f = (int *) malloc(3*num_faces * sizeof(int));
	geo->nf = num_faces;
	geo->c = (color *) malloc(num_points * sizeof(color));
	geo->ce = (color *) malloc(num_edges * sizeof(color));
	return geo;
}

obj_kinematics *obj_kinematics_new() {
	obj_kinematics *k = (obj_kinematics *) malloc(sizeof(obj_kinematics));
	int i;
	for (i = 0; i < 3; i++) {
		k->ctr[i] = 0;
		k->pos[i] = 0;
		k->d_pos[i] = 0;
		k->dd_pos[i] = 0;
		//k->rot[i] = 0;
		//k->d_rot[i] = 0;
		//k->dd_rot[i] = 0;
	}
	k->rot = matrix_new(3, 3);
	matrix_make_ident(k->rot);
	k->d_rot = matrix_new(3, 3);
	matrix_make_ident(k->d_rot);
	k->dd_rot = matrix_new(3, 3);
	matrix_make_ident(k->dd_rot);
	return k;
}

void obj_geometry_free(obj_geometry *geo) {
	if (geo == NULL)
		return;
	//debug_w("freeing points at ptr %d", (int) geo->p);
	matrix_free(geo->p);
	matrix_free(geo->tp);
	matrix_free(geo->pp);
	matrix_free(geo->fp);
	//debug_n("freed");
	//debug_w("freeing edges at ptr %d", (int) geo->e);
	free(geo->e);
	//debug_n("freed");
	//debug_w("freeing faces at ptr %d", (int) geo->f);
	free(geo->f);
	//debug_n("freed");
	//debug_w("freeing colors at ptr %d", (int) geo->c);
	free(geo->c);
	//debug_n("freed");
	//debug_w("freeing edge colors at ptr %d", (int) geo->ce);
	free(geo->ce);
	//debug_n("freed");
	//debug_w("freeing obj_geometry struct at ptr %d", (int) geo);
	free(geo);
	//debug_n("freed");
}

void obj_kinematics_free(obj_kinematics *knm) {
	matrix_free(knm->dd_rot);
	matrix_free(knm->d_rot);
	matrix_free(knm->rot);
	free(knm);
}

void obj_fields_attach(int type, void **fields_ptr) {
	switch (type) {
		case OBJ_BASIC:
			return;
		case OBJ_CAMERA:
			{
			*fields_ptr = camera_fields_init();
			return;
			}
		case OBJ_AIRCRAFT:
			{
			*fields_ptr = aircraft_fields_init();
			return;
			}
	}
	return;
}

void obj_fields_free(int type, void *fields) {
	if (fields == NULL)
		return;
	switch (type) {
		case OBJ_CAMERA:
			{
			camera_fields_free(fields);
			return;
			}
		case OBJ_AIRCRAFT:
			{
			aircraft_fields_free(fields);
			return;
			}
	}
	return;
}

/*
int object_add_point(object *o, double x, double y, double z) {
	return matrix_addpoint_fromcoords(o->g->p, x, y, z);
}
*/

int object_add_edge(obj_geometry *g, int p1, int p2) {
	if (g->num_edges >= g->max_edges)
		return 0;
	g->e[g->num_edges*2] = p1;
	g->e[g->num_edges*2 + 1] = p2;
	g->num_edges++;
	return g->num_edges;
}
