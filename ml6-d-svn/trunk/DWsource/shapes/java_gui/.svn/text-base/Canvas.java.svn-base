import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.image.*;
import javax.imageio.*;

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
	tmpline = new PointMatrix(2);
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
    
    public void setDrawing(double x0, double y0, double x1, double y1, double x2, double y2, double rx, double ry, double rz, int mode) {
	
	if ( mode == gui.LINE_MODE )
	    tmpline.addEdge( x0, y0, 0, x1, y1, 0);
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
