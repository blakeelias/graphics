#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "matrix.h"

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


void my_main(int polygons)
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

 void* pixels = newImage();

 int frames = 1;
 char basename[1024];
 memset(basename, 0, 1024);

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
  }
 }

 if (frames < 1)
  frames = 1;

 int q;
 for (q = 0; q < frames; q++)
 {
  clear(pixels);
  destroyPoints(&stack);

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
     draw(pixels, tempPoints);
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
     draw(pixels, tempPoints);
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
     draw(pixels, tempPoints);
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
     draw(pixels, tempPoints);
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
                   op[i].op.move.d[1] * d,
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
     saveBMP(out, pixels);
     fclose(out);
     printf("Saved to %s!", op[i].op.save.p->name);
//    printf("Save: %s",op[i].op.save.p->name);
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
    case DISPLAY:
     out = popen("display -", "w");
     saveBMP(out, pixels);
     pclose(out);
//    printf("Display");
     break;
   }
  }

  if (frames > 1)
  {
   printf("Writing frame %i...\n", q + 1);

   char fname[1024];
   sprintf(fname, "%s%05i.bmp", basename, q);
   out = fopen(fname, "wb");
   saveBMP(out, pixels);
   fclose(out);
  }
 }

 if (frames > 1)
 {
  char command[1024];
  sprintf(command, "convert -delay 4 %s?????.bmp %s.gif", basename, basename);
  printf("%s\n", command);
  i = system(command);

//  sprintf(command, "rm -f %s?????.bmp", basename);
//  printf("%s\n", command);
//  i = system(command);
 }

 free(pixels);
}

