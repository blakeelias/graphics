#include <math.h>
#include <stdio.h>

#include "ml6.h"
#include "matrix.h"
#include "matrix_stack.h"
#include "display.h"
#include "draw.h"
#include "light_shade.h"

//put in points of polygon in order - returns 1 if it's a front face, 0 otherwise
int front_face(double x0, double y0, double z0,
	       double x1, double y1, double z1,
	       double x2, double y2, double z2,
	       double cam[3]) {

  double normx = (y1-y0)*(z2-z0) - (y2-y0)*(z1-z0);
  double normy = (x2-x0)*(z1-z0) - (x1-x0)*(z2-z0);
  double normz = (x1-x0)*(y2-y0) - (x2-x0)*(y1-y0);
  
  double centerx = (x0+x1+x2)/3;
  double centery = (y0+y1+y2)/3;
  double centerz = (z0+z1+z2)/3;

  double viewx = cam[0] - centerx;
  double viewy = cam[1] - centery;
  double viewz = cam[2] - centerz;

  double norm_mag = sqrt(normx*normx + normy*normy + normz*normz);
  normx /= norm_mag;
  normy /= norm_mag;
  normz /= norm_mag;

  double view_mag = sqrt(viewx*viewx + viewy*viewy + viewz*viewz);
  viewx /= view_mag;
  viewy /= view_mag;
  viewz /= view_mag;

  if (normx*viewx + normy*viewy + normz*viewz > 0)
    return 1;
  else
    return 0;
}

void shade_polygon(double points[3][3], screen s, color c) {
  int i;
  int bottom_point, top_point, left_point;
  double xr, xl, zr, zl, y;
  double dxr_dy, dxl_dy, dzr_dy, dzl_dy;

  top_point = 0;
  for (i = 0; i < 3; i++) {
    if (points[i][1] > points[top_point][1]) {
      top_point = i;
    }
  }
  
  bottom_point = top_point;
  for (i = 0; i < 3; i++) {
    if (points[i][1] < points[bottom_point][1]) {
      bottom_point = i;
    }
  }

  left_point = 3 - top_point - bottom_point; // the "other" point, neither top nor bottom

  printf("bottom: (%lf %lf %lf); top: (%lf %lf %lf); left (%lf %lf %lf)\n",
	 points[bottom_point][0],points[bottom_point][1],points[bottom_point][2],
	 points[top_point][0],points[top_point][1],points[top_point][2],
	 points[left_point][0],points[left_point][1],points[left_point][2]);

  
  dxl_dy = (points[left_point][0] - points[bottom_point][0])/(points[left_point][1] - points[bottom_point][1]);
  dzl_dy = (points[left_point][2] - points[bottom_point][2])/(points[left_point][1] - points[bottom_point][1]);

  dxr_dy = (points[top_point][0] - points[bottom_point][0])/(points[top_point][1] - points[bottom_point][1]);
  dzr_dy = (points[top_point][2] - points[bottom_point][2])/(points[top_point][1] - points[bottom_point][1]);

  printf("dxl_dy: %2.2lf, dzl_dy: %2.2lf, dxr_dy: %2.2lf, dzr_dy: %2.2lf\n", dxl_dy, dzl_dy, dxr_dy, dzl_dy);

  xl = xr = points[bottom_point][0];
  zl = zr = points[bottom_point][2];
  for (y = points[bottom_point][1]; y <= points[top_point][1]; y++) {
    if (abs(y - points[left_point][1]) < 1) {
      dxl_dy = (points[top_point][0] - points[left_point][0])/(points[top_point][1] - points[left_point][1]);
      dzl_dy = (points[top_point][2] - points[left_point][2])/(points[top_point][1] - points[left_point][1]);
      xl = points[left_point][0];
    }
    draw_line(xl, y, zl, xr, y, zr, s, c);
    xl += dxl_dy;
    xr += dxr_dy;
    zl += dzl_dy;
    zr += dzr_dy;
  }
}

double get_luminosity(double points[3][3], double lightX, double lightY, double lightZ, double intensity, double cam[3]) {
  double avg, amb, diff, spec;
  amb = get_amb(intensity);
  printf("amb = %f\n", amb);
  diff = get_diff(points, lightX, lightY, lightZ, intensity);
  printf("diff = %f\n", diff);
  spec = get_spec(points, lightX, lightY, lightZ, intensity, cam);
  printf("spec = %f\n", spec);
  avg = (amb+diff+spec)/3;
  printf("avg = %f\n", avg);
  return avg;
}

void illuminate_color(color *c, double lum) {
  lum = 255 * (2*lum - 1);  // originally from 0 to 1, now from -255 to 255
  c->red += lum;
  if (c->red > 255) c->red = 255;
  if (c->red < 0) c->red = 0;
  c->green += lum;
  if (c->green > 255) c->green = 255;
  if (c->green < 0) c->green = 0;
  c->blue += lum;
  if (c->blue > 255) c->blue = 255;
  if (c->blue < 0) c->blue = 0;
}

