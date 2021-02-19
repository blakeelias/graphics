#ifndef _UI_H
#define _UI_H

void initWindow(int *argc, char ***argv, int width, int height, char *window_title);
void drawPixel(unsigned char R, unsigned char G, unsigned char B, int x, int y);
void drawPixelInt(unsigned int color, int x, int y);
void clearScreen(void);
void updateScreen(void);
void updateScreenRect(int x, int y, int w, int h);
void doGtk(void);

#endif
