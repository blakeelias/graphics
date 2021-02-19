#include "line.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
//#define ANTIALIAS

//Insert your line algorithm here
//#ifndef ANTIALIAS
void draw_line(int x0, int y0, int x1, int y1, unsigned int color) {
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
			//plot(s, c, y, x);
		} else {
			//plot(s, c, x, y);
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
void draw_line_aa(int x0, int y0, int x1, int y1, unsigned int color) {
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
	double slope, dtmp, intery, fracy;
	slope = (double) dy / dx;
	intery = y0 + slope;
	if(flip){
		//plot(s, c, y0, x0);
		//plot(s, c, y1, x1);
	} else {
		//plot(s, c, x0, y0);
		//plot(s, c, x1, y1);
	}
	double sqrtpfy, sqrtmfy;
	int i;
	for(i = x0 + 1; i < x1; i++){
		fracy = modf(intery, &dtmp);
		if(flip){
			oc1 = s[(int) dtmp    ][YRES - 1 - i];
			oc2 = s[(int) dtmp + 1][YRES - 1 - i];
		} else {
			oc1 = s[i][YRES - 1 - (int) dtmp];
			oc2 = s[i][YRES - 2 - (int) dtmp];
		}
		sqrtpfy = sqrt(      fracy);
		sqrtmfy = sqrt(1.0 - fracy);
		cc1.red   = (sqrtmfy * c.red  ) + (sqrtpfy * oc1.red  );
		cc1.green = (sqrtmfy * c.green) + (sqrtpfy * oc1.green);
		cc1.blue  = (sqrtmfy * c.blue ) + (sqrtpfy * oc1.blue );
		cc2.red   = (sqrtpfy * c.red  ) + (sqrtmfy * oc2.red  );
		cc2.green = (sqrtpfy * c.green) + (sqrtmfy * oc2.green);
		cc2.blue  = (sqrtpfy * c.blue ) + (sqrtmfy * oc2.blue );
		if(cc1.red   > MAX_COLOR){ cc1.red   = MAX_COLOR; }
		if(cc1.green > MAX_COLOR){ cc1.green = MAX_COLOR; }
		if(cc1.blue  > MAX_COLOR){ cc1.blue  = MAX_COLOR; }
		if(cc2.red   > MAX_COLOR){ cc2.red   = MAX_COLOR; }
		if(cc2.green > MAX_COLOR){ cc2.green = MAX_COLOR; }
		if(cc2.blue  > MAX_COLOR){ cc2.blue  = MAX_COLOR; }
		if(flip){
			//plot(s, cc1, (int) dtmp, i);
			//printf(PIXEL_INFO_STRING, "1-1", (int) dtmp    , i, cc1.red, cc1.green, cc1.blue,
			//                                                      c.red,   c.green,   c.blue, 1.0 - fracy,
			//                                                    oc1.red, oc1.green, oc1.blue,       fracy);
			//plot(s, cc2, (int) dtmp + 1, i);
			//printf(PIXEL_INFO_STRING, "1-2", (int) dtmp + 1, i, cc2.red, cc2.green, cc2.blue,
			//                                                      c.red,   c.green,   c.blue,       fracy,
			//                                                    oc2.red, oc2.green, oc2.blue, 1.0 - fracy);
		} else {
			//plot(s, cc1, i, (int) dtmp);
			//printf(PIXEL_INFO_STRING, "2-1", i, (int) dtmp    , cc1.red, cc1.green, cc1.blue,
			//                                                      c.red,   c.green,   c.blue, 1.0 - fracy,
			//                                                    oc1.red, oc1.green, oc1.blue,       fracy);
			//plot(s, cc2, i, (int) dtmp + 1);
			//printf(PIXEL_INFO_STRING, "2-2", i, (int) dtmp + 1, cc2.red, cc2.green, cc2.blue,
			//                                                      c.red,   c.green,   c.blue,       fracy,
			//                                                    oc2.red, oc2.green, oc2.blue, 1.0 - fracy);
		}
		intery += slope;
	}
}
//#endif
*/
