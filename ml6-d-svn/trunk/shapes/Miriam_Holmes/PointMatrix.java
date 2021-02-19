import java.io.*;
import java.util.*;
import java.lang.Math.*;

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
    
    // plot a hermite curve between (x1, y1) and (x3, y3), using (x2, y2) and (x4, y4) to define tangents
    public void hermiteCurve(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {

	// in row major order
	Matrix inverse = new Matrix();
	inverse.m[0][0] = 2;
	inverse.m[0][1] = -2;
	inverse.m[0][2] = 1;
	inverse.m[0][3] = 1;
	inverse.m[1][0] = -3;
	inverse.m[1][1] = 3;
	inverse.m[1][2] = -2;
	inverse.m[1][3] = -1;
	inverse.m[2][0] = 0;
	inverse.m[2][1] = 0;
	inverse.m[2][2] = 1;
	inverse.m[2][3] = 0;
	inverse.m[3][0] = 1;
	inverse.m[3][1] = 0;
	inverse.m[3][2] = 0;
	inverse.m[3][3] = 0;

	// in column major order
	Matrix multiplicand = new Matrix(2);
	// x values
	multiplicand.m[0][0] = x1;
	multiplicand.m[1][0] = x3;
	multiplicand.m[2][0] = x2 - x1;
	multiplicand.m[3][0] = x4 - x3;
	// y values
	multiplicand.m[0][1] = y1;
	multiplicand.m[1][1] = y3;
	multiplicand.m[2][1] = y2 - y1;
	multiplicand.m[3][1] = y4 - y3;

	curvify(inverse, multiplicand);
    }
    
    // plot a bezier curve between (x1, y1) and (x3, y3), using (x2, y2) and (x4, y4) to pull the curve
    public void bezierCurve(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {

	// in row major order
	Matrix inverse = new Matrix();
	inverse.m[0][0] = -1;
	inverse.m[0][1] = 3;
	inverse.m[0][2] = 3;
	inverse.m[0][3] = 1;
	inverse.m[1][0] = -3;
	inverse.m[1][1] = -6;
	inverse.m[1][2] = 3;
	inverse.m[1][3] = 0;
	inverse.m[2][0] = -3;
	inverse.m[2][1] = 3;
	inverse.m[2][2] = 0;
	inverse.m[2][3] = 0;
	inverse.m[3][0] = 1;
	inverse.m[3][1] = 0;
	inverse.m[3][2] = 0;
	inverse.m[3][3] = 0;

	// in column major order
	Matrix multiplicand = new Matrix(2);
	// x values
	multiplicand.m[0][0] = x1;
	multiplicand.m[1][0] = x2;
	multiplicand.m[2][0] = x3;
	multiplicand.m[3][0] = x4;
	// y values
	multiplicand.m[0][1] = y1;
	multiplicand.m[1][1] = y2;
	multiplicand.m[2][1] = y3;
	multiplicand.m[3][1] = y4;

	curvify(inverse, multiplicand);
    }

    // curvify generates the points on the curve in the proper order and appends them to the PointMatrix given an inverse matrix and points or mainipulations of them
    private void curvify(Matrix inverse, Matrix multiplicand){
	final double step = .05;
	multiplicand.matrixMult(inverse);
	double ax = multiplicand.m[0][0];
	double bx = multiplicand.m[1][0];
	double cx = multiplicand.m[2][0];
	double dx = multiplicand.m[3][0];
	double ay = multiplicand.m[0][1];
	double by = multiplicand.m[1][1];
	double cy = multiplicand.m[2][1];
	double dy = multiplicand.m[3][1];

	addEdge(dx, dy, 0,
		ax * step*step*step + bx * step*step + cx * step + dx,
		ay * step*step*step + by * step*step + cy * step + dy,
		0);

	for (double t = step; t < 1; t += step){
	    addEdge(m[0][lastCol-1],
		    m[1][lastCol-1],
		    m[2][lastCol-1],
		    ax * t*t*t + bx * t*t + cx * t + dx,
		    ay * t*t*t + by * t*t + cy * t + dy,
		    0);
	}
    }

    public void renderTorusMesh(double r1, double r2, 
				double offx, double offy, double step) {
    }		


    //makes a torus	
    public void generateTorus(double rTorus, double rCircle, double offx, double offy) {
	final int nPhiSteps = 16; // number of times circle gets rotated (larger number --> smoother surface of torus)
	final int nThetaSteps = 10; // number of points on the circle (larger number --> smoother curve)
	PointMatrix[] circles = new PointMatrix[nPhiSteps]; // each circle is its own PointMatrix

	// INITIALIZES AN ARRAY OF THE TORUS'S POINTS
	for (int iCircle = 0; iCircle < nPhiSteps; iCircle++){
	    circles[iCircle] = new PointMatrix();
	    double phi = iCircle * 2*Math.PI/nPhiSteps;
	    for (int iThetaStep = 0; iThetaStep < nThetaSteps; iThetaStep++ ){
		double theta = iThetaStep * 2*Math.PI/nThetaSteps;
		circles[iCircle].addPoint(rTorus * Math.cos(phi) + rCircle * Math.cos(theta) * Math.cos(phi) + offx,
					      rCircle * Math.sin(theta) + offy,
					      -rTorus * Math.sin(phi) - rCircle * Math.cos(theta) * Math.sin(phi));
	     }
	}

	// MAKING CIRCLES
	for (int iCircles = 0; iCircles < nPhiSteps; iCircles++){
	    PointMatrix currentCircle = circles[iCircles];
	    for (int iPoints = 0; iPoints < nThetaSteps - 1; iPoints++){
		this.addEdge(currentCircle.m[0][iPoints],
			     currentCircle.m[1][iPoints],
			     currentCircle.m[2][iPoints],
			     currentCircle.m[0][iPoints + 1],
			     currentCircle.m[1][iPoints + 1],
			     currentCircle.m[2][iPoints + 1]);
	    }
	    
	    // makes the last point connect to the first point
	    this.addEdge(m[0][lastCol-1],
			 m[1][lastCol-1],
			 m[2][lastCol-1],
			 currentCircle.m[0][0],
			 currentCircle.m[1][0],
			 currentCircle.m[2][0]);
	 }

	// LATITUDE LINES
	 for (int latitude = 0; latitude < nThetaSteps; latitude++){
	    for (int longitude = 0; longitude < nPhiSteps - 1; longitude++){
		this.addEdge(circles[longitude].m[0][latitude],
			     circles[longitude].m[1][latitude],
			     circles[longitude].m[2][latitude],
			     circles[longitude + 1].m[0][latitude],
			     circles[longitude + 1].m[1][latitude],
			     circles[longitude + 1].m[2][latitude]);
	    }
	    
	    this.addEdge(circles[nPhiSteps - 1].m[0][latitude],
			 circles[nPhiSteps - 1].m[1][latitude],
			 circles[nPhiSteps - 1].m[2][latitude],
			 circles[0].m[0][latitude],
			 circles[0].m[1][latitude],
			 circles[0].m[2][latitude]);
	   
	}


    }


    public void renderSphereMesh(double r, double offx, double offy) {
    }		
	
    //makes a sphere	
    public void generateSphere(double r, double offx, double offy) {
	final int nPhiSteps = 20; // number of times semicircle gets rotated (== the number of lines of longitude) (larger number --> more longitude lines)
	final int nThetaSteps = 20; // number of points on the semicircle (larger number --> smoother curve)
	PointMatrix[] semicircles = new PointMatrix[nPhiSteps + 1]; // each semicircle is its own PointMatrix

	// INITIALIZES AN ARRAY OF THE SPHERE'S POINTS
	for (int iSemicircle = 0; iSemicircle < nPhiSteps; iSemicircle++){
	    semicircles[iSemicircle] = new PointMatrix();
	    for (int iThetaStep = 0; iThetaStep < nThetaSteps; iThetaStep++ ){		
		semicircles[iSemicircle].addPoint(r * Math.sin(iThetaStep * Math.PI/nThetaSteps) * Math.cos(iSemicircle * 2*Math.PI/nPhiSteps) + offx,
						  r * Math.cos(iThetaStep * Math.PI/nThetaSteps) + offy,
						  -r * Math.sin(iThetaStep * Math.PI/nThetaSteps) * Math.sin(iSemicircle * 2*Math.PI/nPhiSteps));		
	     }
	 }
	semicircles[nPhiSteps] = new PointMatrix();
	semicircles[nPhiSteps].addPoint(r * Math.sin((nThetaSteps - .01) * Math.PI/nThetaSteps) * Math.cos((nPhiSteps - .01) * 2*Math.PI/nPhiSteps) + offx,
					 r * Math.cos((nThetaSteps - .01) * Math.PI/nThetaSteps) + offy,
					-r * Math.sin((nThetaSteps - .01) * Math.PI/nThetaSteps) * Math.sin((nPhiSteps - .01) * 2*Math.PI/nPhiSteps));


	
	 // LONGITUDE LINES
	 for (int iSemicircles = 0; iSemicircles < nPhiSteps; iSemicircles++){
	     PointMatrix currentSemicircle = semicircles[iSemicircles];
	     for (int iPoints = 0; iPoints < nThetaSteps - 1; iPoints++){
		 this.addEdge(currentSemicircle.m[0][iPoints],
			      currentSemicircle.m[1][iPoints],
			      currentSemicircle.m[2][iPoints],
			      currentSemicircle.m[0][iPoints + 1],
			      currentSemicircle.m[1][iPoints + 1],
			      currentSemicircle.m[2][iPoints + 1]);
	     }

	     // makes the last point match the first point
	     m[0][lastCol-1] = currentSemicircle.m[0][nThetaSteps - 1];
	     m[1][lastCol-1] = currentSemicircle.m[1][nThetaSteps - 1];
	     m[2][lastCol-1] = currentSemicircle.m[2][nThetaSteps - 1];
	     m[3][lastCol-1] = currentSemicircle.m[3][nThetaSteps - 1];
	 }
	 for (int jSemicircles = 0; jSemicircles < nPhiSteps; jSemicircles++){
	     this.addEdge(semicircles[jSemicircles].m[0][nThetaSteps - 1],
			  semicircles[jSemicircles].m[1][nThetaSteps - 1],
			  semicircles[jSemicircles].m[2][nThetaSteps - 1],
			  semicircles[nPhiSteps].m[0][0],
			  semicircles[nPhiSteps].m[1][0],
			  semicircles[nPhiSteps].m[2][0]);
	 }
	 

	
	 
	// LATITUDE LINES
	 for (int latitude = 0; latitude < nThetaSteps; latitude++){
	    for (int longitude = 0; longitude < nPhiSteps - 1; longitude++){
		this.addEdge(semicircles[longitude].m[0][latitude],
			     semicircles[longitude].m[1][latitude],
			     semicircles[longitude].m[2][latitude],
			     semicircles[longitude + 1].m[0][latitude],
			     semicircles[longitude + 1].m[1][latitude],
			     semicircles[longitude + 1].m[2][latitude]);
	    }
	    
	    this.addEdge(semicircles[nPhiSteps - 1].m[0][latitude],
			 semicircles[nPhiSteps - 1].m[1][latitude],
			 semicircles[nPhiSteps - 1].m[2][latitude],
			 semicircles[0].m[0][latitude],
			 semicircles[0].m[1][latitude],
			 semicircles[0].m[2][latitude]);
	   
	}
	 

    }

    // does nothing
    public void renderCircle(double r, double offx, double offy, double step) {
	generateCircle(r, offx, offy, step);
    }

    /* generates the points on the circle and puts them into this PointMatrix in such a way that renderCircle works
       Circle centered at (x, y) with radius r: 
       X = (r)cos(T * 2PI) + offx 
       Y = (r)sin(T * 2PI) + offy 
     */
    public void generateCircle(double r, double offx, double offy, double step) {
	int startIndex = lastCol;
	for(double t = 0; t < 1; t +=step){
	    addEdge (r * Math.cos(t * 2 * Math.PI) + offx, r * Math.sin(t * 2 * Math.PI) + offx, 0,
		     r * Math.cos((t + step) * 2 * Math.PI) + offx, r * Math.sin((t + step) * 2 * Math.PI) + offx, 0
		    );
	}
	// makes the last point match the first point
	m[0][lastCol-1] = m[0][startIndex];
	m[1][lastCol-1] = m[1][startIndex];
	m[2][lastCol-1] = m[2][startIndex];
	m[3][lastCol-1] = m[3][startIndex];
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
	if (lastCol == m[0].length)
	    grow();
	m[0][lastCol] = x;
	m[1][lastCol] = y;
	m[2][lastCol] = z;
	m[3][lastCol] = 1;
	lastCol++;
    }
    public void addPoint(double x, double y, double z) {
	addPoint((int)Math.floor(x + .5), (int)Math.floor(y + .5), (int)Math.floor(z + .5));
    }

    /*======== public void addEdge() ==========
      Inputs:
      x, y, and z coordinates of the two points that define the line segment
      Returns: 
      adds the line connecting (x0, y0, z0) and (x1, y1, z1)
      to the calling object
      should use addPoint
      ====================*/
    public void addEdge(int x0, int y0, int z0, int x1, int y1, int z1) {
	addPoint(x0, y0, z0);
	addPoint(x1, y1, z1);
    }

    public void addEdge(double x0, double y0, double z0, double x1, double y1, double z1) {
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