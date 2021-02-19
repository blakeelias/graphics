#ifndef _SCENE_H
#define _SCENE_H

#include "objects.h"
#include "globals.h"

// Types
#define NODE_TFORM 0
#define NODE_OBJ 1

/*
A "scene" is a tree of nodes that describes the geometry and movement of the universe.

To start a new scene:

node *scene_graph_root = scene_add_tform(obj_kinematics_new(), NULL, how_many_children_you_think_you'll_need);

This will create an identity transform that you can use as the root of your graph. Add other nodes as children, grandchildren, etc. of this root node.
*/
node *scene_add_tform(obj_kinematics *k, node *parent_node, int achild);
node *scene_add_obj(object *o, node *parent_node, int achild);
void scene_print(node *subtree);
void scene_rm_leaf(node *leaf);
void scene_free(node *subtree); // call this on the root node to free the entire graph, or on another node to free a subtree

#define NODE_CHILDREN_REALLOC_INCREMENT 1

#endif

