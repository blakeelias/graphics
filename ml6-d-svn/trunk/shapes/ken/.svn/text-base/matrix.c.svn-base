#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IABS(i)      (((i) < 0) ? -(i) : (i))
#define img          ((u32*)rawImage)
#define PIXEL(x, y)  img[(y * dWidth) + x]
#define RGB(r, g, b) (((r) << 16) | ((g) << 8) | (b))
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

uint dWidth  = 400;
uint dHeight = 300;

typedef struct
{
 Matrix* pointList;
 int pointCount;
 int pointCap;
} Points;

Points points;



void clear(void* rawImage)
{
 int i;
 for (i = 0; i < (dWidth * dHeight); i++)
  img[i] = RGB(0, 0, 0);
}

void plot(void* rawImage, int x, int y, u32 color)
{
 if (x < 0) return;
 if (y < 0) return;
 if (x >= dWidth)  return;
 if (y >= dHeight) return;

 PIXEL(x, y) = color;
}

void draw_line(int x1, int y1, int x2, int y2, void* rawImage, u32 color)
{
 int dx = x2 - x1;
 int dy = y2 - y1;

 int qx = x1;
 int qy = y1;

 int* const ind = (IABS(dx) > IABS(dy)) ? &qx : &qy;
 int* const dep = (IABS(dx) > IABS(dy)) ? &qy : &qx;

 int limit = (IABS(dx) > IABS(dy)) ? x2 : y2;

 if (*ind > limit)
 {
  draw_line(x2, y2, x1, y1, rawImage, color);
  return;
 }

 const int dind = IABS(  (IABS(dx) > IABS(dy)) ? dx : dy  );
 const int ddep = IABS(  (IABS(dx) > IABS(dy)) ? dy : dx  );

 int inc = ((dx * dy) < 0) ? -1 : 1;

 int d = 2 * ddep - dind;//2dy - dx

 while (*ind <= limit)
 {
  plot(rawImage, qx, qy, color);

  if (d >= 0)
  {
   (*dep) += inc;
   d -= dind;
  }

  d += ddep;
  (*ind) ++;
 }
}


void writeInt(FILE* out, uint num, uint bytes)
{
 fwrite(&num, 1, bytes, out);
}
#define writeI(num, i) writeInt(out, num, i)
#define write1(num)    writeI(num, 1)
#define write2(num)    writeI(num, 2)
#define write3(num)    writeI(num, 3)
#define write4(num)    writeI(num, 4)
#define LINE           (dWidth * 3)
#define PITCH          ((LINE & 3) ? ((LINE & ~3) + 4) : LINE)
void saveBMP(FILE* out, void* rawImage)
{
 uint size = PITCH * dHeight;
 int x, y;
 write2(0x4D42);
 write4(14 + 40 + size);
 write4(0);
 write4(14 + 40);
 write4(40);
 write4(dWidth);
 write4(dHeight);
 write4(0x00180001);
 write4(0);
 write4(size);
 write4(0);
 write4(0);
 write4(0);
 write4(0);
 for (y = (dHeight - 1); y >= 0; y--)
 {
  for (x = 0; x < dWidth; x++)
   write3(PIXEL(x, y));
  writeI(0, PITCH - LINE);
 }
}

void destroyPoints(Points points)
{
 free(points.pointList);
}

void drawLines(void* image, Points points)
{
 while (points.pointCount--)
 {
  int i1 = points.pointCount--;
  int i2 = points.pointCount;

  draw_line((int)points.pointList[i1].data[0], (int)points.pointList[i1].data[1],
            (int)points.pointList[i2].data[0], (int)points.pointList[i2].data[1],
            image, RGB(255, 255, 255));
 }
}

void draw(void* image)
{
 clear(image);
 drawLines(image, points);
}














void initMatrix(Matrix* matrix, int rows, int cols)
{
 if ((rows > 4) || (cols > 4))
 {
  printf("What's the need for a matrix bigger than 4x4?\n");
  return;
 }

 int i;

 matrix->rows = rows;
 matrix->cols = cols;
 for (i = 0; i < 16; i++)
  matrix->data[i] = 0.0;
}

void addPoint(Points* points, double x, double y, double z)
{
 if (points->pointCount >= points->pointCap)
 {
  points->pointCap += 10;
  points->pointList = realloc(points->pointList, points->pointCap * sizeof(Matrix));
 }


 points->pointList[points->pointCount].rows = 4;
 points->pointList[points->pointCount].cols = 1;
 points->pointList[points->pointCount].data[0] = x;
 points->pointList[points->pointCount].data[1] = y;
 points->pointList[points->pointCount].data[2] = z;
 points->pointList[points->pointCount].data[3] = 1.0;

 points->pointCount++;
}

