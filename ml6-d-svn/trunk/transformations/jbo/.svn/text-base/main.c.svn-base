#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"

void parse_file(char *filename, struct matrix *transform, struct matrix *pm, screen s);
color get_white();

int main() {
  //printf("START\n"); ////////////////
  
  struct matrix *m = new_matrix(4, 4);
  struct matrix *points = new_matrix(4, 0);
  
  screen s;
  
  parse_file("script", m, points, s);
  
  //print_matrix(points);

  //The following tests various matrix functions
  /*
  m = make_translate(1, 2, 3);
  print_matrix(m);
  printf("\n");
  
  m = make_rotX(30);
  print_matrix(m);
  printf("\n");
  
  m = make_rotY(30);
  print_matrix(m);
  printf("\n");
  
  m = make_rotZ(30);
  print_matrix(m);
  printf("\n");
  
  m = make_scale(1, 2, 3);
  print_matrix(m);
  printf("\n");
  */
  
  free_matrix(m);
  free_matrix(points);
  
  return 0;
}

void parse_file (char *filename, struct matrix *transform, struct matrix *pm, screen s) {
  int n = 1024, i;
  char *string_buf;
  float point_buf[6];
  string_buf = (char *) malloc(sizeof(char) * n);
  FILE *script = fopen(filename, "r");
  
  while (getline(&string_buf, &n, script) != -1) {
    switch(string_buf[0]) {
    
      case 'l':
        for (i = 0; i < 5; i++) {
          getdelim(&string_buf, &n, ' ', script);
          point_buf[i] = atoi(string_buf);
        }
        getline(&string_buf, &n, script);
        point_buf[5] = atoi(string_buf);
        add_edge(pm, point_buf[0], point_buf[1], point_buf[2], point_buf[3], point_buf[4], point_buf[5]);\
        break;
        
      case 'i':
        ident(transform);
        break;
      
      case 's':
        getdelim(&string_buf, &n, ' ', script);
        point_buf[0] = atof(string_buf);
        getdelim(&string_buf, &n, ' ', script);
        point_buf[1] = atof(string_buf);
        getline(&string_buf, &n, script);
        point_buf[2] = atof(string_buf);
        matrix_mult(make_scale(point_buf[0], point_buf[1], point_buf[2]), transform);
        break;
        
      case 't':
        getdelim(&string_buf, &n, ' ', script);
        point_buf[0] = atoi(string_buf);
        getdelim(&string_buf, &n, ' ', script);
        point_buf[1] = atoi(string_buf);
        getline(&string_buf, &n, script);
        point_buf[2] = atoi(string_buf);
        matrix_mult(make_translate(point_buf[0], point_buf[1], point_buf[2]), transform);
        break;
        
      case 'x':
        getline(&string_buf, &n, script);
        matrix_mult(make_rotX(atof(string_buf)), transform);
        break;
        
      case 'y':
        getline(&string_buf, &n, script);
        matrix_mult(make_rotY(atof(string_buf)), transform);
        break;
        
      case 'z':
        getline(&string_buf, &n, script);
        matrix_mult(make_rotZ(atof(string_buf)), transform);
        break;
        
      case 'a':
        //print_matrix(transform); printf("\n"); //////////////////
        matrix_mult(transform, pm);
        //print_matrix(pm); printf("\n"); ///////////////
        break;
      
      case 'v':
        clear_screen(s);
        draw_lines(pm, s, get_white());
        display(s);
        break;
        
      case 'g':
        clear_screen(s);
        draw_lines(pm, s, get_white());
        getline(&string_buf, &n, script);
        save_extension(s, string_buf);
        break;
      
      default:
        break;
    }
  }
  
  free(string_buf);
  fclose(script);
}

color get_white() {
  color c;
  c.red = 255;
  c.green = 255;
  c.blue = 255;
  return c;
}
