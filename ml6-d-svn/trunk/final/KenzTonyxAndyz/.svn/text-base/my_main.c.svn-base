#include <math.h>
#include <SDL/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "matrix.h"

#define AKEY_W (1 << 0)
#define AKEY_S (1 << 1)
#define AKEY_A (1 << 2)
#define AKEY_D (1 << 3)

#define AKEY_UP    (1 << 4)
#define AKEY_DOWN  (1 << 5)
#define AKEY_LEFT  (1 << 6)
#define AKEY_RIGHT (1 << 7)

#define STP_MOVE 20
#define STP_TURN 5

typedef struct
{
 char key[256];
 double valStart;
 double valEnd;
 int frameStart;
 int frameEnd;
} Entry;

Entry* symTable = NULL;
uint symSize = 0;
uint symCap = 0;

Entry* getEntry(char* key, int frame)
{
 Entry* rt = NULL;

 int i;
 for (i = 0; i < symSize; i++)
 {
  if (!strcasecmp(key, symTable[i].key))
  {
   rt = &symTable[i];

   if ((rt->frameStart <= frame) && (rt->frameEnd >= frame))
    break;
  }
 }

 return rt;
}

double getEntryValue(char* key, int frame)
{
 Entry* rt = getEntry(key, frame);
 if (!rt) return 1.0;

 if (rt->frameStart >= frame)
  return rt->valStart;

 if (rt->frameEnd <= frame)
  return rt->valEnd;

 return ((rt->valEnd - rt->valStart) * (frame - rt->frameStart) / (rt->frameEnd - rt->frameStart)) + rt->valStart;
}

void printSymbolTable(int f)
{
 int i;
 printf("Frame %i values:\n", f);
 for (i = 0; i < symSize; i++)
 {
  printf("%s: %f\n", symTable[i].key, getEntryValue(symTable[i].key, f));
 }
}


void addEntry(Entry* entry)
{
 if (symSize >= symCap)
 {
  symCap += 16;
  symTable = realloc(symTable, symCap * sizeof(Entry));
 }

 symTable[symSize++] = *entry;
}

void addEntryValue(char* key, double val)
{
 Entry entry;
 strcpy(entry.key, key);
 entry.valStart = val;
 entry.valEnd = val;
 entry.frameStart = 0;
 entry.frameEnd = 0;

 addEntry(&entry);
}

static void writeLines(FILE* out, Points points)
{
 void* img = newImage();
 draw(img, points);
 saveBMP(out, img);
 free(img);
}

int cX = 0;
int cY = 0;
int cZ = 0;

int cRX = 0;
int cRY = 0;

Matrix camera;

uint32_t keys = 0;

int sQuit;

void nvStep()
{
 cX = 0;
 cY = 0;
 cZ = 0;
 cRX = 0;
 cRY = 0;


 if (keys & AKEY_W)
  cZ += STP_MOVE;
 if (keys & AKEY_S)
  cZ -= STP_MOVE;
 if (keys & AKEY_A)
  cX -= STP_MOVE;
 if (keys & AKEY_D)
  cX += STP_MOVE;

 if (keys & AKEY_UP)
  cRX -= STP_TURN;
 if (keys & AKEY_DOWN)
  cRX += STP_TURN;
 if (keys & AKEY_LEFT)
  cRY -= STP_TURN;
 if (keys & AKEY_RIGHT)
  cRY += STP_TURN;
}

void nvResetCamera()
{
 makeTranslate(&camera, 0.0, -dHeight, 400.0);
}

#define nvKey(key) ((active) ? (keys |= (key)) : (keys &= ~(key)))

