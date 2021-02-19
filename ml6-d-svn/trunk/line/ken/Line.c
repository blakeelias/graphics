#ifdef USE_SDL
#include "SDL.h"
#endif
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define IABS(i)      (((i) < 0) ? -(i) : (i))
#define img          ((u32*)rawImage)
#define PIXEL(x, y)  img[(y * dWidth) + x]
#define RGB(r, g, b) (((r) << 16) | ((g) << 8) | (b))
typedef unsigned int uint;
typedef int8_t    s8;
typedef uint8_t   u8;
typedef int16_t  s16;
typedef uint16_t u16;
typedef int32_t  s32;
typedef uint32_t u32;
typedef int64_t  s64;
typedef uint64_t u64;
uint dWidth  = 640;
uint dHeight = 480;





////////////////////////////////////////////////////////////////
//Drawing code is here
////////////////////////////////////////////////////////////////

void clear(void* rawImage)
{
 int i;
 for (i = 0; i < (dWidth * dHeight); i++)
  img[i] = RGB(0, 0, 0);
}

void plot(void* rawImage, int x, int y, u32 color)
{
 if (x < 0) return;
 if (y < 0) return;
 if (x >= dWidth)  return;
 if (y >= dHeight) return;

 PIXEL(x, y) = color;
}

void draw_line(int x1, int y1, int x2, int y2, void* rawImage, u32 color)
{
 int dx = x2 - x1;
 int dy = y2 - y1;

 int qx = x1;
 int qy = y1;

 int* const ind = (IABS(dx) > IABS(dy)) ? &qx : &qy;
 int* const dep = (IABS(dx) > IABS(dy)) ? &qy : &qx;

 int limit = (IABS(dx) > IABS(dy)) ? x2 : y2;

 if (*ind > limit)
 {
  draw_line(x2, y2, x1, y1, rawImage, color);
  return;
 }

 const int dind = IABS(  (IABS(dx) > IABS(dy)) ? dx : dy  );
 const int ddep = IABS(  (IABS(dx) > IABS(dy)) ? dy : dx  );

 int inc = ((dx * dy) < 0) ? -1 : 1;

 int d = 2 * ddep - dind;//2dy - dx

 while (*ind <= limit)
 {
  plot(rawImage, qx, qy, color);

  if (d >= 0)
  {
   (*dep) += inc;
   d -= dind;
  }

  d += ddep;
  (*ind) ++;
 }
}

void draw(void* s)
{
 clear(s);

 int XRES = dWidth;
 int YRES = dHeight;

 u32 c = RGB(0, 255, 0);

 draw_line(0, 0, XRES-1, YRES - 75, s, c);
 draw_line(0, 0, XRES - 75, YRES-1, s, c);
 draw_line(0, YRES-1, XRES-1, 75, s, c);
 draw_line(0, YRES-1, XRES - 75, 0, s, c);

 c = RGB(0, 0, 255);

 draw_line(XRES - 1, YRES - 1, 0, 75, s, c);
 draw_line(XRES - 1, YRES -1, 75, 0, s, c);
 draw_line(XRES - 1, 0, 0, YRES - 75, s, c);
 draw_line(XRES - 1, 0, 75, YRES - 1, s, c);

 c = RGB(255, 0, 0);

 draw_line(0, 0, XRES - 1, YRES - 1, s, c);
 draw_line(0, YRES - 1, XRES - 1, 0, s, c);

 draw_line(0, YRES / 2, XRES - 1, YRES / 2, s, c);
 draw_line(XRES / 2, 0, XRES / 2, YRES - 1, s, c);
}

////////////////////////////////////////////////////////////////
//Don't touch anything below this
////////////////////////////////////////////////////////////////





void writeInt(FILE* out, uint num, uint bytes)
{
 fwrite(&num, 1, bytes, out);
}
#define writeI(num, i) writeInt(out, num, i)
#define write1(num)    writeI(num, 1)
#define write2(num)    writeI(num, 2)
#define write3(num)    writeI(num, 3)
#define write4(num)    writeI(num, 4)
#define LINE           (dWidth * 3)
#define PITCH          ((LINE & 3) ? ((LINE & ~3) + 4) : LINE)
void saveBMP(void* rawImage)
{
 FILE* out = fopen("out.bmp", "wb");
 uint size = PITCH * dHeight;
 int x, y;
 write2(0x4D42);
 write4(14 + 40 + size);
 write4(0);
 write4(14 + 40);
 write4(40);
 write4(dWidth);
 write4(dHeight);
 write4(0x00180001);
 write4(0);
 write4(size);
 write4(0);
 write4(0);
 write4(0);
 write4(0);
 for (y = (dHeight - 1); y >= 0; y--)
 {
  for (x = 0; x < dWidth; x++)
   write3(PIXEL(x, y));
  writeI(0, PITCH - LINE);
 }
 fclose(out);

 printf("Saved to out.bmp!\n");
}
int main(int argc, char** argv)
{
 if ((argc > 1) && strchr(argv[1], 'x'))
 {
  int w = atoi(argv[1]);
  int h = atoi(strchr(argv[1], 'x') + 1);
  if ((w <= 0) || (h <= 0))
   fprintf(stderr, "Invalid dimensions entered, keeping resolution at 640x480\n");
  else
   fprintf(stderr, "Resolution changed to %ix%i\n", dWidth = w, dHeight = h);
 }
 void* pixels = malloc(4 * dWidth * dHeight);
 draw(pixels);
 saveBMP(pixels);
#ifdef USE_SDL
 const char title[32] = "Graphics";
 atexit(SDL_Quit);
 SDL_Init(SDL_INIT_VIDEO);
 SDL_WM_SetCaption(title, title);
 SDL_Surface* screen = SDL_SetVideoMode(dWidth, dHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
 SDL_Surface* bfr = SDL_CreateRGBSurfaceFrom(pixels, dWidth, dHeight, 32, dWidth * 4, 0xff0000, 0xff00, 0xff, 0);
 SDL_Event event;
 while (screen)
 {
  SDL_Rect rect = (SDL_Rect){0, 0, dWidth, dHeight};
  SDL_BlitSurface(bfr, &rect, screen, &rect);
  SDL_Flip(screen);
  SDL_Delay(200);
  while (SDL_PollEvent(&event))
   if (event.type == SDL_QUIT)
    screen = NULL;
 }
 SDL_FreeSurface(bfr);
#endif
 free(pixels);
 return 0;
}

