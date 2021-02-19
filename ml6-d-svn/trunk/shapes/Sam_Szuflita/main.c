#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include <sys/stat.h>

void parse_file ( char * filename, 
				 struct matrix * transform, 
				 struct matrix * pm,
				 screen s);

int main() {
	//printf("ahoy matey\n");
	umask(000);
	
	struct matrix *m;
	struct matrix *points;
	screen s;
	
	int r, c;
	r = 4;
	c = 4;
	
	m = new_matrix(4, 4);
	points = new_matrix(4, 4);
	
	ident(m);
	
	int i = 0;
	while (i < points->cols){
		points->m[3][i] = 1;
		i++;
	}
	
	
	parse_file("script.txt", m, points, s);
	
	//The following tests various matrix functions
	/*
	 m = new_matrix(r, c);
	 a = new_matrix(r, c);  
	 
	 for (r=0; r < m->rows; r++)
	 for (c=0; c < m->cols; c++)
	 m->m[r][c] = 5;
	 
	 print_matrix(m);
	 printf("\n");
	 
	 ident(m);
	 print_matrix(m);
	 printf("\n");
	 
	 scalar_mult(7, m);
	 print_matrix(m);
	 printf("\n");
	 
	 copy_matrix(m, a);
	 print_matrix(a);
	 printf("\n");
	 
	 ident(m);
	 
	 matrix_mult(a, m);
	 print_matrix(a);
	 printf("\n");*/
	
	
	//free_matrix(a);
	//free_matrix(m);
	
	return 0;
}

void parse_file ( char * filename, 
				 struct matrix * transform, 
				 struct matrix * pm,
				 screen s) {
	
	FILE *fd;
	
	if (!(fd = fopen(filename, "r")))
		printf("Y U NO OPEN!\n");
	
	char buff[100];
	double doubles[6];
	
	struct matrix * helper;
	
	color c;
	c.red = 255;
	c.green = 255;
	c.blue = 0;
	
	while (fgets(buff, 100, fd)){
		
		if (! (strcmp(buff, "l\n"))){
			fscanf(fd, "%lf %lf %lf %lf %lf %lf", doubles, doubles+1, doubles+2, doubles+3, doubles+4, doubles+5);
			//printf("Adding line: %lf %lf %lf %lf %lf %lf\n", doubles[0], doubles[1], doubles[2], doubles[3], doubles[4], doubles[5]);
			add_edge(pm, doubles[0], doubles[1], doubles[2], doubles[3], doubles[4], doubles[5]);
			//print_matrix(pm);
		}
		
		if (! (strcmp(buff, "i\n"))){
			printf("Identing transform\n");
			ident(transform);
			//print_matrix(transform);
		}
		
		if (! (strcmp(buff, "s\n"))){
			fscanf(fd, "%lf %lf %lf", doubles, doubles+1, doubles+2);
			printf("Scaling by: %lf %lf %lf\n", doubles[0], doubles[1], doubles[2]);
			matrix_mult(make_scale(doubles[0], doubles[1], doubles[2]), transform);
			//print_matrix(transform);
		}
		
		if (! (strcmp(buff, "t\n"))){
			fscanf(fd, "%lf %lf %lf", doubles, doubles+1, doubles+2);
			printf("Translating by: %lf %lf %lf\n", doubles[0], doubles[1], doubles[2]);
			matrix_mult(make_translate(doubles[0], doubles[1], doubles[2]), transform);
			//print_matrix(transform);
		}
		
		if (! (strcmp(buff, "x\n"))){
			fscanf(fd, "%lf", doubles);
			printf("Rotating about x by: %lf\n", doubles[0]);
			matrix_mult(make_rotX(doubles[0]), transform);
			//print_matrix(transform);
		}
		
		if (! (strcmp(buff, "y\n"))){
			fscanf(fd, "%lf", doubles);
			printf("Rotating about y by: %lf\n", doubles[0]);
			matrix_mult(make_rotY(doubles[0]), transform);
			//print_matrix(transform);
		}
		
		if (! (strcmp(buff, "z\n"))){
			fscanf(fd, "%lf", doubles);
			printf("Rotating about z by: %lf\n", doubles[0]);
			matrix_mult(make_rotZ(doubles[0]), transform);
			//print_matrix(transform);
		}
		
		if (! (strcmp(buff, "m\n"))){
			fscanf(fd, "%lf %lf %lf", doubles, doubles+1, doubles+2);
			printf("Drawing a sphere at %lf %lf of radius %lf\n", doubles[1], doubles[2], doubles[0]);
			helper = render_sphere(doubles[0], doubles[1], doubles[2]);
			generate_sphere(pm, helper);
		}
		
		if (! (strcmp(buff, "c\n"))){
			fscanf(fd, "%lf %lf %lf %lf", doubles, doubles+1, doubles+2, doubles+3);
			printf("Making a circle of radius %lf at %lf %lf with step size %lf\n", doubles[0], doubles[1], doubles[2], doubles[3]);
			helper = render_circle(doubles[0], doubles[1], doubles[2], doubles[3]);
			generate_circle(pm, helper);
		}
		
		if (! (strcmp(buff, "d\n"))){
			fscanf(fd, "%lf %lf %lf %lf", doubles, doubles+1, doubles+2, doubles+3);
			printf("Making a torus of Radius %lf with radius %lf at %lf %lf", doubles[0], doubles[1], doubles[2], doubles[3]);
			helper = render_torus(doubles[0], doubles[1], doubles[2], doubles[3]);
			generate_torus(pm, helper);
		}
		
		if (! (strcmp(buff, "h\n"))){
			fscanf(fd, "%lf %lf %lf %lf %lf %lf %lf %lf", doubles, doubles+1, doubles+2, doubles+3, doubles+4, doubles+5, doubles+6, doubles+7);
			printf("Drawing a Hermite curve from %lf %lf to %lf %lf\n", doubles[0], doubles[1], doubles[4], doubles[5]);
			generate_hermite(pm, doubles[0], doubles[1], doubles[2], doubles[3], doubles[4], doubles[5], doubles[6], doubles[7]);
			//render_hermite(pm, helper);
		}
		
		if (! (strcmp(buff, "b\n"))){
			fscanf(fd, "%lf %lf %lf %lf %lf %lf %lf %lf", doubles, doubles+1, doubles+2, doubles+3, doubles+4, doubles+5, doubles+6, doubles+7);
			printf("Drawing a Bezier curve from %lf %lf to %lf %lf\n", doubles[0], doubles[1], doubles[4], doubles[5]);
			generate_bezier(pm, doubles[0], doubles[1], doubles[2], doubles[3], doubles[4], doubles[5], doubles[6], doubles[7]);
			//render_hermite(pm, helper);
		}
		
		if (! (strcmp(buff, "v\n"))){
			draw_lines(pm, s, c);
			display(s);
			clear_screen(s);
		}

		if (! (strcmp(buff, "a\n"))){
			matrix_mult(transform, pm);
			//print_matrix(transform);
		}
		
		if (! (strcmp(buff, "g\n"))){
			fscanf(fd, "%s", buff);
			save_ppm(s, buff);
		}
		
	}
}









