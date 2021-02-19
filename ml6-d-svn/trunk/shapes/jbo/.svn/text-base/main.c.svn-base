#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "geo.h"
#include "matrix.h"
#include "ui.h"

int flag;
SDL_TimerID timerID;
SDL_Event event;

struct matrix *m;
struct shape *universe;

void parse_file(char *filename, struct matrix *transform, struct shape *u);
Uint32 timer_callback(Uint32 interval, void *param);
void processEvents();
void terminate();

int main(int argc, char **argv) {
  initWindow();
  
  m = matrix_newMatrix(4, 4);
  universe = geo_newShape(65536, 65536);
  
  timerID = SDL_AddTimer(20, timer_callback, &flag);
  
  parse_file("script", m, universe);
  
  terminate();
  
  return 0;
}

void parse_file(char *filename, struct matrix *transform, struct shape *u) {
  int i, loop_char_count, temp;
  size_t n = 1024;
  char *string_buf;
  double point_buf1[3], point_buf2[3];
  double big_buf[8];
  int edge_buf[2];
  string_buf = (char *) malloc(sizeof(char) * n);
  FILE *script = fopen(filename, "r");
  
  temp = getline(&string_buf, &n, script);
  while (temp != -1) {
    
    loop_char_count += temp;
    //printf("%c\n", string_buf[0]); ////////////////////
    switch(string_buf[0]) {
      
      case '/':
        break;
        
      case '{':
        loop_char_count = 0;
        break;
        
      case '}':
        fseek(script, -1 * loop_char_count, SEEK_CUR);
        loop_char_count = 0;
        break;
        
      case 'p':
        for (i = 0; i < 2; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf1[i] = atof(string_buf);
        }
        loop_char_count += getline(&string_buf, &n, script);
        point_buf1[2] = atof(string_buf);
        geo_addPoint(u, point_buf1);
        break;
        
      case 'e':
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        edge_buf[0] = atoi(string_buf);
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        edge_buf[1] = atoi(string_buf);
        geo_addEdge(u, edge_buf[0], edge_buf[1]);
        break;
        
      case 'l':
        for (i = 0; i < 3; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf1[i] = atof(string_buf);
        }
        for (i = 0; i < 2; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf2[i] = atof(string_buf);
        }
        loop_char_count += getline(&string_buf, &n, script);
        point_buf2[2] = atof(string_buf);
        
        geo_addLine(u, point_buf1, point_buf2);
        break;
      
      case 'c':
        for (i = 0; i < 3; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf1[i] = atof(string_buf);
        }
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        big_buf[0] = atof(string_buf);
        for (i = 0; i < 3; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf2[i] = atof(string_buf);
        }
        loop_char_count += getline(&string_buf, &n, script);
        edge_buf[0] = atof(string_buf);
        geo_concatenate(u, geo_makeCircle(point_buf1, big_buf[0], point_buf2, edge_buf[0]));
        break;
        
      case 'm':
        for (i = 0; i < 3; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf1[i] = atof(string_buf);
        }
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        big_buf[0] = atof(string_buf);
        for (i = 0; i < 3; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf2[i] = atof(string_buf);
        }
        loop_char_count += getline(&string_buf, &n, script);
        edge_buf[0] = atof(string_buf);
        geo_concatenate(u, geo_makeSphere(point_buf1, big_buf[0], point_buf2, edge_buf[0]));
        break;
      
      case 'd':
        for (i = 0; i < 3; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf1[i] = atof(string_buf);
        }
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        big_buf[0] = atof(string_buf);
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        big_buf[1] = atof(string_buf);
        for (i = 0; i < 3; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          point_buf2[i] = atof(string_buf);
        }
        loop_char_count += getline(&string_buf, &n, script);
        edge_buf[0] = atof(string_buf);
        geo_concatenate(u, geo_makeTorus(point_buf1, big_buf[0], big_buf[1], point_buf2, edge_buf[0]));
        break;
      
      case 'h':
      	for (i = 0; i < 7; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          big_buf[i] = atof(string_buf);
        }
        loop_char_count += getline(&string_buf, &n, script);
        big_buf[7] = atof(string_buf);
        geo_concatenate(u, geo_makeHermite(big_buf[0], big_buf[1], big_buf[2] - big_buf[0], big_buf[3] - big_buf[1], big_buf[4], big_buf[5], big_buf[6] - big_buf[4], big_buf[7] - big_buf[5]));
      	break;
      	
    	case 'b':
    		for (i = 0; i < 7; i++) {
          loop_char_count += getdelim(&string_buf, &n, ' ', script);
          big_buf[i] = atof(string_buf);
        }
        loop_char_count += getline(&string_buf, &n, script);
        big_buf[7] = atof(string_buf);
        geo_concatenate(u, geo_makeBezier(big_buf[0], big_buf[1], big_buf[2], big_buf[3], big_buf[6], big_buf[7], big_buf[4], big_buf[5]));
    		break;
        
      case 'i':
        matrix_ident(transform);
        break;
      
      case 's':
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        point_buf1[0] = atof(string_buf);
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        point_buf1[1] = atof(string_buf);
        loop_char_count += getline(&string_buf, &n, script);
        point_buf1[2] = atof(string_buf);
        matrix_matrixMult(matrix_makeScale(point_buf1[0], point_buf1[1], point_buf1[2]), transform);
        break;
        
      case 't':
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        point_buf1[0] = atoi(string_buf);
        loop_char_count += getdelim(&string_buf, &n, ' ', script);
        point_buf1[1] = atoi(string_buf);
        loop_char_count += getline(&string_buf, &n, script);
        point_buf1[2] = atoi(string_buf);
        matrix_matrixMult(matrix_makeTranslate(point_buf1[0], point_buf1[1], point_buf1[2]), transform);
        break;
        
      case 'x':
        loop_char_count += getline(&string_buf, &n, script);
        matrix_matrixMult(matrix_makeRotX(atof(string_buf)), transform);
        break;
        
      case 'y':
        loop_char_count += getline(&string_buf, &n, script);
        matrix_matrixMult(matrix_makeRotY(atof(string_buf)), transform);
        break;
        
      case 'z':
        loop_char_count += getline(&string_buf, &n, script);
        matrix_matrixMult(matrix_makeRotZ(atof(string_buf)), transform);
        break;
        
      case 'a':
        //print_matrix(transform); printf("\n"); //////////////////
        matrix_matrixMult(transform, u->points);
        //print_matrix(pm); printf("\n"); ///////////////
        break;
      
      case 'v':
        flag = 1;
        //printf("v\n");
        draw_all(u->points, u->edges, u->numEdges, 255, 255, 255);
        updateScreen();
        while (flag) {
          processEvents();
        }
        clearScreen();
        break;
      
      default:
        break;
    }
    temp = getline(&string_buf, &n, script);
  }
  
  free(string_buf);
  fclose(script);
}

void processEvents() {
  //printf("Polling...\n");
  while (SDL_PollEvent(&event)) {
    //printf("Event!\n");
    switch(event.type) {
    
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          printf("left down %d %d\n", event.button.x, event.button.y);
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
          printf("right down %d %d\n", event.button.x, event.button.y);
          SDL_WM_ToggleFullScreen(screen);
        }
        break;
        
     
      case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
          printf("left up %d %d\n", event.button.x, event.button.y);
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
          printf("right up %d %d\n", event.button.x, event.button.y);
        }
        break;
     
        
      case SDL_QUIT:
        terminate();
        break;
    }
  }
}

Uint32 timer_callback(Uint32 interval, void *param) {
  //printf("callback\n");
  *((int *) param) = 0;
  return interval;
}

void terminate() {
  matrix_freeMatrix(m);
  geo_freeShape(universe);
  exit(EXIT_SUCCESS);
}
