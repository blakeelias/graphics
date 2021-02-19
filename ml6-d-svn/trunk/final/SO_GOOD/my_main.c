
#include "my_main.h"

void my_main(int polygons){
	
	//Prepare for main loop to run:
	//Initiate variables
	//Set up frames / knobs
	//Set up portals
	//Set up file name
	
	screen *s_ptr = (screen *) malloc(sizeof(screen));
	stack_init();
	
	int i, j, k, num_knobs, num_frames, current_frame, num_points, current_point;
	i = j = k = num_knobs = num_frames = current_frame = num_points = current_point = 0;
	
	char * basename;
	
	struct matrix * pm = new_matrix(4,0);
	
	struct matrix * P = new_matrix(4,4);
	ident(P);
	struct matrix * Pinverse = new_matrix(4,4);
	ident(Pinverse);
	
	struct portal * p1, * p2;
	
	//Count knobs
	for (i = 0; i < lastsym; i++){
		if (symtab[i].type == SYM_VALUE){
			num_knobs++;
		}
	}
	
	//Prepare table of knobs
	struct knob * knobs = (struct knob *)malloc (num_knobs * sizeof(struct knob));
	
	for (i = 0; i < lastsym; i++){
		if (symtab[i].type == SYM_VALUE){
			knobs[j].name = symtab[i].name;
			knobs[j].value = (double) symtab[i].s.value;
			knobs[j].which = j;
			j++;
		}
	}
	
	//Get knob values from user [WHO WOULD EVER DO THIS]
	{
		/*
		 double temp = 15;
		 char buff[100];
		 
		 for (j = 0; j < num_knobs; j++){
		 printf("knob: %s\tvalue: %lf\n", knobs[j].name, knobs[j].value);
		 }
		 
		 while (temp > -1){
		 printf("knob name: ");
		 scanf("%s", buff);
		 printf("new value: ");
		 scanf("%lf", &temp);
		 //printf("just scanned: %s %lf\n", buff, temp);
		 if (temp > -1){
		 for (j = 0; j < num_knobs; j++){
		 if (! strcmp(knobs[j].name, buff)){
		 knobs[j].value = (double) temp;
		 }
		 printf("knob: %s\tvalue: %lf\n", knobs[j].name, knobs[j].value);
		 }
		 }
		 }
		 */
	}
	
	//Count frames
	for (i = 0; i < lastop; i++){
		if (op[i].opcode == FRAMES)
			num_frames = op[i].op.frames.num_frames;
	}
	//printf("numbef of frames: %i\n", num_frames);
	
	//Set up a chart to hold knob values
	double chart[num_knobs][num_frames];
	
	//Fill chart up with initial values for knobs
	for (k = 0; k < num_knobs; k++){
		for (j = 0; j < num_frames; j++){
			chart[k][j] = knobs[k].value;
		}
	}
	
	//Set up basename
	for (i = 0; i < lastop; i++){
		if (op[i].opcode == BASENAME){
			basename = (char *)malloc(sizeof(char) * strlen(op[i].op.basename.p->name));
			strcpy(basename, op[i].op.basename.p->name);
		}
		
	}
	//printf("basename: %s\n", basename);
	
	//Handle varies
	for (i = 0; i < lastop; i++){
		if (op[i].opcode == VARY){
			char * knob_name = (char *)malloc(strlen(op[i].op.vary.p->name) * sizeof(char));
			strcpy(knob_name, op[i].op.vary.p->name);
			//printf("knob_name: %s\n", knob_name);
			int start = op[i].op.vary.start_frame;
			int end = op[i].op.vary.end_frame;
			double knob0 = op[i].op.vary.start_val;
			double knob1 = op[i].op.vary.end_val;
			double increment = (double)(knob1 - knob0) / (double)(end - start);
			//printf("increment: %lf\n", increment);
			
			// find which knob we're dealing with
			
			for (j = 0; j < num_knobs; j++){
				if (! strcmp(knobs[j].name, knob_name)){
					k = j;
				}
			}
			
			//edit chart
			chart[k][start - 1] = knob0;
			chart[k][end - 1] = knob1;
			
			for (j = start - 1; j < end - 2; j++){
				chart[k][j+1] = chart[k][j] + increment;
			}
			
			/*//print out chart
			 for (j = 0; j < num_knobs; j++){
			 printf("%s:", knobs[j].name);
			 for (k = 0; k < num_frames; k++){
			 printf("\t%lf", chart[j][k]);
			 }
			 printf("\n");
			 }*/
		}
	}
	
	//Handle portals: unfinished
	for (i = 0; i < lastop; i++){
		if (op[i].opcode == PORTAL){
			
			// x1 y1 z1 r1 tx1 ty1 tz1
			
			
			p1 = (struct portal *)malloc(sizeof(struct portal));
			p1->p[0] = op[i].op.portal.d[0];
			p1->p[1] = op[i].op.portal.d[1];
			p1->p[2] = op[i].op.portal.d[2];
			
			p1->r = op[i].op.portal.d[3];
			
			p1->t[0] = op[i].op.portal.d[4];
			p1->t[1] = op[i].op.portal.d[5];
			p1->t[2] = op[i].op.portal.d[6];
			
			p1->which = 1;
			
			p2 = (struct portal *)malloc(sizeof(struct portal));
			p2->p[0] = op[i].op.portal.d[7];
			p2->p[1] = op[i].op.portal.d[8];
			p2->p[2] = op[i].op.portal.d[9];
			
			p2->r = op[i].op.portal.d[10];
			
			p2->t[0] = op[i].op.portal.d[11];
			p2->t[1] = op[i].op.portal.d[12];
			p2->t[2] = op[i].op.portal.d[13];
			
			p2->which = -1;
			
			//handle translations
			
			struct matrix * helper = make_translate(-1 * p1->p[0], -1 * p1->p[1], -1 * p1->p[2]);
			matrix_mult(make_rotX(p2->t[0] - p1->t[0]), helper);
			matrix_mult(make_rotY(p2->t[1] - p1->t[1]), helper);
			matrix_mult(make_rotZ(p2->t[2] - p2->t[2]), helper);
			
			matrix_mult(make_translate(p2->p[0], p2->p[1], p2->p[2]), helper);
			
			matrix_mult(helper, P);
			
			helper = make_translate(p1->p[0] - p2->p[0], p1->p[1] - p2->p[1], p1->p[2] - p2->p[2]);
			matrix_mult(helper, Pinverse);
			
			//handle rotations and scalings
			
			//free_matrix(helper);
		}
	}
	
	//Set up data for pointlist
	for (i = 0; i < lastop; i++){
		switch(op[i].opcode){
				
			case SPHERE:
				num_points += 1100;
				break;
				
			case TORUS:
				num_points += 2300;
				break;
				
			case LINE:
				num_points += 2;
				break;
				
			case BOX:
				num_points += 8;
				break;
		}
	}
	printf("num_points: %i\n", num_points);
	
	
	//point_data will store information about points:
	//[0] whether or not they were in the portal last time
	//[1] the number of times they've been in that portal
	int point_data[2][num_points];
	bzero(point_data, sizeof(point_data));
	
	
	//Generate all points
	for (current_frame = 0; current_frame < num_frames; current_frame++){
		stack_init();
		pm = new_matrix(4,0);
		clear_screen(s_ptr);
		for (i = 0; i < lastop; i++){
			switch(op[i].opcode){
					
				case SPHERE:
				{	
					struct matrix * helper = new_matrix(4,0);
					draw_sphere(helper,
								op[i].op.sphere.d[0], op[i].op.sphere.d[1],
								op[i].op.sphere.r);
					matrix_mult(stack->m, helper);
					for (j = 0; j < 600; j++){
						add_point(pm, helper->m[0][j], helper->m[1][j], helper->m[2][j]);
					}
				}
					break;
					
				case TORUS:
				{	
					struct matrix * helper = new_matrix(4,0);
					draw_torus(helper,
							   op[i].op.torus.d[0], op[i].op.torus.d[1],
							   op[i].op.torus.r1, op[i].op.torus.r0);
					matrix_mult(stack->m, helper);
					for (j = 0; j < 1000; j++){
						add_point(pm, helper->m[0][j], helper->m[1][j], helper->m[2][j]);
					}
				}
					break;
					
				case BOX:
				{
					struct matrix *helper = render_box(op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d0[2], op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
					matrix_mult(stack->m, helper);
					for (j = 0; j < 600; j++){
						add_point(pm, helper->m[0][j], helper->m[1][j], helper->m[2][j]);
					}
				}
					break;
					
				case LINE:
				{
					struct matrix *m = new_matrix(4, 0);
					add_edge(m, op[i].op.line.p0[0], op[i].op.line.p0[1], op[i].op.line.p0[2], op[i].op.line.p1[0], op[i].op.line.p1[1], op[i].op.line.p1[2]);
					matrix_mult(stack->m, m);
					add_edge(pm, m->m[0][0], m->m[1][0], m->m[2][0], m->m[0][1], m->m[1][1], m->m[2][1]);
				}
					break;
				case MOVE:
				{
					double knob_value;
					char * name = op[i].op.move.p->name;
					for (j = 0; j < num_knobs; j++){
						if (! strcmp(knobs[j].name, name)){
							k = j;
						}
						knob_value = chart[k][current_frame];
						//printf("knob: %s\tknob_value: %lf\n", name, knob_value);
					}
					struct matrix *m = make_translate(knob_value * op[i].op.move.d[0], knob_value * op[i].op.move.d[1], knob_value * op[i].op.move.d[2]);
					//scalar_mult(knob_value, m);
					matrix_mult(m, pm);
					//free(m);
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
						knob_value = chart[k][current_frame];
						//printf("knob: %s\tknob_value: %lf\n", name, knob_value);
					}
					struct matrix *m = make_scale( 1 + knob_value * (op[i].op.move.d[0] - 1),
												  1 + knob_value * (op[i].op.move.d[1] - 1),
												  1 + knob_value * (op[i].op.move.d[2]) - 1);
					//scalar_mult(knob_value, m);
					matrix_mult(m, stack->m);
					//free(m);
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
					knob_value = chart[k][current_frame];
					if (op[i].op.rotate.axis == 0)
						m = make_rotX(op[i].op.rotate.degrees * knob_value);
					else if (op[i].op.rotate.axis == 1)
						m = make_rotY(op[i].op.rotate.degrees * knob_value);
					else if (op[i].op.rotate.axis == 2)
						m = make_rotZ(op[i].op.rotate.degrees * knob_value);
					//printf("knob name: %s\tknob value: %lf\n", name, knob_value);
					//scalar_mult(knob_value, m);
					//print_matrix(m);
					matrix_mult(m, stack->m);
					//free(m);
				}
					break;
					
				case PUSH:
					stack_push();
					break;
					
				case POP:
					stack_pop();
					break;
			}
			//stack_print();
		}
		
		//Handle portal stuff
		for (i = 0; i < lastop; i++){
			if (op[i].opcode == PORTAL){
				
				
				printf("applying transformations!\n");
				//Apply transformations
				
				struct matrix * point_holder = new_matrix(4,1);
				
				for (j = 0; j < num_points; j++){
					
					k = point_data[1][j];
					
					point_holder->m[0][0] = pm->m[0][j];
					point_holder->m[1][0] = pm->m[1][j];
					point_holder->m[2][0] = pm->m[2][j];
					point_holder->m[3][0] = pm->m[3][j];
					
					while (k > 0){
						matrix_mult(P, point_holder);
						k--;
					}
					while (k < 0){
						matrix_mult(Pinverse, point_holder);
						k++;
					}
					
					pm->m[0][j] = point_holder->m[0][0];
					pm->m[1][j] = point_holder->m[1][0];
					pm->m[2][j] = point_holder->m[2][0];
					pm->m[3][j] = point_holder->m[3][0];
					
				}
				
				//Check for collisions
				
				for (j = 0; j < num_points; j++){
					
					//collision test
					
					k = collision_test(pm->m[0][j], pm->m[1][j], pm->m[2][j], p1);
					
					if (k == 0)
						if (point_data[0][j] == 1)
							point_data[1][j]++;
					
					point_data[0][j] = k;
					
				/*	k = collision_test(pm->m[0][j], pm->m[1][j], pm->m[2][j], p2);
					
					if (k == 0)
						if (point_data[0][j] == 1)
							point_data[1][j]--;
					
					point_data[0][j] = k;*/
					
				}
			}
		}
		
		
		//Handle saving
		for (i = 0; i < lastop; i++){
			if (op[i].opcode == SAVE){
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
				printf("writing file: %s\n", filename);
				draw_lines(pm, *s_ptr, *white);
				save_extension(*s_ptr, filename);
				//free(white);
			}
			
			
		}
		
		//free_matrix(pm);
	}
	
	
}





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


