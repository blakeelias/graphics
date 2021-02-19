#ifndef LIGHT_SHADE_H
#define LIGHT_SHADE_H

void shade_polygon(double points[3][3], screen s, color c);
double get_luminosity(double points[3][3], double lightX, double lightY, double lightZ, double intensity, double cam[3]);
void illuminate_color(color *c, double luminosity);
double get_amb(double intensity);
double get_diff(double points[3][3], double lightX, double lightY, double lightZ, double intensity);
double get_spec(double points[3][3], double lightX, double lightY, double lightZ, double intensity, double cam[3]);
int front_face(double x0, double y0, double z0,
	       double x1, double y1, double z1,
	       double x2, double y2, double z2,
	       double cam[3]);
double *surface_normal(double x0, double y0, double z0,
		       double x1, double y1, double z1,
		       double x2, double y2, double z2);
double *vertex_normal(struct matrix *points, double x, double y, double z);
void normalize(double vector[3], double magnitude);

#endif
