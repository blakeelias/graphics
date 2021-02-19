#ifndef GEO_H
#define GEO_H

#include "matrix.h"

struct shape {
  struct matrix *points;
  int *edges;
  int numEdges;
  int maxEdges;
} shape;

int geo_addPoint(struct shape *s, double *point);
int geo_addEdge(struct shape *s, int point1, int point2);
int geo_addLine(struct shape *s, double *point1, double *point2);

struct shape *geo_newShape(int numPoints, int numEdges);
void geo_freeShape(struct shape *s);
int geo_concatenate(struct shape *a, struct shape *b);
struct shape *geo_merge(struct shape *a, struct shape *b);
struct shape *geo_makeCircle(double *center, double r, double *rot, int res);
struct shape *geo_makeSphere(double *center, double r, double *rot, int res);
struct shape *geo_makeTorus(double *center, double R, double r, double *rot, int res);
struct shape *geo_makeHermite(double p1x, double p1y, double v1x, double v1y, double p2x, double p2y, double v2x, double v2y);
struct shape *geo_makeBezier(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double p4x, double p4y);

#endif
