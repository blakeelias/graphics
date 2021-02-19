#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "globals.h"
#include "parse.h"
#include "objects.h"
#include "matrix.h"
#include "scene.h"
#include "camera.h"

#define PARSE_SCALE 1

#define BUF_REALLOC_INC 256

void parse_scene(char *filename){
	d_debug_w(D_PARSE_S, "Parsing '%s'.", filename);
	FILE *in;
	if((in = fopen(filename, "r")) == NULL){
		error_w("File open on '%s' failed: %m", filename);
		raise(SIGABRT);
	}
	//int tabs;
	char *buf;
	int abuf = BUF_REALLOC_INC, nbuf = 0;
	//int i;
	int tmp;
	buf = malloc(abuf * sizeof(char));
	while(1){
		if(abuf == nbuf){
			buf = realloc(buf, abuf += BUF_REALLOC_INC);
		}
		if((buf[nbuf++] = fgetc(in)) == EOF){
			break;
		}
		if(buf[nbuf - 1] != ';'){
			tmp = 0;
			while(tmp != EOF && tmp != '\n'){
				tmp = fgetc(in);
			}
			continue;
		}
		d_debug_w(D_PARSE_S, "Line:\n'%s'", buf);
	}
	
	
	
	root_node = scene_add_tform(obj_kinematics_new(), NULL, 32);
	
	obj_kinematics *cam_k = obj_kinematics_new();
	node *cam_tform = scene_add_tform(cam_k, root_node, 1);
	cam_node = scene_add_obj(object_new(OBJ_CAMERA, 0, 0, 0), cam_tform, 0);
	
	cam_tform->n.k->pos[0] = -25;
	((camera_fields *) (cam_node->n.o->f))->d = 1;
	
	obj_kinematics *rootk;
	rootk = obj_kinematics_new();
	node *roottform;
	roottform = scene_add_tform(   rootk, root_node, 1);
	
	object *demoobj;
	demoobj = parse_object("data/models/demo.obj");
	scene_add_obj(demoobj, roottform, 0);
	
	return;
}

