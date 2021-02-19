#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "ml6.h"
#include "matrix.h"
#include "draw.h"
#include "stack.h"
#include "display.h"

void my_main(int polygons) {
  int num_frames = count_frames();
  int num_knobs = count_knobs();
  struct knob * knobs = (struct knob *)malloc (num_knobs * sizeof(struct knob));
  double knob_table[num_knobs][num_frames];
  int i,j;
  for (i = 0; i < num_knobs; i++) {
    for (j = 0; j < num_frames; j++) {
      knob_table[i][j] = knobs[i].init_value;
    }
  }
  for (i = 0; i < lastop; i++) {
    if (op[i].opcode == VARY) {
      int active;
      char * name = malloc(strlen(op[i].op.vary.p->name) * sizeof(char));
      strcpy(name,op[i].op.vary.p->name);
      int start = op[i].op.vary.start_frame;
      int end = op[i].op.vary.end_frame;
      double start_val = op[i].op.vary.start_val;
      double end_val = op[i].op.vary.end_val;
1      double increment = (double)(end_val - start_val) / (double)(end - start);
      for (j = 0; j < num_knobs; j++) {
	if (!strcmp(name,knobs[j].name))
	  active = j;
      }
      for (j = start; j <= end; j++) {
	knob_table[active][j] = increment * (j - start) + start_val;
      }
    }
  }
}

int count_frames() {
  int i, num_frames;
  for (i = 0; i < lastop; i++){
    if (op[i].opcode == FRAMES)
      num_frames = op[i].op.frames.num_frames;
  }
  return num_frames;
}

int count_knobs(){
  int num = 0;
  for (i = 0; i < lastsym; i++){
    if (symtab[i].type == SYM_VALUE){
      num++;
    }
  }
  return num;
}

int get_knob_data(struct knob * knobs) {
  int i;
  int j = 0;
  for (i = 0; i < lastsym; i++){
    if (symtab[i].type == SYM_VALUE){
      knobs[j].name = symtab[i].name;
      knobs[j].init_value = (double) symtab[i].s.value;
      knobs[j].which = j;
      j++;
    }
  }
}

