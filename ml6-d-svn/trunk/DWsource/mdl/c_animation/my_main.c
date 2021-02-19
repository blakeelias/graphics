#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "stack.h"
#include "matrix.h"
#include "ml6.h"
#include "draw.h"
#include "display.h"
#include "my_main.h"


void print_knobs() {
 
 int i;

  printf("ID\tNAME\t\tTYPE\t\tVALUE\n");
  for (i=0; i < lastsym; i++) {

    if ( symtab[i].type == SYM_VALUE ) {
      printf("%d\t%s\t\t", i, symtab[i].name);

      printf("SYM_VALUE\t");
      printf("%6.2f", symtab[i].s.value);
    }
    printf("\n");
  }
}


void print_frame_knobs( struct vary_node **a) {
  
  int i;
  struct vary_node *vn;
  for (i=0; i < num_frames; i++) {

    printf("frame %d:", i);
    vn = a[i];
    while ( vn ) {
      printf("\tKnob: %s, value: %lf\n", vn->name, vn->value);
      vn = vn->next;
    }
  }
}

void process_knobs() {

  int i;
  double v;

  if ( lastsym == 0 )
    return;

  do {
    printf("Knob List:\n");
    print_knobs();
    printf("Enter knob ID to set (-1 to stop): ");
    scanf("%d", &i);
    
    if ( i != -1 ) {
      printf("Eneter new value for %s: ", 
	     symtab[i].name);
      scanf("%lf", &v);
      symtab[i].s.value = v;
    }
    printf("\n");
  } while ( i != -1 );
}


void first_pass() {
  
  int i;
  int frame_check;
  int vary_check;
  int name_check;

  frame_check = 0;
  vary_check = 0;
  name_check = 0;

  for (i=0; i < lastop; i++) {

    if ( op[i].opcode == FRAMES ) {
      num_frames = op[i].op.frames.num_frames;
      frame_check = 1;
    }
    
    else if ( op[i].opcode == BASENAME ) {
      strncpy( name, op[i].op.basename.p->name, sizeof(name) );
      name_check = 1;
    }

    else if ( !(vary_check) && op[i].opcode == VARY ) 
      vary_check = 1;
  }
    
  if ( vary_check && !(frame_check) ) {
    printf("Vary command found without setting number of frames\n");
    exit(0);
  }
  

  if ( frame_check && !(name_check) ) {
    printf("Animation code found but basename was not set, using \"frame\" as basename\n");
    strncpy( name, "frame", sizeof(name));
  }

}
      
struct vary_node ** second_pass() {

  int i, j, k;
  int start_f, end_f, start_v, end_v;
  struct vary_node **knob_values;
  struct vary_node *new_node;
  char knob_names[50][128];

  int count;
  int knob_found;

  count = 0;
  knob_found = 0;
  knob_values = (struct vary_node **)calloc( num_frames, 
					     sizeof( struct vary_node *) );



