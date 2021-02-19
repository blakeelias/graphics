package nonMDL;

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
    private final static int maxRGB = 16777216;  // 2^24
    private final static int NUMCOLORS = 21;  // number of different colors used on triangles

    public Frame() {
	maxx=300; maxy=300; maxcolor=255;
	bi = new BufferedImage(maxx,maxy,BufferedImage.TYPE_BYTE_INDEXED);
    }

    // connects triplets of points into triangles
    public void drawTriangles(PointMatrix pm, Color c) {
	Color triangleColor;

	final double // must be 0-1
	    iAmbR = 1, iDifR = 1, iSpeR = 1,
	    iAmbG = 1, iDifG = 1, iSpeG = 1,
	    iAmbB = 1, iDifB = 1, iSpeB = 1;
	Lighting light = new Lighting();

	for (int i = 0; i < pm.getLastCol(); i += 3){

	    Vector intoTheLight, normal, leg1, leg2, view;
	    double IRed, IGreen, IBlue;

	    view = new Vector(new PointMatrix(0, 0, -1));

	    // calculate intensity values for red, green, and blue for this triangle
	    intoTheLight = new Vector(new PointMatrix(pm.m[0][i], pm.m[1][i], pm.m[2][i]), light.source).normalize();
	    leg1 = new Vector(new PointMatrix(pm.m[0][i], pm.m[1][i], pm.m[2][i]),
			      new PointMatrix(pm.m[0][i+1], pm.m[1][i+1], pm.m[2][i+1]));
	    leg2 = new Vector(new PointMatrix(pm.m[0][i+1], pm.m[1][i+1], pm.m[2][i+1]),
			      new PointMatrix(pm.m[0][i+2], pm.m[1][i+2], pm.m[2][i+2]));
	    normal = leg1.normalizedNormalVector(leg2);


	    IRed = iAmbR*light.kAmbR +
		iDifR*light.kDifR*intoTheLight.dotProduct(normal) +
		iSpeR*light.kSpeR*(view.dotProduct(normal.scalarMult(2*intoTheLight.dotProduct(normal)).minus(intoTheLight)));

	    IGreen = iAmbG*light.kAmbG +
		iDifG*light.kDifG*intoTheLight.dotProduct(normal) +
		iSpeG*light.kSpeG*(view.dotProduct(normal.scalarMult(2*intoTheLight.dotProduct(normal)).minus(intoTheLight)));

	    IBlue = iAmbB*light.kAmbB +
		iDifB*light.kDifB*intoTheLight.dotProduct(normal) +
		iSpeB*light.kSpeB*(view.dotProduct(normal.scalarMult(2*intoTheLight.dotProduct(normal)).minus(intoTheLight)));

	    // set triangleColor, based on the original c
	    triangleColor =
		new Color((int)(Math.max(Math.min(c.getRed()*IRed, 255), 0)),
			  (int)(Math.max(Math.min(c.getGreen()*IGreen, 255), 0)),
			  (int)(Math.max(Math.min(c.getBlue()*IBlue, 255), 0)));

	    drawLine((int)Math.floor(pm.m[0][i] + .5),
		     (int)Math.floor(pm.m[1][i] + .5),
		     (int)Math.floor(pm.m[0][i+1] + .5),
		     (int)Math.floor(pm.m[1][i+1] + .5),
		     triangleColor);
	    drawLine((int)Math.floor(pm.m[0][i+1] + .5),
		     (int)Math.floor(pm.m[1][i+1] + .5),
		     (int)Math.floor(pm.m[0][i+2] + .5),
		     (int)Math.floor(pm.m[1][i+2] + .5),
		     triangleColor);
	    drawLine((int)Math.floor(pm.m[0][i+2] + .5),
		     (int)Math.floor(pm.m[1][i+2] + .5),
		     (int)Math.floor(pm.m[0][i] + .5),
		     (int)Math.floor(pm.m[1][i] + .5),
		     triangleColor);
	    
	    // finding highest and lowest vertices
	    int vHiIndex = // index in pm of the vertex with the lowest y value (the highest point)
	    	pm.m[1][i] < pm.m[1][i+1] ?
	    	pm.m[1][i] < pm.m[1][i+2] ? i : i+2 :
	    	pm.m[1][i+1] < pm.m[1][i+2] ? i+1 : i+2;
	    int vLoIndex = // index in pm of the vertex with the highest y value (the lowest point)
	    	pm.m[1][i] > pm.m[1][i+1] ?
	    	pm.m[1][i] > pm.m[1][i+2] ? i : i+2 :
	    	pm.m[1][i+1] > pm.m[1][i+2] ? i+1 : i+2;
	    int vOtherIndex = // on left or right
		3 * (i+1) - (vLoIndex + vHiIndex);

	    int xHiLo, xOther;
	    for(int y = (int)Math.floor(pm.m[1][vHiIndex] + .5) + 1; 
		(int)Math.floor(pm.m[1][vLoIndex] + .5) - y > 1;
		y++){
		xHiLo = gimmeX(y, pm.m[1][vHiIndex], pm.m[1][vLoIndex], pm.m[0][vHiIndex], pm.m[0][vLoIndex]);
		xOther = y < pm.m[1][vOtherIndex] ? // note: smaller y is higher on the screen
		    gimmeX (y, pm.m[1][vHiIndex], pm.m[1][vOtherIndex], pm.m[0][vHiIndex], pm.m[0][vOtherIndex]) :
		    gimmeX (y, pm.m[1][vLoIndex], pm.m[1][vOtherIndex], pm.m[0][vLoIndex], pm.m[0][vOtherIndex]);
		drawLine(xHiLo, y, xOther, y, triangleColor);
	    }

	    //  c = new Color((c.getRGB() + maxRGB/NUMCOLORS) % maxRGB);
	}
    }

    //given two  points on a line and a y value, gives x value
    private int gimmeX(double y, double y0, double y1, double x0, double x1){
	return (int)Math.floor((y - y0)*(x1 -x0)/(y1 - y0) + x0 +.5); //in the real world, wouldn't call this every time and make it compute the slope every time...etc.
    }

    /*======== public void drawLines() ==========
      Inputs:  PointMatrix pm
      Color c 
      Returns: 
      calls drawLine so that it draws all the lines within PointMatrix pm
      ====================*/
    public void drawLines(PointMatrix pm, Color c) {
	for (int i = 0; i < pm.getLastCol(); i++){
	    drawLine((int)Math.floor(pm.m[0][i] + .5),
		     (int)Math.floor(pm.m[1][i] + .5),
		     (int)Math.floor(pm.m[0][++i] + .5),
		     (int)Math.floor(pm.m[1][i] + .5),
		     c);
	}
    }	

    public void drawLine (double x0, double y0, double x1, double y1, Color c){
	drawLine((int)Math.floor(x0 + .5),
		 (int)Math.floor(y0 + .5),
		 (int)Math.floor(x1 + .5),
		 (int)Math.floor(y1 + .5),
		 c);
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