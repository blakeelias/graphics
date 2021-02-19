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

    //Don't worry about this method yet
    public void renderCurve(double x1, double y1, double x2, double y2,
                            double x3, double y3, double x4, double y4, double step) {
    }

    public void renderTorusMesh(double ox, double oy, double cx, double cy, 
				double rx, double ry, 
				double rotx, double roty, double rotz) {
    }		

    public void generateTorus(double r1, double r2, 
			      double offx, double offy, double step) {
    }


    public void renderSphereMesh(double cx, double cy, 
				 double rx, double ry, 
				 double rotx, double roty, double rotz) {
    }		
		
    public void generateSphere(double r, double offx, double offy, double step) {
    }
		
    public void generateCircle(double cx, double cy, double rx, double ry) {

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