#ifndef _SCREEN_H
#define _SCREEN_H

#include "camera.h"
#include "globals.h"
#include "objects.h"
#include "scene.h"

void screen_init(void);
void screen_main(void); // Calls render_scene()
void screen_toggle_fullscreen(void);

void screen_clear(void);
void screen_draw_pixel(int x, int y, color c);
void screen_refresh(void);

#endif
