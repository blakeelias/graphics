#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
	
	int i, j, temp;
	
	//Make x0 < x1
	
	if (x0 > x1){
		temp = x0;
		x0 = x1;
		x1 = temp;
		
		temp = y0;
		y0 = y1;
		y1 = temp;
	}
	
	//Handle horizontal lines
	if (y0 == y1){
		i = 0;
		while (x0 + i < x1){
			plot(s, c, x0 + i, y0);
			i++;
		}
		return;
	}
	
	//Handle vertical lines
	if (x0 == x1){
		i = 0;
		while (y0 + i < y1){
			plot(s, c, x0, y0 + i);
			i++;
		}
		return;
	}
	
	
	
	//Prepare f(x,y)
	int d = 0;
	int dx = x1 - x0;
	int dy = y1 - y0;
	
	//Handle slope of 1
	if (dx == dy){
		i = 0;
		while (x0 + i < x1){
			plot(s, c, x0 + i, y0 + i);
			i++;
		}
		return;
	}
	
	
	//Handle slope of -1
	if (dx == -dy){
		i = 0;
		while (x0 + i < x1){
			plot(s, c, x0 + i, y0 - i);
			i++;
		}
		return;
	}
	
	
	//Handle positive slopes less than 1
	if (dx > dy && dy > 0){
		i = 0;
		j = 0;
		while (x0 + i < x1){
			plot (s, c, x0 + i, y0 + j);
			if (d < 0){
				i++;
				d = d + dy;
			}
			else {
				i++;
				j++;
				d = d + dy - dx;
			}
		}
		return;
	}
	
	//Handle positive slopes greater than 1
	if (dy > dx){
		i = 0;
		j = 0;
		while (y0 + j < y1){
			plot (s, c, x0 + i, y0 + j);
			if (d < 0){
				j++;
				d = d + dx;
			}
			else {
				i++;
				j++;
				d = d + dx - dy;
			}
		}
		return;
	}
	
	//Handle negative slopes greater than -1
	if (dx > -dy && dy < 0){
		i = 0;
		j = 0;
		while (x0 + i < x1){
			plot (s, c, x0 + i, y0 - j);
			if (d < 0){
				i++;
				d = d - dy;
			}
			else {
				i++;
				j++;
				d = d - dy - dx;
			}
		}
		return;
	}
	
	//Handle negative slopes greater than -1
	if (dx < -dy && dy < 0){
		i = 0;
		j = 0;
		while (y1 + j < y0){
			plot (s, c, x1 - i, y1 + j);
			if (d < 0){
				j++;
				d = d + dx;
			}
			else {
				i++;
				j++;
				d = d + dx + dy;
			}
		}
		return;
	}

printf("");
}

