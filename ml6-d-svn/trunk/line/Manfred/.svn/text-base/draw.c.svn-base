#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"



void draw_line(int x1, int y1, int x2, int y2, screen s, color c){

//TODO use nonrecursive methods
//printf("Feed: x1:%d y1:%d x2:%d y2:%d ",x1,y1,x2,y2);

if((x1>x2)&&(y1>y2)){
printf(" converted x ");
draw_line(x2,y2,x1,y1, s, c);
return;
}


//printf("Conversion: x1:%d y1:%d x2:%d y2:%d ",x1,y1,x2,y2);
int xeq=0;
int yeq=0;

if(x1==x2){++xeq;}
if(y1==y2){++yeq;}

if(xeq||yeq){
while((x1!=x2)&&(y1!=y2)){
plot(s,c,x1,y1);
x1=x1+xeq;
y1=y1+yeq;
}
return;
}

double slope;
int rt=0;
double offset;

if((y2-y1)>(x2-x1)){//y>x
slope=((double)x2-(double)x1)/((double)y2-(double)y1);
//printf("slope: %f\n\n",slope);
offset=x1+.5;
while(y1!=y2){
plot(s,c,(int)offset,y1);
offset=offset+slope;
y1++;
}
}

else{ //x>y
slope=((double)y2-(double)y1)/((double)x2-(double)x1);
//printf("slope: %f\n\n",slope);
rt=1;
offset=y1+.5;
while(x1!=x2){
plot(s,c,x1,(int)offset);
offset=offset+slope;
x1++;
}
}

return;

}
