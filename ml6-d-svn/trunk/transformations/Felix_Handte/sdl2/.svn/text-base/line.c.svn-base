#include "globals.h"
#include "line.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void line_draw(int x0, int y0, int x1, int y1, color c, int start){
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
			pixel(y, x) = c.i;
		} else {
			pixel(x, y) = c.i;
		}
		err -= dy;
		if(err < 0){
			y += yinc;
			err += dx;
		}
	}
}

void line_draw_aa(int x0, int y0, int x1, int y1, color c, int start){
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
		if(start){
			pixel(y0, x0) = c.i;
		}
		pixel(y1, x1) = c.i;
	} else {
		if(start){
			pixel(x0, y0) = c.i;
		}
		pixel(x1, y1) = c.i;
	}
	double sqrtpfy, sqrtmfy;
	int i;
	for(i = x0 + 1; i < x1; i++){
		fracy = modf(intery, &dtmp);
		if(flip){
			oc1.i = pixel((int) dtmp    , i);
			oc2.i = pixel((int) dtmp + 1, i);
		} else {
			oc1.i = pixel(i, (int) dtmp);
			oc2.i = pixel(i, (int) dtmp + 1);
		}
		sqrtpfy = sqrt(      fracy);
		sqrtmfy = sqrt(1.0 - fracy);
		ctmp = (sqrtmfy * c.c.r) + (sqrtpfy * oc1.c.r); if(ctmp > MAX_COLOR){ cc1.c.r = MAX_COLOR; } else { cc1.c.r = ctmp; }
		ctmp = (sqrtmfy * c.c.g) + (sqrtpfy * oc1.c.g); if(ctmp > MAX_COLOR){ cc1.c.g = MAX_COLOR; } else { cc1.c.g = ctmp; }
		ctmp = (sqrtmfy * c.c.b) + (sqrtpfy * oc1.c.b); if(ctmp > MAX_COLOR){ cc1.c.b = MAX_COLOR; } else { cc1.c.b = ctmp; }
		ctmp = (sqrtpfy * c.c.r) + (sqrtmfy * oc1.c.r); if(ctmp > MAX_COLOR){ cc2.c.r = MAX_COLOR; } else { cc2.c.r = ctmp; }
		ctmp = (sqrtpfy * c.c.g) + (sqrtmfy * oc1.c.g); if(ctmp > MAX_COLOR){ cc2.c.g = MAX_COLOR; } else { cc2.c.g = ctmp; }
		ctmp = (sqrtpfy * c.c.b) + (sqrtmfy * oc1.c.b); if(ctmp > MAX_COLOR){ cc2.c.b = MAX_COLOR; } else { cc2.c.b = ctmp; }
		if(flip){
			pixel((int) dtmp    , i) = cc1.i;
			pixel((int) dtmp + 1, i) = cc2.i;
		} else {
			pixel(i, (int) dtmp    ) = cc1.i;
			pixel(i, (int) dtmp + 1) = cc2.i;
		}
		intery += slope;
	}
}