void nvInput(SDLKey sym, int active)
{
 switch (sym)
 {
  case SDLK_w:
   nvKey(AKEY_W);
   break;
  case SDLK_s:
   nvKey(AKEY_S);
   break;
  case SDLK_a:
   nvKey(AKEY_A);
   break;
  case SDLK_d:
   nvKey(AKEY_D);
   break;
  case SDLK_UP:
   nvKey(AKEY_UP);
   break;
  case SDLK_DOWN:
   nvKey(AKEY_DOWN);
   break;
  case SDLK_LEFT:
   nvKey(AKEY_LEFT);
   break;
  case SDLK_RIGHT:
   nvKey(AKEY_RIGHT);
   break;
  case SDLK_q:
   sQuit = 1;
   break;
  case SDLK_r:
   nvResetCamera();
   break;
  default:
   break;
 }
}

#undef nvKey

void zAddLine(Points* target, Matrix* m1, Matrix* m2, Matrix* matrix)
{
 Matrix p1;
 Matrix p2;

 multiplyMatrices(&p1, matrix, m1);
 multiplyMatrices(&p2, matrix, m2);

 p1.data[2] = (p1.data[2] + 50.0) / 100.0;
 p2.data[2] = (p2.data[2] + 50.0) / 100.0;

 if ((p1.data[2] <= 0.01) ||
     (p2.data[2] <= 0.01))
  return;

 p1.data[0] /= p1.data[2];
 p1.data[1] /= p1.data[2];
 p1.data[0] += dWidth >> 1;
 p1.data[1] += dHeight >> 1;

 p2.data[0] /= p2.data[2];
 p2.data[1] /= p2.data[2];
 p2.data[0] += dWidth >> 1;
 p2.data[1] += dHeight >> 1;

 addPoint(target, p1.data[0],
                  p1.data[1],
                  p1.data[2]);
 addPoint(target, p2.data[0],
                  p2.data[1],
                  p2.data[2]);
}

void nvRender(SDL_Surface* scr, Points points)
{
 Matrix temp;
 Matrix temp2;

 makeTranslate(&temp, -cX, -cY, -cZ);
 multiplyMatrices(&temp2, &temp, &camera);
 camera = temp2;

 makeRotX(&temp, -cRX);
 multiplyMatrices(&temp2, &temp, &camera);
 camera = temp2;

 makeRotY(&temp, -cRY);
 multiplyMatrices(&temp2, &temp, &camera);
 camera = temp2;

 Points p;
 memset(&p, 0, sizeof(Points));

 temp  = getMP(-50.0, dHeight, 0.0);
 temp2 = getMP(50.0,  dHeight, 0.0);
 zAddLine(&p, &temp, &temp2, &camera);

 temp  = getMP(0.0, dHeight - 50.0, 0.0);
 temp2 = getMP(0.0, dHeight + 50.0, 0.0);
 zAddLine(&p, &temp, &temp2, &camera);

 temp  = getMP(0.0, dHeight, -50.0);
 temp2 = getMP(0.0, dHeight, 50.0);
 zAddLine(&p, &temp, &temp2, &camera);

 int i;
 for (i = 0; i < points.pointCount; i += 2)
  zAddLine(&p, &points.pointList[i], &points.pointList[i + 1], &camera);

 SDL_LockSurface(scr);
 draw(scr->pixels, p);
 SDL_UnlockSurface(scr);

 destroyPoints(&p);
}