double* getMatrixCell(Matrix* m, int row, int col)
{
 if (row < 0) return NULL;
 if (col < 0) return NULL;
 if (row >= m->rows) return NULL;
 if (col >= m->cols) return NULL;

 return &m->data[(row * m->cols) + col];
}

void printMatrix(Matrix* m)
{
 int row, col;
 for (row = 0; row < m->rows; row++)
 {
  for (col = 0; col < m->cols; col++)
   printf("%f ", *getMatrixCell(m, row, col));

  printf("\n");
 }
}

int identityMatrix(Matrix* m)
{
 if (m->rows != m->cols)
  return -1;

 int row, col;
 for (row = 0; row < m->rows; row++)
 {
  for (col = 0; col < m->cols; col++)
  {
   if (row == col)
    *getMatrixCell(m, row, col) = 1.0;
   else
    *getMatrixCell(m, row, col) = 0.0;
  }
 }

 return 0;
}

void multiplyMatrix(Matrix* result, Matrix* m, double d)
{
 result->rows = m->rows;
 result->cols = m->cols;

 int i;
 for (i = 0; i < (m->rows * m->cols); i++)
  result->data[i] = m->data[i] * d;
}

int multiplyMatrices(Matrix* result, Matrix* m1, Matrix* m2)
{
 if (m1->cols != m2->rows)
  return -1;

 int limit = m1->cols;
 int row, col, i;

 result->rows = m1->rows;
 result->cols = m2->cols;

 for (row = 0; row < result->rows; row++)
 {
  for (col = 0; col < result->cols; col++)
  {
   double r = 0.0;
   for (i = 0; i < limit; i++)
   {
    r += (*getMatrixCell(m1, row, i)) * (*getMatrixCell(m2, i, col));
   }
   *getMatrixCell(result, row, col) = r;
  }
 }

 return 0;
}

void copyMatrix(Matrix* dst, const Matrix* src)
{
 *dst = *src;
}

void apply(Points points, Matrix* m)
{
 Matrix res;
 while (points.pointCount--)
 {
  multiplyMatrices(&res, m, &points.pointList[points.pointCount]);
  points.pointList[points.pointCount] = res;
 }
}


void makeTranslate(Matrix* dst, double x, double y, double z)
{
 dst->rows = dst->cols = 4;
 memcpy(dst->data,
 (double[]){
  1.0, 0.0, 0.0, x,
  0.0, 1.0, 0.0, y,
  0.0, 0.0, 1.0, z,
  0.0, 0.0, 0.0, 1.0,
 },
 sizeof(double) * 16);
}

void makeScale(Matrix* dst, double x, double y, double z)
{
 dst->rows = dst->cols = 4;
 memcpy(dst->data,
 (double[]){
  x,   0.0, 0.0, 0.0,
  0.0, y,   0.0, 0.0,
  0.0, 0.0, z,   0.0,
  0.0, 0.0, 0.0, 1.0,
 },
 sizeof(double) * 16);
}

void makeRotX(Matrix* dst, int deg)
{
 double s = sin(deg * M_PI / 180.0);
 double c = cos(deg * M_PI / 180.0);
 dst->rows = dst->cols = 4;
 memcpy(dst->data,
 (double[]){
  1.0, 0.0, 0.0, 0.0,
  0.0, c,   -s,  0.0,
  0.0, s,   c,   0.0,
  0.0, 0.0, 0.0, 1.0,
 },
 sizeof(double) * 16);
}

void makeRotY(Matrix* dst, int deg)
{
 double s = sin(deg * M_PI / 180.0);
 double c = cos(deg * M_PI / 180.0);
 dst->rows = dst->cols = 4;
 memcpy(dst->data,
 (double[]){
  c,   0.0, s,   0.0,
  0.0, 1.0, 0.0, 0.0,
  -s,  0.0, c,   0.0,
  0.0, 0.0, 0.0, 1.0,
 },
 sizeof(double) * 16);
}

void makeRotZ(Matrix* dst, int deg)
{
 double s = sin(deg * M_PI / 180.0);
 double c = cos(deg * M_PI / 180.0);
 dst->rows = dst->cols = 4;
 memcpy(dst->data,
 (double[]){
  c,   -s,  0.0, 0.0,
  s,   c,   0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0,
 },
 sizeof(double) * 16);
}

