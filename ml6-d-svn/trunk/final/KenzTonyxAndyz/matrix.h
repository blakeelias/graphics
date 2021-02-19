#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdio.h>

#define dWidth  800
#define dHeight 600

typedef unsigned int uint;

typedef int8_t    s8;
typedef uint8_t   u8;
typedef int16_t  s16;
typedef uint16_t u16;
typedef int32_t  s32;
typedef uint32_t u32;
typedef int64_t  s64;
typedef uint64_t u64;

typedef struct
{
 double data[16];
 int rows;
 int cols;
} Matrix;


#define getMP(x, y, z) \
((Matrix){ \
 {x, y, z, 1.0}, \
 4, \
 1, \
})

typedef struct
{
 Matrix* pointList;
 int pointCount;
 int pointCap;
} Points;

void* newImage();
void clear(void* rawImage);

void plot(void* rawImage, int x, int y, u32 color);
void plotZ(void* rawImage, int x, int y, int z, u32 color);

void saveBMP(FILE* out, void* rawImage);

void destroyPoints(Points* points);
void draw(void* image, Points points);
void dump(Points* target, Points src);
void addPoint(Points* points, double x, double y, double z);

void initMatrix(Matrix* matrix, int rows, int cols);
void pushMatrix(Points* points);
void popMatrix(Points* points);
Matrix* top(Points points);
void printMatrix(Matrix* m);

int identityMatrix(Matrix* m);
void multiplyMatrix(Matrix* result, Matrix* m, double d);
int multiplyMatrices(Matrix* result, Matrix* m1, Matrix* m2);
int addMatrices(Matrix* result, Matrix* m1, Matrix* m2);
int subtractMatrices(Matrix* result, Matrix* m1, Matrix* m2);

void apply(Points points, Matrix* m);

void makeTranslate(Matrix* dst, double x, double y, double z);
void makeScale(Matrix* dst, double x, double y, double z);
void makeRotX(Matrix* dst, int deg);
void makeRotY(Matrix* dst, int deg);
void makeRotZ(Matrix* dst, int deg);

void addCircle(Points* points, double radius, double x, double y, double step);
void addHermite(Points* points, int* x, int* y, double step);
void addBezier(Points* points, int* x, int* y, double step);
void addSphere(Points* points, double radius, double x, double y, double z);
void addBox(Points* points, double x, double y, double z, double w, double h, double d);
void addTorus(Points* points, double wholeR, double circR, double x, double y, double z);

#endif

