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
  
    private PointMatrix edges;
    private Matrix transform;
    private BufferedImage bi;
    private PointMatrix tmpline;
    private Color c;
    boolean drawing=false;    
    
    public Canvas() {
	edges = new PointMatrix();
	tmpline = new PointMatrix();
	transform = new Matrix();
	transform.ident();
	c = Color.blue;
    }
  
    public void apply() {
	edges.matrixMult( transform );
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
    public void setDrawing(double x0, double y0, double x1, double y1, double x2, double y2, double rx, double ry, double rz, int mode) {
      
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
		tmpline.renderSphereMesh(x1, y1, x0, y0, rx, ry, rz);
		tmpline.generateSphere(r, x1, y1, step);
	    }
      
	if ( mode == gui.TORUS_MODE)
	    {
		//tmpline.renderTorusMesh(x1, y1, xc, yc, x0, y0, rx, ry, rz);
		//tmpline.generateTorus(r1, r2, xc, yc, step);
	    }
      
	/*   if ( mode == gui.HERMITE_MODE)
      {
        step = 0.01;
        tmpline.renderHermiteCurve(x0, y0, x1, y1, x2, y2, rx, ry, step);
      }
      
      if ( mode == gui.BEZIER_MODE)
      {
        step = 0.01;
        tmpline.renderBezierCurve(x0, y0, x1, y1, x2, y2, rx, ry, step);
	}*/

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
    
    //canvas.addSphere(xes[0], ys[0], x, y, rx, ry, rz);
    //generateSphere(double r, double offx, double offy, double step)
    //renderSphereMesh(double cx, double cy, double rx, double ry, double rotx, double roty, double rotz)
    public void addSphere(int x0, int y0, int xc, int yc, double rx, double ry, double rz)
    {
	double step = 0.01;
	double a = rx-xc; double b = ry-yc;
	double r = Math.sqrt(a*a + b*b);
	edges.renderSphereMesh(xc, yc, x0, y0, rx, ry, rz);
	edges.generateSphere(r, xc, yc, step);
	this.update(this.getGraphics());
}
    
//canvas.addTorus(xes[0], ys[0], xes[1], ys[1], x, y, rx, ry, rz);
//renderTorusMesh(double ox, double oy, double cx, double cy, double rx, double ry, double rotx, double roty, double rotz)
//generateTorus(double r1, double r2, double offx, double offy, double step)
public void addTorus(int x0, int y0, int x1, int y1, int xc, int yc, double rx, double ry, double rz)
{
    double step = 0.01;
    double a = rx-xc; double b = ry-yc;
    double r1 = Math.sqrt(a*a + b*b);
    double a2 = rx-x1; double b2 = ry-y1;
    double r2 = Math.sqrt(a2*a2 + b2*b2);
    edges.renderTorusMesh(x1, y1, xc, yc, x0, y0, rx, ry, rz);
    edges.generateTorus(r1, r2, xc, yc, step);
}
     
// public void renderHermiteCurve(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double step)
public void addHermite(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
    double step = 0.01;
    edges.renderHermiteCurve(x0, y0, x1, y1, x2, y2, x3, y3, step);
}
    
// public void renderBezierCurve(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double step)
public void addBezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
    double step = 0.01;
    edges.renderBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3, step);
}
    
public void clearTmp() {
    tmpline.clear();
}
    
public void clearPoints() {
    edges.clear();
    this.update(this.getGraphics());
}
     
public void paintComponent(Graphics g) {
       
    super.paintComponent(g);
    bi = (BufferedImage)this.createImage(WIDTH, HEIGHT);
    Graphics2D g2 = bi.createGraphics();
       
    if (drawing) {
	g2.setColor(c.red);
	for (int i=0; i < tmpline.getLastCol() - 1; i+=2) 
	    g2.drawLine((int)tmpline.getX(i),(int)tmpline.getY(i),
			(int)tmpline.getX(i+1),(int)tmpline.getY(i+1));
    }
       
    int col = edges.getLastCol();
       
    g2.setColor(c);
       
    for (int i=0; i < col - 1; i+=2) {
	g2.drawLine( (int)edges.getX(i), (int)edges.getY(i), 
                     (int)edges.getX(i+1), (int)edges.getY(i+1));     
    } 
       
    ((Graphics2D)g).drawImage(bi,null,0,0);
}
}