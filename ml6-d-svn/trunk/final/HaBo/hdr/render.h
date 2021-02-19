#ifndef _RENDER_H
#define _RENDER_H

#include "objects.h"
#include "scene.h"

void render_scene(node *scene, node *cam); // Traverses scene graph and calls render_object on the object contained in each node.
void render_object(object *o, object *cam, matrix *cam_tform);

#endif
