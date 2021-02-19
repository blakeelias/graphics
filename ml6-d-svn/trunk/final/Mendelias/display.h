#ifndef DISPLAY_H
#define DISPLAY_H

#define NUM_COLORS 12

void plot( screen, color, int, int, double);
void clear_screen( screen s);
void save_ppm( screen s, char *file);
void save_extension( screen s, char *file);
void display( screen s);

#endif
