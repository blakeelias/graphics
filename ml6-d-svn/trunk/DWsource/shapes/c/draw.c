#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"

void render_curve( struct matrix *points, double x1, double y1, 
		   double x2, double y2, 
		   double x3, double y3, 
		   double x4, double y4, double step) {

  double x, y, t;
  struct matrix * xcoefs;
  struct matrix * ycoefs;
  
  //generate the coeficients
  xcoefs = generate_bezier_coefs(x1, x2, x3, x4);
  ycoefs = generate_bezier_coefs(y1, y2, y3, y4);

  //  xcoefs = generate_hermite_coefs(x1, x2, x3, x4);
  //  ycoefs = generate_hermite_coefs(y1, y2, y3, y4);
  printf("a = %lf b = %lf c = %lf d = %lf\n", xcoefs->m[0][0],
	 xcoefs->m[1][0], xcoefs->m[2][0], xcoefs->m[3][0]);

  for (t=step; t <= 1; t+= step) {
    
    x = xcoefs->m[0][0] * t * t * t + xcoefs->m[1][0] * t * t
      + xcoefs->m[2][0] * t + xcoefs->m[3][0];

    y = ycoefs->m[0][0] * t * t * t + ycoefs->m[1][0] * t * t
      + ycoefs->m[2][0] * t + ycoefs->m[3][0];

    add_edge(points, x1, y1, 0, x, y, 0);
    x1 = x;
    y1 = y;
  }

  free_matrix(xcoefs);
  free_matrix(ycoefs);
}
    

void generate_torus_mesh( struct matrix *points, double r, double r2,
		     double offx, double offy, double step) {

  double x, y, z, rt, c;

  for(rt=0; rt <= 1; rt+= step) 
    for(c=0; c <= 1; c+= step) {

      x = r2 * cos(2 * M_PI * rt) + r * cos(2 * M_PI * c) * cos(2 * M_PI * rt)
	+ offx;
      y = r * sin(2 * M_PI * c) + offy;
      z = -1 * r2 * sin(2 * M_PI * rt) - r * cos(2 * M_PI * c) * 
	sin(2 * M_PI * rt);
    
      add_point(points, x, y, z);      
    }
}

void render_torus_mesh( struct matrix *points, double r, double r2,
			 double offx, double offy, double step) {
  
  struct matrix *temp;
  int i, j, index, offset;
  double ns;
  int num_steps;
 
  //wont work in ubuntu due to strange typecasting problems
  //  num_steps = (int)1/step;
  ns = 1.0/step;
  num_steps = (int)ns;

  temp = new_matrix(4, num_steps * num_steps);
  generate_torus_mesh(temp, r, r2, offx, offy, step);
  
  //longitudinal lines
  for (i=0; i < num_steps; i++)
    for (j=0; j < num_steps; j++) {
      
      index = i * num_steps + j;
      if ( j == num_steps - 1 ) {
	//add edge *9 -> *0
	add_edge(points, 
		 temp->m[0][index], temp->m[1][index], temp->m[2][index],
		 temp->m[0][index+1-num_steps], 
		 temp->m[1][index+1-num_steps], 
		 temp->m[2][index+1-num_steps]);
       
      }
      else {
	//add edge j -> j + 1
	add_edge(points, 
		 temp->m[0][index], temp->m[1][index], temp->m[2][index],
		 temp->m[0][index+1], temp->m[1][index+1], temp->m[2][index+1]);
      }
    }
  
  //latitudinal lines
  for (i=0; i < num_steps; i++) 
    for (j=0; j < num_steps; j++) {
   
      index = i * num_steps + j;
      offset = (10 - index) - 20 * (int)floor( (10 - index)/20.0);

      if ( i == num_steps - 1 ) {
	add_edge(points, 
		 temp->m[0][index], temp->m[1][index], temp->m[2][index],
		 temp->m[0][ index - num_steps * i ], 
		 temp->m[1][ index - num_steps * i ],
		 temp->m[2][ index - num_steps * i ]); 
      }
      else {
	add_edge(points, 
		 temp->m[0][index], temp->m[1][index], temp->m[2][index],
		 temp->m[0][index + num_steps], 
		 temp->m[1][index + num_steps], 
		 temp->m[2][index + num_steps]);
      }
    }

  //points only
  /*
  for( i=0; i < temp->lastcol; i++)
    add_edge(points, temp->m[0][i], temp->m[1][i], temp->m[2][i], 
	     temp->m[0][i], temp->m[1][i], temp->m[2][i]);
  */

  free_matrix(temp);
}
    

