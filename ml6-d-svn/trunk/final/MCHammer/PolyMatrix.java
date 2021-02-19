import java.io.*;
import java.util.*;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.event.*;
import javax.imageio.*;

// PolyMatrix: The PointMatrix with Color and Attitude, ...but mostly Color, and ideally Lighting in the Future

public class PolyMatrix extends Matrix
{
  public static final int XY_MODE = 1;
  public static final int XZ_MODE = 2;
  public static final int YZ_MODE = 3;

//public PointMatrix pm;
  public Color color;
  public ArrayList<Color> allColors;
  public int counter;
  private int lastCol;
  
  
  public PolyMatrix(Color c)
  {
    super();
    lastCol = 0;
    
    color = c;
    allColors = new ArrayList<Color>(255);
    allColors.add(0, color);
    counter = 0;
    //pm = new PointMatrix();
  }
  
  public PolyMatrix( int column, Color c ) {
    super( column );
    lastCol = 0;
    
    color = c;
    allColors = new ArrayList<Color>(255);
    allColors.add(0, color);
    counter = 0;
    //pm = new PointMatrix();
    
  }
  
  
  
 /* public void addEdge(double x0, double y0, double z0,  
                      double x1, double y1, double z1, Color c)
  {
    pm.addEdge(x0, y0, z0, x1, y1, z1);
    allColors.set(counter, c);
  } */
  
  public static double Distance(double x1, double y1, double x2, double y2) {
    
    return Math.sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  }
  