double get_amb(double intensity){ //I made this function in case we end up doing something interesting with K_a
  //return K_a*intensity;
  return intensity;
}
double get_diff(double points[3][3], double lightX, double lightY, double lightZ, double intensity){
  //printf("Light source location check: (%lf, %lf, %lf)\n", lightX, lightY, lightZ);
  double normx = (points[1][1]-points[0][1])*(points[2][2]-points[0][2]) - (points[2][1]-points[0][1])*(points[1][2]-points[0][2]); //N in the formula
  double normy = (points[2][0]-points[0][0])*(points[1][2]-points[0][2]) - (points[1][0]-points[0][0])*(points[2][2]-points[0][2]);
  double normz = (points[1][0]-points[0][0])*(points[2][1]-points[0][1]) - (points[2][0]-points[0][0])*(points[1][1]-points[0][1]);
  
  double norm_mag = sqrt(normx*normx + normy*normy + normz*normz);
  normx /= norm_mag;
  normy /= norm_mag;
  normz /= norm_mag;
  if (normz < 0)
    printf("normz < 0\n");

  double polycenterx = (points[0][0]+points[0][1]+points[0][2])/3;
  double polycentery = (points[1][0]+points[1][1]+points[1][2])/3;
  double polycenterz = (points[2][0]+points[2][1]+points[2][2])/3;

  double rayx = lightX - polycenterx; //L in the formula
  double rayy = lightY - polycentery;
  double rayz = lightZ - polycenterz;

  double ray_mag = sqrt(rayx*rayx + rayy*rayy + rayz*rayz);
  rayx /= ray_mag;
  rayy /= ray_mag;
  rayz /= ray_mag;

  double prod = (normx*rayx + normy*rayy + normz*rayz);
  if (prod < 0)
    prod = 0;
  //printf("In diff, intensity = %lf and dot product = %lf\n", intensity, prod);
  return intensity * prod; //if anything with K_d, multiply by that too
}

double get_spec(double points[3][3], double lightX, double lightY, double lightZ, double intensity, double cam[3]){
  double normx = (points[1][1]-points[0][1])*(points[2][2]-points[0][2]) - (points[2][1]-points[0][1])*(points[1][2]-points[0][2]); //N in the formula
  double normy = (points[2][0]-points[0][0])*(points[1][2]-points[0][2]) - (points[1][0]-points[0][0])*(points[2][2]-points[0][2]);
  double normz = (points[1][0]-points[0][0])*(points[2][1]-points[0][1]) - (points[2][0]-points[0][0])*(points[1][1]-points[0][1]);
  
  double norm_mag = sqrt(normx*normx + normy*normy + normz*normz);
  normx /= norm_mag;
  normy /= norm_mag;
  normz /= norm_mag;

  double polycenterx = (points[0][0]+points[1][0]+points[2][0])/3;
  double polycentery = (points[0][1]+points[1][1]+points[2][1])/3;
  double polycenterz = (points[0][2]+points[1][2]+points[2][2])/3;

  double rayx = lightX - polycenterx;//L in the formula
  double rayy = lightY - polycentery;
  double rayz = lightZ - polycenterz;

  double ray_mag = sqrt(rayx*rayx + rayy*rayy + rayz*rayz);
  rayx /= ray_mag;
  rayy /= ray_mag;
  rayz /= ray_mag;

  double viewx = cam[0] - polycenterx; //V in the formula
  double viewy = cam[1] - polycentery;
  double viewz = cam[2] - polycenterz;

  double view_mag = sqrt(viewx*viewx + viewy*viewy + viewz*viewz); //normalize V
  viewx /= view_mag;
  viewy /= view_mag;
  viewz /= view_mag;

  double subcalcx =  2*normx*(rayx*normx + rayy*normy + rayz*normz) - rayx; //calculate components of(2*N*(L dot N) - L)
  double subcalcy =  2*normy*(rayx*normx + rayy*normy + rayz*normz) - rayy;
  double subcalcz =  2*normz*(rayx*normx + rayy*normy + rayz*normz) - rayz;
  
  double specular = intensity*(viewx*subcalcx + viewy*subcalcy + viewz*subcalcz); //multiply K_s here if implemented
  if (specular < 0)
    specular = 0;
  return specular;
}

double *surface_normal(double x0, double y0, double z0,
		       double x1, double y1, double z1,
		       double x2, double y2, double z2) {
  double *normal = (double *) malloc(3 * sizeof(double));
  normal[0] = (y1-y0)*(z2-z0) - (y2-y0)*(z1-z0);
  normal[1] = (x2-x0)*(z1-z0) - (x1-x0)*(z2-z0);
  normal[2] = (x1-x0)*(y2-y0) - (x2-x0)*(y1-y0);
  return normal;
}

void normalize(double vector[3], double magnitude) {
  double mag = sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
  vector[0] *= magnitude/mag;
  vector[1] *= magnitude/mag;
  vector[2] *= magnitude/mag;
}

double *vertex_normal(struct matrix *points, double x, double y, double z) {
  double *normal;
  double *avg_normal;
  int npolygons = 0;
  int i;
  avg_normal = (double *) calloc(3, sizeof(double));
  for (i = 0; i < points->lastcol-2; i+=3) {
    if ((abs(points->m[0][i]   - x) < 1 && abs(points->m[1][i]   - y) < 1 && abs(points->m[2][i]   - z) < 1) ||
	(abs(points->m[0][i+1] - x) < 1 && abs(points->m[1][i+1] - y) < 1 && abs(points->m[2][i+1] - z) < 1) ||
	(abs(points->m[0][i+2] - x) < 1 && abs(points->m[1][i+2] - y) < 1 && abs(points->m[2][i+2] - z) < 1)) {
      normal = surface_normal(points->m[0][i], points->m[1][i], points->m[2][i],
			      points->m[0][i+1], points->m[1][i+1], points->m[2][i+1],
			      points->m[0][i+2], points->m[1][i+2], points->m[2][i+2]);
      normalize(normal, 50);
      avg_normal[0] += normal[0];
      avg_normal[1] += normal[1];
      avg_normal[2] += normal[2];
      npolygons++;
    }
  }
  for (i = 0; i < 3; i++) {
    if (npolygons != 0)
      avg_normal[i] /= npolygons;
  }
  return avg_normal;
}
