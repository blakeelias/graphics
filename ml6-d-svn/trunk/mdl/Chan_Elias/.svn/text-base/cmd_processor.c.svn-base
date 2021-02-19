#include <stdio.h>
#include <unistd.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "matrix_stack.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "parametrics.h"
#include "splines.h"

void cmd_processor(struct matrix * pm, screen s)
{
  int i;
  color c;
  c.red = 0;
  c.green = 0;
  c.blue = 255;
  struct matrix *new_transform;
  double x, y, z, r;  // transformation values after knob scalings
  
  int frame, num_frames = 1;
  int num_frame_digits = 1;
  char *basename = 0;
  char * BUF1;
  char * BUF2;
  char * PPM=".ppm";

  new_transform = new_matrix(4, 4);
  ident(new_transform);
  matrix_stack_init(new_transform);

  SYMTAB **knob_vals;

  for (frame = 0; frame < num_frames+1; frame++) {
    printf("Frame %d\n", frame);
    // Initial scan for "VARY" ranges
    if (frame == 0) {
      for (i=0;i<lastop;i++) {
	switch (op[i].opcode) {
	case VARY:
	  printf("Vary: %s, frames %4.0f to %4.0f, value %4.0f - %4.0f\n",
		 op[i].op.vary.p->name, 
		 op[i].op.vary.start_frame,
		 op[i].op.vary.end_frame,
		 op[i].op.vary.start_val,
		 op[i].op.vary.end_val);
	  if (num_frames <= 1) {
	    printf("Set FRAMES more than 1 before calling VARY\n");
	    break;
	  }
	  SYMTAB *knob = lookup_symbol(op[i].op.vary.p->name);
	  int symtab_index = knob - symtab; // knob's location in the table
	  printf("symtab_index: %d\n", symtab_index);
	  int range_length = op[i].op.vary.end_frame - op[i].op.vary.start_frame;
	  printf("range_length: %d\n", range_length);
	  double knob_increment = op[i].op.vary.end_val - op[i].op.vary.start_val;
	  knob_increment /= range_length;
	  printf("knob_increment: %lf\n", knob_increment);
	  printf("Sym tab:\n");
	  print_symtab();
	  int ff;
	  for (ff = 0; ff <= range_length; ff++) {
	    knob_vals[(int)op[i].op.vary.start_frame+ff][symtab_index].s.value = op[i].op.vary.start_val + ff*knob_increment;
	  }
	  for ( ; op[i].op.vary.start_frame + ff < num_frames &&
		  knob_vals[(int)op[i].op.vary.end_frame+ff] == 0; ff++) {
	    knob_vals[(int)op[i].op.vary.start_frame+ff] = knob_vals[(int)op[i].op.vary.end_frame];
	  }
	  break;
	case FRAMES:
	  printf("Num frames: %4.0f\n",op[i].op.frames.num_frames);
	  num_frames = op[i].op.frames.num_frames;
	  knob_vals = (SYMTAB **) calloc(num_frames, sizeof(SYMTAB *));
	  int f;
	  for (f = 0; f < num_frames; f++) {
	    printf("Creating knob table for frame %d\n", f);
	    knob_vals[f] = (SYMTAB *) calloc(MAX_SYMBOLS, sizeof(SYMTAB));
	    copy_symtab(symtab, knob_vals[f], MAX_SYMBOLS);
	  }
	  num_frame_digits = (int)(log(num_frames)/log(10)) + 1;
	  break;
	case BASENAME:
	  printf("Basename: %s\n",op[i].op.basename.p->name);
	  basename = op[i].op.basename.p->name;
	  break;
	}
      }
      continue;
    }

    clear_screen(s);
    pm = new_matrix(4, 1);

    matrix_stack_flush();
    if (num_frames > 1) {
      copy_symtab(knob_vals[frame-1], symtab, MAX_SYMBOLS);
    }
    print_symtab();

    for (i=0;i<lastop;i++) {
	//matrix_stack_flush();
      printf("%d: ",i);
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
	  printf("Sphere: %6.2f %6.2f %6.2f r=%6.2f\n",
		 op[i].op.sphere.d[0],op[i].op.sphere.d[1],
		 op[i].op.sphere.d[2],
		 op[i].op.sphere.r);
	  draw_sphere(pm,
		      op[i].op.sphere.d[0], op[i].op.sphere.d[1],
		      op[i].op.sphere.r);
	  if (op[i].op.sphere.constants != NULL)
	    {
	      printf("\tconstants: %s",op[i].op.sphere.constants->name);
	    }
	  if (op[i].op.sphere.cs != NULL)
	    {
	      printf("\tcs: %s",op[i].op.sphere.cs->name);
	    }

	  break;
	case TORUS:
	  printf("Torus: %6.2f %6.2f %6.2f r0=%6.2f r1=%6.2f",
		 op[i].op.torus.d[0],op[i].op.torus.d[1],
		 op[i].op.torus.d[2],
		 op[i].op.torus.r0,op[i].op.torus.r1);
	  draw_torus(pm,
		     op[i].op.torus.d[0],
		     op[i].op.torus.d[1],
		     op[i].op.torus.r1,
		     op[i].op.torus.r0);
	  if (op[i].op.torus.constants != NULL)
	    {
	      printf("\tconstants: %s",op[i].op.torus.constants->name);
	    }
	  if (op[i].op.torus.cs != NULL)
	    {
	      printf("\tcs: %s",op[i].op.torus.cs->name);
	    }

	  break;
	case BOX:
	  printf("Box: d0: %6.2f %6.2f %6.2f d1: %6.2f %6.2f %6.2f",
		 op[i].op.box.d0[0],op[i].op.box.d0[1],
		 op[i].op.box.d0[2],
		 op[i].op.box.d1[0],op[i].op.box.d1[1],
		 op[i].op.box.d1[2]);
	  draw_box(pm,op[i].op.box.d0[0],op[i].op.box.d0[1],op[i].op.box.d0[2],op[i].op.box.d1[0],op[i].op.box.d1[1],op[i].op.box.d1[2]);
	  if (op[i].op.box.constants != NULL)
	    {
	      printf("\tconstants: %s",op[i].op.box.constants->name);
	    }
	  if (op[i].op.box.cs != NULL)
	    {
	      printf("\tcs: %s",op[i].op.box.cs->name);
	    }

	  break;
	case LINE:
	  printf("Line: from: %6.2f %6.2f %6.2f to: %6.2f %6.2f %6.2f",
		 op[i].op.line.p0[0],op[i].op.line.p0[1],
		 op[i].op.line.p0[2],
		 op[i].op.line.p1[0],op[i].op.line.p1[1],
		 op[i].op.line.p1[2]);
	  add_edge(pm,
		   op[i].op.line.p0[0],
		   op[i].op.line.p0[1],
		   op[i].op.line.p0[2],
		   op[i].op.line.p1[0],
		   op[i].op.line.p1[1],
		   op[i].op.line.p1[2]);
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
	  //	print_symtab();
	  break;
	case MOVE:
	  printf("Move: %6.2f %6.2f %6.2f",
		 op[i].op.move.d[0],op[i].op.move.d[1],
		 op[i].op.move.d[2]);
	  x = op[i].op.move.d[0];
	  y = op[i].op.move.d[1];
	  z = op[i].op.move.d[2];

	  if (op[i].op.move.p != NULL)
	    {
	      printf("\tknob: %s",op[i].op.move.p->name);
	      SYMTAB *knob = lookup_symbol(op[i].op.move.p->name);
	      x *= knob->s.value;
	      y *= knob->s.value;
	      z *= knob->s.value;
	    }
	  new_transform = make_translate(x, y, z);
	  matrix_mult(new_transform, matrix_stack.last->m);
	  free_matrix(new_transform);

	  break;
	case SCALE:
	  printf("Scale: %6.2f %6.2f %6.2f",
		 op[i].op.scale.d[0],op[i].op.scale.d[1],
		 op[i].op.scale.d[2]);
	  x = op[i].op.scale.d[0];
	  y = op[i].op.scale.d[1];
	  z = op[i].op.scale.d[2];

	  if (op[i].op.scale.p != NULL)
	    {
	      printf("\tknob: %s",op[i].op.scale.p->name);
	      SYMTAB *knob = lookup_symbol(op[i].op.scale.p->name);
	      x *= knob->s.value;
	      y *= knob->s.value;
	      z *= knob->s.value;
	    }
	  new_transform = make_scale(x, y, z);
	  matrix_mult(new_transform, matrix_stack.last->m);
	  free_matrix(new_transform);

	  break;
	case ROTATE:
	  printf("Rotate: axis: %6.2f degrees: %6.2f",
		 op[i].op.rotate.axis,
		 op[i].op.rotate.degrees);
	  r = op[i].op.rotate.degrees;

	  if (op[i].op.rotate.p != NULL)
	    {
	      printf("\tknob: %s",op[i].op.rotate.p->name);
	      SYMTAB *knob = lookup_symbol(op[i].op.rotate.p->name);
	      r *= knob->s.value;
	    }

	  if (op[i].op.rotate.axis==0.0)
	    new_transform = make_rotX(r);
	  if (op[i].op.rotate.axis==1.0)
	    new_transform = make_rotY(r);
	  if (op[i].op.rotate.axis==2.0)
	    new_transform = make_rotZ(r);

	  matrix_mult(new_transform, matrix_stack.last->m);
	  free_matrix(new_transform);

	  break;
	case BASENAME:
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
	  break;
	case VARY:
	  break;
	case PUSH:
	  printf("Push");
	  struct matrix* nm = new_matrix(4, 4);
	  copy_matrix(matrix_stack.last->m, nm);
	  matrix_stack_push(nm);
	  break;
	case POP:
	  printf("Pop");
	  matrix_stack_pop();
	  break;
	case GENERATE_RAYFILES:
	  printf("Generate Ray Files");
	  break;
	case SAVE:
	  printf("Save: %s",op[i].op.save.p->name);
	  draw_lines(pm, s, c);
	  /*if (basename == NULL) {
	    basename = (char *)malloc(8);
	    strcpy(basename, "default");
	    }*/
	  //char *filename = (char *)malloc(sizeof(basename)+5);
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
    if(num_frames>1){//ANIM
	//printf("MULTIFRAME");
	printf("Save: %s", basename);
	//fprintf(stderr,"TEST");
	draw_lines(pm, s, c);
	//fprintf(stderr,"TEST");
	  //char *filename = (char *)malloc(sizeof(basename)+5);
	BUF1=calloc(255,sizeof(char));
	BUF2=calloc(255,sizeof(char));
	//fprintf(stderr,"TEST");
	strcpy(BUF1, basename);
	//fprintf(stderr,"TEST");
	sprintf(BUF2,"%0*d", num_frame_digits, frame);
	//fprintf(stderr,"TEST");
	strcat(BUF1,BUF2);
	strcat(BUF1,PPM);
	//fprintf(stderr,"TEST");
	printf("%s",BUF1);
	save_ppm(s, BUF1);
	free(BUF1);
	free(BUF2);
	//fprintf(stderr,"TEST");
    }

  }
  free_matrix(pm);
}