void render_sphere_mesh( struct matrix *points, double r,
			 double offx, double offy, double step) {
  
  struct matrix *temp;
  int i, j, index, offset;
  double ns;
  int num_steps;
 
  ns = 1.0/step;
  num_steps = (int)ns;

  temp = new_matrix(4, (int)1/step * (int)1/step);
  generate_sphere_mesh(temp, r, offx, offy, step);
  
  //longitudinal lines
  for (i=0; i < num_steps; i++)
    for (j=0; j < num_steps; j++) {
      
      index = i * num_steps + j;
      if ( j == num_steps - 1 ) {
	//add edge *9 -> *0
	add_edge(points, 
		 temp->m[0][index], temp->m[1][index], temp->m[2][index],
		 temp->m[0][index+1-num_steps], 
		 temp->m[1][index+1-num_steps], 
		 temp->m[2][index+1-num_steps]);
       
      }
      else {
	//add edge j -> j + 1
	add_edge(points, 
		 temp->m[0][index], temp->m[1][index], temp->m[2][index],
		 temp->m[0][index+1], temp->m[1][index+1], temp->m[2][index+1]);
      }
    }
  
  //latitudinal lines
  for (i=0; i < num_steps; i++) 
    for (j=0; j < num_steps; j++) {

      index = i * num_steps + j;
      offset = (10 - index) - 20 * (int)floor( (10 - index)/20.0);

      if ( i == num_steps - 1 ) {
	//add edge *9 -> *0
	add_edge(points, 
		 temp->m[0][index], temp->m[1][index], temp->m[2][index],
		 temp->m[0][ offset ], 
		 temp->m[1][ offset ],
		 temp->m[2][ offset ]); 
      }
      else {
	add_edge(points, 
		 temp->m[0][index], temp->m[1][index], temp->m[2][index],
		 temp->m[0][index + num_steps], 
		 temp->m[1][index + num_steps], 
		 temp->m[2][index + num_steps]);
      }
    }
  
  //points only
  /*
  for( i=0; i < temp->lastcol; i++) 
    add_edge(points, temp->m[0][i], temp->m[1][i], temp->m[2][i], 
	     temp->m[0][i], temp->m[1][i], temp->m[2][i]);
  */
  free_matrix(temp);
}
    

void generate_sphere_mesh( struct matrix *points, double r,
			   double offx, double offy, double step) {

  double x, y, z, c, rt;

  for( rt=0; rt <= 1; rt+=step) 
    for( c=0; c <= 1; c+=step ) {

      x = r * cos(2 * M_PI * c) * cos(M_PI * rt) + offx;
      y = r * sin(2 * M_PI * c) + offy;
      z = r * -1 * cos(2 * M_PI * c) * sin(M_PI * rt);
      add_point(points, x, y, z);
    }
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
void render_circle( struct matrix *points, double r, 
		    double offx, double offy, double step) {

  struct matrix *temp;
  int i;
  temp = new_matrix(4, (int)1/step );
  
  //generate the points for a circle, store them in temp
  generate_circle(temp, r, offx, offy, step);
  
  //go through temp and add edges accordingly
  //temp[0] -> temp[1], temp[1] -> temp[2] ...
  for (i = 0; i < temp->lastcol-1; i++) 
    add_edge(points, temp->m[0][i], temp->m[1][i], temp->m[2][i], 
	     temp->m[0][i+1], temp->m[1][i+1], temp->m[2][i+1]);
 
  //add a point to close the circle
  add_edge(points, temp->m[0][i], temp->m[1][i], temp->m[2][i], 
	   temp->m[0][0], temp->m[1][0], temp->m[2][0]);

  free_matrix(temp);
} 
	     

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
void  generate_circle(struct matrix *points, double r, 
		    double offx, double offy, double step) {

  double x0, y0, x, y, t;
  x0 = r + offx;
  y0 = offy;

  for (t = step; t <= 1; t+= step) {

    x = r * cos(2 * M_PI * t) + offx;
    y = r * sin(2 * M_PI * t) + offy;

    add_point(points, x0, y0, 0);
    x0 = x;
    y0 = y;
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

