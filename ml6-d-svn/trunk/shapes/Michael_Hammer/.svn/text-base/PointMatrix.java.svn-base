import java.io.*;
import java.util.*;

public class PointMatrix extends Matrix {
  
    private int lastCol;
  
    public PointMatrix() {
	super();
	lastCol = 0;
    }
  
    public PointMatrix( int c ) {
	super( c );
	lastCol = 0;
    }
  
    public void renderHermiteCurve(double x1, double y1, double x2, double y2,
				   double x3, double y3, double x4, double y4, double step) {
	Matrix c = new Matrix();
	c.makeHermiteInverse();
	Matrix p = new Matrix(1);
	p.m[0][0] = x1; p.m[1][0] = x2; p.m[2][0] = x3-x1; p.m[3][0] = x4-x2;
	p.m[0][1] = y1; p.m[1][1] = y2; p.m[2][1] = y3-y1; p.m[3][1] = y4-y2;
    
	c.matrixMult(p);
	double ax = c.m[0][0]; double bx = c.m[1][0]; double cx = c.m[2][0]; double dx = c.m[3][0];
	double ay = c.m[0][1]; double by = c.m[1][1]; double cy = c.m[2][1]; double dy = c.m[3][1];
    
	double x; double y; double xx; double yy;
	for (double d = 0; d <= 1; d+=step)
	    {
		x = ax*d*d*d + bx*d*d + cx*d + dx;
		y = ay*d*d*d + by*d*d + cy*d + dy;
		xx = ax*(d+step)*(d+step)*(d+step) + bx*(d+step)*(d+step) + cx*(d+step) + dx;
		yy = ay*(d+step)*(d+step)*(d+step) + by*(d+step)*(d+step) + cy*(d+step) + dy;
		addEdge(x, y, 0, xx, yy, 0);
	    }
    }
  
    public void renderBezierCurve(double x1, double y1, double x2, double y2,
				  double x3, double y3, double x4, double y4, double step) {
	Matrix c = new Matrix();
	c.makeBezier();
    
	Matrix p = new Matrix(1);
	p.m[0][0] = x1; p.m[1][0] = x2; p.m[2][0] = x3; p.m[3][0] = x4;
	p.m[0][1] = y1; p.m[1][1] = y2; p.m[2][1] = y3; p.m[3][1] = y4;
    
	c.matrixMult(p);
	double ax = c.m[0][0]; double bx = c.m[0][1]; double cx = c.m[0][2]; double dx = c.m[0][3];
	double ay = c.m[0][0]; double by = c.m[0][1]; double cy = c.m[0][2]; double dy = c.m[0][3];
    
	double x; double y; double xx; double yy;
	for (double d = 0; d <= 1; d+=step)
	    {
		x = ax*d*d*d + bx*d*d + cx*d + dx;
		y = ay*d*d*d + by*d*d + cy*d + dy;
		xx = ax*(d+step)*(d+step)*(d+step) + bx*(d+step)*(d+step) + cx*(d+step) + dx;
		yy = ay*(d+step)*(d+step)*(d+step) + by*(d+step)*(d+step) + cy*(d+step) + dy;
		addEdge(x, y, 0, xx, yy, 0);
	    }
    }
  
    public void renderTorusMesh(double ox, double oy, double cx, double cy, 
				double rx, double ry, 
				double rotx, double roty, double rotz) {
	double step = 0.01;
	double a = rx-cx; double b = ry-cy;
	double r1 = Math.sqrt(a*a + b*b);
	double a2 = rx-ox; double b2 = ry-oy;
	double r2 = Math.sqrt(a2*a2 + b2*b2);
	double theta; double phi;
	for (theta = 0; theta <= 2*Math.PI; theta += step)
	    {
		for (phi = 0; phi <= Math.PI; phi+=step)
		    {
			double x = r1 * r2 * Math.cos(theta) + r2 * Math.cos(phi) + cx;
			double y = r1 * Math.sin(theta) + cy;
			double z = -r1 * Math.cos(theta)*Math.sin(phi);
			addEdge(x,y,z,x,y,z);
		    }
	    }
    }  
  
