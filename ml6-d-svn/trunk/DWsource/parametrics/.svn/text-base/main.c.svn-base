#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "parametrics.h"

int main() {

  struct matrix *points;
  screen s;
  color g;
 
  points = new_matrix(4, 25);

 
  g.red = 0;
  g.blue = 255;
  g.green = 255;


  clear_screen(s);  
  render_parametric(points, *squarex, *barty, .01);
  draw_lines(points, s, g);
  display(s);

  /*
  clear_screen(s);  
  render_parametric(points, *line_x, *line_y, .1);
  draw_lines(points, s, g);
  display(s);

  clear_screen(s);  
  render_parametric(points, *square_x, *square_y, .01);
  draw_lines(points, s, g);
  display(s);

  render_parametric(points, *circle_x, *circle_y, .05);
  draw_lines(points, s, g);
  display(s);
  */


  free_matrix(points);

  return 0;
}