  for (i=0; i < lastop; i++) {

    if ( op[i].opcode == VARY ) {

      start_f = op[i].op.vary.start_frame;
      end_f = op[i].op.vary.end_frame;
      start_v = op[i].op.vary.start_val;
      end_v = op[i].op.vary.end_val;

      if ( start_f < 0 || end_f >= num_frames || start_f >= end_f) {

	printf("Invalid vary command for knob: %s\n", op[i].op.vary.p->name );
	exit(0);
      }
            
      for (k=0; k < count; k++) {
	printf("searching for knob %s %s \n", knob_names[k], op[i].op.vary.p->name);
	printf("cmp value: %d\n",strncmp( knob_names[k], op[i].op.vary.p->name, 
					  sizeof(knob_names[k])));
	knob_found = 0;
	if ( strncmp( knob_names[k], op[i].op.vary.p->name, 
		      sizeof(knob_names[k])) == 0) {
	  printf("found knob!\n");
	  knob_found = 1;
	  break;
	}
      }

      if ( knob_found == 0) {
	printf("copying name\n");
	strncpy(knob_names[count], op[i].op.vary.p->name, sizeof(knob_names[count]));
	count++;
      }
      
      printf("loop: %d\n", i);

      for (j=0; j < num_frames; j++) {
	

	if ( knob_found == 0) {

	  new_node = (struct vary_node*)calloc(1, sizeof( struct vary_node));
	  strncpy( new_node->name, op[i].op.vary.p->name, sizeof( new_node->name ) );
	  new_node->next = NULL;

	  if ( j < start_f )
	    new_node->value = start_v;
	  else if ( j > end_f )
	    new_node->value = end_v;
	  else {
	    if ( start_v < end_v )
	      new_node->value = (j - start_f) * 
		(double)(end_v - start_v)/(double)(end_f - start_f);

	    else if ( start_v > end_v ) 
	      new_node->value = (end_f - j) * 
		(double)(end_v - start_v)/(double)(end_f - start_f) * -1;

	  }
	  
	  if ( !(knob_values[j]) )
	    knob_values[j] = new_node;
	  else {
	    new_node->next = knob_values[j];
	    knob_values[j] = new_node;
	  }
	}
	//knob already exists
	else {

	  if ( j >= start_f && j <= end_f ) {
	    
	    printf("modifying existing knob for frame: %d\n", j);

	    new_node = knob_values[j];
	    while ( strncmp(new_node->name, op[i].op.vary.p->name,
			    sizeof(new_node->name)) != 0 )
	      new_node = new_node->next;

	    if ( start_v < end_v )
	      new_node->value = (j - start_f) * 
		(double)(end_v - start_v)/(double)(end_f - start_f);

	    else if ( start_v > end_v ) 
	      new_node->value = (end_f - j) * 
		(double)(end_v - start_v)/(double)(end_f - start_f) * -1;
	  }
	}
      }
    }
  }
  return knob_values;
}


