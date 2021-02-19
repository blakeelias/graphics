#include "camera.h"

#include <stdlib.h>

void *camera_fields_init() {
	void *f = malloc(sizeof(camera_fields));
	return f;
}

void camera_fields_free(void *f) {
	free(f);
}
