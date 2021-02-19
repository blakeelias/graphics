#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geo.h"





int geo_addPoint(struct shape *s, double *point) {
  if (!matrix_addPoint(s->points, point))
    return 0;
  return s->points->nextCol;
}
  
int geo_addEdge(struct shape *s, int point1, int point2) {
  if (s->numEdges >= s->maxEdges)
    return 0;
  s->edges[2 * s->numEdges] = point1;
  s->edges[2 * s->numEdges + 1] = point2;
  s->numEdges++;
  return s->numEdges;
}

int geo_addLine(struct shape *s, double *point1, double *point2) {
  if (s->numEdges >= s->maxEdges || s->points->nextCol + 1 >= s->points->cols)
    return 0;
  geo_addEdge(s, s->points->nextCol, s->points->nextCol + 1);
  matrix_addPoint(s->points, point1);
  matrix_addPoint(s->points, point2);
  return s->points->nextCol;
}





struct shape *geo_newShape(int maxPoints, int maxEdges) {
  struct shape *s = (struct shape *) malloc(sizeof(struct shape));
  s->points = matrix_newMatrix(maxPoints, 4);
  s->edges = (int *) malloc(2 * maxEdges * sizeof(int));
  s->numEdges = 0;
  s->maxEdges = maxEdges;
  return s;
}

void geo_freeShape(struct shape *s) {
  matrix_freeMatrix(s->points);
  free(s->edges);
  free(s);
}

int geo_concatenate(struct shape *a, struct shape *b) {
  if (a->numEdges + b->numEdges > a->maxEdges || a->points->nextCol + b->points->nextCol > a->points->cols)
    return 0;
  int k = a->points->nextCol;
  matrix_concatenate(a->points, b->points);
  int i;
  for (i = 0; i < b->numEdges; i++) {
    geo_addEdge(a, k + b->edges[2 * i], k + b->edges[2 * i + 1]);
  }
  return a->points->nextCol;
}

struct shape *geo_merge(struct shape *a, struct shape *b) {
  struct shape *c = geo_newShape(a->points->cols + b->points->cols, a->maxEdges + b->maxEdges);
  c->points = matrix_merge(a->points, b->points);
  int i;
  for (i = 0; i < a->numEdges; i++) {
    geo_addEdge(c, a->edges[2 * i], a->edges[2 * i + 1]);
  }
  int k = a->numEdges;
  for (i = 0; i < b->numEdges; i++) {
    geo_addEdge(c, k + b->edges[2 * i], k + b->edges[2 * i + 1]);
  }
  return c;
}





struct shape *geo_makeCircle(double *center, double r, double *rot, int res) {

  struct shape *circle = geo_newShape(res, res);
  double point[3];
  double angle_incr = 2 * M_PI / res;
  int i;
  for (i = 0; i < res; i++) {
    point[0] = r * cos(i * angle_incr);
    point[1] = r * sin(i * angle_incr);
    point[2] = 0;
    geo_addPoint(circle, point);
  }
  for (i = 1; i < res; i++) {
    geo_addEdge(circle, i - 1, i);
  }
  geo_addEdge(circle, res - 1, 0);
  
  struct matrix *tform = matrix_makeRotX(rot[0]);
  matrix_matrixMult(matrix_makeRotY(rot[1]), tform);
  matrix_matrixMult(matrix_makeRotZ(rot[2]), tform);
  matrix_matrixMult(matrix_makeTranslate(center[0], center[1], center[2]), tform);
  matrix_matrixMult(tform, circle->points);
  
  matrix_freeMatrix(tform);
  return circle;
}


struct shape *geo_makeSphere(double *center, double r, double *rot, int res) {

  struct shape *sphere = geo_newShape(res * res, 2 * res * res);
  double circle_spinner[3];
  double origin[3];
  double angle_incr = 360. / res;
  int i, j;
  for (i = 0; i < res / 2; i++) {
    circle_spinner[0] = i * angle_incr;
    geo_concatenate(sphere, geo_makeCircle(origin, r, circle_spinner, res));
  }
  
  for (i = 0; i < res / 2 - 1; i++) {
    for (j = 0; j < res; j++) {
      geo_addEdge(sphere, res * i + j, res * (i + 1) + j);
    }
  }
  
  for (j = 0; j < res; j++) {
    geo_addEdge(sphere, res - j, res * (res / 2 - 1) + j);
  }
  
  
  struct matrix *tform = matrix_makeRotX(rot[0]);
  matrix_matrixMult(matrix_makeRotY(rot[1]), tform);
  matrix_matrixMult(matrix_makeRotZ(rot[2]), tform);
  matrix_matrixMult(matrix_makeTranslate(center[0], center[1], center[2]), tform);
  matrix_matrixMult(tform, sphere->points);
  
