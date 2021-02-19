#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "world.h"
#include "objects.h"
#include "parse.h"
#include "scene.h"
#include "camera.h"

//#define NUM_OBJECTS 256

void world_init(void) {

	root_node = scene_add_tform(obj_kinematics_new(), NULL, 0);
	
	obj_kinematics *rootk, *planek/*, *missilek*/;
	   rootk = obj_kinematics_new();
	  planek = obj_kinematics_new();
	//missilek = obj_kinematics_new();
	
	object *plane;
	plane = parse_object("data/models/plane2.obj");
	plane->type = OBJ_AIRCRAFT;
	obj_fields_attach(OBJ_AIRCRAFT, &(plane->f));
	
	//object *missile;
	//missile = parse_object("data/models/missile.obj");
	//missilek->pos[1] = 10;
	
	object *sphere;
	sphere = parse_object("data/models/sphere.obj");
	
	node *roottform, *planetform/*, *missiletform*/;
	
	debug_n("adding root tform");
	roottform = scene_add_tform(   rootk, root_node, 2);
	debug_n("adding plane tform");
	planetform = scene_add_tform(  planek, roottform, 2);
	//missiletform = scene_add_tform(missilek, roottform, 1);
	
	node *plane_node = scene_add_obj(plane, planetform, 0);
	//scene_add_obj(missile, missiletform, 0);
	scene_add_obj(sphere, roottform, 0);
	
	obj_kinematics *cam_k = obj_kinematics_new();
	node *cam_tform = scene_add_tform(cam_k, planetform, 1);
	cam_node = scene_add_obj(object_new(OBJ_CAMERA, 0, 0, 0), cam_tform, 0);
	cam_tform->n.k->pos[0] = -25;
	cam_tform->n.k->pos[2] = -3;
	((camera_fields *) (cam_node->n.o->f))->d = 1;
	
	usrctl_node = plane_node;
	
}

// No longer needed
/*
object *world_make_cube(double side) { // Demonstration purposes only

	object *o = object_new(OBJ_AIRCRAFT, 8, 12, 6);
	matrix *pm = o->g->p; // point matrix
	
	matrix_addpoint_fromcoords(pm,  side/2,  side/2,  side/2);
	matrix_addpoint_fromcoords(pm,  side/2,  side/2, -side/2);
	matrix_addpoint_fromcoords(pm,  side/2, -side/2,  side/2);
	matrix_addpoint_fromcoords(pm,  side/2, -side/2, -side/2);
	matrix_addpoint_fromcoords(pm, -side/2,  side/2,  side/2);
	matrix_addpoint_fromcoords(pm, -side/2,  side/2, -side/2);
	matrix_addpoint_fromcoords(pm, -side/2, -side/2,  side/2);
	matrix_addpoint_fromcoords(pm, -side/2, -side/2, -side/2);
	
	object_add_edge(o->g, 0, 1);
	object_add_edge(o->g, 1, 3);
	object_add_edge(o->g, 3, 2);
	object_add_edge(o->g, 2, 0);
	object_add_edge(o->g, 4, 5);
	object_add_edge(o->g, 5, 7);
	object_add_edge(o->g, 7, 6);
	object_add_edge(o->g, 6, 4);
	object_add_edge(o->g, 0, 4);
	object_add_edge(o->g, 1, 5);
	object_add_edge(o->g, 2, 6);
	object_add_edge(o->g, 3, 7);
	
	int i;
	color *point_colors = o->g->c;
	for (i = 0; i < 8; i++) {
		point_colors[i] = (color) (unsigned int) 0x00ffffff;
	}
	color *edge_colors = o->g->ce;
	for (i = 0; i < 12; i++) {
		edge_colors[i] = (color) (unsigned int) 0x00ffffff;
	}
	
	return o;
}
*/
