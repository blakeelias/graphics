import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.image.*;
import javax.imageio.*;
import java.lang.Object;

public class Canvas extends JPanel {
  
  public static final int WIDTH = 600;
  public static final int HEIGHT = 600;
  
  //private PointMatrix edges;
  private PointMatrix edges;
  //private ArrayList<PointMatrix> edges;
  private int psv = 0;
  private PolyMatrix polygons;
  private Matrix transform;
  private BufferedImage bi;
  private PointMatrix tmpline;
  private PolyMatrix tmppoly;
  private Color c;
  //private ArrayList<Color> colors;
  private int psvc;
  private int theMode;
  
  boolean drawing=false;    
  private int shade;
    
  public Canvas() {
    edges = new PointMatrix();
    polygons = new PolyMatrix(Color.blue);
    /*for (int i = 0; i < edges.size(); i++)
    {
      PointMatrix tm = new PointMatrix();
      edges.set(0, tm);
    }*/
    //colors = new ArrayList<Color>(100);
    tmpline = new PointMatrix();
    tmppoly = new PolyMatrix(Color.blue);
    transform = new Matrix();
    transform.ident();
    c = Color.blue;
    
  }
  
  public void apply() {
    edges.matrixMult( transform );
    polygons.matrixMult ( transform );
    transform.ident();
    this.update(this.getGraphics());
  } 
  
    public void scale(double x, double y, double z) {
      transform.makeScale(x, y, z);
      apply();
    }
    
    public void translate(double x, double y, double z) {
      transform.makeTranslate(x, y, z);
      apply();
    }
    
    public void rotX( double theta ) {
      theta = theta * (Math.PI / 180);
      transform.makeRotX( theta );
      apply();
    }
    
    public void rotY( double theta ) {
      theta = theta * (Math.PI / 180);
      transform.makeRotY( theta );
      apply();
    }
    
    public void rotZ( double theta ) {
      theta = theta * (Math.PI / 180);
      transform.makeRotZ( theta );
      apply();
    }
    
    //canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, rx, ry, rz, CIRCLE_MODE);
    //canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, rx, ry, rz, SPHERE_MODE);
    //canvas.setDrawing(xes[0], ys[0], xes[1], ys[1], x, y, rx, ry, rz, TORUS_MODE);
    public void setDrawing(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double rx, double ry, double rz, int mode, int[] color, int shading) {
      
      shade = shading;
      Color tmp = new Color(color[0], color[1], color[2]);
      if (c.hashCode() != tmp.hashCode() )
      {
        //edges.add(psv, cur);
        //colors.add(psv, c);
        c = tmp;
        psv++;
        //cur.clear(); // Once PM cur clears, it is lost in the arraylist. Thus, this DOES NOT separate colors
        //Instead, save an array of numbers that tells you when to change color maybe??? or add color as a parameter to addEdge
      }
      
      theMode = mode;
      double step;
      
      if ( mode == gui.LINE_MODE )
        tmpline.addEdge( x0, y0, 0, x1, y1, 0);
      
      if ( mode == gui.CIRCLE_MODE)
      {
        tmpline.generateCircle(x1, y1, x0, y0);
      }
      
      if ( mode == gui.SPHERE_MODE)
      {
        step = 0.01;
        double a = x1-x0; double b = y1-y0;
        double r = Math.sqrt(a*a + b*b);
       // tmpline.renderSphereMesh(x1, y1, x0, y0, rx, ry, rz);
        tmpline.generateSphere(r, x0, y0, step);
       // tmpline.renderSphereMesh(x0, y0, r, step);
      }
      
      if ( mode == gui.BOX_MODE)
      {
        tmpline.generateBox(x0, y0, x1, y1);
      }
      
      if ( mode == gui.TORUS_MODE)
      {
        step = 0.01;
        double e = Math.abs(x1-x0);
        double f = Math.abs(y1-y0);
        double r1 = Math.sqrt(e*e + f*f);
        double g = x2 - x1;
        double h = y2 - y1;
        double r2 = Math.sqrt( g*g +h*h);
       // tmpline.generateTorus(rx, ry, x0, y0, step);
        tmpline.generateTorus(r1/5, r2/5, x0, y0, step);
       // tmpline.renderTorusMesh(x1,y1,x0,y0,x2,y2,rx,ry,rz);
      }
      
      if ( mode == gui.HERMITE_MODE)
      {
        step = 0.01;
        tmpline.renderHermiteCurve(x0, y0, x1, y1, x2, y2, x3, y3, step);
      }
      
      if ( mode == gui.BEZIER_MODE)
      {
        step = 0.01;
        tmpline.renderBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3, step);
      }
      
