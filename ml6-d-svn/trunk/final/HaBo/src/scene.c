#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "objects.h"
#include "scene.h"

node *scene_add_node(node *parent_node, int achild);
void scene_print_helper(node *subtree, int generation);


node *scene_add_node(node *parent_node, int achild) {

	if(parent_node != NULL){
		if(parent_node->nchild >= parent_node->achild){
			while(parent_node->nchild >= parent_node->achild){
				parent_node->achild += NODE_CHILDREN_REALLOC_INCREMENT;
			}
			debug_n("Reallocing");
			void *temp = realloc(parent_node->child, parent_node->achild * sizeof(node *));
			if(temp == NULL){
				error_n("Realloc failed.");
				raise(SIGSEGV);
			}
			parent_node->child = temp;
		}
	} else {
		//error_n("Null parent_node!");
		//*((int *) 0x0) = 0;
		//return NULL;
	}
		
	node *n = (node *) malloc(sizeof(node));
	
	n->parent = parent_node;
	if(parent_node != NULL){
		n->child_id = parent_node->nchild;
		parent_node->child[parent_node->nchild] = n;
		parent_node->nchild++;
	}
	
	n->child = (node **) malloc(achild * sizeof(node *));
	n->nchild = 0;
	n->achild = achild;
	
	return n;
}

node *scene_add_tform(obj_kinematics *k, node *parent_node, int achild) {
	node *n = scene_add_node(parent_node, achild);
	if (n == NULL)
		return NULL;
	n->type = NODE_TFORM;
	n->n.k = k;
	return n;
}

node *scene_add_obj(object *o, node *parent_node, int achild) {
	node *n = scene_add_node(parent_node, achild);
	if (n == NULL)
		return NULL;
	n->type = NODE_OBJ;
	n->n.o = o;
	return n;
}


void scene_print(node *subtree) {
	scene_print_helper(subtree, 0);
}

void scene_print_helper(node *subtree, int generation) {
	int i;
	for (i = 0; i < generation; i++)
		fprintf(stderr, " ");
	fprintf(stderr, "Gen %d, child %d, node type %d, %d/%d children",
	       generation, subtree->child_id, subtree->type, subtree->nchild, subtree->achild);
	/*if(subtree->type == NODE_OBJ && subtree->n.o->type == OBJ_BASIC){
		printf(", geometry %x", (unsigned int) subtree->n.o->g);
	}*/
	fprintf(stderr, "\n");
	for (i = 0; i < subtree->nchild; i++)
		scene_print_helper(subtree->child[i], generation + 1);
}

void scene_rm_leaf(node *leaf) {
	//free(leaf->child);
	switch (leaf->type) {
		case (NODE_TFORM):
			//debug_w("freeing tform at ptr %d\n", (int) leaf->n.k);
			obj_kinematics_free(leaf->n.k);
			//debug_n("freed\n");
			break;
		case (NODE_OBJ):
			//debug_w("freeing obj at ptr %d\n", (int) leaf->n.o);
			object_free(leaf->n.o);
			//debug_n("freed\n");
			break;
	}
	//free(leaf);
}



void scene_free(node *subtree) {
	scene_print(subtree);
	int i;
	for (i = 0; i < subtree->nchild; i++)
		debug_n("Freeing subtree...");
		scene_free(subtree->child[i]);
	debug_n("Freeing leaf!");
	scene_rm_leaf(subtree);
}


