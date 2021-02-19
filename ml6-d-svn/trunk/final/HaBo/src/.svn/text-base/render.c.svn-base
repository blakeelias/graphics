#include <math.h>

#include "camera.h"
#include "line.h"
#include "matrix.h"
#include "render.h"
#include "stack.h"
#include "surface.h"

void render_subtree(node *n, object *cam, matrix *cam_tform);
matrix *render_get_cam_tform(node *cam);

void render_scene(node *scene, node *cam) {
	//debug_w("child %d, node type %d, max %d children", scene->child_id, scene->type, scene->max_child);
	//debug_w("%lf", scene->child[0]->n.k->pos[0]);
	matrix *m = render_get_cam_tform(cam);
	render_subtree(scene, cam->n.o, m);
	//matrix_free(m);
}

void render_subtree(node *n, object *cam, matrix *cam_tform) {
	static matrix *temp = NULL;
	if(temp == NULL){
		temp = matrix_new(4, 4);
	}
	if (n->type == NODE_OBJ) {
		render_object(n->n.o, cam, cam_tform);
	}
	if (n->type == NODE_TFORM) {
		matrix_make_transform(temp,
		                      n->n.k->pos[0], n->n.k->pos[1], n->n.k->pos[2], n->n.k->rot);
		
		//debug_n("Push\n");
		//matrix_print(temp);
		stack_push(temp);
	}
	//matrix_free(temp);
	int i;
	for (i = 0; i < n->nchild; i++) {
		render_subtree(n->child[i], cam, cam_tform);	
	}
	if (n->type == NODE_TFORM) {
		//debug_n("Pop\n"); 
		stack_pop();
	}
}

matrix *render_get_cam_tform(node *cam) {
	static matrix *m = NULL;
	if(m == NULL){
		m = matrix_new(4, 4);
	}
	static matrix *temp = NULL;
	if(temp == NULL){
		temp = matrix_new(4, 4);
	}
	matrix_make_ident(m);
	node *n = cam->parent;
	while (n != NULL) {
		if (n->type == NODE_TFORM) {
			obj_kinematics *k = n->n.k;
			matrix_make_tform_inv(temp, k->pos[0], k->pos[1], k->pos[2], k->rot);
			matrix_mult_inplace(m, temp);
			matrix_copy(temp, m);
			//matrix_print(m);
		}
		n = n->parent;
	}
	// Force the camera to be level with the horizon
	/*
	matrix_make_rot_x(temp, atan2(m->m[2][1], m->m[2][2]) *180/M_PI);
	float cam_trans[3];
	int i;
	//for (i = 0; i < 3; i++) {
		//cam_trans[i] = m->m[3][i];
	//}
	matrix_mult_inplace(temp, m);
	//for (i = 0; i < 3; i++) {
		//m->m[3][i] = cam_trans[i];
	//}
	//matrix_print(m);
	*/
	return m;
}