      if ( mode == gui.TRIPRISM_MODE)
      {
        double a = x0; double b = y0;
        double xm = x1; double ym = y1;
        double d1 = PointMatrix.Distance(a, b, xm, ym);
        double d2 = PointMatrix.Distance(a, ym, xm, ym);
        double d3 = PointMatrix.Distance(a, ym, a, b);
        double cos = d2 / d1;
        double sin = d3 / d1;
        
        double c = xm - d1*cos; double d = ym - d1*sin;
        double e = xm + d1*cos; double f = ym + d1*sin;
        
        tmpline.generateTriPrism(a,b,c,d,e,f);
      }
      
      if ( mode == gui.POLY_CIRCLE_MODE)
      {
        tmppoly.generateCircle(x1, y1, x0, y0, Color.red);
        if (shading == 1)
          tmppoly.shadeCircle(x1, y1, x0, y0, Color.red);
      }
      
      if ( mode == gui.POLY_BOX_MODE) // It is separated for shading and lighting
      {
        tmppoly.generateBox(x0, y0, x1, y1, Color.red);
        if (shading == 1)
          tmppoly.shadeBox(x0, y0, x1, y1, Color.red);
      }
      
      if ( mode == gui.POLY_SPHERE_MODE)
      {
        step = 0.01;
        double a = x1-x0; double b = y1-y0;
        double r = Math.sqrt(a*a + b*b);
       // tmpline.renderSphereMesh(x1, y1, x0, y0, rx, ry, rz);
        tmppoly.generateSphere(r, x0, y0, step, Color.red);
       // tmpline.renderSphereMesh(x0, y0, r, step);
        if (shading == 1)
          tmppoly.shadeSphere(r, x0, y0, step, Color.red);
      }
      
      if ( mode == gui.POLY_TORUS_MODE)
      {
        step = 0.01;
        double e = Math.abs(x1-x0);
        double f = Math.abs(y1-y0);
        double r1 = Math.sqrt(e*e + f*f);
        double g = x2 - x1;
        double h = y2 - y1;
        double r2 = Math.sqrt( g*g +h*h);
       // tmpline.generateTorus(rx, ry, x0, y0, step);
        tmppoly.generateTorus(r1/5, r2/5, x0, y0, step, Color.red);
       // tmpline.renderTorusMesh(x1,y1,x0,y0,x2,y2,rx,ry,rz);
        if (shading == 1)
          tmppoly.shadeTorus(r1/5, r2/5, x0, y0, step, Color.red);
      }
      
      if ( mode == gui.POLY_TRIPRISM_MODE)
      {
        double a = x0; double b = y0;
        double xm = x1; double ym = y1;
        double d1 = PointMatrix.Distance(a, b, xm, ym);
        double d2 = PointMatrix.Distance(a, ym, xm, ym);
        double d3 = PointMatrix.Distance(a, ym, a, b);
        double cos = d2 / d1;
        double sin = d3 / d1;
        
        double c = xm - d1*cos; double d = ym - d1*sin;
        double e = xm + d1*cos; double f = ym + d1*sin;
        
        tmppoly.generateTriPrism(a,b,c,d,e,f, Color.red);
        if (shading == 1)
          tmppoly.shadeTriPrism(a,b,c,d,e,f, Color.red);
      }
      
      if ( mode == gui.POLY_TRIANGLE_MODE)
      {
        
      }
      
      if ( mode == gui.POLY_RECTANGLE_MODE)
      {
        
      }
      
      if ( mode == gui.POLY_QUAD_MODE)
      {
        
      }

