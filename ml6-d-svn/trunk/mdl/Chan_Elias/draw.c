#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "matrix_stack.h"
#include "display.h"
#include "draw.h"

#define prontv printf

void draw_sphere(struct matrix *points, double x, double y, double r) { //RELIES ON CONNECT FOR DORITO READINESS
  double phi, theta, step;
  int nsteps = 32;
  double xcor, ycor, zcor;

  struct matrix *sphere_points = new_matrix(4, 2);

  step = 2 * M_PI / nsteps;
  for (phi = 0; phi <= M_PI + step; phi += step) {
    for (theta = 0; theta < 2 * M_PI; theta += step) {
      xcor = r * cos(theta) * cos(phi) + x;
      ycor = r * sin(theta) + y;
      zcor = -r * cos(theta) * sin(phi);
      add_point(sphere_points, xcor, ycor, zcor);
    }
  }
  
  connect_dots(sphere_points, points, nsteps, nsteps/2);
}

void draw_torus(struct matrix *points, double x, double y, double R, double r) { //RELIES ON CONNECT FOR DORITO READINESS
  double phi, theta, step;
  int nsteps = 32;
  double xcor, ycor, zcor;

  struct matrix *torus_points = new_matrix(4, 2);

  step = 2 * M_PI / nsteps;
  for (phi = 0; phi <= 2 * M_PI + step; phi += step) {
    for (theta = 0; theta < 2 * M_PI; theta += step) {
      xcor = r * cos(theta) * cos(phi) + R * cos(phi) + x;
      ycor = r * sin(theta) + y;
      zcor = -r * cos(theta) * sin(phi) - R * sin(phi);
      add_point(torus_points, xcor, ycor, zcor);
    }
  }
  
  connect_dots(torus_points, points, nsteps, nsteps);
}

void draw_box(struct matrix *points, double x1, double y1, double z1, double x2, double y2, double z2) { //DORITO READY
  x2 += x1; // the second set of coordinates is a depth, not a point
  y2 += y1; // add the coordinates to generate point #2
  z2 += z1;

  add_polygon(points, x2,y2,z1, x1,y2,z1, x1,y1,z1);
  add_polygon(points, x2,y1,z1, x2,y2,z1, x1,y1,z1);
  
  add_polygon(points, x2,y2,z2, x2,y2,z1, x2,y1,z1);
  add_polygon(points, x2,y1,z1, x2,y2,z2, x2,y1,z2);
  
  add_polygon(points, x1,y2,z2, x2,y2,z2, x2,y1,z2);
  add_polygon(points, x1,y1,z2, x1,y2,z2, x2,y1,z2);
  
  add_polygon(points, x2,y2,z2, x2,y2,z1, x2,y1,z1);
  add_polygon(points, x2,y1,z1, x2,y2,z2, x2,y1,z2);
  
  add_polygon(points, x2,y2,z2, x1,y2,z2, x1,y2,z1);
  add_polygon(points, x2,y2,z1, x2,y2,z2, x1,y2,z1);
  
  add_polygon(points, x1,y2,z1, x1,y2,z2, x1,y1,z2);
  add_polygon(points, x1,y1,z1, x1,y2,z1, x1,y1,z2);
  
  /*
  add_edge(points, x1,y1,z1, x2,y1,z1);
  add_edge(points, x2,y1,z1, x2,y2,z1);
  add_edge(points, x2,y2,z1, x1,y2,z1);
  add_edge(points, x1,y2,z1, x1,y1,z1);

  add_edge(points, x1,y1,z2, x2,y1,z2);
  add_edge(points, x2,y1,z2, x2,y2,z2);
  add_edge(points, x2,y2,z2, x1,y2,z2);
  add_edge(points, x1,y2,z2, x1,y1,z2);

  add_edge(points, x1,y1,z1, x1,y1,z2);
  add_edge(points, x2,y1,z1, x2,y1,z2);
  add_edge(points, x2,y2,z1, x2,y2,z2);
  add_edge(points, x1,y2,z1, x1,y2,z2);
*/
}

