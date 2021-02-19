#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
/*
//Don't worry about this yet
void render_curve( struct matrix *points, double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3, 
                   double x4, double y4, double step) {
}
*/

//GENERATE BEZIER
void render_curve(struct matrix * d, double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, double step){
double t;
double q;
double x1;
double y1;
double x2;
double y2;
//int dpoints=0;
for(t=0; t<=(1-step); t=t+step){
q=t+step;
fprintf(stderr,"x1:%f y1:%f x2:%f y2:%f T:%f\n",x1, y1, x2, y2, t);
x1=(ax*(1-t)*(1-t)*(1-t)+bx*(1-t)*(1-t)*t+cx*(1-t)*t*t+dx*t*t*t);
y1=(ay*(1-t)*(1-t)*(1-t)+by*(1-t)*(1-t)*t+cy*(1-t)*t*t+dy*t*t*t);
x2=(ax*(1-q)*(1-q)*(1-q)+bx*(1-q)*(1-q)*q+cx*(1-q)*q*q+dx*q*q*q);
y2=(ay*(1-q)*(1-q)*(1-q)+by*(1-q)*(1-q)*q+cy*(1-q)*q*q+dy*q*q*q);
add_edge(d,x1,y1,0,x2,y2,0);
/*
spliine[dpoints][0]=ax*(1-t)*(1-t)*(1-t)+bx*(1-t)*(1-t)*t+cx*(1-t)*t*t+dx*t*t*t;
spliine[dpoints][1]=ay*(1-t)*(1-t)*(1-t)+by*(1-t)*(1-t)*t+cy*(1-t)*t*t+dy*t*t*t;
*/
//dpoints++;
}
} 




/*======== void render_torus_mesh() ==========
Inputs:   struct matrix *points
         double r
	 double r2
         double offx
         double offy
         double step 
Returns: 
Calls generate_torus_mesh to get the points on the surface of a torus.
Calls add_edge to add the necesary lines to edges to draw a torus

03/21/11 12:45:10
jdyrlandweaver
====================*/    
void render_torus_mesh(struct matrix * d, double r, double rr, double offx, double offy, double step) {
//REWRITE
step=64;
double kyuub [64][64][4];
int cv;
int kv;
double cvv=0;
double kvv=0;
//double r;
//double rr;//=0 if sphere

for(kv=0; kv<64; kv++){
for(cv=0; cv<64; cv++){
kyuub[cv][kv][0]=(cos(2*M_PI*(cvv))*(rr+(r*cos(2*M_PI*(kvv)))))+offx;
kyuub[cv][kv][1]=(sin(2*M_PI*(cvv))*(rr+(r*cos(2*M_PI*(kvv)))))+offy;
kyuub[cv][kv][2]=sin(2*M_PI*(kvv));
//connect_edge(kyuub[cv][kv][0], kyuub[cv][kv][1], kyuub[cv][kv][2], kyuub[cv][kv][0], kyuub[cv][kv][1], kyuub[cv][kv][2]);
cvv=cvv+(1/step);
}
kvv=kvv+(1/step);
}

//VPASS
for(kv=0; kv<64; kv++){
for(cv=0; cv<63; cv++){
add_edge(d,kyuub[cv][kv][0], kyuub[cv][kv][1], kyuub[cv][kv][2], kyuub[cv+1][kv][0], kyuub[cv+1][kv][1], kyuub[cv+1][kv][2]);
}

add_edge(d,kyuub[0][kv][0],kyuub[0][kv][1],kyuub[0][kv][2],kyuub[63][kv][0],kyuub[63][kv][1],kyuub[63][kv][2]);
}


//HPASS
for(cv=0; cv<64; cv++){
for(kv=0; kv<63; kv++){
add_edge(d,kyuub[cv][kv][0], kyuub[cv][kv][1], kyuub[cv][kv][2], kyuub[cv][kv+1][0], kyuub[cv][kv+1][1], kyuub[cv][kv+1][2]);
}

add_edge(d,kyuub[0][kv][0],kyuub[0][kv][1],kyuub[0][kv][2],kyuub[63][kv][0],kyuub[63][kv][1],kyuub[63][kv][2]);
}
}

