#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geo.h"





int geo_addPoint(struct shape *s, matrix_t *point) {
  matrix_addPoint(s->points, point);
  return s->points->nc;
}

  
int geo_addEdge(struct shape *s, int point1, int point2) {
  if (s->numEdges >= s->maxEdges)
    return 0;
  s->edges[2 * s->numEdges] = point1;
  s->edges[2 * s->numEdges + 1] = point2;
  s->numEdges++;
  return s->numEdges;
}

int geo_addLine(struct shape *s, matrix_t *point1, matrix_t *point2) {
  if (s->numEdges >= s->maxEdges || s->points->nc + 1 >= s->points->ac)
    return 0;
  geo_addEdge(s, s->points->nc, s->points->nc + 1);
  matrix_addPoint(s->points, point1);
  matrix_addPoint(s->points, point2);
  return s->points->nc;
}





struct shape *geo_newShape(int maxPoints, int maxEdges) {
  struct shape *s = (struct shape *) malloc(sizeof(struct shape));
  s->points = matrix_new(maxPoints, 4);
  s->edges = (int *) malloc(2 * maxEdges * sizeof(int));
  s->numEdges = 0;
  s->maxEdges = maxEdges;
  return s;
}

void geo_freeShape(struct shape *s) {
  matrix_free(s->points);
  free(s->edges);
  free(s);
}	

int geo_concatenate(struct shape *a, struct shape *b) {
  if (a->numEdges + b->numEdges > a->maxEdges || a->points->nc + b->points->nc > a->points->ac)
    return 0;
  int k = a->points->nc;
  matrix_concatenate(a->points, b->points);
  int i;
  for (i = 0; i < b->numEdges; i++) {
    geo_addEdge(a, k + b->edges[2 * i], k + b->edges[2 * i + 1]);
  }
  return a->points->nc;
}

/*
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
*/




/*
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
*/

/* 
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
*/
