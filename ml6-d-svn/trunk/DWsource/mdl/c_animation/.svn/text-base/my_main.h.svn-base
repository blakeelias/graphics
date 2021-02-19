#ifndef MY_MAIN_H
#define MY_MAIN_H

int num_frames = 1;
char name[128];

struct vary_node {

  char name[128];
  double value;
  struct vary_node *next;
};
  
void print_frame_knobs( struct vary_node **);
void print_knobs();
void process_knobs();
void first_pass();
struct vary_node ** second_pass();
void my_main(int);

#endif