object *parse_object(char *filename){
	d_debug_w(D_PARSE, "Parsing '%s'.", filename);
	FILE *in;
	if((in = fopen(filename, "r")) == NULL){
		error_w("File open on '%s' failed: %m", filename);
		raise(SIGABRT);
	}
	char buf[256];
	int numverts = 0,
	    numtexts = 0,
	    numnorms = 0,
	    numfaces = 0;
	int i;
	while(fgets(buf, 256, in) != NULL){
		for(i = 0; buf[i] == ' '; i++);
		if(buf[i] == '#'){
		} else
		if(!strncmp(buf + i, "v " , 2)){
			numverts++;
		} else
		if(!strncmp(buf + i, "vt ", 3)){
			numtexts++;
		} else
		if(!strncmp(buf + i, "vn ", 3)){
			numnorms++;
		} else
		if(!strncmp(buf + i, "f " , 2)){
			numfaces++;
		}
	}
	d_debug_w(D_PARSE, "\n  vertices = %d,\n  textures = %d,\n  normals = %d,\n  faces = %d.", numverts, numtexts, numnorms, numfaces);
	rewind(in); // almost equivalent to fseek(in, 0, SEEK_SET);
	matrix *v = matrix_new(numverts, 4);
	int *edges;
	edges = malloc(numfaces * 3 * 2 * sizeof(int));
	int *faces;
	faces = malloc(numfaces * 3 * sizeof(int));
	i = 0;
	int nv  = 0;//,
	//    nvt = 0,
	//    nvn = 0;
	int nf  = 0;
	int ne  = 0;
	int fv[3];
	int dovp[3];
	while(fgets(buf, 256, in) != NULL){
		for(i = 0; buf[i] == ' '; i++);
		if(buf[i] == '#'){
			continue;
		}
		if(!strncmp(buf + i, "v " , 2)){
			for(i++; buf[i] == ' '; i++);
			v->m[nv][0] = PARSE_SCALE * atof(buf + i);
			for(; buf[i] != ' '; i++);
			for(; buf[i] == ' '; i++);
			v->m[nv][2] = PARSE_SCALE * atof(buf + i); // NOTE: OUT OF ORDER!!!!
			for(; buf[i] != ' '; i++);
			for(; buf[i] == ' '; i++);
			v->m[nv][1] = PARSE_SCALE * atof(buf + i); // NOTE: OUT OF ORDER!!!!
			v->m[nv][3] = 1;
			//d_debug_w(D_PARSE, "Vertex %d:\n  x = %lf,\n  y = %lf,\n  z = %lf", nv, v->m[nv][0], v->m[nv][1], v->m[nv][2]);
			nv++;
		} /*else
		if(!strncmp(buf + i, "vn ", 3)){
			for(i++; buf[i] == ' '; i++);
			v->m[nvn][0] = atof(buf + i);
			for(; buf[i] != ' '; i++);
			for(; buf[i] == ' '; i++);
			v->m[nvn][1] = atof(buf + i);
			for(; buf[i] != ' '; i++);
			for(; buf[i] == ' '; i++);
			v->m[nvn][2] = atof(buf + i);
			v->m[nvn][3] = 0;
			d_debug_w(D_PARSE, "Normal %d:\n  x = %lf,\n  y = %lf,\n  z = %lf", nv, v->m[nvn][0], v->m[nvn][1], v->m[nvn][2]);
			nvn++;
		}*/ else
		if(!strncmp(buf + i, "f " , 2)){
			for(i++; buf[i] == ' '; i++);
			fv[0] = atoi(buf + i) - 1;
			for(; buf[i] != ' '; i++);
			for(; buf[i] == ' '; i++);
			fv[1] = atoi(buf + i) - 1;
			for(; buf[i] != ' '; i++);
			for(; buf[i] == ' '; i++);
			fv[2] = atoi(buf + i) - 1;
			//d_debug_w(D_PARSE, "Face %d:\n  v1 = %d,\n  v2 = %d,\n  v3 = %d", nf, fv[0], fv[1], fv[2]);
			dovp[0] = 1;
			dovp[1] = 1;
			dovp[2] = 1;
			for(i = 0; i < ne; i++){
				if(edges[2 * i] == fv[0]){
					if(edges[2 * i + 1] == fv[1]){
						dovp[0] = 0;
					} else
					if(edges[2 * i + 1] == fv[2]){
						dovp[2] = 0;
					}
				}
				if(edges[2 * i] == fv[1]){
					if(edges[2 * i + 1] == fv[0]){
						dovp[0] = 0;
					} else
					if(edges[2 * i + 1] == fv[2]){
						dovp[1] = 0;
					}
				}
				if(edges[2 * i] == fv[2]){
					if(edges[2 * i + 1] == fv[0]){
						dovp[2] = 0;
					} else
					if(edges[2 * i + 1] == fv[1]){
						dovp[1] = 0;
					}
				}
			}
			if(dovp[0]){
				edges[2 * ne    ] = fv[0];
				edges[2 * ne + 1] = fv[1];
				ne++;
				//d_debug_w(D_PARSE, "Added Edge %d: (%d, %d)", ne, fv[0], fv[1]);
			}// else {
				//d_debug_n(D_PARSE, "Edge skipped.");
			//}
			if(dovp[1]){
				edges[2 * ne    ] = fv[1];
				edges[2 * ne + 1] = fv[2];
				ne++;
				//d_debug_w(D_PARSE, "Added Edge %d: (%d, %d)", ne, fv[0], fv[1]);
			}// else {
				//d_debug_n(D_PARSE, "Edge skipped.");
			//}
			if(dovp[2]){
				edges[2 * ne    ] = fv[0];
				edges[2 * ne + 1] = fv[2];
				ne++;
				//d_debug_w(D_PARSE, "Added Edge %d: (%d, %d)", ne, fv[0], fv[1]);
			}// else {
				//d_debug_n(D_PARSE, "Edge skipped.");
			//}
			//memcpy(faces + 3 * nf, fv, 3 * sizeof(int));
			faces[3 * nf    ] = fv[0];
			faces[3 * nf + 1] = fv[1];
			faces[3 * nf + 2] = fv[2];
			nf++;
		}
		
	}
	d_debug_w(D_PARSE, "%d edges.", ne);
	//for(i = 0; i < ne; i++){
	//	d_debug_w(D_PARSE, "Edge %d: (%d, %d)", i, edges[2 * i], edges[2 * i + 1]);
	//}
	
	object *o;
	//o = (object *) malloc(sizeof(object));
	o = object_new(OBJ_BASIC, 1, 1, 1);
	obj_geometry *g;
	g = o->g;
	//debug_w("g = %x", (unsigned int) g);
	g->tp->m[0][0] = 0;
	matrix_free(g->p);
	matrix_free(g->tp);
	matrix_free(g->pp);
	g->p = v;
	g->tp = matrix_new(numverts, 4);
	g->pp = matrix_new(2 * ne, 4);
	// Note Bene:
	// I'm not using the point matrix created by object_new();
	edges = realloc(edges, ne * 2 * sizeof(int));
	free(g->e);
	g->e = edges;
	g->num_edges = ne;
	g->max_edges = ne;
	free(g->f);
	g->f = faces;
	g->nf = numfaces;
	free(g->c);
	free(g->ce);
	g->c  = (color *) malloc(numverts * sizeof(color));
	g->ce = (color *) malloc(ne       * sizeof(color));
	for(i = 0; i < numverts; i++){
		g->c [i] = (color) (unsigned int) 0x00ffffff;
	}
	for(i = 0; i < ne; i++){
		g->ce[i] = (color) (unsigned int) 0x00ffffff;
	}
	
	d_debug_w(D_PARSE, "Parsed '%s'.", filename);
	
	fclose(in);
	return o;
}
