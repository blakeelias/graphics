#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
//#include <errno.h>
#include "draw.h"
#include "matrix.h"
#include "ui.h"

//extern int errno;

int flag;
SDL_TimerID timerID;
SDL_Event event;

//struct timespec *tp;
//long nsec_total;

void parse_file(char *filename, struct matrix *transform, struct matrix *pm, int *lines);
Uint32 timer_callback(Uint32 interval, void *param);
void processEvents();

int main(int argc, char **argv) {
  //printf("START\n");
  /*
  tp = (struct timespec *) malloc(sizeof(struct timespec));
  int err = clock_gettime(CLOCK_REALTIME, tp);
  nsec_total = tp->tv_nsec;
  */
  
  initWindow();
  
  struct matrix *m = matrix_newMatrix(4, 4);
  struct matrix *points = matrix_newMatrix(1024, 4);
  int lines[1024];
  
  timerID = SDL_AddTimer(20, timer_callback, &flag);
  
  parse_file("script", m, points, lines);
  
  matrix_free(m);
  matrix_free(points);
  
  //free(tp);
  return 0;
}

void parse_file(char *filename, struct matrix *transform, struct matrix *pm, int *lines) {
  //printf("parse\n");
  int i, loop_char_count, temp;
  int num_lines = 0;
  size_t n = 1024;
  char *string_buf;
  double point_buf1[3], point_buf2[3];
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
        matrix_addPoint(pm, point_buf1);
        break;
        
      case 'e':
      
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
        
        add_edge(pm, point_buf1, point_buf2, lines, &num_lines);
        
        break;
        
      case 'm':
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
        matrix_matrixMult(transform, pm);
        //print_matrix(pm); printf("\n"); ///////////////
        break;
      
      case 'v':
        flag = 1;
        draw_lines(pm, lines, num_lines, 255, 255, 255);
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
        //if (event.button.button == SDL_BUTTON_LEFT) {
          //printf("left down %d %d\n", event.button.x, event.button.y);
        //}
        if (event.button.button == SDL_BUTTON_RIGHT) {
          //printf("right down %d %d\n", event.button.x, event.button.y);
          SDL_WM_ToggleFullScreen(screen);
        }
        break;
        
      /*
      case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
          printf("left up %d %d\n", event.button.x, event.button.y);
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
          printf("right up %d %d\n", event.button.x, event.button.y);
        }
        break;
      */
        
      case SDL_QUIT:
        exit(EXIT_SUCCESS);
        break;
    }
  }
}

Uint32 timer_callback(Uint32 interval, void *param) {
  //printf("callback\n");
  *((int *) param) = 0;
  /*
  clock_gettime(CLOCK_REALTIME, tp);
  int temp = tp->tv_nsec;
  //printf("%li\n", temp - nsec_total);
  nsec_total = temp;
  */
  return interval;
}
