#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {
  screen s;
  color c;
  c.red=0;
  c.green=MAX_COLOR;
  c.blue=0;
  char fname[256];
  char ch;
  int a[6];
  int points=0;
  struct matrix *m = new_matrix(4,0);
  int i;

  while(1)
    {
      scanf("%c",&ch);
      switch (ch)
	{
	case 'l':
	  scanf("%d %d %d %d %d %d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5]);
	  m->m[0][points]=a[0];
	  m->m[1][points]=a[1];
	  m->m[2][points]=a[2];
	  m->m[3][points]=1;
	  points++;
	  grow_matrix(m,points+1);
	  m->m[0][points]=a[3];
	  m->m[1][points]=a[4];
	  m->m[2][points]=a[5];
	  m->m[3][points]=1;
	  points++;
	  grow_matrix(m,points+1);
	  break;
	case 'i':
	  printf("M is now an identity matrix\n");
	  break;
	case 's':
	  scanf("%d %d %d",&a[0],&a[1],&a[2]);
	  make_scale(a[0],a[1],a[2],m);
	  break;
	case 't':
	  scanf("%d %d %d",&a[0],&a[1],&a[2]);
	  make_translate(a[0],a[1],a[2],m);
	  break;
	case 'x':
	  scanf("%d",&a[0]);
	  make_rotX(a[0],m);
	case 'y':
	  scanf("%d",&a[0]);
	  make_rotY(a[0],m);
	  break;
	case 'z':
	  scanf("%d",&a[0]);
	  make_rotZ(a[0],m);
	  break;
	case'a':
	  printf("M is now an identity matrix\n");
	  break;
	case 'v':
	  for(i=0;i<points;i=i+2)
	    {
	      draw_line(m->m[0][i],m->m[1][i],m->m[0][i+1],m->m[1][i+1],s,c);
	    }
	  break;
	case 'g':
	  display(s);
	  //scanf("%s",fname);
	  //save_ppm(s,fname);
	  break;
	}
    } 
  return 1;
}
