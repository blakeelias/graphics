#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
 
  
  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;
  
  clear_screen(s);
  struct matrix *m;
  struct matrix *points = new_matrix(4,1);
  int x0, y0, z0, x1, y1, z1;
  char letter;
  char *filename;
  filename = malloc(256 * sizeof(char));
  while(1)
    {
      scanf("%s",&letter);
      switch(letter)
	{
	case 'l':
	  scanf("%d %d %d %d %d %d", &x0,&y0,&z0,&x1,&y1,&z1);
	  add_edge(points , x0, y0, z0, x1, y1, z1);
	  print_matrix(points);
	  printf("case l\n");
	  break;
	case 'i':
	  ident(m);
	  printf("case i\n");
	  break;
	case 's':
	  scanf("%d %d %d", &x0, &y0,&z0);
	  m = make_scale(x0, y0, z0);
	  print_matrix(m);
	  printf("case s\n");
	  break;
	case 't':
	  scanf("%d %d %d", &x0, &y0, &z0);
	  m = make_translate(x0 , y0, z0);
	  print_matrix(m);
	  printf("case t\n");
	  break;
	case 'x':
	  scanf("%d" , &x0);
	  m = make_rotX(y0);
	  printf("case x\n");
	  break;
	case 'y':
	  scanf("%df" , &y0);
	  m = make_rotY(y0);
	  printf("case y\n");
	  break;
	case 'z':
	  scanf("%d" , &z0);
	  m = make_rotZ(z0);
	  break;
	case 'a':
	  matrix_mult(m, points);
	  printf("case a\n");
	  break;
	case 'v':
	  print_matrix(points);
	  clear_screen(s);
	  draw_lines(points, s , c);
	  display(s);
	  printf("displayed\n");
	  break;
	case 'g':
	  scanf("%s" , &filename);
	  printf("%s" , filename);
	  save_extension(s, filename);
	  printf("case g\n");
	  break;
	}
    }
  //octant 1
  draw_line(0, 0, XRES-1, YRES - 75, s, c);
  //octant 2
  draw_line(0, 0, XRES - 75, YRES-1, s, c);
  //octant 8
  draw_line(0, YRES-1, XRES-1, 75, s, c);
  //octant 7
  draw_line(0, YRES-1, XRES - 75, 0, s, c);

  c.green = 0;
  c.blue = MAX_COLOR;
  //octant 5
  draw_line(XRES - 1, YRES - 1, 0, 75, s, c);
  //octant 6
  draw_line(XRES - 1, YRES -1, 75, 0, s, c);
  //octant 4
  draw_line(XRES - 1, 0, 0, YRES - 75, s, c);
  //octant 3
  draw_line(XRES - 1, 0, 75, YRES - 1, s, c);
  
  c.blue = 0;
  c.red = MAX_COLOR;
  //y = x, y = -x
  draw_line(0, 0, XRES - 1, YRES - 1, s, c);
  draw_line(0, YRES - 1, XRES - 1, 0, s, c);

  //horizontal, vertical line
  draw_line(0, YRES / 2, XRES - 1, YRES / 2, s, c);
  draw_line(XRES / 2, 0, XRES / 2, YRES - 1, s, c);
  
  display(s);
  
  save_extension(s, "1.png");

  return;
}
