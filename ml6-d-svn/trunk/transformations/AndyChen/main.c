#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"

void parse_file ( char * filename, 
		  struct matrix * transform, 
		  struct matrix * pm,
		  screen s);

int main() {

  struct matrix *translation, *point_matrix;
 
  screen s;
  
  translation = new_matrix(4, 4);
  point_matrix = new_matrix(4, 1);
  parse_file("script", translation, point_matrix, s);
 
  return 0;
  //The following tests various matrix functions
  
  /* m = new_matrix(r, c);
  a = new_matrix(r, c);  

  for (r=0; r < m->rows; r++)
    for (c=0; c < m->cols; c++)
      m->m[r][c] = 5;
  
  print_matrix(m);
  printf("\n");

  ident(m);
  print_matrix(m);
  printf("\n");

  scalar_mult(7, m);
  print_matrix(m);
  printf("\n");

  copy_matrix(m, a);
  print_matrix(a);
  printf("\n");

  ident(m);

  matrix_mult(a, m);
  print_matrix(a);
  printf("\n");


  free_matrix(a);
  free_matrix(m);
  
  translation = make_translate(4,5,17);
  print_matrix(translation);

  scale = make_scale(4,6,11);
  print_matrix(scale);
  
  rotx = make_rotX(90);
  print_matrix(rotx);
  
  roty = make_rotY(90);
  print_matrix(roty);

  rotz = make_rotZ(90);
  print_matrix(rotz);*/
  
  
}

void parse_file ( char * filename, 
	     struct matrix * transform, 
	     struct matrix * pm,
	     screen s) {
  ident(transform);
  
  FILE *input = fopen(filename, "r");
  char *line[100][30];
  int count,i;
  color c;
  c.red = 0;
  c.green = 255;
  c.blue = 0;
  

  //create an array of strings representing file
  for(i=0;fgets(line[i], 50, input)!=NULL;i++)
    {  
    }
  count = i;
  
  
  for(i=0;i<count;i++)
    {
      
      if (strcmp(line[i],"l\n")==0)
	{ i++;
	  char * temp;
	  int conversion;
	  //first point
	  temp = strtok(line[i], " "); 
	  conversion = atoi(temp);
	  pm -> m[0][pm->lastcol] = conversion;
	  

	  temp = strtok(NULL, " "); 
	  conversion = atoi(temp);
         pm -> m[1][pm->lastcol] = conversion;
	  
	  
	  temp = strtok(NULL, " "); 
	  conversion = atoi(temp);
	  pm -> m[2][pm->lastcol] = conversion;
	  
	  
	  pm -> m[3][pm->lastcol] = 1;
	  pm->lastcol++;
	  grow_matrix(pm, pm->lastcol + 1);

	  //second point
    	  temp = strtok(NULL, " "); 
	  conversion = atoi(temp);
	  pm -> m[0][pm->lastcol] = conversion;
	  
	  
	  temp = strtok(NULL, " "); 
	  conversion = atoi(temp);
	  pm -> m[1][pm->lastcol] = conversion;
	  
	  
	  temp = strtok(NULL, " "); 
	  conversion = atoi(temp);
	  pm -> m[2][pm->lastcol] = conversion;
	  
	  pm -> m[3][pm->lastcol] = 1;
	  pm -> lastcol ++;
	  grow_matrix(pm, pm->lastcol + 1);
	  
	}
      if(strcmp(line[i],"i\n")==0)
	{
	  ident(transform);}
      if(strcmp(line[i],"s\n")==0)
	{
	  struct matrix *transformationtemp;
	  i++;
	  char * temp;
	  int conversionx,conversiony,conversionz;
	  temp = strtok(line[i], " "); 
	  conversionx = atoi(temp);


	  temp = strtok(NULL, " "); 
	  conversiony = atoi(temp);

	  
	  temp = strtok(NULL, " "); 
	  conversionz = atoi(temp);

	  
	  transformationtemp =make_scale(conversionx, conversiony, conversionz); 	  
	  matrix_mult(transformationtemp, transform);
	  
	}
	if(strcmp(line[i],"t\n")==0)
	{
	  struct matrix *transformationtemp;
	  i++;
	  char * temp;
	  int conversionx,conversiony,conversionz;
	  temp = strtok(line[i], " "); 
	  conversionx = atoi(temp);


	  temp = strtok(NULL, " "); 
	  conversiony = atoi(temp);

	  
	  temp = strtok(NULL, " "); 
	  conversionz = atoi(temp);

	  
	  transformationtemp =make_translate(conversionx, conversiony, conversionz); 
	  matrix_mult(transformationtemp, transform);
	  
	}
	
    if(strcmp(line[i],"x\n")==0)
	{
	  struct matrix *transformationtemp;
	  i++;
	  char * temp;
	  int conversion;
	  temp = strtok(line[i], " "); 
	  conversion = atoi(temp);
	  transformationtemp =make_rotX(conversion); 
	  
	  matrix_mult(transformationtemp, transform);
	  
	}
    
       if(strcmp(line[i],"y\n")==0)
	{
	  struct matrix *transformationtemp;
	  i++;
	  char * temp;
	  int conversion;
	  temp = strtok(line[i], " "); 
	  conversion = atoi(temp);
	  transformationtemp =make_rotY(conversion);
	  
	  matrix_mult(transformationtemp, transform);
	  
	  
	}
       if(strcmp(line[i],"z\n")==0)
	{
	struct matrix *transformationtemp;
	  i++;
	  char * temp;
	  int conversion;
	  temp = strtok(line[i], " "); 
	  conversion = atoi(temp);
	  transformationtemp =make_rotZ(conversion); 
	 
	  matrix_mult(transformationtemp, transform);}
      if(strcmp(line[i],"a\n")==0)
	{
	  
	  matrix_mult(transform,pm);
	 
	}
      if(strcmp(line[i],"v\n")==0)
	{
	  int i = 0;
	  // its cols -1 because theres an extra column in the point matrix just in case
	 
	  for (i=0; i<pm->cols-1; i++)
	    {
	      draw_line(pm->m[0][i],pm->m[1][i],pm->m[0][i+1],pm->m[1][i+1],s,c );
	      i++;
	      
	    }
	  display(s);
	}
      if(strcmp(line[i],"g\n")==0)
	{i++;
	  save_ppm(s, line[i]);
	}
     
    }
  
  }  