/*
struct matrix * p=new_matrix(d->rows,d->cols);
struct matrix * t;

copy_matrix(d,p);
generate_sphere_mesh(p,r,r2,0,step);
t=make_translate(offx, offy, 0);
matrix_mult(p,t);
free_matrix(t);

//vertical pass
int kd;
int fd;
for(kd=0;kd<(1/step);++kd){
	for(fd=0;fd<(1/step)-1;++fd){
		add_edge(d,p->m[(int)(fd+(kd*(1/step)))][0],p->m[(int)(fd+(kd*(1/step)))][1],p->m[(int)(fd+(kd*(1/step)))][2],p->m[(int)(fd+1+(kd*(1/step)))][0],p->m[(int)(fd+1+(kd*(1/step)))][1],p->m[(int)(fd+1+(kd*(1/step)))][2]);
	}
	add_edge(d,p->m[(int)(kd*(1/step))][0],p->m[(int)(kd*(1/step))][1],p->m[(int)(kd*(1/step))][2],p->m[(int)(fd+1+(kd*(1/step)))][0],p->m[(int)(fd+1+(kd*(1/step)))][1],p->m[(int)(fd+1+(kd*(1/step)))][2]);
}

//horizontal pass
kd=0;
fd=0;
for(fd=0;fd<(1/step)-1;++kd){
	for(kd=0;kd<(1/step);++kd){
		add_edge(d,p->m[(int)(fd+(kd*(1/step)))][0],p->m[(int)(fd+(kd*(1/step)))][1],p->m[(int)(fd+(kd*(1/step)))][2],p->m[(int)(fd+1+(kd*(1/step)))][0],p->m[(int)(fd+1+(kd*(1/step)))][1],p->m[(int)(fd+1+(kd*(1/step)))][2]);
	}
	add_edge(d,p->m[(int)(kd*(1/step))][0],p->m[(int)(kd*(1/step))][1],p->m[(int)(kd*(1/step))][2],p->m[(int)(fd+1+(kd*(1/step)))][0],p->m[(int)(fd+1+(kd*(1/step)))][1],p->m[(int)(fd+1+(kd*(1/step)))][2]);
}
*/

    
/*======== void generate_torus_mesh() ==========
Inputs:   struct matrix *points
         double r
	 double r2
         double offx
         double offy
         double step 
Returns: 
Generates the points on the surface of the sphere
with circle radius r, offset radius r2
and center (offx, offy), stores them in points.
//TODO: ok not really a todo, but the sphere is really a degenerate torus, so this isnt needed.
03/21/11 12:45:10
jdyrlandweaver
====================*/
void generate_torus_mesh( struct matrix *points, double r, double r2,
			 double offx, double offy, double step) {
//UNUSED
}

