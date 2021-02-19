#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "matrix_stack.h"
#include "display.h"
#include "draw.h"
#include "shapes.h"
#include "light_shade.h"


/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, int x, int y, int z) {

  if ( points->lastcol == points->cols )
    grow_matrix(points, points->cols + 100);

  struct matrix* point = new_matrix(4, 1);

  point->m[0][0] = x;
  point->m[1][0] = y;
  point->m[2][0] = z;
  point->m[3][0] = 1;

  matrix_mult(matrix_stack.last->m, point);

  points->m[0][points->lastcol] = point->m[0][0];
  points->m[1][points->lastcol] = point->m[1][0];
  points->m[2][points->lastcol] = point->m[2][0];
  points->m[3][points->lastcol] = point->m[3][0];

      
  points->lastcol++;
}


/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {

  int i;
  if ( points->lastcol < 2 ) {
    printf("Need at least 2 points to draw a line!\n");
    return;
  }

  for (i=0; i < points->lastcol - 1; i+=2) 
    draw_line(points->m[0][i], points->m[1][i], points->m[2][i],
	      points->m[0][i+1], points->m[1][i+1], points->m[2][i+1], s, c);
    
    
}

void draw_polygons(struct matrix *points, screen s, color c[NUM_COLORS]) {
  int i;
  double p[3][3];
  double camera_location[3];
  camera_location[0] = 150;
  camera_location[1] = 150;
  camera_location[2] = 300;

  if (points->lastcol < 3) {
    printf("Need at least 3 points to draw polygons\n");
    return;
  }
  for (i = 0; i < points->lastcol - 2; i+= 3) {
    if (front_face(points->m[0][i],   points->m[1][i],   points->m[2][i],
		   points->m[0][i+1], points->m[1][i+1], points->m[2][i+1],
		   points->m[0][i+2], points->m[1][i+2], points->m[2][i+2],
		   camera_location)) {

      p[0][0] = points->m[0][i];
      p[0][1] = points->m[1][i];
      p[0][2] = points->m[2][i];
      p[1][0] = points->m[0][i+1];
      p[1][1] = points->m[1][i+1];
      p[1][2] = points->m[2][i+1];
      p[2][0] = points->m[0][i+2];
      p[2][1] = points->m[1][i+2];
      p[2][2] = points->m[2][i+2];

      double centerx = (p[0][0]+p[1][0]+p[2][0])/3;
      double centery = (p[0][1]+p[1][1]+p[2][1])/3;
      double centerz = (p[0][2]+p[1][2]+p[2][2])/3;

      double *normal[3];
      normal[0] = surface_normal(p[0][0], p[0][1], p[0][2],
				 p[1][0], p[1][1], p[1][2],
				 p[2][0], p[2][1], p[2][2]);
      normalize(normal[0], 50);
      double normx = centerx + normal[0][0];
      double normy = centery + normal[0][1];
      double normz = centerz + normal[0][2];


      double lum = get_luminosity(p, 80, 240, 250, 1.0, camera_location);
      printf("get_luminosity returned %lf\n", lum);
      color shade = c[(i/3)%NUM_COLORS];
      illuminate_color(&shade, lum);

      /*shade.blue = c[(i/3)%NUM_COLORS].blue*lum;
      shade.red = c[(i/3)%NUM_COLORS].red*lum;
      shade.green = c[(i/3)%NUM_COLORS].green*lum;*/
      

      // draw polygon
      draw_line(points->m[0][i],   points->m[1][i],   points->m[2][i],
		points->m[0][i+1], points->m[1][i+1], points->m[2][i+1], s, shade);
      draw_line(points->m[0][i+1], points->m[1][i+1], points->m[2][i+1],
		points->m[0][i+2], points->m[1][i+2], points->m[2][i+2], s, shade);
      draw_line(points->m[0][i+2], points->m[1][i+2], points->m[2][i+2],
		points->m[0][i],   points->m[1][i],   points->m[2][i], s, shade);
      
      shade_polygon(p, s, shade);

      shade.red = 255 - shade.red;
      shade.green = 255 - shade.green;
      shade.blue = 255 - shade.blue;

      // draw surface normal
      //draw_line(centerx, centery, centerz,
      //		normx, normy, normz, s, shade);

      // draw vertex normals
      /*int j = 0;
      for (j = 0; j < 3; j++) {
      	normal[0] = vertex_normal(points, points->m[0][i+j],   points->m[1][i+j],   points->m[2][i+j]);
     	normx = points->m[0][i+j] + normal[0][0];
	normy = points->m[1][i+j] + normal[0][1];
	normz = points->m[2][i+j] + normal[0][2];
	printf("Vertex normal line: %lf, %lf, %lf\nvertex normal vector: %lf, %lf, %lf\n",
	       normx, normy, normz, normal[0][0], normal[0][1], normal[0][2]);
	//free(normal);
		draw_line(points->m[0][i+j],   points->m[1][i+j],   points->m[2][i+j],
			  //points->m[0][i+j],   points->m[1][i+j],   points->m[2][i+j],
			  normx, normy, normz,
			  s, shade);
			  }*/

      printf("\npolygon %d:\n%lf %lf %lf\n%lf %lf %lf\n%lf %lf %lf\n",
	   i/3,
	   points->m[0][i], points->m[1][i], points->m[2][i],
	   points->m[0][i+1], points->m[1][i+1], points->m[2][i+1],
	   points->m[0][i+2], points->m[1][i+2], points->m[2][i+2]);
    }
    else {
      printf("not drawing: polygon %d\n", i/3);
    }
  }
}

