#include <math.h>
#include <stdio.h>

#include "ml6.h"
#include "matrix.h"
#include "matrix_stack.h"
#include "display.h"
#include "draw.h"
#include "shapes.h"

void draw_sphere(struct matrix *points,
		 double x, double y, double z, double r) {
  double phi, theta, step;
  int nsteps = 32;
  double xcor, ycor, zcor;

  struct matrix *sphere_points = new_matrix(4, 2);

  step = 2 * M_PI / nsteps;
  for (phi = 0; phi <= 2 * M_PI + step; phi += step) {
    for (theta = 0; theta < 2 * M_PI + step; theta += step) {
      xcor = r * cos(theta) * cos(phi) + x;
      ycor = r * sin(theta) + y;
      zcor = -r * cos(theta) * sin(phi) + z;
      add_point(sphere_points, xcor, ycor, zcor);
    }
  }
  
  connect_dots_sphere(sphere_points, points, nsteps+1, nsteps);
}

void connect_dots_sphere(struct matrix *sphere_points, struct matrix *points, int nsteps_lat, int nsteps_lon) {
  int lon, lat;
  
  for (lat = 0; lat < nsteps_lat; lat++) {
      for (lon = 0; lon < nsteps_lon; lon++) {
	add_polygon(points,
		    sphere_points->m[0][lon*nsteps_lat+lat],
		    sphere_points->m[1][lon*nsteps_lat+lat],
		    sphere_points->m[2][lon*nsteps_lat+lat],

		    sphere_points->m[0][lon*nsteps_lat+lat+1],
		    sphere_points->m[1][lon*nsteps_lat+lat+1],
		    sphere_points->m[2][lon*nsteps_lat+lat+1],

		    sphere_points->m[0][(lon+1)*nsteps_lat+lat],
		    sphere_points->m[1][(lon+1)*nsteps_lat+lat],
		    sphere_points->m[2][(lon+1)*nsteps_lat+lat]);

	add_polygon(points,
		    sphere_points->m[0][(lon+1)*nsteps_lat+lat],
		    sphere_points->m[1][(lon+1)*nsteps_lat+lat],
		    sphere_points->m[2][(lon+1)*nsteps_lat+lat],
		    
		    sphere_points->m[0][lon*nsteps_lat+lat+1],
		    sphere_points->m[1][lon*nsteps_lat+lat+1],
		    sphere_points->m[2][lon*nsteps_lat+lat+1],


		    sphere_points->m[0][(lon+1)*nsteps_lat+lat+1],
		    sphere_points->m[1][(lon+1)*nsteps_lat+lat+1],
		    sphere_points->m[2][(lon+1)*nsteps_lat+lat+1]);
      }
    }
}

void draw_torus(struct matrix *points,
		double x, double y, double z, double R, double r) {
  double phi, theta, step;
  int nsteps = 16;
  double xcor, ycor, zcor;

  struct matrix *torus_points = new_matrix(4, 2);

  step = 2 * M_PI / nsteps;
  for (phi = 0; phi <= 2 * M_PI + step; phi += step) {
    for (theta = 0; theta < 2 * M_PI + step; theta += step) {
      xcor = r * cos(theta) * cos(phi) + R * cos(phi) + x;
      ycor = r * sin(theta) + y;
      zcor = -r * cos(theta) * sin(phi) - R * sin(phi) + z;
      add_point(torus_points, xcor, ycor, zcor);
    }
  }
  
  connect_dots_torus(torus_points, points, nsteps+1, nsteps);
}

void connect_dots_torus(struct matrix *sphere_points, struct matrix *points, int nsteps_lat, int nsteps_lon) {
  int lon, lat;
  
  for (lat = 0; lat < nsteps_lat; lat++) {
      for (lon = 0; lon < nsteps_lon; lon++) {
	add_polygon(points,
		    sphere_points->m[0][lon*nsteps_lat+lat],
		    sphere_points->m[1][lon*nsteps_lat+lat],
		    sphere_points->m[2][lon*nsteps_lat+lat],

		    sphere_points->m[0][lon*nsteps_lat+lat+1],
		    sphere_points->m[1][lon*nsteps_lat+lat+1],
		    sphere_points->m[2][lon*nsteps_lat+lat+1],

		    sphere_points->m[0][(lon+1)*nsteps_lat+lat],
		    sphere_points->m[1][(lon+1)*nsteps_lat+lat],
		    sphere_points->m[2][(lon+1)*nsteps_lat+lat]);

	add_polygon(points,
		    sphere_points->m[0][(lon+1)*nsteps_lat+lat],
		    sphere_points->m[1][(lon+1)*nsteps_lat+lat],
		    sphere_points->m[2][(lon+1)*nsteps_lat+lat],
		    
		    sphere_points->m[0][lon*nsteps_lat+lat+1],
		    sphere_points->m[1][lon*nsteps_lat+lat+1],
		    sphere_points->m[2][lon*nsteps_lat+lat+1],


		    sphere_points->m[0][(lon+1)*nsteps_lat+lat+1],
		    sphere_points->m[1][(lon+1)*nsteps_lat+lat+1],
		    sphere_points->m[2][(lon+1)*nsteps_lat+lat+1]);
      }
    }
}


void draw_box(struct matrix *points, double x1, double y1, double z1, double x2, double y2, double z2) {
  x2 += x1; // the second set of coordinates is a depth, not a point
  y2 += y1; // add the coordinates to generate point #2
  z2 += z1;

  add_polygon(points, x1,y1,z1, x1,y2,z1, x2,y2,z1); // AHF
  add_polygon(points, x1,y1,z1, x2,y2,z1, x2,y1,z1); // AFB
  add_polygon(points, x1,y1,z1, x2,y1,z1, x1,y1,z2); // ABC
  add_polygon(points, x2,y1,z1, x2,y1,z2, x1,y1,z2); // BCD
  add_polygon(points, x2,y1,z1, x2,y2,z1, x2,y2,z2); // BFE
  add_polygon(points, x2,y1,z1, x2,y2,z2, x2,y1,z2); // BED
  add_polygon(points, x1,y1,z2, x2,y1,z2, x2,y2,z2); // CDE <-- has problem in rotated cube
  add_polygon(points, x1,y1,z2, x2,y2,z2, x1,y2,z2); // CEG
  add_polygon(points, x1,y1,z1, x1,y1,z2, x1,y2,z1); // ACH
  add_polygon(points, x1,y1,z2, x1,y2,z2, x1,y2,z1); // CGH
  add_polygon(points, x1,y2,z1, x2,y2,z2, x2,y2,z1); // HEF
  add_polygon(points, x1,y2,z1, x1,y2,z2, x2,y2,z2); // HGE
  

}

void render_parametric(struct matrix * points, 
		       double func_x(double t),
		       double func_y(double t), double step) {
  
  double t = 0;
  double x0, y0, x1, y1;

  x0 = func_x(t);
  y0 = func_y(t);

  for (t=step; t <= 1.0; t+=step) {

    x1 = func_x(t);
    y1 = func_y(t);
    printf("t: %lf\t x: %lf\t y: %lf\n", t, x1, y1);
    add_edge(points, x0, y0, 0, x1, y1, 0);

    x0 = x1;
    y0 = y1;
  }

  add_edge(points, x0, y0, 0, func_x(0), func_y(0), 0);
}
