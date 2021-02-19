#ifndef ML6_H
#define ML6_H

#define XRES 400
#define YRES 400
#define MAX_COLOR 255

struct point {
  //int alpha;
  int red;
  int green;
  int blue;
};

typedef struct point color;
typedef struct point screen[XRES + 1][YRES + 1];

#endif