void add_polygon(struct matrix *points,
		 int x0, int y0, int z0,
		 int x1, int y1, int z1,
		 int x2, int y2, int z2) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
  add_point(points, x2, y2, z2);
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should call add_point
====================*/
void add_edge( struct matrix * points, 
	       int x0, int y0, int z0, 
	       int x1, int y1, int z1) {

  add_point( points, x0, y0, z0);
  add_point( points, x1, y1, z1);
}


//Insert your line algorithm here
void draw_line(int x0, int y0, double z0,
	       //double nx0, double ny0, double nz0,
	       int x1, int y1, double z1,
	       //double nx1, double ny1, double nz1,
	       screen s, color c) {
  int octant = 1;
  
  if (x0 > x1) {
    octant = x1;
    x1 = x0;
    x0 = octant;
    octant = y1;
    y1 = y0;
    y0 = octant;
    octant = 1;
  }

  // slope >= 1, octant 2: reflect x and y, then reverse again when plotting
  if (y1-y0 >= x1-x0) {
    octant = x1;
    x1 = y1;
    y1 = octant;
    octant = x0;
    x0 = y0;
    y0 = octant;
    octant = 2;
  }

  // -1 < slope < 0, octant 8: negate y coordinates, reflect again when plotting
  else if (y1-y0 <= 0 && y1-y0 >= x0-x1) {
    y0 *= -1;
    y1 *= -1;
    octant = 8;
  }

  // slope < -1, octant 7: negate y coordinate then reflect x and y, undo when plotting
  else if (y1-y0 < x0-x1) {
    y0 *= -1;
    y1 *= -1;
    octant = x1;
    x1 = y1;
    y1 = octant;
    octant = x0;
    x0 = y0;
    y0 = octant;
    octant = 7;
  }

  int dy = y1-y0;
  int dx = x1-x0;
  double dz_dx = (z1-z0)/(x1-x0);
  int d = 2*dy - dx;

  /*double dnx_dx = (nx1-nx0)/(x1-x0);
  double dny_dx = (ny1-ny0)/(x1-x0);
  double dnz_dx = (nz1-nz0)/(x1-x0);*/
  color shade;

  for (; x0 <= x1; x0++) {
    
    if (octant == 2)
      plot(s, c, y0, x0, z0);
    else if (octant == 1)
      plot(s, c, x0, y0, z0);
    else if (octant == 8)
      plot(s, c, x0, -y0, z0);
    else if (octant == 7)
      plot(s, c, y0, -x0, z0);
    if (d >= 0) {
      y0++;
      d -= dx;
    }
    d += dy;
    z0 += dz_dx;
  }
}