void connect_dots(struct matrix *sphere_points, struct matrix *points, int nsteps_lat, int nsteps_lon) { //DORITO READY
  int lon, lat;
  printf("%d points\n", sphere_points->lastcol);
  for (lon = 0; lon < nsteps_lon; lon++) {
    for (lat = 0; lat < nsteps_lat - 1; lat++) {
      add_edge(points,
	       sphere_points->m[0][lon*nsteps_lat+lat], sphere_points->m[1][lon*nsteps_lat+lat], sphere_points->m[2][lon*nsteps_lat+lat],
	       sphere_points->m[0][lon*nsteps_lat+lat+1], sphere_points->m[1][lon*nsteps_lat+lat+1], sphere_points->m[2][lon*nsteps_lat+lat+1]);
    }
    add_edge(points,
	     sphere_points->m[0][lon*nsteps_lat+lat], sphere_points->m[1][lon*nsteps_lat+lat], sphere_points->m[2][lon*nsteps_lat+lat],
	     sphere_points->m[0][lon*nsteps_lat], sphere_points->m[1][lon*nsteps_lat], sphere_points->m[2][lon*nsteps_lat]);
  }

  for (lat = 0; lat < nsteps_lat; lat++) {
    for (lon = 0; lon < nsteps_lon; lon++) {
      add_edge(points,
	 sphere_points->m[0][lon*nsteps_lat+lat], sphere_points->m[1][lon*nsteps_lat+lat], sphere_points->m[2][lon*nsteps_lat+lat],
	 sphere_points->m[0][(lon+1)*nsteps_lat+lat], sphere_points->m[1][(lon+1)*nsteps_lat+lat], sphere_points->m[2][(lon+1)*nsteps_lat+lat]);
    }
  }
}

void render_parametric(struct matrix * points, double func_x(double t), double func_y(double t), double step){ //DO NOT USE WITH DORITOS
  
  double t = 0;
  double x0, y0, x1, y1;

  x0 = func_x(t);
  y0 = func_y(t);

  for (t=step; t <= 1.0; t+=step) {

    x1 = func_x(t);
    y1 = func_y(t);
    prontv("t: %lf\t x: %lf\t y: %lf\n", t, x1, y1);
    add_edge(points, x0, y0, 0, x1, y1, 0);

    x0 = x1;
    y0 = y1;
  }

  add_edge(points, x0, y0, 0, func_x(0), func_y(0), 0);
}

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
void draw_lines( struct matrix * points, screen s, color c) { //REDIR TO DORITO CODE IN HERE
//SHAMELESS DORITO REDIRECTION
draw_polygons(points, screen s, color c);
return;
/*
  int i;
  if ( points->lastcol < 2 ) {
    printf("Need at least 2 points to draw a line!\n");
    return;
  }

  for (i=0; i < points->lastcol - 1; i+=2) 
    draw_line(points->m[0][i], points->m[1][i], 
	      points->m[0][i+1], points->m[1][i+1], s, c);
    
  */  
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should call add_point
====================*/
void add_edge( struct matrix * points, int x0, int y0, int z0, int x1, int y1, int z1) {

  add_point( points, x0, y0, z0);
  add_point( points, x1, y1, z1);
}

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
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
  int d = 2*dy - dx;
  for (; x0 <= x1; x0++) {
    if (octant == 2)
      plot(s, c, y0, x0);
    else if (octant == 1)
      plot(s, c, x0, y0);
    else if (octant == 8)
      plot(s, c, x0, -y0);
    else if (octant == 7)
      plot(s, c, y0, -x0);
    if (d >= 0) {
      y0++;
      d -= dx;
    }
    d += dy;
  }
}

void add_polygon(struct matrix * points, int x0, int y0, int z0, int x1, int y1, int z1, int x2, int y2, int z2){
	add_point(points, x0,y0,z0);
	add_point(points, x1,y1,z1);
	add_point(points, x2,y2,z2);
}

void draw_polygons(struct matrix * points, screen s, color c) {

  int i;
  if ( points->lastcol < 3 ) {
    printf("Need at least 3 points to draw a dorito!\n");
    return;
  }
//BACKFACE CULLING IMPLEMENTED
//THE METHOD USED HERE IS REALLY DAMN SLOW. FIND A BETTER ONE LATER.
int xv0;	//x vector, point 0 to 1
int yv0;	//y vector, point 0 to 1
int xv1;	//x vector, point 1 to 2
int yv1;  	//y vector, point 1 to 2
int xvcc;	//xv0, rotated counterclockwise
int yvcc; 	//yv0, rotated counterclockwise
int xvcw;	//xv0, rotated clockwise
int yvcw;	//yv0, rotated clockwise
double dfcc;    //distance from counterclockwise
double dfcw;	//distance from clockwise


  for (i=0; i < points->lastcol - 2; i+=3) {

	xv0=(points->m[0][i+1])-(points->m[0][i]);
	yv0=(points->m[1][i+1])-(points->m[1][i]);
	xv1=(points->m[0][i+2])-(points->m[0][i+1]);
	yv1=(points->m[1][i+2])-(points->m[1][i+1]);
	xvcc=-(yv0);
	yvcc=(xv0);
	xvcw=(yv0);
	yvcw=-(xv0);
	dfcc=sqrt((((double)xvcc-(double)xv1)*((double)xvcc-(double)xv1))+(((double)yvcc-(double)yv1)*((double)yvcc-(double)yv1)));
	dfcw=sqrt((((double)xvcw-(double)xv1)*((double)xvcw-(double)xv1))+(((double)yvcw-(double)yv1)*((double)yvcw-(double)yv1)));
	if(dfcc<dfcw){
		draw_line(points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1], s, c);
		draw_line(points->m[0][i], points->m[1][i], points->m[0][i+2], points->m[1][i+2], s, c);
		draw_line(points->m[0][i+1], points->m[1][i+1], points->m[0][i+1], points->m[1][i+1], s, c);    
		}
}	
}

