#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "aircraft.h"
#include "globals.h"
#include "matrix.h"



/*
Object types

If type OBJ_BLAH exists in the list below (with the exception of OBJ_BASIC),
there are files blah.c and blah.h that contain definitions for the following:

a typedef'd struct named blah_fields;
blah_fields *blah_fields_init();
void blah_fields_free(blah_fields *f);
*/
#define OBJ_BASIC 0
#define OBJ_CAMERA 1
#define OBJ_AIRCRAFT 2

// Object flags
//#define OBJ_FL_STATIC 1


// Objects are put in nodes and strung together as a linked list called a scene. See scene.h


object *object_new(int type, int num_points, int num_edges, int num_faces);
void object_free(object *o);

obj_geometry *obj_geometry_new(int num_points, int num_edges, int num_faces);
obj_kinematics *obj_kinematics_new();

void obj_geometry_free(obj_geometry *geo);
void obj_kinematics_free(obj_kinematics *knm);

void obj_fields_attach(int type, void **fields_ptr);
void obj_fields_free(int type, void *fields);


//int object_add_point(object *o, double x, double y, double z);
int object_add_edge(obj_geometry *g, int p1, int p2); // Returns new number of edges, or 0 if full

#endif