/*======== void render_sphere_mesh() ==========
Inputs:   struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Calls generate_sphere_mesh to get the points on the surface of a sphere.
Calls add_edge to add the necesary lines to edges to draw a sphere

03/21/11 12:45:10
jdyrlandweaver
====================*/    
void render_sphere_mesh(struct matrix * d, double r, double offx, double offy, double step){
//REWRITE
//cheap recycling of torus code. step is locked at 64.
//TODO:uncheapen?
render_torus_mesh(d,r,0,offx,offy,step);
}
/*
struct matrix * p=new_matrix(d->rows,d->cols);
struct matrix * t;

copy_matrix(d,p);
generate_sphere_mesh(p,r,0,0,step);
t=make_translate(offx, offy,0);
matrix_mult(p,t);
free_matrix(t);

//vertical pass
int kd;
int fd;
for(kd=0;kd<(1/step);++kd){
	for(fd=0;fd<(1/step)-1;++fd){
		add_edge(d,p->m[(int)(fd+(kd*(1/step)))][0],p->m[(int)(fd+(kd*(1/step)))][1],p->m[(int)(fd+(kd*(1/step)))][2],p->m[(int)(fd+1+(kd*(1/step)))][0],p->m[(int)(fd+1+(kd*(1/step)))][1],p->m[(int)(fd+1+(kd*(1/step)))][2]);
	}
	add_edge(d,p->m[(int)(kd*(1/step))][0],p->m[(int)(kd*(1/step))][1],p->m[(int)(kd*(1/step))][2],p->m[(int)(fd+1+(kd*(1/step)))][0],p->m[(int)(fd+1+(kd*(1/step)))][1],p->m[(int)(fd+1+(kd*(1/step)))][2]);
}

//horizontal pass
kd=0;
fd=0;
for(fd=0;fd<(1/step)-1;++kd){
	for(kd=0;kd<(1/step);++kd){
		add_edge(d,p->m[(int)(fd+(kd*(1/step)))][0],p->m[(int)(fd+(kd*(1/step)))][1],p->m[(int)(fd+(kd*(1/step)))][2],p->m[(int)(fd+1+(kd*(1/step)))][0],p->m[(int)(fd+1+(kd*(1/step)))][1],p->m[(int)(fd+1+(kd*(1/step)))][2]);
	}
	add_edge(d,p->m[(int)(kd*(1/step))][0],p->m[(int)(kd*(1/step))][1],p->m[(int)(kd*(1/step))][2],p->m[(int)(fd+1+(kd*(1/step)))][0],p->m[(int)(fd+1+(kd*(1/step)))][1],p->m[(int)(fd+1+(kd*(1/step)))][2]);
}

}*/
    
/*======== void generate_sphere_mesh() ==========
Inputs:   struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Generates the points on the surface of the sphere
with radius r and center (offx, offy), stores them in points.

03/21/11 12:45:10
jdyrlandweaver
====================*/
void generate_sphere_mesh(struct matrix * d, double r, double offx, double offy, double step){

struct matrix * t;
int ds=1/step;
int v=0;

struct matrix * vp=new_matrix(4,ds+1); //+1 just in case
struct matrix * p=new_matrix(4,ds+1);

generate_circle(vp,r,offx,offy,step);
copy_matrix(vp,p);
int k=0;
for(v=0;v<1;v=v+step){
t=make_rotX(2*v*step*M_PI);
matrix_mult(t,p);
free_matrix(t);
append_matrix(d,p,k*(1/step)); //THIS IS NOT IMPLEMENTED;TODO
copy_matrix(vp,p);
++k;
}
free_matrix(p);
free_matrix(vp);
}


/*======== void render_circle() ==========
Inputs:   struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Uses generate_circle to create the points necessary for a circle.
Calls add_edge to create the lines necessary from the given points
03/15/10 19:37:43
jonalf
====================*/
void render_circle(struct matrix * d, double r, double offx, double offy, double step){
//REWRITE
//int points=1/step;
double kv=0;
double tmpx=r+offx;
double tmpy=offy;
double tmpx2=r*cos(2*M_PI*kv)+offx;
double tmpy2=r*sin(2*M_PI*kv)+offy;
fprintf(stdout,"INIT PASS\n");

for(kv=0; kv<=1+step+step; kv=kv+step){
fprintf(stdout,"TMP: %f,%f\n TMP2: %f,%f\n KV=%f\n",tmpx,tmpy,tmpx2,tmpy2,kv);
add_edge(d,tmpx,tmpy,0,tmpx2,tmpy2,0);
tmpx=tmpx2;
tmpy=tmpy2;
tmpx2=r*cos(2*M_PI*kv)+offx;
tmpy2=r*sin(2*M_PI*kv)+offy;

//add_edge(d,r*cos(2*M_PI*kv)+offx,r*sin(2*M_PI*kv)+offy,0,r*cos(2*M_PI*(kv+step))+offx,r*sin(2*M_PI*(kv+step))+offy,0);
}/*
kv=kv+step;
tmpx2=r*cos(2*M_PI*kv)+offx;
tmpy2=r*sin(2*M_PI*kv)+offy;*/
//add_edge(d,r+offx,offy,0,tmpx2,tmpy2,0);
}
/*
struct matrix * p=new_matrix(d->rows,d->cols);
copy_matrix(d,p);
generate_circle(p,r,offx,offy,step);

int i;
int k=0;

for(i=1; i>0; i=(i-step)){
++k;
add_edge(d,p->m[k-1][0],p->m[k-1][1],0,p->m[k][0],p->m[k][1],0);
}

k++;
add_edge(d,p->m[0][0],p->m[0][1],0,p->m[k][0],p->m[k][1],0);

free_matrix(p);
} 
	     */