void shade_polygon(x0,y0,x1,y1,x2,y2, screen s, color c){

if (x0==x1){shade_triangle(x2,y2,x0,y0,x1,y1,s,c);		return;} 
if (x1==x2){shade_triangle(x0,y0,x1,y1,x2,y2,s,c);		return;}
if (x0==x2){shade_triangle(x1,y1,x2,y2,x0,y0,s,c);		return;}

if (y0==y1){
shade_triangle(x0,y0,x2,y2,x2,y0,s,c);		
shade_triangle(x1,y1,x2,y2,x2,y0,s,c);
return;} 


if (y1==y2){
shade_triangle(x1,y1,x0,y0,x0,y1,s,c);		
shade_triangle(x2,y2,x0,y0,x0,y1,s,c);
return;}

if (y0==y2){
shade_triangle(x0,y0,x1,y1,x1,y0,s,c);		
shade_triangle(x2,y2,x1,y1,x1,y0,s,c);
return;}



int xlow;
int xhigh;
int pty;

if(x0<x1&&x0<x2){xlow=0;}
if(x2<x1&&x0>x2){xlow=2;}
if(x2>x1&&x0>x1){xlow=1;}
if(x0>x1&&x0>x2){xhigh=0;}
if(x2>x1&&x0<x2){xhigh=2;}
if(x2<x1&&x0<x1){xhigh=1;}


if(xlow==0&&xhigh==1){
pty=(double(x2)*(((double)y1-(double)y0)/((double)x1-(double)x0)))+y0;
shade_triangle(x0,y0,x2,y2,x2,pty,s,c);		
shade_triangle(x1,y1,x2,y2,x2,pty,s,c);
return;
}

if(xlow==0&&xhigh==2){
pty=(double(x1)*(((double)y2-(double)y0)/((double)x2-(double)x0)))+y0;
shade_triangle(x0,y0,x1,y1,x1,pty,s,c);		
shade_triangle(x2,y2,x1,y1,x1,pty,s,c);
return;
}

if(xlow==2&&xhigh==0){
pty=(double(x1)*(((double)y0-(double)y2)/((double)x0-(double)x2)))+y2;
shade_triangle(x0,y0,x1,y1,x1,pty,s,c);		
shade_triangle(x2,y2,x1,y1,x1,pty,s,c);
return;
}

if(xlow==2&&xhigh==1){
pty=(double(x0)*(((double)y1-(double)y2)/((double)x1-(double)x2)))+y2;
shade_triangle(x1,y1,x0,y0,x0,pty,s,c);		
shade_triangle(x2,y2,x0,y0,x0,pty,s,c);
return;
}

if(xlow==1&&xhigh==0){
pty=(double(x2)*(((double)y0-(double)y1)/((double)x0-(double)x1)))+y1;
shade_triangle(x0,y0,x2,y2,x2,pty,s,c);		
shade_triangle(x1,y1,x2,y2,x2,pty,s,c);
return;
}

if(xlow==1&&xhigh==2){
pty=(double(x0)*(((double)y2-(double)y1)/((double)x2-(double)x1)))+y1;
shade_triangle(x1,y1,x0,y0,x0,pty,s,c);		
shade_triangle(x2,y2,x0,y0,x0,pty,s,c);
return;
}

}

void shade_triangle(x0,y0,x1,y1,x2,y2, screen s, color c){

if(x1!=x2){exit(2);}//SOMETHING IS VERY WRONG

int dir=1; //(+)=<|,-->; (-)=|>,<---;
if(x0>x2){dir=-1;}

/* //DOESNT MATTER
int yhigh=1;
if(y2>y1){yhigh=2;}
*/

double slope1=(((double)y1-(double)y0))/((double)x1-(double)x0));
double slope2=(((double)y2-(double)y0))/((double)x2-(double)x0));

double tp=y0+.5;
double bp=y0+.5;
int d;
int k=x0;

for(d=0;d<(x2-x0;++d){
draw_vert((int)tp,(int)bp,k,s,c);
tp+slope1;
bp+slope2;
k+=dir;
}


}

void draw_vert(int y0, y1, x, screen s, color c){
int dir=1;
if(y0>y1){dir=-1;}
int i;
for(i=(y0-y1);i!=0;i+=dir){
plot(s, c, y0+i, x);
}

}