    public void generateTorus(double r1, double r2, 
			      double offx, double offy, double step) {
    
    }
  
  
    public void renderSphereMesh(double cx, double cy, 
				 double rx, double ry, 
				 double rotx, double roty, double rotz) {
	double step = 0.1;
	double a = rx-cx; double b = ry-cy;
	double r = Math.sqrt(a*a + b*b);
	double theta; double phi;
	for (theta = 0; theta <= 2*Math.PI; theta += step)
	    {
		for (phi = 0; phi <= Math.PI; phi+=step)
		    {
			double x = r * Math.cos(theta)*Math.cos(phi) + cx;
			double y = r * Math.sin(theta) + cy;
			double z = -r * Math.cos(theta)*Math.sin(phi);
			addEdge(x,y,z,x,y,z);
		    }
	    }
    }  
  
    public void generateSphere(double r, double offx, double offy, double step) {
	/*PointMatrix s = new PointMatrix();
    double theta; double phi;
    for (theta = 0; theta <= 2*Math.PI; theta += step)
    {
      for (phi = 0; phi <= Math.PI; phi+=step, lastCol++)
      {
        double x = r * Math.cos(theta)*Math.cos(phi) + offx;
        double y = r * Math.sin(theta) + offy;
        double z = -r * Math.cos(theta)*Math.sin(phi);
        s.m[0][lastCol] = x; s.m[0][lastCol] = y; s.m[0][lastCol] = z;
        lastCol++;
        double xx = r * Math.cos(theta+step)*Math.cos(phi+step) + offx;
        double yy = r * Math.sin(theta+step) + offy;
        double zz = -r * Math.cos(theta+step)*Mathdouble zz = -r * Math.cos(theta+step)*Math.sin(phi+step);

        s.m[0][lastCol] = xx; s.m[0][lastCol] = yy; s.m[0][lastCol] = zz;

        addEdge(x,y,z,xx,yy,zz);

      }

      }*/

    }

  

    public void generateCircle(double cx, double cy, double rx, double ry) {

	double step = 0.01;

	double a = rx-cx; double b = ry-cy;

	double r = Math.sqrt(a*a + b*b);

	for (double s = 0; s <=1; s += step)

	    {

		double x = r * Math.cos(2*Math.PI * s) + cx;

		double y = r * Math.sin(2*Math.PI * s) + cy;

		double x1 = r * Math.cos(2*Math.PI * (s+step)) + cx;

		double y1 = r * Math.sin(2*Math.PI * (s+step)) + cy;

		addEdge(x, y, 0, x1, y1, 0);

	    }

    }

  

  

    /*======== public void addPoint() ==========

   Inputs:  int x

   int y

   int z 

   Returns: 

   adds (x, y, z) to the calling object

   if lastcol is the maxmium value for this current matrix, 

   call grow

   ====================*/

    public void addPoint(double x, double y, double z) {

    

	if ( lastCol == m[0].length ) 

	    grow();

    

	m[0][lastCol] = x;

	m[1][lastCol] = y;

	m[2][lastCol] = z;

	m[3][lastCol] = 1;

	lastCol++;

    }

  

    /*======== public void addEdge() ==========

   Inputs:  int x0

   int y0

   int z0

   int x1

   int y1

   int z1 

   Returns: 

   adds the line connecting (x0, y0, z0) and (x1, y1, z1)

   to the calling object

   should use addPoint

   ====================*/

    public void addEdge(double x0, double y0, double z0, 

			double x1, double y1, double z1) {

    

	addPoint(x0, y0, z0);

	addPoint(x1, y1, z1);

    }

  

  

  

    /*======== accessors ==========

      ====================*/

    public int getLastCol() {

	return lastCol;

    }

    public int  getX(int c) {

	return (int)m[0][c];

    }

    public int  getY(int c) {

	return (int)m[1][c];

    }

    public int  getZ(int c) {

	return (int)m[2][c];

    }

    public void clear() {

	super.clear();

	lastCol = 0;

    }

  

    public PointMatrix copy() {

    

	PointMatrix n = new PointMatrix( m[0].length );

	for (int r=0; r<m.length; r++)

	    for (int c=0; c<m[r].length; c++)

		n.m[r][c] = m[r][c];

	n.lastCol = lastCol;

	return n;

    }

    

}