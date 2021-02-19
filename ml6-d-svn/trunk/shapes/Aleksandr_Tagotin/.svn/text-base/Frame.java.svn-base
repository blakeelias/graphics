/*========== Frame.java ==========
  Wrapper class for java's built in BufferedImage class.
  Allows use of java's DrawLine and image saving methods

  =========================*/

import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import javax.imageio.*;

public class Frame {

    private int maxx, maxy, maxcolor;
    private BufferedImage bi;

    public Frame() {
	maxx=300; maxy=300; maxcolor=255;
	bi = new BufferedImage(maxx,maxy,BufferedImage.TYPE_BYTE_INDEXED);
    }

    /*======== public void drawLines() ==========
      Inputs:  PointMatrix pm
      Color c 
      Returns: 
      calls drawLine so that it draws all the lines within PointMatrix pm
      ====================*/
    public void drawLines(PointMatrix pm, Color c) {
	
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
    public void save(String filename) {
	try {
	    File fn = new File(filename);
	    ImageIO.write(bi,"png",fn);
	}
	catch (IOException e) {}
    }

}