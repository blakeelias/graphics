import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.image.*;
import javax.imageio.*;

public class Canvas extends JPanel {

    private PointMatrix edges;
    private BufferedImage bi;
    private PointMatrix tmpline;
    private Color c;
    boolean drawing=false;    
    
    public Canvas() {
	edges = new PointMatrix();
	tmpline = new PointMatrix(2);	
	c = Color.blue;
    }
    

    /*======== public void setDrawing() ==========
      Inputs:  int x0
               int y0
	       int x1
	       int y1 
      Returns: 
      sets drawing to true and adds a line to the tmpLine PointMatrix

      ====================*/
    public void setDrawing(int x0, int y0, int x1, int y1) {
    }

    
    public void stopDrawing() {
	drawing=false;
    }
  
    public BufferedImage getBufferedImage() {
	return bi;
    }

    public Dimension getPreferredSize() {
	return new Dimension(300,300);
    }


    /*======== public void addLine() ==========
      Inputs:  int x0
               int y0
	       int z0
	       int x1
	       int y1
	       int z1 
      Returns: 
      Adds the specified line to the edges PointMatrix
      ====================*/
    public void addLine(int x0, int y0, int z0, int x1, int y1, int z1) {
    }


    /*======== public void addPoint() ==========
      Inputs:  int x0
         int y0
         int z0 
      Returns: 
      add a single point to the edges PointMatrix
      ====================*/
    public void addPoint(int x0, int y0, int z0) {
    }


    public void clearTmp() {
	tmpline.clear();
    }



    /*======== public void paintComponent() ==========
      Inputs:  Graphics g 
      Returns: 
      draws the edges stored in tmpLine or edges to the canvas
      you must update this to work with matricies instead of an 
      array of Line objects   
      ====================*/
    public void paintComponent(Graphics g) {

	super.paintComponent(g);
	bi = (BufferedImage)this.createImage(300,300);
	Graphics2D g2 = bi.createGraphics();

	//this should only be the temporary lines
	if (drawing) {
	    g2.setColor(c.red);
	    //draw tmpline, the java drawLine call is as follows:
	    //g2.drawLine( x0, y0, x1, y1);
	}
	
	g2.setColor(c);
	
	//use java's drawline to draw the lines in the edges PointMatrix

	((Graphics2D)g).drawImage(bi,null,0,0);
    }
}