void addPoints(Points vertices, int limit)
{
 int i;
 for (i = 0; i < limit; i++)
 {
  addPoint(&points,
           vertices.pointList[i].data[0],
           vertices.pointList[i].data[1],
           vertices.pointList[i].data[2]);
  addPoint(&points,
           vertices.pointList[(i + 1) % vertices.pointCount].data[0],
           vertices.pointList[(i + 1) % vertices.pointCount].data[1],
           vertices.pointList[(i + 1) % vertices.pointCount].data[2]);
 }
}

inline void addCurve(Points vertices)
{
 addPoints(vertices, vertices.pointCount - 1);
}

inline void addPolygon(Points vertices)
{
 addPoints(vertices, vertices.pointCount);
}

Points createCircle(int radius, int x, int y, double step)
{
 double t;
 double cX, cY;

 Points rt;
 memset(&rt, 0, sizeof(Points));

 for (t = 0.0; t < 1.0; t += step)
 {
  cX = radius * cos(t * M_PI * 2) + x;
  cY = radius * sin(t * M_PI * 2) + y;
  addPoint(&rt, cX, cY, 0.0);
 }

 return rt;
}

Points createHermite(int* x, int* y, double step)
{
 double t;
 double cX, cY;

 Points rt;
 memset(&rt, 0, sizeof(Points));

 for (t = 0.0; t <= 1.0; t += step)
 {
  const double coefP0 =  (2.0 * pow(t, 3.0)) - (3.0 * pow(t, 2.0)) + 1.0;
  const double coefP1 = -(2.0 * pow(t, 3.0)) + (3.0 * pow(t, 2.0));

  const double coefC0 = pow(t, 3.0) - (2.0 * pow(t, 2.0)) + t;
  const double coefC1 = pow(t, 3.0) -        pow(t, 2.0);

  cX = (coefP0 * x[0]) + (coefC0 * x[1]) + (coefP1 * x[2]) + (coefC1 * x[3]);
  cY = (coefP0 * y[0]) + (coefC0 * y[1]) + (coefP1 * y[2]) + (coefC1 * y[3]);
  addPoint(&rt, cX, cY, 0.0);
 }

 return rt;
}

Points createBezier(int* x, int* y, double step)
{
 double t;
 double cX, cY;

 Points rt;
 memset(&rt, 0, sizeof(Points));

 for (t = 0.0; t <= 1.0; t += step)
 {
  const double coefP0 = pow(1.0 - t, 3.0);
  const double coefP1 = pow(t,       3.0);

  const double coefC0 = 3 * pow(1 - t, 2.0) * t;
  const double coefC1 = 3 * pow(t, 2.0) * (1 - t);

  cX = (coefP0 * x[0]) + (coefC0 * x[1]) + (coefP1 * x[2]) + (coefC1 * x[3]);
  cY = (coefP0 * y[0]) + (coefC0 * y[1]) + (coefP1 * y[2]) + (coefC1 * y[3]);
  addPoint(&rt, cX, cY, 0.0);
 }

 return rt;
}

void addCircle(int radius, int x, int y, double step)
{
 Points circle = createCircle(radius, x, y, step);
 addPolygon(circle);
 destroyPoints(circle);
}

void addHermite(int* x, int* y, double step)
{
 Points hermite = createHermite(x, y, step);
 addCurve(hermite);
 destroyPoints(hermite);
}

void addBezier(int* x, int* y, double step)
{
 Points bezier = createBezier(x, y, step);
 addCurve(bezier);
 destroyPoints(bezier);
}

void whirlCircle(int radius, int cx, int cy, int x, int y, int step, int limit)
{
 Points circle = createCircle(radius, cx, cy, .05);
 Matrix tempPoints[circle.pointCount];

 Matrix trans;
 Matrix m;
 Matrix m2;

 initMatrix(&trans, 4, 4);
 identityMatrix(&trans);

 makeTranslate(&m, -x, -y, 0.0);
 multiplyMatrices(&m2, &m, &trans);
 trans = m2;

 makeRotY(&m, step);
 multiplyMatrices(&m2, &m, &trans);
 trans = m2;

 makeTranslate(&m, x, y, 0.0);
 multiplyMatrices(&m2, &m, &trans);
 trans = m2;

 int i, j;

 for (i = 0; i < (limit / step); i++)
 {
  memcpy(tempPoints, circle.pointList, circle.pointCount * sizeof(Matrix));
  apply(circle, &trans);
  addPolygon(circle);

  for (j = 0; j < circle.pointCount; j++)
  {
   addPoint(&points,
            tempPoints[j].data[0],
            tempPoints[j].data[1],
            tempPoints[j].data[2]);
   addPoint(&points,
            circle.pointList[j].data[0],
            circle.pointList[j].data[1],
            circle.pointList[j].data[2]);
  }
 }

 destroyPoints(circle);
}

