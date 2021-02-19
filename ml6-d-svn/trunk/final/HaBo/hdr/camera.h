#ifndef _CAMERA_H
#define _CAMERA_H

#include "scene.h"

typedef struct _camera_fields {
	double d; // distance between eye and screen
	// add more stuff
} camera_fields;

void *camera_fields_init();
void camera_fields_free(void *f);

#endif