void my_main()
{
 Points stack;
 Points tempPoints;
 Matrix mat;
 Matrix mat2;

 void (*rotateCommand)(Matrix*, int);

 double d;

 Entry entry;

 FILE* out;

 memset(&stack, 0, sizeof(Points));
 memset(&tempPoints, 0, sizeof(Points));

 int frames = 1;
 char basename[1024];
 memset(basename, 0, 1024);

 int navigate = 0;

 int i;
 for (i = 0; i < lastop; i++)
 {
  switch (op[i].opcode)
  {
   case BASENAME:
    strcpy(basename, op[i].op.basename.p->name);
//    printf("Basename: %s",op[i].op.basename.p->name);
    break;
   case TWEEN:
    printf("Tween: %4.0f %4.0f, %s %s",
     op[i].op.tween.start_frame,
     op[i].op.tween.end_frame,
     op[i].op.tween.knob_list0->name,
     op[i].op.tween.knob_list1->name);
    break;
   case FRAMES:
    frames = op[i].op.frames.num_frames;
//    printf("Num frames: %4.0f",op[i].op.frames.num_frames);
    break;
   case VARY:
    strcpy(entry.key, op[i].op.vary.p->name);
    entry.valStart   = op[i].op.vary.start_val;
    entry.valEnd     = op[i].op.vary.end_val;
    entry.frameStart = op[i].op.vary.start_frame;
    entry.frameEnd   = op[i].op.vary.end_frame;
    addEntry(&entry);
//    printf("Vary: %4.0f %4.0f, %4.0f %4.0f",
//     op[i].op.vary.start_frame,
//     op[i].op.vary.end_frame,
//     op[i].op.vary.start_val,
//     op[i].op.vary.end_val);
    break;
   case SET:
    addEntryValue(op[i].op.set.p->name, op[i].op.set.p->s.value);
//    printf("Set: %s %6.2f",
//     op[i].op.set.p->name,
//     op[i].op.set.p->s.value);
    break;
   case DISPLAY:
    printf("The Display command is deprecated. You should use the Navigate command instead\n");
   case NAVIGATE:
    navigate = 1;
    printf("Navigate Enabled\n");
    break;
  }
 }

 if (frames < 1)
  frames = 1;

 Points animation[frames];
 memset(animation, 0, sizeof(animation));

 int q;
 for (q = 0; q < frames; q++)
 {
  destroyPoints(&stack);
  destroyPoints(&tempPoints);

  pushMatrix(&stack);

  for (i = 0; i < lastop; i++)
  {
   switch (op[i].opcode)
   {
    case LIGHT:
     printf("Light: %s at: %6.2f %6.2f %6.2f",
      op[i].op.light.p->name,
      op[i].op.light.c[0], op[i].op.light.c[1],
      op[i].op.light.c[2]);
     break;
    case AMBIENT:
     printf("Ambient: %6.2f %6.2f %6.2f",
      op[i].op.ambient.c[0],
      op[i].op.ambient.c[1],
      op[i].op.ambient.c[2]);
     break;
    case CONSTANTS:
     printf("Constants: %s",op[i].op.constants.p->name);
     break;
    case SAVE_COORDS:
     printf("Save Coords: %s",op[i].op.save_coordinate_system.p->name);
     break;
    case CAMERA:
     printf("Camera: eye: %6.2f %6.2f %6.2f\taim: %6.2f %6.2f %6.2f",
      op[i].op.camera.eye[0], op[i].op.camera.eye[1],
      op[i].op.camera.eye[2],
      op[i].op.camera.aim[0], op[i].op.camera.aim[1],
      op[i].op.camera.aim[2]);
     break;
    case SPHERE:
     addSphere(&tempPoints,
               op[i].op.sphere.r,
               op[i].op.sphere.d[0],
               op[i].op.sphere.d[1],
               op[i].op.sphere.d[2]);
     apply(tempPoints, top(stack));
     dump(&animation[q], tempPoints);
     destroyPoints(&tempPoints);
//     printf("Sphere: %6.2f %6.2f %6.2f r=%6.2f\n",
//      op[i].op.sphere.d[0],op[i].op.sphere.d[1],
//      op[i].op.sphere.d[2],
//      op[i].op.sphere.r);
     if (op[i].op.sphere.constants != NULL)
      printf("\tconstants: %s\n",op[i].op.sphere.constants->name);
     if (op[i].op.sphere.cs != NULL)
      printf("\tcs: %s\n",op[i].op.sphere.cs->name);
     break;
    case TORUS:
     addTorus(&tempPoints,
              op[i].op.torus.r1,
              op[i].op.torus.r0,
              op[i].op.torus.d[0],
              op[i].op.torus.d[1],
              op[i].op.torus.d[2]);
     apply(tempPoints, top(stack));
     dump(&animation[q], tempPoints);
     destroyPoints(&tempPoints);
//    printf("Torus: %6.2f %6.2f %6.2f r0=%6.2f r1=%6.2f",
//     op[i].op.torus.d[0],op[i].op.torus.d[1],
//     op[i].op.torus.d[2],
//     op[i].op.torus.r0,op[i].op.torus.r1);
     if (op[i].op.torus.constants != NULL)
      printf("\tconstants: %s",op[i].op.torus.constants->name);
     if (op[i].op.torus.cs != NULL)
      printf("\tcs: %s",op[i].op.torus.cs->name);
     break;
    case BOX:
     addBox(&tempPoints,
            op[i].op.box.d0[0],
            op[i].op.box.d0[1],
            op[i].op.box.d0[2],
            op[i].op.box.d1[0],
            op[i].op.box.d1[1],
            op[i].op.box.d1[2]);
     apply(tempPoints, top(stack));
     dump(&animation[q], tempPoints);
     destroyPoints(&tempPoints);
//    printf("Box: d0: %6.2f %6.2f %6.2f d1: %6.2f %6.2f %6.2f",
//     op[i].op.box.d0[0],op[i].op.box.d0[1],
//     op[i].op.box.d0[2],
//     op[i].op.box.d1[0],op[i].op.box.d1[1],
//     op[i].op.box.d1[2]);
     if (op[i].op.box.constants != NULL)
      printf("\tconstants: %s",op[i].op.box.constants->name);
     if (op[i].op.box.cs != NULL)
      printf("\tcs: %s",op[i].op.box.cs->name);
     break;
    case LINE:
     addPoint(&tempPoints,
              op[i].op.line.p0[0],
              op[i].op.line.p0[1],
              op[i].op.line.p0[2]);
     addPoint(&tempPoints,
              op[i].op.line.p1[0],
              op[i].op.line.p1[1],
              op[i].op.line.p1[2]);
     apply(tempPoints, top(stack));
     dump(&animation[q], tempPoints);
     destroyPoints(&tempPoints);
//    printf("Line: from: %6.2f %6.2f %6.2f to: %6.2f %6.2f %6.2f",
//     op[i].op.line.p0[0],op[i].op.line.p0[1],
//     op[i].op.line.p0[1],
//     op[i].op.line.p1[0],op[i].op.line.p1[1],
//     op[i].op.line.p1[1]);
     if (op[i].op.line.constants != NULL)
      printf("\n\tConstants: %s",op[i].op.line.constants->name);
     if (op[i].op.line.cs0 != NULL)
      printf("\n\tCS0: %s",op[i].op.line.cs0->name);
     if (op[i].op.line.cs1 != NULL)
      printf("\n\tCS1: %s",op[i].op.line.cs1->name);
     break;
    case MESH:
     printf("Mesh: filename: %s",op[i].op.mesh.name);
     if (op[i].op.mesh.constants != NULL)
      printf("\tconstants: %s",op[i].op.mesh.constants->name);
     break;
    case MOVE:
     d = 1.0;
     if (op[i].op.move.p != NULL)
     {
      d = getEntryValue(op[i].op.move.p->name, q);
//      printf("\tknob: %s\n",op[i].op.move.p->name);
     }
     makeTranslate(&mat,
                   op[i].op.move.d[0] * d,
                   -op[i].op.move.d[1] * d,
                   op[i].op.move.d[2] * d);
//     printf("Move: %6.2f %6.2f %6.2f\n",
//      op[i].op.move.d[0],op[i].op.move.d[1],
//      op[i].op.move.d[2]);
     multiplyMatrices(&mat2, top(stack), &mat);
     *top(stack) = mat2;
     break;
    case SCALE:
     d = 1.0;
     if (op[i].op.scale.p != NULL)
     {
      d = getEntryValue(op[i].op.scale.p->name, q);
//      printf("\tknob: %s\n",op[i].op.scale.p->name);
     }
     makeScale(&mat,
               op[i].op.scale.d[0] * d,
               op[i].op.scale.d[1] * d,
               op[i].op.scale.d[2] * d);
//     printf("Scale: %6.2f %6.2f %6.2f\n",
//      op[i].op.scale.d[0],op[i].op.scale.d[1],
//      op[i].op.scale.d[2]);
     multiplyMatrices(&mat2, top(stack), &mat);
     *top(stack) = mat2;
     break;
    case ROTATE:
     d = 1.0;
     if (op[i].op.rotate.p != NULL)
     {
      d = getEntryValue(op[i].op.rotate.p->name, q);
//     printf("\tknob: %s",op[i].op.rotate.p->name);
     }
     switch (op[i].op.rotate.axis)
     {
      case 0:
       rotateCommand = makeRotX;
       break;
      case 1:
       rotateCommand = makeRotY;
       break;
      default:
       rotateCommand = makeRotZ;
       break;
     }
     rotateCommand(&mat, op[i].op.rotate.degrees * d);
//    printf("Rotate: axis: %6.2f degrees: %6.2f",
//     op[i].op.rotate.axis,
//     op[i].op.rotate.degrees);
     multiplyMatrices(&mat2, top(stack), &mat);
     *top(stack) = mat2;
     break;
    case SAVE_KNOBS:
     printf("Save knobs: %s",op[i].op.save_knobs.p->name);
     break;
    case PUSH:
     pushMatrix(&stack);
//    printf("Push");
     break;
    case POP:
     popMatrix(&stack);
//    printf("Pop");
     break;
    case GENERATE_RAYFILES:
     printf("Generate Ray Files");
     break;
    case SAVE:
     out = fopen(op[i].op.save.p->name, "wb");
     writeLines(out, animation[q]);
     fclose(out);
     printf("Saved to %s!", op[i].op.save.p->name);
     break;
    case SHADING:
     printf("Shading: %s",op[i].op.shading.p->name);
     break;
    case SETKNOBS:
     printf("Setknobs: %f",op[i].op.setknobs.value);
     break;
    case FOCAL:
     printf("Focal: %f",op[i].op.focal.value);
     break;
   }
  }

  if ((frames > 1) && *basename)
  {
   printf("Writing frame %i...\n", q + 1);
   char fname[1024];
   sprintf(fname, "%s%03i.bmp", basename, q);

   out = fopen(fname, "wb");
   writeLines(out, animation[q]);
   fclose(out);
  }
 }

 if (navigate)
 {
  const char* title = "MDL Navigator";
  SDL_Surface* screen;
  SDL_Event event;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
   printf("Failure\n");
   return;
  }
  SDL_WM_SetCaption(title, title);
  if (!(screen = SDL_SetVideoMode(dWidth, dHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)))
  {
   printf("Failure\n");
   return;
  }

  long t = SDL_GetTicks();

  q = 0;
  sQuit = 0;
  nvResetCamera();
  while (1)
  {
   t += 50;
   int diff = t - SDL_GetTicks();
   if (diff < 10)
   {
    t += 10 - diff;
    diff = 10;
   }

   SDL_Delay(diff);

   while (SDL_PollEvent(&event))
   {
    switch (event.type)
    {
     case SDL_KEYDOWN:
      nvInput(event.key.keysym.sym, 1);
      break;
     case SDL_KEYUP:
      nvInput(event.key.keysym.sym, 0);
      break;
     case SDL_QUIT:
      sQuit = 1;
      break;
    }
   }

   if (sQuit)
   {
    SDL_Quit();
    break;
   }

   nvStep();
   SDL_FillRect(screen, NULL, 0xffffffffUL);
   nvRender(screen, animation[q]);
   SDL_Flip(screen);
   q = (q + 1) % frames;
  }
 }
}
