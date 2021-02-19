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

    public static double Distance(double x1, double y1, double x2, double y2) {

	return Math.sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

    public void renderCurve(double x1, double y1, double x2, double y2,
			    double x3, double y3, double x4, double y4, double step) {

	
	PointMatrix xcoefs = new PointMatrix(1); 
	PointMatrix ycoefs = new PointMatrix(1); 
	
	double x, y, z, ax, bx, cx, dx, ay, by, cy, dy;

	xcoefs.generateBezierCoefs(x1, x2, x3, x4);
	ycoefs.generateBezierCoefs(y1, y2, y3, y4);

	ax = xcoefs.getX(0);
	bx = xcoefs.getY(0);
	cx = xcoefs.getZ(0);
	dx = xcoefs.getD(0);

	ay = ycoefs.getX(0);
	by = ycoefs.getY(0);
	cy = ycoefs.getZ(0);
	dy = ycoefs.getD(0);

	for (double t=step; t <= 1; t+= step) {

	    x = ax * t * t * t + bx * t * t + cx * t + dx;
	    y = ay * t * t * t + by * t * t + cy * t + dy;
	    
	    addEdge(x1, y1, 0, x, y, 0);
	    x1 = x;
	    y1 = y;
	}
    }


    public void renderTorusMesh(double r1, double r2, double cx, double cy, double step) {

	int index, offset;

	int size = (int)(1.0 / step);
	PointMatrix tmp = new PointMatrix(size*size);
	
	tmp.generateTorus(r1, r2, cx, cy, step);

	//longitude lines
	for (int i=0; i < size; i++ )
	    for (int j=0; j < size; j++ ) {
		
		index = i * size + j;
		if ( j == size - 1 ) 
		    addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
			     tmp.getX(index + 1 - size), 
			     tmp.getY(index + 1 - size), 
			     tmp.getZ(index + 1 - size));
		else
		    addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
			     tmp.getX(index + 1), 
			     tmp.getY(index + 1), 
			     tmp.getZ(index + 1));
	    }

	//latitude lines
	for (int i=0; i < size; i++ )
	    for (int j=0; j < size; j++ ) {
		
		index = i * size + j;
		offset = (10 - index) - size * 
		    (int)Math.floor( (10 - index) / 20.0);

		
		if ( i == size - 1 ) 
		    addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
			     tmp.getX( index - i * size ), 
			     tmp.getY( index - i * size ), 
			     tmp.getZ( index - i * size ));
		else
		    addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
			     tmp.getX(index + size), 
			     tmp.getY(index + size), 
			     tmp.getZ(index + size));
	    }			     
	
	//Points only
	/*
	  for (int i=0; i < tmp.lastCol; i++)
	  addEdge( tmp.getX(i), tmp.getY(i), tmp.getZ(i),
	  tmp.getX(i), tmp.getY(i), tmp.getZ(i));
	*/
    }		

    public void generateTorus(double r1, double r2, double offx, double offy, double step) {

	double x, y, z, rt, c;

	for(rt=0; rt <= 1; rt+= step) 
	    for(c=0; c <= 1; c+= step) {

		x = r2 * Math.cos(2 * Math.PI * rt) + 
		    r1 * Math.cos(2 * Math.PI * c) * Math.cos(2 * Math.PI * rt)
		    + offx;
		y = r1 * Math.sin(2 * Math.PI * c) + offy;
		z = -1 * r2 * Math.sin(2 * Math.PI * rt) - 
		    r1 * Math.cos(2 * Math.PI * c) * Math.sin(2 * Math.PI * rt);
    
		addPoint( x, y, z);      
	    }
    }


    public void renderSphereMesh(double cx, double cy, double r, double step) {
	
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
			     tmp.getZ(index + 1 - size));
		else
		    addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
			     tmp.getX(index + 1), 
			     tmp.getY(index + 1), 
			     tmp.getZ(index + 1));
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
			     tmp.getZ( offset ));
		else
		    addEdge( tmp.getX(index), tmp.getY(index), tmp.getZ(index),
			     tmp.getX(index + size), 
			     tmp.getY(index + size), 
			     tmp.getZ(index + size));
	    }			     
		
	//Points only
	/*
	  for (int i=0; i < tmp.lastCol; i++)
	  addEdge( tmp.getX(i), tmp.getY(i), tmp.getZ(i),
	  tmp.getX(i), tmp.getY(i), tmp.getZ(i));
	*/
    }		
		
    public void generateSphere(double r, double offx, double offy, double step) {
	double x, y, z;
	for(double rt=0; rt <= 1; rt+= step )
	    for(double c=0; c <= 1; c+= step ) {

		x = r * Math.cos(2 * Math.PI * c) * 
		    Math.cos(Math.PI * rt) + offx;
		y = r * Math.sin(2 * Math.PI * c) + offy;
		z = -1 * r * Math.cos(2 * Math.PI * c) * Math.sin(Math.PI * rt);
		
		addPoint(x, y, z);
	    }
    }
		
    public void generateCircle(double cx, double cy, double rx, double ry) {

	double x0, y0, x, y, step, r;
      	step = .01;

	r = Distance(cx, cy, rx, ry);
	x0 = r + cx;
	y0 = cy;

	for( double t= step; t <= 1; t+= step) {
	    
	    x = r * Math.cos( 2 * Math.PI * t) + cx;
	    y = r * Math.sin( 2 * Math.PI * t) + cy;

	    addEdge(x0, y0, 0, x, y, 0);
	    x0 = x;
	    y0 = y;
	}

	addEdge(x0, y0, 0, r + cx, cy, 0);
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
    public double  getX(int c) {
	return m[0][c];
    }
    public double  getY(int c) {
	return m[1][c];
    }
    public double  getZ(int c) {
	return m[2][c];
    }
    public double  getD(int c) {
	return m[3][c];
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