inline void addSphere(int radius, int x, int y)
{
 whirlCircle(radius, x, y, x, y, 15, 180);
}

inline void addTorus(int wholeR, int circR, int x, int y)
{
 whirlCircle(circR, x + wholeR - circR, y, x, y, 15, 360);
}

void interpret(void* image)
{
 memset(&points, 0, sizeof(Points));

 Matrix m;
 initMatrix(&m, 4, 4);

 Matrix s;
 Matrix res;

 FILE* out;

 char command;
 int x[4];
 int y[4];
 int z[4];
 int deg, deg2;
 int i;

 double t;

 char fname[64];

 while (1)
 {
  if (scanf("%c", &command) < 0)
   break;

  switch (command)
  {
   case 'l':
    i = scanf("%i %i %i %i %i %i", &x[0], &y[0], &z[0], &x[1], &y[1], &z[1]);
    addPoint(&points, x[0], y[0], z[0]);
    addPoint(&points, x[1], y[1], z[1]);
    break;
   case 'c':
    i = scanf("%i %i %i %lf", &deg, &x[0], &y[0], &t);
    addCircle(deg, x[0], y[0], t);
    break;
   case 'm':
    i = scanf("%i %i %i", &deg, &x[0], &y[0]);
    addSphere(deg, x[0], y[0]);
    break;
   case 'd':
    i = scanf("%i %i %i %i", &deg, &deg2, &x[0], &y[0]);
    addTorus(deg, deg2, x[0], y[0]);
    break;
   case 'h':
    i = scanf("%i %i %i %i %i %i %i %i", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3]);
    addHermite(x, y, .05);
    break;
   case 'b':
    i = scanf("%i %i %i %i %i %i %i %i", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3]);
    addBezier(x, y, .05);
    break;
   case 'i':
    identityMatrix(&m);
    break;
   case 's':
    i = scanf("%i %i %i", &x[0], &y[0], &z[0]);
    makeScale(&s, x[0], y[0], z[0]);
    multiplyMatrices(&res, &s, &m);
    m = res;
    break;
   case 't':
    i = scanf("%i %i %i", &x[0], &y[0], &z[0]);
    makeTranslate(&s, x[0], y[0], z[0]);
    multiplyMatrices(&res, &s, &m);
    m = res;
    break;
   case 'x':
    i = scanf("%i", &deg);
    makeRotX(&s, deg);
    multiplyMatrices(&res, &s, &m);
    m = res;
    break;
   case 'y':
    i = scanf("%i", &deg);
    makeRotY(&s, deg);
    multiplyMatrices(&res, &s, &m);
    m = res;
    break;
   case 'z':
    i = scanf("%i", &deg);
    makeRotZ(&s, deg);
    multiplyMatrices(&res, &s, &m);
    m = res;
    break;
   case 'a':
    apply(points, &m);
    break;
   case 'v':
    draw(image);

    out = popen("display -", "w");
    saveBMP(out, image);
    pclose(out);

    break;
   case 'g':
    i = scanf("%s", fname);
    if (!(strchr(fname, '.') && (!strcasecmp(strrchr(fname, '.'), ".bmp"))))
     strcat(fname, ".bmp");
    draw(image);

    out = fopen(fname, "wb");
    saveBMP(out, image);
    fclose(out);

    printf("Saved to %s!\n", fname);
    break;
  }
 }
}
int main(int argc, char** argv)
{
 if ((argc > 1) && strchr(argv[1], 'x'))
 {
  int w = atoi(argv[1]);
  int h = atoi(strchr(argv[1], 'x') + 1);
  if ((w <= 0) || (h <= 0))
   fprintf(stderr, "Invalid dimensions entered, keeping resolution at %ix%i\n", dWidth, dHeight);
  else
   fprintf(stderr, "Resolution changed to %ix%i\n", dWidth = w, dHeight = h);
 }
 void* pixels = malloc(4 * dWidth * dHeight);
 interpret(pixels);
 free(pixels);
 return 0;
}

