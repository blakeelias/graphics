#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"
#include "display.h"
#include "draw.h"
#include "ml6.h"
#include "stack.h"
#include "matrix.h"

void my_main( int polygons ) {

  //print_pcode();
  

  int i,j=-1;
  int numknobs=0;
  int knobc=0;
  double numframes=0;
  
  screen *scr = (screen *)malloc(sizeof(screen));
  new_stack();
  int k;
  for(k=0;k<lastsym;k++)
    {
      if (symtab[k].type == SYM_VALUE)
	numknobs++;
    }
  printf("Num knobs: %d\n\n", numknobs);

  double **knobvalues;
  char **knobnames;
  struct matrix *pm;
  do {
    printf("\nframe number %d\n", j);
    clear_screen(*scr);
  pm = new_matrix(4,0);

  for (i=0;i<lastop;i++)
    {
      printf("which command we're on%d: \n",i);
      switch (op[i].opcode)
	{
	case LIGHT:
	
	  break;
	case AMBIENT:
	
	  break;

	case CONSTANTS:

	  break;
	case SAVE_COORDS:
	  
	  break;
	case CAMERA:


	  break;
	case SPHERE:
	  {
	    if (j==-1)break;
	    printf("sphere\n");
	    struct matrix *t=new_matrix(4,1);
	    //print_matrix(t);
	    //printf("here");
	    render_sphere_mesh(t,op[i].op.sphere.r,op[i].op.sphere.d[0],op[i].op.sphere.d[1],0.05);
	    // print_matrix(t);
	    //printf("here");
	    matrix_mult(s->m[s->top-1],t);
	    append_matrix(pm,t);
	    free_matrix(t);
	    //printf("here");

	  }
	  break;
	case TORUS:
	  {
	    if (j==-1)break;
	    printf("torus\n");
	    struct matrix *t=new_matrix(4,0);
	    render_torus_mesh(t,op[i].op.torus.r0,op[i].op.torus.r1,op[i].op.torus.d[0],op[i].op.torus.d[1],0.05);
	    matrix_mult(s->m[s->top-1],t);
	    append_matrix(pm,t);
	    free_matrix(t);
	    //printf("here");
	  }
	  break;

	case BOX:
	  { printf("box\n");
	    if (j==-1)break;
	    struct matrix *tmp = render_box(op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	    matrix_mult(s->m[s->top-1], tmp);
	    append_matrix(pm, tmp);
	    free_matrix(tmp);
	  }

	  break;

	case LINE:
	  {
	    if (j==-1)break;
	    printf("line\n");
	    struct matrix *t=new_matrix(4,0);
	    add_edge(t,op[i].op.line.p0[0],op[i].op.line.p0[1],op[i].op.line.p0[2],op[i].op.line.p1[0],op[i].op.line.p1[1],op[i].op.line.p1[2]);
	    matrix_mult(s->m[s->top-1],t);
	    append_matrix(pm,t);
	    free_matrix(t);
	  }
	  break;
	case MESH:
	  if (j==-1)break;
	  break;

	case SET:
	  if (j==-1)break;
	  //printf("%s\n", op[i].op.set.p->name);
	  break;

	case MOVE:
	  { printf(" move\n");
	    if (j==-1)break;
	    double knobvalue=1;
	    char *name;
	    int x;
	    if(op[i].op.move.p != NULL)
	      {
		name = op[i].op.move.p->name;
		for(x=0;x<numknobs;x++)
		  {
		    if(strcmp(knobnames[x],name)==0)
		      break;
		  }
		knobvalue=knobvalues[j][x];
	      }
	    //printf("%lf\n",x);
	    printf("%lf, %lf, %lf \n", op[i].op.move.d[0]*knobvalue,op[i].op.move.d[1]*knobvalue,op[i].op.move.d[2]*knobvalue);
	  move(op[i].op.move.d[0]*knobvalue,op[i].op.move.d[1]*knobvalue,op[i].op.move.d[2]*knobvalue);
	  
	 
	  }
	  break;

	case SCALE:
	  {printf("scale\n");
	    if (j==-1)break;
	    char *name;
	    int x;
	    double knobvalue=1;
	    if(op[i].op.scale.p != NULL)
	      {
		name = op[i].op.scale.p->name;
		for(x=0;x<numknobs;x++)
		  {
		    if(strcmp(knobnames[x],name)==0)
		      break;
		  }
		knobvalue=knobvalues[j][x];
		//free(name);
	      }
	    
	    struct matrix *t=make_scale(op[i].op.scale.d[0]*knobvalue,op[i].op.scale.d[1]*knobvalue,op[i].op.scale.d[2]*knobvalue);
	    matrix_mult(t,s->m[s->top-1]);
	    free_matrix(t);
	    
	  }
	  break;

	case ROTATE:
	  {
	    if (j==-1)break;
	    printf("rotate\n");
	    char *name;
	    int x;
	    double knobvalue=1;
	    if(op[i].op.rotate.p != NULL)
	      {
		name = op[i].op.rotate.p->name;
		for(x=0;x<numknobs;x++)
		  {
		    if(strcmp(knobnames[x],name)==0)
		      break;
		  }
		
		knobvalue=knobvalues[j][x];
		//free(name);
		
	      }
	    
	    //printf("%lf\n",x);
	    struct matrix *t;
	    if(op[i].op.rotate.axis == 0)
	      { t=make_rotX(op[i].op.rotate.degrees*knobvalue);
		printf("%lf\n", op[i].op.rotate.degrees*knobvalue);
	      }
	    else if(op[i].op.rotate.axis == 1)
	      { t=make_rotY(op[i].op.rotate.degrees*knobvalue);
		printf("%lf\n", op[i].op.rotate.degrees*knobvalue);}
	    else if(op[i].op.rotate.axis == 2)
	      {t=make_rotZ(op[i].op.rotate.degrees*knobvalue);
		printf("%lf\n", op[i].op.rotate.degrees*knobvalue);}
	    matrix_mult(t,s->m[s->top-1]);
	    free_matrix(t);
	    
	  }
	  break;

	case BASENAME:
  if (j==-1)break;
	    printf("basename\n");
	    color *c = (color *)malloc(sizeof(color));
	    c->red=MAX_COLOR;
	    c->green=MAX_COLOR;
	    c->blue=MAX_COLOR;
	    draw_lines(pm,*scr,*c);
	    
	    char buffer[1000000];
	    if (j<10)
	      {sprintf(buffer, "0%d", j);}
	    else
	      { sprintf(buffer, "%d", j);}
	    
	    strcat(buffer, op[i].op.basename.p->name);
	    
	    
	      printf("%s", buffer);
		save_extension(*scr,buffer);
	  break;

	case SAVE_KNOBS:

	  break;

	case TWEEN:

	  break;

	case FRAMES:
	  if(j==-1){
	    numframes = op[i].op.frames.num_frames;
	    printf("number of frames%lf\n", numframes);
	    knobvalues = (double **)malloc(numframes * sizeof(double *));
	    knobnames = (char **)malloc(numknobs * sizeof(char *));
	    int p;
	    for(p=0;p<numframes;++p)
	      {
		knobvalues[p] = (double *)malloc(numknobs*sizeof(double));
	      }
	    for(p=0;p<numknobs;++p)
	      {
		knobnames[p] = malloc(80 * sizeof(char));
	      }
	  }
	  
	   
	  break;
	case VARY:
	  {
	    
	    if(j==-1) {
	      int startframe,endframe,currentframe;
	      double startval,endval;
	      startframe = op[i].op.vary.start_frame;
	      currentframe=startframe;
	      endframe = op[i].op.vary.end_frame;
	      startval = op[i].op.vary.start_val;
	      endval = op[i].op.vary.end_val;
	      
	      double interval = ((double)(endval-startval))/(endframe-startframe);
	      printf("interval: %lf\n", interval);
   	      for(;currentframe<=endframe;++currentframe)
		{
		  printf("\ncurrentframe: %lf, knobc: %d\n",currentframe,knobc);
		   knobvalues[currentframe][knobc]=(currentframe-startframe)*interval + startval;
		}
	      int startc;
	      if(startframe>0)
		{
		  for(startc=0;startc<startframe;startc++)
		    {
		      knobvalues[startc][knobc]=startval;
		    }
		}
	      if(endframe<numframes)
		{
		  for(startc=endframe;startc<numframes;startc++)
		    {
		      knobvalues[startc][knobc]=endval;
		    }
		}
	      knobnames[knobc]=op[i].op.vary.p->name;
	      //printf("%s\n", knobnames[knobc]);
	      //printf("%s\n", op[i].op.vary.p->name);
	      knobc++;
	      }
	  }
	  break;

	case PUSH:
	  if (j==-1)break;
	  printf("push\n");
	  push();
	  break;

	case POP:
	  if (j==-1)break;
	  printf("pop\n");
	  pop();
	  break;

	case GENERATE_RAYFILES:
	  if (j==-1)break;
	  break;

	case SAVE:
	  {
	    if (j==-1)break;
	    printf("save\n");
	    color *c = (color *)malloc(sizeof(color));
	    c->red=MAX_COLOR;
	    c->green=MAX_COLOR;
	    c->blue=MAX_COLOR;
	    draw_lines(pm,*scr,*c);
	    save_extension(*scr,op[i].op.save.p->name);
	  }
	  break;

	case SHADING:

	  break;

	case SETKNOBS:

	  break;

	case FOCAL:

	  break;

	case DISPLAY:
	  {
	    if (j==-1)break;
	    printf("display\n");
	    color *c = (color *)malloc(sizeof(color));
	    c->red=MAX_COLOR;
	    c->green=MAX_COLOR;
	    c->blue=MAX_COLOR;
	    draw_lines(pm,*scr,*c);
	    display(*scr);
	    free(c);
	  }
	  break;
	  
	  //printf("hi\n");
	}
      //printf("hi\n");
	  
    }
 if (j==-1) {
	    int q,w;
	    for(q=0;q<numframes;++q)
	      for(w=0;w<numknobs;++w)
		{
		  printf("Knob name: %s, knob value: %lf\n", knobnames[w], knobvalues[q][w]);
		}
	    
		}	  
  j++;
  free_matrix(pm);
  new_stack();
  // clear_screen(*scr);
  }while(j<numframes);
 
    
}
