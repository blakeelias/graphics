#include <stdio.h>

#include "globals.h"
#include "surface.h"
#include "line.h"
#include "matrix.h"


void surface_draw(matrix *m, int offset, color c){
	double **p = m->m;
	double px[6];
	double py[6];
	int lineonscreen[3];
	int i;
	for(i = 0; i < 3; i++){
		//error_w("p[%d] - p[%d]", pindex[i % 3], pindex[(i + 1) % 3]);
		lineonscreen[i] = line_intersect(
			p[offset + ( i      % 3)][0],
			p[offset + ( i      % 3)][1],
			p[offset + ((i + 1) % 3)][0],
			p[offset + ((i + 1) % 3)][1],
			px + 2 * i    ,
			py + 2 * i    ,
			px + 2 * i + 1,
			py + 2 * i + 1);
	}
	//error_w("Face:\n\t(%lf, %lf)-(%lf, %lf),\n\t(%lf, %lf)-(%lf, %lf),\n\t(%lf, %lf)-(%lf, %lf).", px[0], py[0], px[1], py[1], px[2], py[2], px[3], py[3], px[4], py[4], px[5], py[5]);
	for(i = 0; i < 3; i++){
		if(lineonscreen[i]){
			line_draw_aa(px[2 * i    ],
			             py[2 * i    ],
			             px[2 * i + 1],
			             py[2 * i + 1],
			             c);
			pixel((int) px[2 * i    ], (int) py[2 * i    ]) = 0x00ffffff;
			pixel((int) px[2 * i + 1], (int) py[2 * i + 1]) = 0x00ffffff;
		}
	}
}
