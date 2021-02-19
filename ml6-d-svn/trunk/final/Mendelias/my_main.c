#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "parametrics.h"
#include "splines.h"
//#include "cmd_processor.c"


void my_main( int polygons ) {

  /*
  int testing = front_face(0,0,0, 0,1,0, 1,0,0, 0,0,1);
  if (testing)
    printf("We have a front face\n");
  else
    printf("We have a back face\n");
  */

  struct matrix *transformation;
  struct matrix *points;
  screen s;
  color c;
  c.red = 0;
  c.green = 0;
  c.blue = 255;

  transformation = new_matrix(4, 4);
  ident(transformation);
  clear_screen(s);

  cmd_processor(points, s);
  
}
