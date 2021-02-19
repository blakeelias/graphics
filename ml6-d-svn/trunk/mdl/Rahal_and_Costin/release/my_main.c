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

void my_main( int polygons ) {
  int i,j,k,num_knobs,num_frames,current_frame;
  char * basename;
  screen *s_ptr = (screen *)malloc(sizeof(screen));
  struct matrix * pm = new_matrix(4,0);
  init();
  num_knobs=0;
  //Get num_knobs
  for(i=0;i<lastsym;i++)
    {
      if(symtab[i].type== SYM_VALUE)
	{
	  num_knobs++;
	}
    }
  //Set up knob list
  struct knob * knobs = (struct knob *)malloc(num_knobs * sizeof(struct knob));
  j=0;
  for(i=0;i<lastsym;i++)
    {
      if (symtab[i].type == SYM_VALUE)
	{
	  knobs[j].name = symtab[i].name;
	  knobs[j].value = (double) symtab[i].s.value;
	  knobs[j].which = j;
	  j++;
	} 
    }
  for (i = 0; i < lastop; i++)
    {
      if (op[i].opcode == FRAMES)
	num_frames = op[i].op.frames.num_frames;
    }
  //Set up knob table
  double table[num_knobs][num_frames];
  for(i=0;i<num_knobs;i++)
    {
      for(j=0;j<num_frames;j++)
	table[i][j]=knobs[i].value;
    }
  
  for (i = 0; i < lastop; i++)
    {
      if (op[i].opcode == BASENAME)
	{
	  basename = (char *)malloc(sizeof(char) * strlen(op[i].op.basename.p->name));
	  strcpy(basename, op[i].op.basename.p->name);
	}
      
    }
  
  for (i = 0; i < lastop; i++)
    {
      if (op[i].opcode == VARY)
	{
	 char * knob_name = (char *)malloc(sizeof(char)*strlen(op[i].op.vary.p->name));
	    strcpy(knob_name,op[i].op.vary.p->name);
	    int start = op[i].op.vary.start_frame;
	    int end = op[i].op.vary.end_frame;
	    double knob_i = op[i].op.vary.start_val;
	    double knob_f = op[i].op.vary.end_val;
	    double step = (double)(knob_f - knob_i) / (double)(end - start);
	    for(j=0;j<num_knobs;j++)
	    {
	      if(!strcmp(knobs[j].name,knob_name))
		k=j;
	    }
	    table[k][start-1]=knob_i;
	    table[k][end-1]=knob_f;
	    for(j=start-1;j<end-2;j++)
	      {
		table[k][j+1]=table[k][j]+step;
	      } 
	}
    }
  
  for(current_frame=0;current_frame<num_frames;current_frame++)
    {
      init();
      pm = new_matrix(4,0);
      clear_screen(*s_ptr);
      for (i=0;i<lastop;i++)
	{
	  switch (op[i].opcode)
	{
	case SPHERE:
	  {
	    render_sphere_mesh(pm,op[i].op.sphere.r,op[i].op.sphere.d[0],op[i].op.sphere.d[1],0.02);
	    matrix_mult(stack->m,pm);
	  }
	case TORUS:
	  {	  
	    render_torus_mesh(pm,op[i].op.torus.r0,op[i].op.torus.r1,op[i].op.torus.d[0],op[i].op.torus.d[1],0.05);
	    matrix_mult(stack->m,pm);
	  }
	    break;
	case BOX:
	  {
	    render_box(op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	    matrix_mult(stack->m,pm);
	  }
	  break;
	case LINE:
	  {
	    add_edge(pm,op[i].op.line.p0[0],op[i].op.line.p0[1],op[i].op.line.p0[2],op[i].op.line.p1[0],op[i].op.line.p1[1],op[i].op.line.p1[2]);
	    matrix_mult(stack->m,pm);
	  }
	  break;
	case MESH:

	  break;
	case SET:

	  break;
	case MOVE:
	  {
	    double knob_value;
	    char * name = op[i].op.move.p->name;
	    for (j = 0; j < num_knobs; j++){
	      if (! strcmp(knobs[j].name, name)){
		k = j;
	      }
	      knob_value = table[k][current_frame];
	    }
	    struct matrix *m = make_translate(knob_value * op[i].op.move.d[0], knob_value * op[i].op.move.d[1], knob_value * op[i].op.move.d[2]);
	    //scalar_mult(knob_value, m);
	    matrix_mult(m, stack->m);
	    free(m);				
	  }
	  break;
	case SCALE:
	  {
	    double knob_value;
	    char * name = op[i].op.scale.p->name;
	    for (j = 0; j < num_knobs; j++){
	      if (! strcmp(knobs[j].name, name)){
							k = j;
	      }
	      knob_value = table[k][current_frame];
	    }
	    struct matrix *m = make_scale( 1 + knob_value * (op[i].op.move.d[0] - 1),
					   1 + knob_value * (op[i].op.move.d[1] - 1),
					   1 + knob_value * (op[i].op.move.d[2]) - 1);
	    //scalar_mult(knob_value, m);
	    matrix_mult(m, stack->m);
	    free(m);  
	  }
	  break;
	case ROTATE:
	  {
	    struct matrix *m;
	    double knob_value;
	    char * name = op[i].op.rotate.p->name;
	    for (j = 0; j < num_knobs; j++){
	      if (! strcmp(knobs[j].name, name)){
		k = j;
	      }
	      
	    }
	    knob_value = table[k][current_frame];
	    if (op[i].op.rotate.axis == 0)
	      m = make_rotX(op[i].op.rotate.degrees * knob_value);
	    else if (op[i].op.rotate.axis == 1)
	      m = make_rotY(op[i].op.rotate.degrees * knob_value);
	    else if (op[i].op.rotate.axis == 2)
	      m = make_rotZ(op[i].op.rotate.degrees * knob_value);
	    matrix_mult(m, stack->m);
	    free(m);
	  }
	  break;
	case BASENAME:
	  
	  break;
	case SAVE_KNOBS:

	  break;
	case TWEEN:

	  break;
	case FRAMES:

	  break;
	case VARY:
	  
	  break;
	case PUSH:
	  push();
	  break;
	case POP:
	  pop();
	  break;
	case GENERATE_RAYFILES:

	  break;
	case SAVE:
	  {
	    color *white = (color *) malloc(sizeof(color));
	    white->red = MAX_COLOR;
	    white->green = MAX_COLOR;
	    white->blue = MAX_COLOR;
	    char num[6];
	    char filename[20];
	    if (current_frame < 10)
	      sprintf(num, "0000%i", current_frame);
	    else if (current_frame < 100)
	      sprintf(num, "000%i", current_frame);
	    else
	      sprintf(num, "00%i", current_frame);
	    strcpy(filename, basename);
	    strcat(filename, num);
	    draw_lines(pm,*s_ptr, *white);
	    save_extension(*s_ptr, filename);
	    free(white);
	  }
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
	  break;
	}
	  printf("\n");
	}
    }
}
