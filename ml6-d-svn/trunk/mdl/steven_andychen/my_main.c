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
  
  int i;
  screen *scr = (screen *)malloc(sizeof(screen));
  new_stack();
  struct matrix *pm = new_matrix(4,0);
  for (i=0;i<lastop;i++)
    {
      printf("%d: ",i);
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
	    printf("sphere\n");
	    struct matrix *t=new_matrix(4,1);
	    //print_matrix(t);
	    //printf("here");
	    render_sphere_mesh(t,op[i].op.sphere.r,op[i].op.sphere.d[0],op[i].op.sphere.d[1],0.02);
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
	  {struct matrix *tmp = render_box(op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	    matrix_mult(s->m[s->top-1], tmp);
	    append_matrix(pm, tmp);
	    free_matrix(tmp);
	  }

	  break;

	case LINE:
	  {
	    printf("line\n");
	    struct matrix *t=new_matrix(4,0);
	    add_edge(t,op[i].op.line.p0[0],op[i].op.line.p0[1],op[i].op.line.p0[2],op[i].op.line.p1[0],op[i].op.line.p1[1],op[i].op.line.p1[2]);
	    matrix_mult(s->m[s->top-1],t);
	    append_matrix(pm,t);
	    free_matrix(t);
	  }
	  break;
	case MESH:
	  
	  break;

	case SET:
	  //printf("%s\n", op[i].op.set.p->name);
	  break;

	case MOVE:
	  {
	    double x=1;
	    SYMTAB *tmp;
	    if(op[i].op.move.p != NULL)
	      {
		tmp = lookup_symbol(op[i].op.move.p->name);
		x=tmp->s.value;
	      }
	    //printf("%lf\n",x);
	  move(op[i].op.move.d[0]*x,op[i].op.move.d[1]*x,op[i].op.move.d[2]*x);
	  
	  printf("after move\n");
	  }
	  break;

	case SCALE:
	  {
	    double x=1;
	    SYMTAB *tmp;
	    if(op[i].op.scale.p != NULL)
	      {
		tmp = lookup_symbol(op[i].op.scale.p->name);
		x=tmp->s.value;
	      }
	    printf("%lf\n", x);
	    printf("scale\n");
	    
	    struct matrix *t=make_scale(op[i].op.scale.d[0]*x,op[i].op.scale.d[1]*x,op[i].op.scale.d[2]*x);
	    matrix_mult(t,s->m[s->top-1]);
	    free_matrix(t);
	    
	  }
	  break;

	case ROTATE:
	  {
	    printf("rotate\n");
	    double x=1;
	    SYMTAB *tmp;
	    if(op[i].op.rotate.p != NULL)
	      {
		tmp = lookup_symbol(op[i].op.rotate.p->name);
		x=tmp->s.value;
	      }
	    printf("%lf\n",x);
	    struct matrix *t;
	    if(op[i].op.rotate.axis == 0)
	      { t=make_rotX(op[i].op.rotate.degrees*x);
		printf("%lf", op[i].op.rotate.degrees*x);
	      }
	    else if(op[i].op.rotate.axis == 1)
	      t=make_rotY(op[i].op.rotate.degrees*x);
	    else if(op[i].op.rotate.axis == 2)
	      t=make_rotZ(op[i].op.rotate.degrees*x);
	    matrix_mult(t,s->m[s->top-1]);
	    free_matrix(t);
	    
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
	  printf("push\n");
	  push();
	  break;

	case POP:
	  printf("pop\n");
	  pop();
	  break;

	case GENERATE_RAYFILES:

	  break;

	case SAVE:
	  {
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
	}
    }
  free(scr);
    
}
