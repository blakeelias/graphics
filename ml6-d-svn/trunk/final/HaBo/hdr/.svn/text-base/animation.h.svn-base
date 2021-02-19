#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <time.h>

#include "scene.h"

struct timespec time_last_update, time_current;

void animation_init();

/*
Updates the position of every object in the scene,
based on the velocity parameters in each object's kinematics data
and how much time has elapsed since the last update.
*/
void animation_update_scene(node *scene);

matrix *rot_temp;

#endif
