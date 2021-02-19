#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "line.h"
#include "darea.h"
#include "constants.h"

//#define ANTIALIAS

extern int height;
extern int width;

//Insert your line algorithm here
//#ifndef ANTIALIAS
void draw_line(int x0, int y0, int x1, int y1, color c){
	int flip, tmp;
	if((flip = (abs(y1 - y0) > abs(x1 - x0)))){
		tmp = x0;
		x0  = y0;
		y0  = tmp;
		tmp = x1;
		x1  = y1;
		y1  = tmp;
	}
	if(x0 > x1){
		tmp = x0;
		x0  = x1;
		x1  = tmp;
		tmp = y0;
		y0  = y1;
		y1  = tmp;
	}
	int dx, dy, yinc, err;
	dx = x1 - x0;
	dy = abs(y1 - y0);
	err = dx / 2;
	if(y1 < y0){
		yinc = -1;
	} else {
		yinc = 1;
	}
	int x, y;
	y = y0;
	for(x = x0; x <= x1; x++){
		if(flip){
			plot(c, y, x);
		} else {
			plot(c, x, y);
		}
		err -= dy;
		if(err < 0){
			y += yinc;
			err += dx;
		}
	}
}
//#else
#define PIXEL_INFO_STRING "%s, (%3d, %3d) = (%3d, %3d, %3d) = (%3d, %3d, %3d)*(%4.2lf) + (%3d, %3d, %3d)*(%4.2lf)\n"
void draw_line_aa(int x0, int y0, int x1, int y1, color c){
	int dx, dy, flip, tmp;
	dx = x1 - x0;
	dy = y1 - y0;
	if((flip = (abs(dy) > abs(dx)))){
		tmp = x0;
		x0  = y0;
		y0  = tmp;
		tmp = x1;
		x1  = y1;
		y1  = tmp;
		tmp = dx;
		dx  = dy;
		dy  = tmp;
	}
	if(x0 > x1){
		tmp = x0;
		x0  = x1;
		x1  = tmp;
		tmp = y0;
		y0  = y1;
		y1  = tmp;
	}
	color cc1, cc2, oc1, oc2;
	unsigned int ctmp;
	double slope, dtmp, intery, fracy;
	slope = (double) dy / dx;
	intery = y0 + slope;
	if(flip){
		plot(c, y0, x0);
		plot(c, y1, x1);
	} else {
		plot(c, x0, y0);
		plot(c, x1, y1);
	}
	double sqrtpfy, sqrtmfy;
	int i;
	for(i = x0 + 1; i < x1; i++){
		fracy = modf(intery, &dtmp);
		if(flip){
			oc1.i = pixel((int) dtmp    , i);
			oc2.i = pixel((int) dtmp + 1, i);
			if(oc1.i != 0){
				printf("oc1 @ (%3d, %3d) = %08X\n", (int) dtmp, height - 1 - i, oc1.i);
			}
		} else {
			oc1.i = pixel(i, (int) dtmp);
			oc2.i = pixel(i, (int) dtmp + 1);
		}
		printf("fracy = %lf\n", fracy);
		sqrtpfy = sqrt(      fracy);
		sqrtmfy = sqrt(1.0 - fracy);
		//cc1.i = 0;
		//cc2.i = 0;
		ctmp = (sqrtmfy * c.c.r) + (sqrtpfy * oc1.c.r); if(ctmp > MAX_COLOR){ cc1.c.r = MAX_COLOR; } else { cc1.c.r = ctmp; }
		ctmp = (sqrtmfy * c.c.g) + (sqrtpfy * oc1.c.g); if(ctmp > MAX_COLOR){ cc1.c.g = MAX_COLOR; } else { cc1.c.g = ctmp; }
		ctmp = (sqrtmfy * c.c.b) + (sqrtpfy * oc1.c.b); if(ctmp > MAX_COLOR){ cc1.c.b = MAX_COLOR; } else { cc1.c.b = ctmp; }
		ctmp = (sqrtpfy * c.c.r) + (sqrtmfy * oc1.c.r); if(ctmp > MAX_COLOR){ cc2.c.r = MAX_COLOR; } else { cc2.c.r = ctmp; }
		ctmp = (sqrtpfy * c.c.g) + (sqrtmfy * oc1.c.g); if(ctmp > MAX_COLOR){ cc2.c.g = MAX_COLOR; } else { cc2.c.g = ctmp; }
		ctmp = (sqrtpfy * c.c.b) + (sqrtmfy * oc1.c.b); if(ctmp > MAX_COLOR){ cc2.c.b = MAX_COLOR; } else { cc2.c.b = ctmp; }
		/*
		cc1.c.r = (sqrtmfy * c.c.r) + (sqrtpfy * oc1.c.r);
		cc1.c.g = (sqrtmfy * c.c.g) + (sqrtpfy * oc1.c.g);
		cc1.c.b = (sqrtmfy * c.c.b) + (sqrtpfy * oc1.c.b);
		cc2.c.r = (sqrtpfy * c.c.r) + (sqrtmfy * oc2.c.r);
		cc2.c.g = (sqrtpfy * c.c.g) + (sqrtmfy * oc2.c.g);
		cc2.c.b = (sqrtpfy * c.c.b) + (sqrtmfy * oc2.c.b);
		if(cc1.c.r > MAX_COLOR){ cc1.c.r = MAX_COLOR; }
		if(cc1.c.g > MAX_COLOR){ cc1.c.g = MAX_COLOR; }
		if(cc1.c.b > MAX_COLOR){ cc1.c.b = MAX_COLOR; }
		if(cc2.c.r > MAX_COLOR){ cc2.c.r = MAX_COLOR; }
		if(cc2.c.g > MAX_COLOR){ cc2.c.g = MAX_COLOR; }
		if(cc2.c.b > MAX_COLOR){ cc2.c.b = MAX_COLOR; }
		*/
		if(flip){
			pixel((int) dtmp    , i) = cc1.i;
			//printf(PIXEL_INFO_STRING, "1-1", (int) dtmp    , i, cc1.red, cc1.green, cc1.blue,
			//                                                      c.red,   c.green,   c.blue, 1.0 - fracy,
			//                                                    oc1.red, oc1.green, oc1.blue,       fracy);
			pixel((int) dtmp + 1, i) = cc2.i;
			//printf(PIXEL_INFO_STRING, "1-2", (int) dtmp + 1, i, cc2.red, cc2.green, cc2.blue,
			//                                                      c.red,   c.green,   c.blue,       fracy,
			//                                                    oc2.red, oc2.green, oc2.blue, 1.0 - fracy);
		} else {
			pixel(i, (int) dtmp    ) = cc1.i;
			//printf(PIXEL_INFO_STRING, "2-1", i, (int) dtmp    , cc1.red, cc1.green, cc1.blue,
			//                                                      c.red,   c.green,   c.blue, 1.0 - fracy,
			//                                                    oc1.red, oc1.green, oc1.blue,       fracy);
			pixel(i, (int) dtmp + 1) = cc2.i;
			//plot(cc2, , );
			//printf(PIXEL_INFO_STRING, "2-2", i, (int) dtmp + 1, cc2.red, cc2.green, cc2.blue,
			//                                                      c.red,   c.green,   c.blue,       fracy,
			//                                                    oc2.red, oc2.green, oc2.blue, 1.0 - fracy);
		}
		intery += slope;
	}
}
//#endif

void plot(color c, int x, int y){
	pixel(x, y) = c.i;
}
