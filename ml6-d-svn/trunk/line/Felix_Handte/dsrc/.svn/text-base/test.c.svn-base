#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

int main(int argc, char *argv[]){

  screen s;
  color c, r, g, b;
 
  #ifndef ALL_WHITE
  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;
  
  r.red = MAX_COLOR;
  r.green = 0;
  r.blue = 0;
  
  g.red = 0;
  g.green = MAX_COLOR;
  g.blue = 0;
  
  b.red = 0;
  b.green = 0;
  b.blue = MAX_COLOR;
  #else
  c.red   = r.red   = g.red   = b.red   = MAX_COLOR;
  c.green = r.green = g.green = b.green = MAX_COLOR;
  c.blue  = r.blue  = g.blue  = b.blue  = MAX_COLOR;
  #endif
  
  clear_screen(s);
  
  ///*
  
  void (*draw_function)(int, int, int, int, screen, color);
  
  if(argc < 2 || strcmp(argv[1], "-a")){
  	draw_function = &draw_line;
  } else {
  	draw_function = &draw_line_aa;
  }
  draw_function(10, 10, 10, 10, s, r);
  draw_function(10, 15, 20, 15, s, r);
  draw_function(10, 20, 20, 20, s, g);
  draw_function(10, 19, 20, 19, s, b);
  draw_function(10, 21, 20, 21, s, r);
  
  draw_function(10, 30, 10, 40, s, g);
  draw_function(11, 30, 11, 40, s, b);
  draw_function( 9, 30,  9, 40, s, r);
  
  draw_function(10, 30, 10, 40, s, g);
  draw_function(11, 30, 11, 40, s, b);
  draw_function( 9, 30,  9, 40, s, r);
  
  draw_function( 9, 30,  9, 40, s, r);
  
  draw_function(50, 50, 60, 60, s, r);
  draw_function(51, 50, 61, 60, s, g);
  draw_function(52, 50, 62, 60, s, b);
  
  draw_function(62, 50, 72, 60, s, r);
  draw_function(61, 50, 71, 60, s, g);
  draw_function(60, 50, 70, 60, s, b);
  
  draw_function(10, 50, 30, 60, s, r);
  draw_function(11, 50, 31, 60, s, g);
  draw_function(12, 50, 32, 60, s, b);
  
  draw_function(22, 50, 42, 60, s, r);
  draw_function(21, 50, 41, 60, s, g);
  draw_function(20, 50, 40, 60, s, b);
  
  draw_function( 10, 70, 30, 80, s, r);
  draw_function( 30, 70, 60, 80, s, r);
  draw_function( 50, 70, 90, 80, s, r);
  draw_function( 70, 70,120, 80, s, r);
  draw_function( 90, 70,150, 80, s, r);
  draw_function(110, 70,180, 80, s, r);
  draw_function(130, 70,210, 80, s, r);
  draw_function(150, 70,240, 80, s, r);
  
  draw_function(10, 90, 40, 110, s, r);
  draw_function(40, 90, 10, 110, s, g);
  draw_function(15, 90, 15, 110, s, b);
  
  draw_function(10, 120, 20, 130, s, r);
  draw_function(15, 120, 25, 130, s, g);
  draw_function(20, 120, 30, 130, s, b);
  
  draw_function(0, 0, XRES - 1, 0, s, r);
  draw_function(0, 0, 0, YRES - 1, s, r);
  draw_function(XRES - 1, 0, XRES - 1, YRES - 1, s, r);
  draw_function(0, YRES - 1, XRES - 1, YRES - 1, s, r);
  
  //draw_function(0, YRES - 1, XRES - 1, 0, s, g);
  draw_function((XRES - 1) / 2, 0, (XRES - 1) / 2, YRES - 1, s, b);
  draw_function(0, (YRES - 1) / 2, XRES - 1, (YRES - 1) / 2, s, b);
  
  int i, j;
  for(i = 200; i <= 400; i += 10){
  	for(j = 200; j <= 400; j += 10){
  		draw_function(300, 300, i, j, s, r);
  	}
  }
  
  /*
  
  draw_function(25, 210, 175, 210, s, r);
  draw_function(25, 215, 175, 216, s, r);
  draw_function(25, 220, 175, 222, s, r);
  draw_function(25, 225, 175, 228, s, r);
  draw_function(25, 230, 175, 234, s, r);
  draw_function(25, 235, 175, 240, s, r);
  draw_function(25, 240, 175, 246, s, r);
  draw_function(25, 245, 175, 252, s, r);
  draw_function(25, 250, 175, 258, s, r);
  draw_function(25, 255, 175, 264, s, r);
  draw_function(25, 260, 175, 270, s, r);
  draw_function(25, 265, 175, 276, s, r);
  draw_function(25, 270, 175, 282, s, r);
  draw_function(25, 275, 175, 288, s, r);
  draw_function(25, 275, 175, 288, s, r);
  
  */
  
  for(i = 0; i < 30; i++){
  	draw_function(20, 210 + 5 * i, 170, 210 + 6 * i, s, g);
  	draw_function(25 + 5 * i, 205, 25 + 6 * i, 355, s, r);
  }
  
  /*
  
  draw_function(300, 300, 300, 350, s, r);
  draw_function(300, 300, 325, 350, s, r);
  draw_function(300, 300, 350, 350, s, r);
  draw_function(300, 300, 350, 325, s, r);
  draw_function(300, 300, 350, 300, s, r);
  draw_function(300, 300, 350, 275, s, r);
  draw_function(300, 300, 350, 250, s, r);
  draw_function(300, 300, 325, 250, s, r);
  draw_function(300, 300, 300, 250, s, r);
  draw_function(300, 300, 275, 250, s, r);
  draw_function(300, 300, 250, 250, s, r);
  draw_function(300, 300, 250, 275, s, r);
  draw_function(300, 300, 250, 300, s, r);
  draw_function(300, 300, 250, 325, s, r);
  draw_function(300, 300, 250, 350, s, r);
  draw_function(300, 300, 275, 350, s, r);
  
  */
  
  //*/

  /*
  
  //octant 1
  draw_function(0, 0, XRES-1, YRES - 75, s, c);
  //octant 2
  draw_function(0, 0, XRES - 75, YRES-1, s, c);
  //octant 8
  draw_function(0, YRES-1, XRES-1, 75, s, c);
  //octant 7
  draw_function(0, YRES-1, XRES - 75, 0, s, c);

  c.green = 0;
  c.blue = MAX_COLOR;
  //octant 5
  draw_function(XRES - 1, YRES - 1, 0, 75, s, c);
  //octant 6
  draw_function(XRES - 1, YRES -1, 75, 0, s, c);
  //octant 4
  draw_function(XRES - 1, 0, 0, YRES - 75, s, c);
  //octant 3
  draw_function(XRES - 1, 0, 75, YRES - 1, s, c);
  
  c.blue = 0;
  c.red = MAX_COLOR;
  //y = x, y = -x
  draw_function(0, 0, XRES - 1, YRES - 1, s, c);
  draw_function(0, YRES - 1, XRES - 1, 0, s, c);

  //horizontal, vertical line
  draw_function(0, YRES / 2, XRES - 1, YRES / 2, s, c);
  draw_function(XRES / 2, 0, XRES / 2, YRES - 1, s, c);
  
  c.red = MAX_COLOR;
  c.green = MAX_COLOR;
  c.blue = MAX_COLOR;
  
  draw_function(XRES / 2, 0, 0, YRES / 2, s, c);
  draw_function(XRES / 2, YRES / 4, XRES / 4, YRES / 2, s, c);
  
  */
  
  display(s);
  
  save_extension(s, "1.png");

  return 0;
}
