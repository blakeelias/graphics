#ifndef _UI_H
#define _UI_H

// User editable:

#define WINDOW_TITLE "Line algorithm"
#define WIDTH 512
#define HEIGHT 512

// Leave be:

#define DEPTH 32 // Total bits per pixel

void initWindow(int *argc, char ***argv);
void drawPixel(unsigned char R, unsigned char G, unsigned char B, int x, int y);
void clearScreen(void);
void updateScreen(void);
void doGtk(void);

#endif
