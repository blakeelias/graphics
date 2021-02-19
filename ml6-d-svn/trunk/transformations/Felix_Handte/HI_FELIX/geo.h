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
//void geo_addShapeToList(struct shape *s, struct shape **list, int *counter);
int geo_concatenate(struct shape *a, struct shape *b);
//struct shape *geo_merge(struct shape *a, struct shape *b);
//struct shape *geo_makeCircle(double *center, double r, double *rot, int res);
//struct shape *geo_makeSphere(double *center, double r, double *rot, int res);
//struct shape *geo_makeTorus(double *center, double R, double r, double *rot, int res);

#endif