  public void renderTorusMesh(double ox, double oy, double cx, double cy, 
                              double rx, double ry, 
                              double rotx, double roty, double rotz, Color c) {
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
        addEdge(x,y,z,x,y,z, c);
      }
    }
  }  
  
  public void generateTorus(double r1, double r2, 
                            double offx, double offy, double step, Color a) {
    double x, y, z, rt, c;

    for(rt=0; rt <= 1; rt+= step) 
      for(c=0; c <= 1; c+= step) {
      
      x = r2 * Math.cos(2 * Math.PI * rt) + 
        r1 * Math.cos(2 * Math.PI * c) * Math.cos(2 * Math.PI * rt)
        + offx;
      y = r1 * Math.sin(2 * Math.PI * c) + offy;
      z = -1 * r2 * Math.sin(2 * Math.PI * rt) - 
        r1 * Math.cos(2 * Math.PI * c) * Math.sin(2 * Math.PI * rt);
    
      addPoint( x, y, z, a);      
    }
  }
  
  public void shadeTorus(double r1, double r2, 
                            double offx, double offy, double step, Color a) {
    
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
  
  public void renderSphereMesh(double cx, double cy, double r, double step, Color c) {
    
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
                tmp.getZ(index + 1 - size), c);
      else
        addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
                tmp.getX(index + 1), 
                tmp.getY(index + 1), 
                tmp.getZ(index + 1), c);
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
                tmp.getZ( offset ), c);
      else
        addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
                tmp.getX(index + size), 
                tmp.getY(index + size), 
                tmp.getZ(index + size), c);
    }        
    
    //Points only
    /*
     for (int i=0; i < tmp.lastCol; i++)
     addEdge( tmp.getX(i), tmp.getY(i), tmp.getZ(i),
     tmp.getX(i), tmp.getY(i), tmp.getZ(i));
     */
  }  
  
  public void generateSphere(double r, double offx, double offy, double step, Color a) {
    double x, y, z;
    for(double rt=0; rt <= 1; rt+= step )
      for(double c=0; c <= 1; c+= step ) {
      
      x = r * Math.cos(2 * Math.PI * c) * 
        Math.cos(Math.PI * rt) + offx;
      y = r * Math.sin(2 * Math.PI * c) + offy;
      z = -1 * r * Math.cos(2 * Math.PI * c) * Math.sin(Math.PI * rt);
      
      addPoint(x, y, z, a);
    }
  }
  
  public void shadeSphere(double r, double offx, double offy, double step, Color a)
  {
    
  }
    
  
  public void generateCircle(double cx, double cy, double rx, double ry, Color c) {
    
    double x0, y0, x, y, step, r;
    step = .01;
    
    r = Distance(cx, cy, rx, ry);
    x0 = r + cx;
    y0 = cy;
    
    for( double t= step; t <= 1; t+= step) {
      
      x = r * Math.cos( 2 * Math.PI * t) + cx;
      y = r * Math.sin( 2 * Math.PI * t) + cy;
      
      addEdge(x0, y0, 0, x, y, 0, c);
      x0 = x;
      y0 = y;
    }

    addEdge(x0, y0, 0, r + cx, cy, 0, c);
  }    
  
  /* (x-cx)*(x-cx) + (y-cx)*(y-cx) = r*r
   * (x-cx)*(x-cx) = r*r - (y-cy)*(y-cy)
   * (x-cx) = Math.sqrt(r*r - (y-cx)*(y-cx))
   * x = Math.sqrt(r*r - (y-cx)*(y-cx)) + cx
   *  */
  public void shadeCircle(double cx, double cy, double rx, double ry, Color c) 
  {
    double r = Distance(cx, cy, rx, ry);
    double minY = cy - r;
    double maxY = cy + r;
    
    double x = -Math.sqrt(r*r - (minY-cy)*(minY-cy)) + cx;
    double xx = Math.sqrt(r*r - (minY-cy)*(minY-cy)) + cx;
    
    for (double y = minY; y < maxY; y++)
    {
      x = -Math.sqrt(r*r - (y-cy)*(y-cy)) + cx;
      xx = Math.sqrt(r*r - (y-cy)*(y-cy)) + cx;
      addEdge(x, y, 0, xx, y, 0, c);
    }
  }
  
  public void generateBox(double ax, double ay, double bx, double by, Color c)
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
    
    addEdge(x0, y0, 0, x0, y0, z, c);
    addEdge(x0, y0, 0, x1, y1, 0, c);
    addEdge(x0, y0, 0, x2, y2, 0, c);
    
    addEdge(x3, y3, 0, x3, y3, z, c);
    addEdge(x3, y3, 0, x1, y1, 0, c);
    addEdge(x3, y3, 0, x2, y2, 0, c);
    
    addEdge(x1, y1, z, x1, y1, 0, c);
    addEdge(x1, y1, z, x0, y0, z, c);
    addEdge(x1, y1, z, x3, y3, z, c);
    
    addEdge(x2, y2, z, x2, y2, 0, c);
    addEdge(x2, y2, z, x0, y0, z, c);
    addEdge(x2, y2, z, x3, y3, z, c);
  }
  
  public void shadeBox(double ax, double ay, double bx, double by, Color c)
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
    
    shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)0, XY_MODE); // Front
    shadeTriangle((int)x1, (int)y1, (int)x2, (int)y2, (int)x3, (int)y3, c, (int)0, XY_MODE);
    
    shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)z, XY_MODE); // Back
    shadeTriangle((int)x1, (int)y1, (int)x2, (int)y2, (int)x3, (int)y3, c, (int)z, XY_MODE);

    shadeTriangle((int)x0, (int)0, (int)x0, (int)z, (int)x2, (int)0, c, (int)y0, XZ_MODE); // Top
    shadeTriangle((int)x0, (int)z, (int)x2, (int)z, (int)x2, (int)0, c, (int)y0, XZ_MODE);
    
    shadeTriangle((int)x1, (int)0, (int)x1, (int)z, (int)x3, (int)0, c, (int)y1, XZ_MODE); // Bottom
    shadeTriangle((int)x1, (int)z, (int)x3, (int)z, (int)x3, (int)0, c, (int)y1, XZ_MODE);
    
    shadeTriangle((int)y0, (int)0, (int)y1, (int)0, (int)y1, (int)z, c, (int)x0, YZ_MODE); // Left
    shadeTriangle((int)y0, (int)0, (int)y1, (int)z, (int)y0, (int)z, c, (int)x0, YZ_MODE);
    
    shadeTriangle((int)y2, (int)0, (int)y3, (int)0, (int)y3, (int)z, c, (int)x2, YZ_MODE); // Right
    shadeTriangle((int)y3, (int)0, (int)y3, (int)z, (int)y2, (int)z, c, (int)x2, YZ_MODE);
  }
  
  public void generateTriangle(double x0, double y0, double x1, double y1, double x2, double y2, Color c)
  {
    addEdge(x0, y0, 0, x1, y1, 0, c);
    addEdge(x0, y0, 0, x2, y2, 0, c);
    addEdge(x1, y0, 0, x2, y2, 0, c);
  }
  
  public void generateTriPrism(double x0, double y0, double x1, double y1, double x2, double y2, Color c)
  {
    double d1 = Distance(x0, y0, x1, y1);
    double d2 = Distance(x0, y0, x2, y2);
    double d3 = Distance(x1, y1, x2, y2);
    double semi = (d1 + d2 + d3) / 3;
    double z = semi;
    
    addEdge(x0, y0, 0, x1, y1, 0, c);
    addEdge(x0, y0, 0, x2, y2, 0, c);
    addEdge(x1, y0, 0, x2, y2, 0, c);
    
    addEdge(x0, y0, z, x1, y1, z, c);
    addEdge(x0, y0, z, x2, y2, z, c);
    addEdge(x1, y0, z, x2, y2, z, c);
    
    addEdge(x0, y0, 0, x0, y0, z, c);
    addEdge(x1, y1, 0, x1, y1, z, c);
    addEdge(x2, y2, 0, x2, y2, z, c);
  }
  
  public void shadeTriPrism(double x0, double y0, double x1, double y1, double x2, double y2, Color c)
  {
    double d1 = Distance(x0, y0, x1, y1);
    double d2 = Distance(x0, y0, x2, y2);
    double d3 = Distance(x1, y1, x2, y2);
    double semi = (d1 + d2 + d3) / 3;
    double z = semi;
    
    shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)0, XY_MODE); // Front
    
    shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)z, XY_MODE); // Back
    
    //shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)z, XY_MODE);
    //shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)z, XY_MODE);
    
    //shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)z, XY_MODE);
    //shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)z, XY_MODE);
    
    //shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)z, XY_MODE);
    //shadeTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, c, (int)z, XY_MODE);
    
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
  
  public void addTriangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, Color a)
  {
    addEdge(x1, y1, z1, x2, y2, z2, a);
    addEdge(x1, y1, z1, x3, y3, z3, a);
    addEdge(x2, y2, z2, x3, y3, z3, a);
  }
    
    
    
    public void shadeTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color c, int depth, int xyz) // modify to take in z parameters
    {
      int lowestPoint = 1; // w/ lowest y
      int middlePoint = 2; // w/ middle y
      int highestPoint = 3; // w/ highest y
      
      int lowestY = y1; // lowest y
      int middleY = y2; // middle y
      int highestY = y3; // highest y
      
      int xwlowestY = x1; // x w/ lowest y
      int xwmiddleY = x2; // x w/ middle y
      int xwhighestY = x3; // x w/ highest y
      
      double m1, m2, m3;
      
      if (y2 < lowestY) {
        xwlowestY = x2; lowestY = y2; lowestPoint = 2;
      }
      if (y3 < lowestY) {
        xwlowestY = x3; lowestY = y3; lowestPoint = 3;
      }
      
      if (y1 > highestY) {
        xwhighestY = x1; highestY = y1; highestPoint = 1;
      }
      
      if (y2 > highestY) {
        xwhighestY = x2; highestY = y2; highestPoint = 2;
      }
      
      if (lowestPoint == 1 && highestPoint == 2) {
        xwmiddleY = x3; middleY = y3; middlePoint = 3;
      }
      
      if (lowestPoint == 1 && highestPoint == 3) {
        xwmiddleY = x2; middleY = y2; middlePoint = 2;
      }
      
      if (lowestPoint == 2 && highestPoint == 1) {
        xwmiddleY = x3; middleY = y3; middlePoint = 3;
      }
      
      if (lowestPoint == 2 && highestPoint == 3) {
        xwmiddleY = x1; middleY = y1; middlePoint = 1;
      }
      
      if (lowestPoint == 3 && highestPoint == 1) {
        xwmiddleY = x2; middleY = y2; middlePoint = 2;
      }
      
      if (lowestPoint == 3 && highestPoint == 2) {
        xwmiddleY = x1; middleY = y1; middlePoint = 1;
      }
      
      System.out.println("lowestY is " + lowestY +"\nmiddleY is " + middleY + "\nhighestY is " + highestY);
      
      if ( (xwmiddleY - xwlowestY) != 0)
        m1 = (middleY - lowestY) / (xwmiddleY - xwlowestY);
      else
        m1 = 0.000;
      if ( (xwhighestY - xwlowestY) != 0)
        m2 = (highestY - lowestY) / (xwhighestY - xwlowestY);
      else
        m2 = 0.000;
      if ( (xwhighestY - xwmiddleY) != 0)
        m3 = (highestY - middleY) / (xwhighestY - xwmiddleY);
      else
        m3 = 0.000;
      
      if (xyz == XY_MODE)
      {
        double x = xwlowestY; // double y = lowestY;
        double xx = xwlowestY; // double yy = lowestY;
        for (int y = lowestY; y <= middleY; y++) // m1, m2
        {
          addEdge(x, y, depth, xx, y, depth, c);
          x += m1; xx+= m2;
        }
        x = xwmiddleY;
        for (int y = middleY; y <= highestY; y++) // m3, m2
        {
          addEdge(x, y, depth, xx, y, depth, c);
          x += m3; xx+= m2;
        }
      }
      if (xyz == XZ_MODE)
      {
        double x = xwlowestY; // double y = lowestY;
        double xx = xwlowestY; // double yy = lowestY;
        for (int y = lowestY; y <= middleY; y++) // m1, m2
        {
          addEdge(x, depth, y, xx, depth, y, c);
          x += m1; xx+= m2;
        }
        x = xwmiddleY;
        for (int y = middleY; y <= highestY; y++) // m3, m2
        {
          addEdge(x, depth, y, xx, depth, y, c);
          x += m3; xx+= m2;
        }
      }
      if (xyz == YZ_MODE)
      {
        double x = xwlowestY; // double y = lowestY;
        double xx = xwlowestY; // double yy = lowestY;
        for (int y = lowestY; y <= middleY; y++) // m1, m2
        {
          addEdge(depth, x, y, depth, xx, y, c);
          x += m1; xx+= m2;
        }
        x = xwmiddleY;
        for (int y = middleY; y <= highestY; y++) // m3, m2
        {
          addEdge(depth, x, y, depth, xx, y, c);
          x += m3; xx+= m2;
        }
      }
    }
    
    public void drawPolygon(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4, Color a)
    {
      addEdge(x1, y1, z1, x2, y2, z2, a);
      addEdge(x2, y2, z2, x3, y3, z3, a);
      addEdge(x3, y3, z3, x4, y4, z4, a);
      addEdge(x4, y4, z4, x1, y1, z1, a);
    }
    
    public void shadePolygon(Polygon p, Color c)
    {
      int[] xxx = p.xpoints;
      int[] yyy = p.ypoints;
      
      double vmin = Integer.MAX_VALUE; // lowest vertex (smallest y)
      double vmax = 0; // highest vertex (biggest y)
      double vleft = Integer.MAX_VALUE; // leftmost vertex (smallest x)
      double vright = 0; // rightmost vertex (biggest y)
      
      double xL = 0, xR = 0, zL, zR;
      
      double dxleft = 0; // move up each line
      double dxright = 0;
      
      for (int i = 0; i < xxx.length; i++)
      {
        if (xxx[i] < vleft)
        {  vleft = xxx[i];   }
        if (xxx[i] > vright)
        {  vright = xxx[i];   }
      }
      
      for (int i = 0; i < yyy.length; i++)
      {
        if (yyy[i] < vleft)
        {  vmin = yyy[i];
           xL = xxx[i];     }
        if (xxx[i] > vright)
        {  vmax = yyy[i];
           xR = xxx[i]; }
      }
      
      zL = xL;
      zR = xR;
      
      dxleft = -(xL - vleft); // top - left
      dxright = xR - vright; // bottom - right
      
      for (int y = (int)vmin; y < vmax; y++)
      {
        addEdge(xL, y, zL, xR, y, zR, c);
        xL += dxleft/(vmax-vmin);
        xR += dxright/(vmax-vmin);
        
        if (xL == vleft)
        {
          dxleft = vleft - xR;
        }
        if (xR == vright)
        {
          dxright = vright - xL;
        }
      }
    }
    
    public void shadePolygons(Polygon[] polygons, Color c)
    {
      for (int i = 0; i < polygons.length; i++)
      {
        this.shadePolygon(polygons[i], c);
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
public void addPoint(double x, double y, double z, Color c) {
  
  if ( lastCol == m[0].length ) 
    grow();
  
  
  
  allColors.add(lastCol, c);
  //counter++;
  
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
                      double x1, double y1, double z1,
                      Color c) {
    
    addPoint(x0, y0, z0, c);
    addPoint(x1, y1, z1, c);
    
    
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
  
  public PolyMatrix copy() {
    
    PolyMatrix n = new PolyMatrix( m[0].length, color );
    for (int r=0; r<m.length; r++)
      for (int c=0; c<m[r].length; c++)
      n.m[r][c] = m[r][c];
    n.lastCol = lastCol;
    return n;
  }
}

// Need to figure out a way to tie a color to a polygon even after it changes