  matrix_freeMatrix(tform);
  return sphere;
}
  
  
struct shape *geo_makeTorus(double *center, double R, double r, double *rot, int res) {

  struct shape *torus = geo_newShape(res * res, 2 * res * res);
  double circle_spinner[3];
  double circle_center[3];
  double angle_incr = 360. / res;
  int i, j;
  for (i = 0; i < res; i++) {
    circle_center[0] = 0;
    circle_center[1] = R * cos(i * angle_incr * M_PI / 180);
    circle_center[2] = R * sin(i * angle_incr * M_PI / 180);
    circle_spinner[0] = i * angle_incr;
    geo_concatenate(torus, geo_makeCircle(circle_center, r, circle_spinner, res));
  }
  
  for (i = 0; i < res - 1; i++) {
    for (j = 0; j < res; j++) {
      geo_addEdge(torus, res * i + j, res * (i + 1) + j);
    }
  }
  
  for (j = 0; j < res; j++) {
    geo_addEdge(torus, j, res * (res - 1) + j);
  }
  
  struct matrix *tform = matrix_makeRotX(rot[0]);
  matrix_matrixMult(matrix_makeRotY(rot[1]), tform);
  matrix_matrixMult(matrix_makeRotZ(rot[2]), tform);
  matrix_matrixMult(matrix_makeTranslate(center[0], center[1], center[2]), tform);
  matrix_matrixMult(tform, torus->points);
  
  matrix_freeMatrix(tform);
  return torus;
}


struct shape *geo_makeHermite(double p1x, double p1y, double v1x, double v1y, double p2x, double p2y, double v2x, double v2y) {

	printf("%lf %lf %lf %lf %lf %lf %lf %lf\n", p1x, p1y, v1x + p1x, v1y + p1y, p2x, p2y, v2x + p2x, v2y + p2y);
	
	int res = 1000;
	struct shape *spline = geo_newShape(res + 1, res);
	
	double Ax = 2*p1x - 2*p2x + 1*v1x + 1*v2x;
	double Ay = 2*p1y - 2*p2y + 1*v1y + 1*v2y;
	double Bx = -3*p1x + 3*p2x - 2*v1x - 1*v2x;
	double By = -3*p1y + 3*p2y - 2*v1y - 1*v2y;
	double Cx = v1x;
	double Cy = v1y;
	double Dx = p1x;
	double Dy = p1y;
	
	//printf("%lf %lf %lf %lf %lf %lf %lf %lf\n", Ax, Ay, Bx, By, Cx, Cy, Dx, Dy);
	
	double step = 1.0/res;
	double t = 0;
	double point[3];
	point[2] = 0;
	int i;
	for (i = 0; i <= res; i++) {
		point[0] = Ax*t*t*t + Bx*t*t + Cx*t + Dx;
		point[1] = Ay*t*t*t + By*t*t + Cy*t + Dy;
		geo_addPoint(spline, point);
		//printf("%lf\n", t);
		t += step;
		//printf("%lf\n", t);
	}
	for (i = 0; i < res; i++) {
		geo_addEdge(spline, i, i+1);
	}
	//printf("HI\n");
	//printf("%lf %lf %lf %lf %lf %lf\n", spline->points->m[0][0], spline->points->m[0][1], spline->points->m[0][2], spline->points->m[1][0], spline->points->m[1][1], spline->points->m[1][2]);
	
	return spline;
}

struct shape *geo_makeBezier(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double p4x, double p4y) {

	printf("%lf %lf %lf %lf %lf %lf %lf %lf\n", p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y);
	
	int res = 1000;
	struct shape *spline = geo_newShape(res + 1, res);
	
	double step = 1.0/res;
	double t = 0;
	double point[3];
	point[2] = 0;
	int i;
	for (i = 0; i <= res; i++) {
		point[0] = (1-t)*(1-t)*(1-t)*p1x + 3*(1-t)*(1-t)*t*p2x + 3*(1-t)*t*t*p3x + t*t*t*p4x;
		point[1] = (1-t)*(1-t)*(1-t)*p1y + 3*(1-t)*(1-t)*t*p2y + 3*(1-t)*t*t*p3y + t*t*t*p4y;
		printf("%lf, %lf\n", point[0], point[1]);
		geo_addPoint(spline, point);
		t += step;
	}
	for (i = 0; i < res; i++) {
		geo_addEdge(spline, i, i+1);
	}
	
	return spline;
}