//Checks if the point x, y, z is within TOLERANCE of the portal
//Returns 1 if it is, 0 otherwise

int collision_test(double x, double y, double z, struct portal * p){
	double a, b, c, r;
	
	struct matrix * point = new_matrix(4,1);
	
	a = p->p[0];
	b = p->p[1];
	c = p->p[2];
	r = p->r;
	
	/*basic test
	 
	 if ((x-a)  > TOLERANCE && y < b + r && y > b - r)
		return 0;
	*/
	//printf("Collision detected at %lf %lf %lf\n", x, y, z);
	
	//sphere test
	if ((x-a)*(x-a) + (y-b)*(y-b) + (z-c)*(z-c) > r * r + TOLERANCE * TOLERANCE)
		return 0;
	
	//linear algebra time!
	point->m[0][0] = x - a;
	point->m[1][0] = y - b;
	point->m[2][0] = z - c;
	point->m[3][0] = 1;
	
	struct matrix * T = make_rotY(-1 * p->t[1]);
	matrix_mult(make_rotZ(-1 * p->t[2]), T);
	
	matrix_mult(T, point);
	
	if ((abs(point->m[0][0]) > TOLERANCE) || (point->m[1][0] * point->m[1][0] + point->m[2][0] * point->m[2][0] > r * r))
		return 1;
	
	return 1;
}