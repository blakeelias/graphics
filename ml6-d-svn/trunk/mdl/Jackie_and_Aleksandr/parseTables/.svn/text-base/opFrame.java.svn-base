/*========== opFrame.java ==========
  Wrapper class for java's built in BufferedImage class.
  Allows use of java's DrawLine and image saving methods

  =========================*/
//package opwork;
package parseTables;
import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import javax.imageio.*;

public class opFrame {

    private int maxx, maxy, maxcolor;
    private BufferedImage bi;

    public opFrame() {
	maxx=600; maxy=300; maxcolor=255;
	bi = new BufferedImage(maxx,maxy,BufferedImage.TYPE_BYTE_INDEXED);
    }

    /*======== public void drawLines() ==========
      Inputs:  opPointMatrix pm
      Color c 
      Returns: 
      calls drawLine so that it draws all the lines within opPointMatrix pm
      ====================*/
    public void drawLines(opPointMatrix pm, Color c) {
	
	for (int i=0; i < pm.getLastCol() - 1; i+=2) 
	    drawLine( pm.getX(i), pm.getY(i),
		      pm.getX(i+1), pm.getY(i+1), c);
    }	


    /*======== public void drawLine() ==========
      Inputs:  int x0
      int y0
      int x1
      int y1
      Color c 
      Returns: 
      Wrapper for java's built in drawLine routine
      ====================*/
    public void drawLine(int x0, int y0, int x1, int y1, Color c) {
	Graphics2D g = bi.createGraphics();
	g.setColor(c);
	g.drawLine(x0,y0,x1,y1);
    }	
 
   
    /*======== public void save() ==========
      Inputs:  String filename 
      Returns: 
      saves the bufferedImage as a png file with the given filename
      ====================*/
 public void run(opPointMatrix pm, opFrame f, Stack<opPointMatrix> s)
{
}
    public void save(String filename) {
	try {
	    File fn = new File(filename);
	    ImageIO.write(bi,"png",fn);
	}
	catch (IOException e) {}
    }

}
