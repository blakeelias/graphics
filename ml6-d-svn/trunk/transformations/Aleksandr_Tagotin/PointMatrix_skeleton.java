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

    /*======== public void addPoint() ==========
      Inputs:  int x
      int y
      int z 
      Returns: 
      adds (x, y, z) to the calling object
      if lastcol is the maxmium value for this current matrix, 
      call grow
      ====================*/
    public void addPoint(int x, int y, int z) {
	int i=0;
	int j=0;
		
		
	if(lastCol==m[0].length)//(this.m[m.length][m[0].length]!= null)
	{grow();
	}
	else
	{m[0][lastCol]=x;
	m[1][lastCol]=y;
	m[2][lastCol]=z;
	m[3][lastCol]=0;
	lastCol++;
	 
	

	}
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
    public void addEdge(int x0, int y0, int z0, int x1, int y1, int z1) {
	addPoint(x0,y0,z0);
	addPoint(x1,y1,z1);
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
