#ifndef _LINE_H
#define _LINE_H

struct indivcolor {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
};

typedef union {
	struct indivcolor c;
	unsigned int i;
} color;

void draw_line   (int x0, int y0, int x1, int y1, color c);
void draw_line_aa(int x0, int y0, int x1, int y1, color c);
void plot(color c, int x, int y);

#endif