void render_frame(double * current_knobs) {
  int i,j;
  double x,y,z,r;
  double knob_val = 1.0;
  screen s;
  color c;
  c.green = 255;
  c.blue = 0;
  c.red = 0;
  struct matrix *transform, *temp;
  struct matrix *pm = new_matrix(4,0);

  struct node *stack = init();
  for (i=0;i<lastop;i++)
    {
      printf("%d: ",i);
      switch (op[i].opcode)
	{
	case LIGHT:
1	  printf("Light: %s at: %6.2f %6.2f %6.2f",
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
	  printf("Sphere: %6.2f %6.2f %6.2f r=%6.2f",
		 op[i].op.sphere.d[0],op[i].op.sphere.d[1],
		 op[i].op.sphere.d[2],
		 op[i].op.sphere.r);
	  if (op[i].op.sphere.constants != NULL)
	    {
	      printf("\tconstants: %s",op[i].op.sphere.constants->name);
	    }
	  if (op[i].op.sphere.cs != NULL)
	    {
	      printf("\tcs: %s",op[i].op.sphere.cs->name);
	    }
	  temp = make_sphere(op[i].op.sphere.r, op[i].op.sphere.d[0], op[i].op.sphere.d[1], op[i].op.sphere.d[2]);
	  matrix_mult(stack->m, temp);
	  print_matrix(pm);
	  print_matrix(temp);
	  append_matrix(pm, temp);
	  break;
	case TORUS:
	  printf("Torus: %6.2f %6.2f %6.2f r0=%6.2f r1=%6.2f",
		 op[i].op.torus.d[0],op[i].op.torus.d[1],
		 op[i].op.torus.d[2],
		 op[i].op.torus.r0,op[i].op.torus.r1);
	  if (op[i].op.torus.constants != NULL)
	    {
	      printf("\tconstants: %s",op[i].op.torus.constants->name);
	    }
	  if (op[i].op.torus.cs != NULL)
	    {
	      printf("\tcs: %s",op[i].op.torus.cs->name);
	    }
	  temp = make_torus(op[i].op.torus.r1, op[i].op.torus.r0, op[i].op.torus.d[0], op[i].op.torus.d[1], op[i].op.torus.d[2]);
	  matrix_mult(stack->m,temp);
	  append_matrix(pm, temp);
	  break;
	case BOX:
	  printf("Box: d0: %6.2f %6.2f %6.2f d1: %6.2f %6.2f %6.2f",
		 op[i].op.box.d0[0],op[i].op.box.d0[1],
		 op[i].op.box.d0[2],
		 op[i].op.box.d1[0],op[i].op.box.d1[1],
		 op[i].op.box.d1[2]);
	  if (op[i].op.box.constants != NULL)
	    {
	      printf("\tconstants: %s",op[i].op.box.constants->name);
	    }
	  if (op[i].op.box.cs != NULL)
	    {
	      printf("\tcs: %s",op[i].op.box.cs->name);
	    }
	  temp = new_matrix(4,0);
	  add_edge(temp, op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d1[2]);
	  add_edge(temp, op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d0[0], op[i].op.box.d1[1], op[i].op.box.d0[2]);
	  add_edge(temp, op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d0[1], op[i].op.box.d0[2]);
	  add_edge(temp, op[i].op.box.d0[0], op[i].op.box.d1[1], op[i].op.box.d1[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	  add_edge(temp, op[i].op.box.d1[0], op[i].op.box.d0[1], op[i].op.box.d1[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	  add_edge(temp, op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	  add_edge(temp, op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d1[2], op[i].op.box.d0[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	  add_edge(temp, op[i].op.box.d0[0], op[i].op.box.d1[1], op[i].op.box.d0[2], op[i].op.box.d0[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	  add_edge(temp, op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d1[2], op[i].op.box.d1[0], op[i].op.box.d0[1], op[i].op.box.d1[2]);
	  add_edge(temp, op[i].op.box.d1[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d0[1], op[i].op.box.d1[2]);
	  add_edge(temp, op[i].op.box.d1[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d0[2]);
	  add_edge(temp, op[i].op.box.d0[0], op[i].op.box.d1[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d0[2]);  
	  matrix_mult(stack->m, temp);
	  append_matrix(pm, temp);
	  break;
	case LINE:
	  printf("Line: from: %6.2f %6.2f %6.2f to: %6.2f %6.2f %6.2f",
		 op[i].op.line.p0[0],op[i].op.line.p0[1],
		 op[i].op.line.p0[1],
		 op[i].op.line.p1[0],op[i].op.line.p1[1],
		 op[i].op.line.p1[1]);
	  if (op[i].op.line.constants != NULL)
	    {
	      printf("\n\tConstants: %s",op[i].op.line.constants->name);
	    }
	  if (op[i].op.line.cs0 != NULL)
	    {
	      printf("\n\tCS0: %s",op[i].op.line.cs0->name);
	    }
	  if (op[i].op.line.cs1 != NULL)
	    {
	      printf("\n\tCS1: %s",op[i].op.line.cs1->name);
	    }
	  temp = new_matrix(4, 0);
	  add_edge(temp, op[i].op.line.p0[0], op[i].op.line.p0[1], op[i].op.line.p0[2], op[i].op.line.p1[0], op[i].op.line.p1[1], op[i].op.line.p1[2]);
	  matrix_mult(stack->m, temp);
	  append_matrix(pm, temp);
	  break;
	case MESH:
	  printf("Mesh: filename: %s",op[i].op.mesh.name);
	  if (op[i].op.mesh.constants != NULL)
	    {
	      printf("\tconstants: %s",op[i].op.mesh.constants->name);
	    }
	  break;
	case SET:
	  printf("Set: %s %6.2f",
		 op[i].op.set.p->name,
		 op[i].op.set.p->s.value);
	  break;
	case MOVE:
	  printf("Move: %6.2f %6.2f %6.2f",
		 op[i].op.move.d[0],op[i].op.move.d[1],
		 op[i].op.move.d[2]);
	  if (op[i].op.move.p != NULL)
	    {
	      printf("\tknob: %s",op[i].op.move.p->name);
	    }
	  x = op[i].op.move.d[0];
	  y = op[i].op.move.d[1];
	  z = op[i].op.move.d[2];
	  transform = make_translate(x,y,z);
	  matrix_mult(transform, stack->m);
	  break;
	case SCALE:
	  printf("Scale: %6.2f %6.2f %6.2f",
		 op[i].op.scale.d[0],op[i].op.scale.d[1],
		 op[i].op.scale.d[2]);
	  if (op[i].op.scale.p != NULL)
	    {
	      printf("\tknob: %s",op[i].op.scale.p->name);
	    }
	  x = op[i].op.scale.d[0];
	  y = op[i].op.scale.d[1];
	  z = op[i].op.scale.d[2];
	  transform = make_scale(x,y,z);
	  matrix_mult(transform, stack->m);
	  free_matrix(transform);
	  break;
	case ROTATE:
	  printf("Rotate: axis: %6.2f degrees: %6.2f",
		 op[i].op.rotate.axis,
		 op[i].op.rotate.degrees);
	  if (op[i].op.rotate.p != NULL)
	    {
	      char * name = op[i].op.rotate.p->name);
	      printf("\tknob: %s",name);
	      for (j = 0; j < num_knobs; j++) {
		if (!strcmp(name,knobs[j].name))
		  knob_val = current_knobs[j];
	      }
	    }
	  r = op[i].op.rotate.degrees * knob_val1;
	  if (op[i].op.rotate.axis==0.0)
	    transform = make_rotX(r);
	  if (op[i].op.rotate.axis==1.0)
	    transform = make_rotY(r);
	  if (op[i].op.rotate.axis==2.0)
	    transform = make_rotZ(r);
	  matrix_mult(transform, stack->m);
	  free_matrix(transform);
	  break;
	case BASENAME:
	  printf("Basename: %s",op[i].op.basename.p->name);
	  break;
	case SAVE_KNOBS:
	  printf("Save knobs: %s",op[i].op.save_knobs.p->name);
	  break;
	case TWEEN:
	  printf("Tween: %4.0f %4.0f, %s %s",
		 op[i].op.tween.start_frame,
		 op[i].op.tween.end_frame,
		 op[i].op.tween.knob_list0->name,
		 op[i].op.tween.knob_list1->name);
	  break;
	case FRAMES:
	  printf("Num frames: %4.0f",op[i].op.frames.num_frames);
	  break;
	case VARY:
	  printf("Vary: %4.0f %4.0f, %4.0f %4.0f",
		 op[i].op.vary.start_frame,
		 op[i].op.vary.end_frame,
		 op[i].op.vary.start_val,
		 op[i].op.vary.end_val);
	  break;
	case PUSH:
	  printf("Push");
	  stack = push(stack);
	  break;
	case POP:
	  printf("Pop");
	  stack = pop(stack);
	  break;
	case GENERATE_RAYFILES:
	  printf("Generate Ray Files");
	  break;
	case SAVE:
	  printf("Save: %s",op[i].op.save.p->name);
	  draw_lines(pm, s, c);
	  save_ppm(s, op[i].op.save.p->name);
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
	  printf("Display");
	  draw_lines(pm, s, c);
	  display(s);
	  break;
	}
      printf("\n");
    }
}