void my_main( int polygons ) {

  struct stack *s;
  struct matrix *transform;
  struct matrix *tmp;  
  double value1;
  double value2;
  double value3;
  double knob_value;
  screen t;
  color g;
  char frame_name[128];
  struct vary_node **knob_nodes;
  struct vary_node *vn;

  g.red = 0;
  g.green = 255;
  g.blue = 255;

  int i;
  int f;
  
  s = new_stack();
  tmp = new_matrix(4, 1000);
  clear_screen( t );


  // print_pcode();
  // print_knobs();
  //check to see if animation code is present
  first_pass();

  //if there is only 1 frame, ask user for knobs, otherwise 
  //scan the file for vary commands and set knobs
  if ( num_frames == 1 )
    process_knobs();
  else {
    knob_nodes = second_pass();
    print_frame_knobs( knob_nodes);
  }

  //need to follow commands for each frame
  for (f=0; f < num_frames; f++ ) {

    //if multiple frames, set correct knobs
    if ( num_frames > 1 ) {
      vn = knob_nodes[f];
      while ( vn ) {
	set_value( lookup_symbol( vn->name), vn->value);
	//	printf("Setting knob: %s %lf\n", vn->name, vn->value);
	vn = vn->next;
      }
    }

    printf("POST KNOB, FRAME: %d\n", f);

    //draw stuff
    for (i=0;i<lastop;i++) {

      //printf("\tOP INDEX: %d\n",i);

      switch (op[i].opcode) {
	
      case PUSH:
	push( s );
	break;
      
      case POP:
	pop( s );
	break;

      case MOVE:	
	value1 = op[i].op.move.d[0];
	value2 = op[i].op.move.d[1];
	value3 = op[i].op.move.d[2];

	if ( op[i].op.move.p != NULL ) {
	  knob_value = lookup_symbol( op[i].op.move.p->name )->s.value;
	  value1 = value1 * knob_value;
	  value2 = value2 * knob_value;
	  value3 = value3 * knob_value;
	}
	
	transform = make_translate( value1, value2, value3);
	matrix_mult( s->data[ s->top ], transform );
	copy_matrix( transform, s->data[ s->top ] );

	//	matrix_mult( transform, s->data[ s-> top ] );
	free_matrix( transform );
	break;
      
      case ROTATE:

	value1 = op[i].op.rotate.degrees;

	if ( op[i].op.rotate.p != NULL ) {
	  knob_value = lookup_symbol( op[i].op.rotate.p->name )->s.value;
	  value1 = value1 * knob_value;
	}

	value1 = value1 * (M_PI / 180);

	if ( op[i].op.rotate.axis == 0 )
	  transform = make_rotX( value1 );

	else if ( op[i].op.rotate.axis == 1 )
	  transform = make_rotY( value1 );

	else if ( op[i].op.rotate.axis == 2 )
	  transform = make_rotZ( value1 );
	
	matrix_mult( s->data[ s->top ], transform );
	copy_matrix( transform, s->data[ s->top ] );
	free_matrix( transform );
	break;

      case SCALE:
	value1 = op[i].op.scale.d[0];
	value2 = op[i].op.scale.d[1];
	value3 = op[i].op.scale.d[2];

	if ( op[i].op.scale.p != NULL ) {
	  knob_value = lookup_symbol( op[i].op.scale.p->name )->s.value;
	  value1 = value1 * knob_value;
	  value2 = value2 * knob_value;
	  value3 = value3 * knob_value;
	}

	transform = make_scale( value1, value2, value3 );
	matrix_mult( s->data[ s->top ], transform );
	copy_matrix(  transform, s->data[ s->top ] );
	free_matrix( transform );
	break;

      case SPHERE:
	render_sphere_mesh( tmp, op[i].op.sphere.r,
			    op[i].op.sphere.d[0],
			    op[i].op.sphere.d[1],
			    op[i].op.sphere.d[2], 0.05);

	if ( op[i].op.sphere.cs != NULL ) 
	  matrix_mult( lookup_symbol( op[i].op.sphere.cs->name)->s.m, tmp); 
	else 
	  matrix_mult( s->data[s->top], tmp ); 

	draw_lines( tmp, t, g);
	clear_matrix(tmp);	
	break;

      case TORUS:
	render_torus_mesh( tmp, op[i].op.torus.r0, op[i].op.torus.r1,
			   op[i].op.torus.d[0], op[i].op.torus.d[1],
			   op[i].op.torus.d[2], 0.05);
      
	if ( op[i].op.torus.cs != NULL ) 
	  matrix_mult( lookup_symbol( op[i].op.torus.cs->name)->s.m, tmp); 
	else 
	  matrix_mult( s->data[s->top], tmp ); 

	draw_lines( tmp, t, g);
	clear_matrix(tmp);
	break;
     
      case BOX:
	render_box( tmp, op[i].op.box.d0[0], 
		    op[i].op.box.d0[1],
		    op[i].op.box.d0[2],
		    op[i].op.box.d1[0],
		    op[i].op.box.d1[1],
		    op[i].op.box.d1[2] );

	if ( op[i].op.box.cs != NULL ) 
	  matrix_mult( lookup_symbol( op[i].op.box.cs->name)->s.m, tmp); 
	else 
	  matrix_mult( s->data[s->top], tmp ); 

	draw_lines( tmp, t, g);
	clear_matrix(tmp);
	break;
      
      case SET:
	set_value( lookup_symbol( op[i].op.set.p->name), 
		   op[i].op.set.p->s.value);
	break;

      case DISPLAY:
	display(t);
	break;     	      
	
      case SAVE:
	save_extension( t, op[i].op.save.p->name );
      }
    }//end oparray loop


    if (num_frames > 1) {

      sprintf( frame_name, "animations/%s%03d.png", name, f);
      //    printf( "%s\n", frame_name );
      save_extension( t, frame_name);
      
      free_stack( s );
      free_matrix( tmp );
      clear_screen( t );
      s = new_stack();
      tmp = new_matrix(4, 1000);
    }
  }


    free_stack( s );
    //  free_matrix( transform );
    free_matrix( tmp );  
}
