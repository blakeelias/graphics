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
  
  public static double Distance(double x1, double y1, double x2, double y2) {

 return Math.sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }
  
  public void renderHermiteCurve(double x1, double y1, double x2, double y2,
                          double x3, double y3, double x4, double y4, double step) {
    PointMatrix xcoefs = new PointMatrix(1); 
 PointMatrix ycoefs = new PointMatrix(1); 
 
 double x, y, z, ax, bx, cx, dx, ay, by, cy, dy;

 xcoefs.generateBezierCoefs(x1, x2, x3, x4);
 ycoefs.generateBezierCoefs(y1, y2, y3, y4);

 ax = xcoefs.getX(0);
 bx = xcoefs.getY(0);
 cx = xcoefs.getZ(0);
 dx = xcoefs.getD(0);

 ay = ycoefs.getX(0);
 by = ycoefs.getY(0);
 cy = ycoefs.getZ(0);
 dy = ycoefs.getD(0);

 for (double t=step; t <= 1; t+= step) {

     x = ax * t * t * t + bx * t * t + cx * t + dx;
     y = ay * t * t * t + by * t * t + cy * t + dy;
     
     addEdge(x1, y1, 0, x, y, 0);
     x1 = x;
     y1 = y;
 }
  }
  
  public void renderBezierCurve(double x1, double y1, double x2, double y2,
                          double x3, double y3, double x4, double y4, double step) {
    PointMatrix xcoefs = new PointMatrix(1); 
 PointMatrix ycoefs = new PointMatrix(1); 
 
 double x, y, z, ax, bx, cx, dx, ay, by, cy, dy;

 xcoefs.generateBezierCoefs(x1, x2, x3, x4);
 ycoefs.generateBezierCoefs(y1, y2, y3, y4);

 ax = xcoefs.getX(0);
 bx = xcoefs.getY(0);
 cx = xcoefs.getZ(0);
 dx = xcoefs.getD(0);

 ay = ycoefs.getX(0);
 by = ycoefs.getY(0);
 cy = ycoefs.getZ(0);
 dy = ycoefs.getD(0);

 for (double t=step; t <= 1; t+= step) {

     x = ax * t * t * t + bx * t * t + cx * t + dx;
     y = ay * t * t * t + by * t * t + cy * t + dy;
     
     addEdge(x1, y1, 0, x, y, 0);
     x1 = x;
     y1 = y;
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
    double x, y, z, rt, c;

 for(rt=0; rt <= 1; rt+= step) 
     for(c=0; c <= 1; c+= step) {

  x = r2 * Math.cos(2 * Math.PI * rt) + 
      r1 * Math.cos(2 * Math.PI * c) * Math.cos(2 * Math.PI * rt)
      + offx;
  y = r1 * Math.sin(2 * Math.PI * c) + offy;
  z = -1 * r2 * Math.sin(2 * Math.PI * rt) - 
      r1 * Math.cos(2 * Math.PI * c) * Math.sin(2 * Math.PI * rt);
    
  addPoint( x, y, z);      
     }
  }
  
  
/*  public void renderSphereMesh(double cx, double cy, 
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
    
    Matrix smesh = new Matrix();
    smesh.renderSphereMesh(
    
    
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
        double zz = -r * Math.cos(theta+step)*Math.sin(phi+step);
        s.m[0][lastCol] = xx; s.m[0][lastCol] = yy; s.m[0][lastCol] = zz;
        addEdge(x,y,z,xx,yy,zz);
      }
    }
  }*/

 public void renderSphereMesh(double cx, double cy, double r, double step) {
 
 int size = (int)(1 / step);

 PointMatrix tmp = new PointMatrix(size*size);
 int index, offset;

 tmp.generateSphere(r, cx, cy, step);
 
 //longitude lines
 for (int i=0; i < size; i++ )
     for (int j=0; j < size; j++ ) {
  
  index = i * size + j;
  if ( j == size - 1 ) 
      addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
        tmp.getX(index + 1 - size), 
        tmp.getY(index + 1 - size), 
        tmp.getZ(index + 1 - size));
  else
      addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
        tmp.getX(index + 1), 
        tmp.getY(index + 1), 
        tmp.getZ(index + 1));
     }

 //latitude lines
 for (int i=0; i < size; i++ )
     for (int j=0; j < size; j++ ) {
  
  index = i * size + j;
  offset = (10 - index) - size * 
      (int)Math.floor( (10 - index) / 20.0);
  
  if ( i == size - 1 ) 
      addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
        tmp.getX( offset ), 
        tmp.getY( offset ), 
        tmp.getZ( offset ));
  else
      addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
        tmp.getX(index + size), 
        tmp.getY(index + size), 
        tmp.getZ(index + size));
     }        
  
 //Points only
 /*
   for (int i=0; i < tmp.lastCol; i++)
   addEdge( tmp.getX(i), tmp.getY(i), tmp.getZ(i),
   tmp.getX(i), tmp.getY(i), tmp.getZ(i));
 */
    }  
  
    public void generateSphere(double r, double offx, double offy, double step) {
 double x, y, z;
 for(double rt=0; rt <= 1; rt+= step )
     for(double c=0; c <= 1; c+= step ) {

  x = r * Math.cos(2 * Math.PI * c) * 
      Math.cos(Math.PI * rt) + offx;
  y = r * Math.sin(2 * Math.PI * c) + offy;
  z = -1 * r * Math.cos(2 * Math.PI * c) * Math.sin(Math.PI * rt);
  
  addPoint(x, y, z);
     }
    }
    
                           
