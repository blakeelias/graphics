#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "ml6.h"
#include "parser.h"
#include "stack.h"
#include "symtab.h"
#include "y.tab.h"

#define TOLERANCE 10

struct portal{
	double p[3];
	double r;
	double t[3];
	int which;
};

int collision_test(double x, double y, double z, struct portal * p);