/*======== void  generate_circle() ==========
Inputs:  struct matrix *points
         double r
         double offx
         double offy
         double step 
Returns: 
Generates the points required for a circle 

03/15/10 19:11:13
jonalf
====================*/
void  generate_circle(struct matrix * d, double r, double offx, double offy, double step){
//UNUSED
//x=a+r cos t
//y=b+r sin t
int k=0;
int i;
for(i=1; i>0; i=(i-step)){
d->m[0][k]=offx + r * cos(M_PI * 2 * step);
d->m[1][k]=offy + r * sin(M_PI * 2 * step);
d->m[2][k]=0;
++k;
}

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
void add_point( struct matrix * points, double x, double y, double z) {

  if ( points->lastcol == points->cols )
    grow_matrix(points, points->lastcol + 100);

  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;
      
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
    draw_line(points->m[0][i], points->m[1][i], 
	      points->m[0][i+1], points->m[1][i+1], s, c);
    
    
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should call add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {

  add_point( points, x0, y0, z0);
  add_point( points, x1, y1, z1);
}

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
 
  int x, y, d, dx, dy;

  x = x0;
  y = y0;
  
  //swap points so we're always draing left to right
  if ( x0 > x1 ) {
    x = x1;
    y = y1;
    x1 = x0;
    y1 = y0;
  }

  //need to know dx and dy for this version
  dx = x1 - x;
  dy = y1 - y;

  //positive slope: Octants 1, 2 (5 and 6)
  if ( dy > 0 ) {

    //slope < 1: Octant 1 (5)
    if ( dx > dy ) {
      d = 2 * dy - dx;
  
      while ( x < x1 ) {
	plot(s, c, x, y);

	if ( d < 0 ) {
	  x = x + 1;
	  d = d + dy;
	}
	else {
	  x = x + 1;
	  y = y + 1;
	  d = d + dy - dx;
	}
      }
    }

    //slope > 1: Octant 2 (6)
    else {
      d = dy - 2 * dx;
      while ( y < y1 ) {

	plot(s, c, x, y );
	if ( d > 0 ) {
	  y = y + 1;
	  d = d - dx;
	}
	else {
	  y = y + 1;
	  x = x + 1;
	  d = d + dy - dx;
	}
      }
    }
  }

  //negative slope: Octants 7, 8 (3 and 4)
  else { 

    //slope > -1: Octant 8 (4)
    if ( dx > abs(dy) ) {
      d = 2 * dy + dx;
  
      while ( x < x1 ) {

	plot(s, c, x, y);

	if ( d > 0 ) {
	  x = x + 1;
	  d = d + dy;
	}
	else {
	  x = x + 1;
	  y = y - 1;
	  d = d + dy + dx;
	}
      }
    }

    //slope < -1: Octant 7 (3)
    else {

      d = dy + 2 * dx;
      while ( y >= y1 ) {
	
	plot(s, c, x, y );
	if ( d < 0 ) {
	  y = y - 1;
	  d = d + dx;
	}
	else {
	  y = y - 1;
	  x = x + 1;
	  d = d + dy + dx;
	}
      }
    }
  }
}