void render_object(object *o, object *cam, matrix *cam_tform) {
	//debug_w("Rendering type %d object\n", o->type);
	obj_geometry *g = o->g;
	static matrix *temp = NULL;
	if(temp == NULL){
		temp = matrix_new(4, 4);
	}
	int i;
	
	if (g == NULL)
		return; // If it doesn't have geometry data (e.g. it's a camera object), don't try to render it
	
	matrix *tfp = g->tp; //matrix_new(g->p->ac, 4); // transformed points // TODO: move this inside the object
	//matrix_copy(g->p, tfp);

	// Transform geometry data according to position and rotation data
	//matrix_mult_inplace(stack->m, tfp);
	//matrix_print(stack->m);
	matrix_mult(stack->m, g->p, tfp);
	
	// Camera transform (Camera ends up looking down positive x (0) axis)
	//matrix_print(cam_tform);
	//debug_w("tfp[0]: (%lf, %lf, %lf, %lf)", tfp->m[0][0], tfp->m[0][1], tfp->m[0][2], tfp->m[0][3]);
	matrix_mult_inplace(cam_tform, tfp);
	//debug_w("tfp[0]: (%lf, %lf, %lf, %lf)", tfp->m[0][0], tfp->m[0][1], tfp->m[0][2], tfp->m[0][3]);
	
	//matrix_print(tfp);

	// Deal with edges that intersect with or are behind the image plane
	matrix *pp = g->pp; //matrix_new(g->num_edges * 2, 4); // point pairs // TODO: move this inside the object
	matrix *fp = g->fp;
	pp->nc = 0;
	fp->nc = 0;
	double c = CLIP_DIST;
	for (i = 0; i < g->num_edges; i++) {
		double *p1 = tfp->m[g->e[2*i    ]];
		double *p2 = tfp->m[g->e[2*i + 1]];
		
		if (p1[0] < c && p2[0] < c)
			continue;
			
		if (p1[0] > c && p2[0] > c) {
			matrix_addpoint(pp, p1);
			matrix_addpoint(pp, p2);
			continue;
		}
		
		double intersection_y = intersect(c, p1, p2, 1);//p1[1] + (c-p1[0])/(p2[0]-p1[0]) * (p2[1] - p1[1]);
		double intersection_z = intersect(c, p1, p2, 2);//p1[2] + (c-p1[0])/(p2[0]-p1[0]) * (p2[2] - p1[2]);
		
		if (p1[0] < c) {
			matrix_addpoint_fromcoords(pp, c, intersection_y, intersection_z);
			matrix_addpoint(pp, p2);
		} else {
			matrix_addpoint(pp, p1);
			matrix_addpoint_fromcoords(pp, c, intersection_y, intersection_z);
		}
	}
	for(i = 0; i < g->nf; i++){
		double *p1 = tfp->m[g->f[3 * i    ]];
		double *p2 = tfp->m[g->f[3 * i + 1]];
		double *p3 = tfp->m[g->f[3 * i + 2]];
		
		double inty, intz;
		
		if(p1[0] <= c){
			if(p2[0] <= c){
				if(p3[0] <= c){
					continue;
				} else {
					/*matrix_addpoint_resize(fp, p3);
					inty = intersect(c, p1, p3, 1);
					intz = intersect(c, p1, p3, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					inty = intersect(c, p2, p3, 1);
					intz = intersect(c, p2, p3, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);*/
				}
			} else {
				if(p3[0] <= c){
					/*matrix_addpoint_resize(fp, p3);
					inty = intersect(c, p1, p2, 1);
					intz = intersect(c, p1, p2, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					inty = intersect(c, p2, p3, 1);
					intz = intersect(c, p2, p3, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);*/
				} else {
					/*matrix_addpoint_resize(fp, p2);
					matrix_addpoint_resize(fp, p3);
					inty = intersect(c, p1, p2, 1);
					intz = intersect(c, p1, p2, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					inty = intersect(c, p1, p3, 1);
					intz = intersect(c, p1, p3, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					matrix_addpoint_resize(fp, p3);*/
				}
			}
		} else {
			if(p2[0] <= c){
				if(p3[0] <= c){
					/*matrix_addpoint_resize(fp, p1);
					inty = intersect(c, p1, p2, 1);
					intz = intersect(c, p1, p2, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					inty = intersect(c, p1, p3, 1);
					intz = intersect(c, p1, p3, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);*/
				} else {
					/*matrix_addpoint_resize(fp, p1);
					matrix_addpoint_resize(fp, p3);
					inty = intersect(c, p1, p2, 1);
					intz = intersect(c, p1, p2, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					inty = intersect(c, p2, p3, 1);
					intz = intersect(c, p2, p3, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					matrix_addpoint_resize(fp, p3);*/
				}
			} else {
				if(p3[0] <= c){
					/*matrix_addpoint_resize(fp, p1);
					matrix_addpoint_resize(fp, p2);
					inty = intersect(c, p1, p3, 1);
					intz = intersect(c, p1, p3, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					inty = intersect(c, p2, p3, 1);
					intz = intersect(c, p2, p3, 2);
					matrix_addpoint_fromcoords_resize(fp, c, inty, intz);
					matrix_addpoint_resize(fp, p2);*/
				} else {
					matrix_addpoint_resize(fp, p1);
					matrix_addpoint_resize(fp, p2);
					matrix_addpoint_resize(fp, p3);
				}
			}
		}
	}
	// Project onto screen surface
	matrix_make_zero(temp);
	temp->m[1][0] = 1;
	temp->m[2][1] = 1;
	temp->m[0][2] = 1;
	temp->m[0][3] = 1 / (((camera_fields *) cam_node->n.o->f)->d);
	
	matrix_mult_inplace(temp, pp);
	matrix_mult_inplace(temp, fp);
	
	for(i = 0; i < pp->nc; i++){
		pp->m[i][0] /= pp->m[i][3];
		pp->m[i][1] /= pp->m[i][3];
		pp->m[i][2] /= pp->m[i][3];
		pp->m[i][3] = 1;
	}
	for(i = 0; i < fp->nc; i++){
		fp->m[i][0] /= fp->m[i][3];
		fp->m[i][1] /= fp->m[i][3];
		fp->m[i][2] /= fp->m[i][3];
		fp->m[i][3] = 1;
	}

	// Scale according to field of view and size of screen; move origin to center of screen
	double pixels_per_meter = screen_w / (2 * (((camera_fields *) cam->f)->d) * tan(((2.0*M_PI)/360)*fov));
	matrix_make_scale(temp, pixels_per_meter, pixels_per_meter, pixels_per_meter);
	matrix_mult_inplace(temp, pp);
	matrix_mult_inplace(temp, fp);
	matrix_make_translate(temp, screen_w/2, screen_h/2, 0);
	matrix_mult_inplace(temp, pp);
	matrix_mult_inplace(temp, fp);
	
	// Draw lines
	for(i = 0; i < pp->nc / 2; i++){
		/*
		debug_w("\n\tDrawing line (%lf,%lf),(%lf,%lf)",
				pp->m[2 * i    ][0],
				pp->m[2 * i    ][1],
				pp->m[2 * i + 1][0],
				pp->m[2 * i + 1][1]
		);
		*/   
		/*line_draw_aa(pp->m[2 * i    ][0],
		             pp->m[2 * i    ][1],
		             pp->m[2 * i + 1][0],
		             pp->m[2 * i + 1][1],
		             (color) 0x00ffffffu);*/
	}
	for(i = 0; i < fp->nc; i += 3){
		surface_draw(fp, i, (color) 0x00777777u);
	}
	//for(i = 0; i <
	
	//matrix_free(pp);
	//matrix_free(tfp);
	//matrix_free(temp);
}
