#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

#include "globals.h"
#include "line.h"
#include "screen.h"

//void color_scale(color *c, double s);
static inline unsigned int color_blend(color a, double as, color b, double bs);
/*static inline */void pixel_draw_aa(int x0, int y0, int x1, int y1, double w0, double w1, color c);

void line_draw(double tx0, double ty0, double tx1, double ty1, color c){
	double ix0, iy0, ix1, iy1;
	int x0, y0, x1, y1;
	if(!line_intersect(tx0, ty0,
	                   tx1, ty1,
	                   &ix0, &iy0,
	                   &ix1, &iy1)){
		return;
	}
	x0 = ix0;
	y0 = iy0;
	x1 = ix1;
	y1 = iy1;
	
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
			if(y >= 0 && y < screen_w && x >= 0 && x < screen_h){
				pixel(y, x) = c.i;
			}
		} else {
			if(x >= 0 && x < screen_w && y >= 0 && y < screen_h){
				pixel(x, y) = c.i;
			}
		}
		err -= dy;
		if(err < 0){
			y += yinc;
			err += dx;
		}
	}
}

void line_draw_aa(double tx0, double ty0, double tx1, double ty1, color c){
	double x0 = 0.0, y0 = 0.0, x1 = 0.0, y1 = 0.0;
	double dtmp;
	// Compute endpoints on the screen or return if line does not pass through screen.
	
	//debug_w("(tx0, ty0) = (%lf, %lf)", tx0, ty0);
	//debug_w("(tx1, ty1) = (%lf, %lf)", tx1, ty1);
	
	if(!line_intersect(tx0, ty0,
	                   tx1, ty1,
	                   &x0, &y0,
	                   &x1, &y1)){
		return;
	}
	
	//debug_w("1(x0, y0) = (%lf, %lf)", x0, y0);
	//debug_w("1(x1, y1) = (%lf, %lf)", x1, y1);
	
	int flip;
	double dx, dy, tmp;
	dx = x1 - x0;
	dy = y1 - y0;
	if((flip = (fabs(dy) > fabs(dx)))){
		//c.i = 0x00ff00ff;
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
	
	//debug_w("2(x0, y0) = (%lf, %lf)", x0, y0);
	//debug_w("2(x1, y1) = (%lf, %lf)", x1, y1);
	
	double slope, intery, fracy;
	double xend, yend0, yend1;
	double xgap0, xgap1;
	int xpxl0, ypxl0, xpxl1, ypxl1;
	
	/*if(dx == 0.0){
		error_n("dx = 0."); // This should be a problem, but apparently isn't. Oh well.
	}*/
	slope = dy / dx;
	xend = nearbyint(x0);
	yend0 = y0 + slope * (xend - x0);
	xgap0 = 1 - modf(x0 + 0.5, &dtmp);
	xpxl0 = xend;
	ypxl0 = floor(yend0);
	intery = yend0 + slope;
	
	xend = nearbyint(x1);
	yend1 = y1 + slope * (xend - x1);
	xgap1 = modf(x1 + 0.5, &dtmp);
	xpxl1 = xend;
	ypxl1 = floor(yend1);
		
	double sqrtpfy, sqrtmfy;
	if(flip){
		fracy = modf(yend0, &dtmp);
		sqrtpfy = sqrt((      fracy) * xgap0);
		sqrtmfy = sqrt((1.0 - fracy) * xgap0);
		if(ypxl0 == screen_w - 1){
			pixel_draw_aa(ypxl0, xpxl0, ypxl0, xpxl0, 1, 0, c);
		} else 
		if(ypxl0 == -1){
			pixel_draw_aa(0, xpxl0, 0, xpxl0, 1, 0, c);
		} else 
		if(ypxl0 < -1 || ypxl0 > screen_w - 1){
		} else {
			pixel_draw_aa(ypxl0, xpxl0, ypxl0 + 1, xpxl0, sqrtmfy, sqrtpfy, c);
		}
		
		fracy = modf(yend1, &dtmp);
		sqrtpfy = sqrt((      fracy) * xgap1);
		sqrtmfy = sqrt((1.0 - fracy) * xgap1);
		if(ypxl1 == screen_w - 1){
			pixel_draw_aa(ypxl1, xpxl1, ypxl1, xpxl1, 1, 0, c);
		} else 
		if(ypxl1 == -1){
			pixel_draw_aa(0, xpxl1, 0, xpxl1, 1, 0, c);
		} else 
		if(ypxl1 < -1 || ypxl1 > screen_w - 1){
		} else {
			pixel_draw_aa(ypxl1, xpxl1, ypxl1 + 1, xpxl1, sqrtmfy, sqrtpfy, c);
		}
	} else {
		fracy = modf(yend0, &dtmp);
		sqrtpfy = sqrt((      fracy) * xgap0);
		sqrtmfy = sqrt((1.0 - fracy) * xgap0);
		if(ypxl0 == screen_h - 1){
			pixel_draw_aa(xpxl0, ypxl0, xpxl0, ypxl0, 1, 0, c);
		} else 
		if(ypxl0 == -1){
			pixel_draw_aa(xpxl0, 0, xpxl0, 0, 1, 0, c);
		} else 
		if(ypxl0 < -1 || ypxl0 > screen_h - 1){
		} else {
			pixel_draw_aa(xpxl0, ypxl0, xpxl0, ypxl0 + 1, sqrtmfy, sqrtpfy, c);
		}
		
		fracy = modf(yend1, &dtmp);
		sqrtpfy = sqrt((      fracy) * xgap1);
		sqrtmfy = sqrt((1.0 - fracy) * xgap1);
		if(ypxl1 == screen_h - 1){
			pixel_draw_aa(xpxl1, ypxl1, xpxl1, ypxl1, 1, 0, c);
		} else 
		if(ypxl1 == -1){
			pixel_draw_aa(xpxl1, 0, xpxl1, 0, 1, 0, c);
		} else 
		if(ypxl1 < -1 || ypxl1 > screen_h - 1){
		} else {
			pixel_draw_aa(xpxl1, ypxl1, xpxl1, ypxl1 + 1, sqrtmfy, sqrtpfy, c);
		}
	}
	
	int i;
	for(i = xpxl0 + 1; i < xpxl1; i++){
		fracy = modf(intery, &dtmp);
		sqrtpfy = sqrt(      fracy);
		sqrtmfy = sqrt(1.0 - fracy);
		if(flip){
			pixel_draw_aa(dtmp, i   , dtmp + 1, i       , sqrtmfy, sqrtpfy, c);
		} else {
			pixel_draw_aa(i   , dtmp, i       , dtmp + 1, sqrtmfy, sqrtpfy, c);
		}
		intery += slope;
	}
}

/*static inline */void pixel_draw_aa(int x0, int y0, int x1, int y1, double w0, double w1, color c){
	pixel(x0, y0) = color_blend((color) pixel(x0, y0), 1 - w0, c, w0);
	pixel(x1, y1) = color_blend((color) pixel(x1, y1), 1 - w1, c, w1);
}

static inline unsigned int color_blend(color a, double as, color b, double bs){
	unsigned int t;
	//usleep(1);
	color c;
	t = (as * a.c.r) + (bs * b.c.r); // This line is like 15 instructions. Why? :(
		if(t > MAX_COLOR){ c.c.r = MAX_COLOR; } else { c.c.r = t; }
	t = (as * a.c.g) + (bs * b.c.g);
		if(t > MAX_COLOR){ c.c.g = MAX_COLOR; } else { c.c.g = t; }
	t = (as * a.c.b) + (bs * b.c.b);
		if(t > MAX_COLOR){ c.c.b = MAX_COLOR; } else { c.c.b = t; }
	return c.i;
}

int line_intersect(double tx0, double ty0,
                   double tx1, double ty1,
                   double *x0, double *y0,
                   double *x1, double *y1){
	/*if(tx0 == 334.12474855140255 &&
	   ty0 == 269.60797841404474 &&
	   tx1 == 334.12474855140249 &&
	   ty1 == 216.46370530821119){
		screen_w++;
		screen_w--;
	}*/
	// Handles vertical lines.
	double temp;
	if(tx0 == tx1){
		if(tx0 < 0 || tx0 > screen_w - 1){
			return 0;
		}
		*x0 = *x1 = tx0;
		if(ty0 < 0){
			if(ty1 < 0){
				return 0;
			}
			*y0 = 0;
		} else
		if(ty0 > screen_h - 1){
			if(ty1 > screen_h - 1){
				return 0;
			}
			*y0 = screen_h - 1;
		} else {
			*y0 = ty0;
		}
		if(ty1 < 0){
			*y1 = 0;
		} else
		if(ty1 > screen_h - 1){
			*y1 = screen_h - 1;
		} else {
			*y1 = ty1;
		}
		if(*y0 > *y1){
			temp = *y0;
			*y0 = *y1;
			*y1 = temp;
		}
	} else
	// Handles horizontal lines.
	if(ty0 == ty1){
		if(ty0 < 0 || ty0 > screen_h - 1){
			return 0;
		}
		*y0 = *y1 = ty0;
		if(tx0 < 0){
			if(tx1 < 0){
				return 0;
			}
			*x0 = 0;
		} else
		if(tx0 > screen_w - 1){
			if(tx1 > screen_w - 1){
				return 0;
			}
			*x0 = screen_w - 1;
		} else {
			*x0 = tx0;
		}
		if(tx1 < 0){
			*x1 = 0;
		} else
		if(tx1 > screen_w - 1){
			*x1 = screen_w - 1;
		} else {
			*x1 = tx1;
		}
		if(*x0 > *x1){
			temp = *x0;
			*x0 = *x1;
			*x1 = temp;
		}
	} else {
		int flip;
		int tscreen_w, tscreen_h;
		double m, b;
		double xints[6]; // left, right, p1, p2, bottom, top,
		//double yints[6];
		int inttype[6]; // 1:=horizontal, 2:=vertical, 3:=endpoint
		
		m = (tx1 - tx0) / (ty1 - ty0);
		if(m < 1 && m > -1){
			flip = 1;
			temp = tx0;
			tx0  = ty0;
			ty0  = temp;
			temp = tx1;
			tx1  = ty1;
			ty1  = temp;
			m = 1 / m;
			tscreen_h = screen_w;
			tscreen_w = screen_h;
		} else {
			flip = 0;
			tscreen_h = screen_h;
			tscreen_w = screen_w;
		}
		b = tx0 - m * ty0;
		//yints[4] = tscreen_h - 1;
		xints[4] = m * (tscreen_h - 1.0) + b;
		inttype[4] = 1;
		//yints[5] = 0;
		xints[5] = b;
		inttype[5] = 1;
		
		m = (ty1 - ty0) / (tx1 - tx0);
		b = ty0 - m * tx0;
		
		xints[0] = 0;
		//yints[0] = b;
		inttype[0] = 2;
		xints[1] = tscreen_w - 1;
		//yints[1] = m * (tscreen_w - 1) + b;
		inttype[1] = 2;
		
		xints[2] = tx0;
		//yints[2] = ty0;
		inttype[2] = 3;
		xints[3] = tx1;
		//yints[3] = tx2;
		inttype[3] = 3;
		
		// sort 'em.
		
		int i, j, n, t;
		double low;
		for(i = 0; i < 5; i++){
			low = xints[i];
			n = i;
			for(j = i + 1; j < 6; j++){
				if(xints[j] < low){
					low = xints[j];
					n = j;
				}
			}
			xints[n] = xints[i];
			xints[i] = low;
			t = inttype[n];
			inttype[n] = inttype[i];
			inttype[i] = t;
		}
		
		// Does this line pass through the screen?
		
		switch(inttype[0]){
			case 1:
				switch(inttype[1]){
					case 1:
						return 0;
						break;
					case 2:
						switch(inttype[2]){
							case 3:
								break;
							default:
								return 0;
								break;
						}
						break;
					case 3:
						switch(inttype[2]){
							case 2:
								break;
							default:
								return 0;
								break;
						}
						break;
				}
				break;
			case 2:
				switch(inttype[1]){
					case 1:
						switch(inttype[2]){
							case 3:
								break;
							default:
								return 0;
								break;
						}
						break;
					case 2:
						return 0;
						break;
					case 3:
						switch(inttype[2]){
							case 1:
								break;
							default:
								return 0;
								break;
						}
						break;
				}
				break;
			case 3:
				switch(inttype[1]){
					case 1:
						switch(inttype[2]){
							case 2:
								break;
							default:
								return 0;
								break;
						}
						break;
					case 2:
						switch(inttype[2]){
							case 1:
								break;
							default:
								return 0;
								break;
						}
						break;
					case 3:
						return 0;
						break;
				}
				break;
		}
		*x0 = xints[2];
		*x1 = xints[3];
		*y0 = m * *x0 + b;
		*y1 = m * *x1 + b;
		
		/*if(*y0 >= tscreen_h){
			raise(SIGABRT);
		}
		if(*y0 <= -1      ){
			raise(SIGABRT);
		}
		if(*y1 >= tscreen_h){
			raise(SIGABRT);
		}
		if(*y1 <= -1      ){
			raise(SIGABRT);
		}
		if(*x0 >= tscreen_w){
			raise(SIGABRT);
		}
		if(*x0 <= -1      ){
			raise(SIGABRT);
		}
		if(*x1 >= tscreen_w){
			raise(SIGABRT);
		}
		if(*x1 <= -1      ){
			raise(SIGABRT);
		}*/
		
		if(*y0 > tscreen_h - 1){
			*y0 = tscreen_h - 1;
		}
		if(*y0 < 0){
			*y0 = 0;
		}
		if(*y1 > tscreen_h - 1){
			*y1 = tscreen_h - 1;
		}
		if(*y1 < 0){
			*y1 = 0;
		}
		if(*x0 > tscreen_w - 1){
			*x0 = tscreen_w - 1;
		}
		if(*x0 < 0){
			*x0 = 0;
		}
		if(*x1 > tscreen_w - 1){
			*x1 = tscreen_w - 1;
		}
		if(*x1 < 0){
			*x1 = 0;
		}
		
		if(*y0 > tscreen_h - 1 ||
		   *y0 < 0            ||
		   *y1 > tscreen_h - 1 ||
		   *y1 < 0            ||
		   *x0 > tscreen_w - 1 ||
		   *x0 < 0            ||
		   *x1 > tscreen_w - 1 ||
		   *x1 < 0            ){
			raise(SIGABRT);
		}
		
		if(flip){
			temp = *x0;
			*x0  = *y0;
			*y0  = temp;
			temp = *x1;
			*x1  = *y1;
			*y1  = temp;
		}
	}
	return 1;
}
