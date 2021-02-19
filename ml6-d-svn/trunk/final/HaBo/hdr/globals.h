#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdio.h>
#include <SDL/SDL_keysym.h>

#include "matrix.h"
#include "macros.h"

struct indivcolor {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
};

typedef union _color {
	struct indivcolor c;
	unsigned int i;
} color;

int screen_w;
int screen_h;
int screen_update;

int fov; // degrees

void *pixel_array;
int   pixel_pitch;

double *zbuffer;

int render_points;
int render_lines;

int keys[SDLK_LAST];

enum debuggroups {
	D_ANY,
	D_ALL,
	
	D_WELCOME,
	D_PARSE,
	D_PARSE_S,
	D_INPUT,
	D_SIGNALS,
	D_FRAME_RATE,
	
	D_LAST
};

typedef struct _obj_geometry {
	matrix *p; // points
	matrix *tp;
	matrix *pp;
	matrix *fp;
	int *e; // edges: pairs of points. e[0] and e[1] store the endpoints of the first edge (by their column numbers in the point matrix), and so on.
	int num_edges;
	int max_edges;
	int *f; // faces: triples of points.
	int nf;
	color *c; // one for every point
	color *ce; // one for every edge
} obj_geometry;

typedef struct _obj_kinematics {
	double    ctr[3]; // center (of rotation)
	double    pos[3]; // position
	double  d_pos[3]; // translational velocity (meters/second)
	double dd_pos[3];
	matrix *rot;
	matrix *d_rot;
	matrix *dd_rot;
} obj_kinematics;

typedef struct _object {
	int type;
	obj_geometry *g;
	void *f; // Object-type-specific fields. Could point to an aircraft_fields, or a camera_fields, etc.
	unsigned char flags;
} object;

typedef union _node_payload {
	object *o;
	obj_kinematics *k;
} node_payload;
	
typedef struct _node {
	int type;
	struct _node *parent;
	int child_id; // keeps track of where this node is indexed in the parent's next[] array
	struct _node **child;
	int nchild;
	int achild;
	node_payload n;
} node;

node *root_node;
node *cam_node;
node *usrctl_node;

int debugs[D_LAST];

#define PROGRAM_NAME "HaBoSim"

#define DEPTH 32
#define MAX_COLOR 255
#define CLIP_DIST 1

#define R2D 180.0/M_PI
#define D2R M_PI/180.0

void globals_init(void);

#endif