public void generateCircle(double cx, double cy, double rx, double ry) {

 double x0, y0, x, y, step, r;
       step = .01;

 r = Distance(cx, cy, rx, ry);
 x0 = r + cx;
 y0 = cy;

 for( double t= step; t <= 1; t+= step) {
     
     x = r * Math.cos( 2 * Math.PI * t) + cx;
     y = r * Math.sin( 2 * Math.PI * t) + cy;

     addEdge(x0, y0, 0, x, y, 0);
     x0 = x;
     y0 = y;
 }

 addEdge(x0, y0, 0, r + cx, cy, 0);
    }    

public void generateBox(double ax, double ay, double bx, double by)
{
  double z = bx - ax; // depth
  double x0, x1, x2, x3; 
  double y0, y1, y2, y3;
  
//  double x4, x5, x6, x7;
//  double y4, y5, y6, y7;
  
  x0 = ax; y0 = ay; // top left
  x1 = ax; y1 = by; // bottom left
  x2 = bx; y2 = ay; // top right
  x3 = bx; y3 = by; // bottom right
  
  addEdge(x0, y0, 0, x0, y0, z);
  addEdge(x0, y0, 0, x1, y1, 0);
  addEdge(x0, y0, 0, x2, y2, 0);
  
  addEdge(x3, y3, 0, x3, y3, z);
  addEdge(x3, y3, 0, x1, y1, 0);
  addEdge(x3, y3, 0, x2, y2, 0);
  
  addEdge(x1, y1, z, x1, y1, 0);
  addEdge(x1, y1, z, x0, y0, z);
  addEdge(x1, y1, z, x3, y3, z);
  
  addEdge(x2, y2, z, x2, y2, 0);
  addEdge(x2, y2, z, x0, y0, z);
  addEdge(x2, y2, z, x3, y3, z);
}

public void generateTriangle(double x0, double y0, double x1, double y1, double x2, double y2)
{
  addEdge(x0, y0, 0, x1, y1, 0);
  addEdge(x0, y0, 0, x2, y2, 0);
  addEdge(x1, y0, 0, x2, y2, 0);
}

public void generateTriPrism(double x0, double y0, double x1, double y1, double x2, double y2)
{
  double d1 = Distance(x0, y0, x1, y1);
  double d2 = Distance(x0, y0, x2, y2);
  double d3 = Distance(x1, y1, x2, y2);
  double semi = (d1 + d2 + d3) / 3;
  double z = semi;
  
  addEdge(x0, y0, 0, x1, y1, 0);
  addEdge(x0, y0, 0, x2, y2, 0);
  addEdge(x1, y0, 0, x2, y2, 0);
  
  addEdge(x0, y0, z, x1, y1, z);
  addEdge(x0, y0, z, x2, y2, z);
  addEdge(x1, y0, z, x2, y2, z);
  
  addEdge(x0, y0, 0, x0, y0, z);
  addEdge(x1, y1, 0, x1, y1, z);
  addEdge(x2, y2, 0, x2, y2, z);
}
  
  /*public void generateCircle(double cx, double cy, double rx, double ry) {
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
  }*/
  
  
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
  public void addEdge(double x0, double y0, double z0,  // add color as parameter???
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
  
    public double  getD(int c) {
 return m[3][c];
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