      drawing=true;
    }
    
    public void stopDrawing() {
      drawing=false;
    }
    
    public BufferedImage getBufferedImage() {
      return bi;
    }
    
    public Dimension getPreferredSize() {
      return new Dimension(WIDTH, HEIGHT);
    }
    
    public void addLine(int x0, int y0, int z0, 
                        int x1, int y1, int z1) {
      edges.addEdge(x0,y0,z0,x1,y1,z1);
      this.update(this.getGraphics());
    }
    
    public void addPoint(int x0, int y0, int z0) {

      edges.addPoint(x0,y0,z0);
      this.update(this.getGraphics());
    }
    
    //canvas.addCircle(xes[0], ys[0], x, y);
    public void addCircle(int x0, int y0, int xc, int yc)
    {
      edges.generateCircle(xc, yc, x0, y0);
      this.update(this.getGraphics());
    }
    
    public void addPolyCircle(int x0, int y0, int xc, int yc, Color c)
    {
      polygons.generateCircle(xc, yc, x0, y0, c);
      if (shade == 1)
        polygons.shadeCircle(xc, yc, x0, y0, c);
      this.update(this.getGraphics());
    }
    
    //canvas.addSphere(xes[0], ys[0], x, y, rx, ry, rz);
    //generateSphere(double r, double offx, double offy, double step)
    //renderSphereMesh(double cx, double cy, double rx, double ry, double rotx, double roty, double rotz)
    public void addSphere(int x0, int y0, int xc, int yc, double rx, double ry, double rz)
    {
      double step = 0.01;
      double a = x0-xc; double b = y0-yc;
      double r = Math.sqrt(a*a + b*b);
      //edges.renderSphereMesh(xc, yc, x0, y0, rx, ry, rz);
      edges.generateSphere(r, xc, yc, step);
      //edges.renderSphereMesh(xc, yc, r, step);
      this.update(this.getGraphics());
    }
    
    public void addPolySphere(int x0, int y0, int xc, int yc, double rx, double ry, double rz, Color c)
    {
      double step = 0.01;
      double a = x0-xc; double b = y0-yc;
      double r = Math.sqrt(a*a + b*b);
      //edges.renderSphereMesh(xc, yc, x0, y0, rx, ry, rz);
      polygons.generateSphere(r, xc, yc, step, c);
      if (shade == 1)
        polygons.shadeSphere(r, xc, yc, step, c);
      //edges.renderSphereMesh(xc, yc, r, step);
      this.update(this.getGraphics());
    }
    
    //canvas.addTorus(xes[0], ys[0], xes[1], ys[1], x, y, rx, ry, rz);
    //renderTorusMesh(double ox, double oy, double cx, double cy, double rx, double ry, double rotx, double roty, double rotz)
    //generateTorus(double r1, double r2, double offx, double offy, double step)
    public void addTorus(int x0, int y0, int x1, int y1, int xc, int yc, double rx, double ry, double rz)
    {
      double step = 0.01;
      double a = x0-xc; double b = y0-yc;
      double r1 = Math.sqrt(a*a + b*b);
      double a2 = x1-x0; double b2 = y1-y0;
      double r2 = Math.sqrt(a2*a2 + b2*b2);
     // edges.renderTorusMesh(x1, y1, xc, yc, x0, y0, rx, ry, rz);
      edges.generateTorus(r1/5, r2/5, xc, yc, step);
      this.update(this.getGraphics());
    }
    
    public void addPolyTorus(int x0, int y0, int x1, int y1, int xc, int yc, double rx, double ry, double rz, Color c)
    {
      double step = 0.01;
      double a = x0-xc; double b = y0-yc;
      double r1 = Math.sqrt(a*a + b*b);
      double a2 = x1-x0; double b2 = y1-y0;
      double r2 = Math.sqrt(a2*a2 + b2*b2);
     // edges.renderTorusMesh(x1, y1, xc, yc, x0, y0, rx, ry, rz);
      polygons.generateTorus(r1/5, r2/5, xc, yc, step, c);
      if (shade == 1)
        polygons.shadeTorus(r1/5, r2/5, xc, yc, step, c);
      this.update(this.getGraphics());
    }
     
    // public void renderHermiteCurve(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double step)
    public void addHermite(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
    {
      double step = 0.01;
      edges.renderHermiteCurve(x0, y0, x1, y1, x2, y2, x3, y3, step);
      this.update(this.getGraphics());
    }
    
    // public void renderBezierCurve(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double step)
    public void addBezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
    {
      double step = 0.01;
      edges.renderBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3, step);
      this.update(this.getGraphics());
    }
    
    public void addBox(double ax,double ay,double bx,double by,double rx, double ry, double rz)
    {
      edges.generateBox(ax, ay, bx, by);
      this.update(this.getGraphics());
    }
    
    public void addPolyBox(double ax,double ay,double bx,double by,double rx, double ry, double rz, Color c)
    {
      polygons.generateBox(ax, ay, bx, by, c);
      if (shade == 1)
        polygons.shadeBox(ax, ay, bx, by, c);
      this.update(this.getGraphics());
    }
    
    public void addTriPrism(double xa, double ya, double xb, double yb)
    {
      double x0 = xa; double y0 = ya;
      double xm = xb; double ym = yb;
      double d1 = PointMatrix.Distance(x0, y0, xm, ym);
      double d2 = PointMatrix.Distance(x0, ym, xm, ym);
      double d3 = PointMatrix.Distance(x0, ym, x0, y0);
      double cos = d2 / d1;
      double sin = d3 / d1;
      
      double x1 = xm - d1*cos; double y1 = ym - d1*sin;
      double x2 = xm + d1*cos; double y2 = ym + d1*sin;
      
      edges.generateTriPrism(x0,y0,x1,y1,x2,y2);
      this.update(this.getGraphics());
    }
    
    public void addPolyTriPrism(double xa, double ya, double xb, double yb, Color c)
    {
      double x0 = xa; double y0 = ya;
      double xm = xb; double ym = yb;
      double d1 = PointMatrix.Distance(x0, y0, xm, ym);
      double d2 = PointMatrix.Distance(x0, ym, xm, ym);
      double d3 = PointMatrix.Distance(x0, ym, x0, y0);
      double cos = d2 / d1;
      double sin = d3 / d1;
      
      double x1 = xm - d1*cos; double y1 = ym - d1*sin;
      double x2 = xm + d1*cos; double y2 = ym + d1*sin;
      
      polygons.generateTriPrism(x0,y0,x1,y1,x2,y2, c);
      if (shade == 1)
        polygons.shadeTriPrism(x0,y0,x1,y1,x2,y2, c);
      this.update(this.getGraphics());
    }
    
    public void clearTmp() {
      tmpline.clear();
      tmppoly.clear();
    }
    
    public void clearPoints() {
      //for (int i = 0; i < edges.size(); i++)
      edges.clear();
      polygons.clear();
      this.update(this.getGraphics());
    }
    
    
    
    
    
    // I = ambient + diffuse + specular
    // I = Ia*ka + 
    //     Id*kd*edges.dotProduct(Camera, Normal) +
    //     Is*ks*edges.dotProduct( (2*Normal*edges.dotProduct(Camera, Normal) - Camera), View)
    
    public void paintComponent(Graphics g) {
      
      super.paintComponent(g);
      bi = (BufferedImage)this.createImage(WIDTH, HEIGHT);
      Graphics2D g2 = bi.createGraphics();
      
      //tmp tmp tmp
      if (drawing) {
        g2.setColor(c.red);
        for (int i=0; i < tmpline.getLastCol() - 1; i+=2) 
          g2.drawLine((int)tmpline.getX(i),(int)tmpline.getY(i),
                      (int)tmpline.getX(i+1),(int)tmpline.getY(i+1));
        
        for (int i=0; i < tmppoly.getLastCol() - 1; i+=2) {
          g2.drawLine((int)tmppoly.getX(i),(int)tmppoly.getY(i),
                      (int)tmppoly.getX(i+1),(int)tmppoly.getY(i+1));
        }
      }
      
      
      int col = edges.getLastCol();
      int polyCol = polygons.getLastCol();
      
      /*Random r = new Random();
       int rand = r.nextInt(255);
       int rand2 = r.nextInt(255);
       int rand3 = r.nextInt(255);
       Color rr = new Color(rand, rand2, rand3);*/
      
      //g2.setColor(rr);
      //g2.setColor(colors.get(j));
      g2.setColor(c);
      
      //System.out.println("J is " +j);
      
      /*for (int i = 0; i < psv; i++)
       {
       System.out.println("Color " + i + "is " + colors.get(i).toString());
       }*/
      
      //final final final
      for (int i=0; i < col - 1; i+=2) {
        g2.drawLine( (int)edges.getX(i), (int)edges.getY(i), 
                    (int)edges.getX(i+1), (int)edges.getY(i+1));     
      }
      
      for (int i=0; i < polyCol - 1; i+=2) {
        c = polygons.allColors.get(polyCol - 1);
        g2.drawLine( (int)polygons.getX(i), (int)polygons.getY(i), 
                    (int)polygons.getX(i+1), (int)polygons.getY(i+1));
      } 
      
      
      ((Graphics2D)g).drawImage(bi,null,0,0);
    }
}
