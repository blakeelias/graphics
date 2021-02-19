package nonMDL;

/*========== Matrix.java ==========
  Matrix will hold a 2-d array of doubles and have a default size of 4x4.
  Handles basic matrix maintenence and math.
  Creates transformation matricies for tralation, scale and rotate
=========================*/

import java.io.*;
import java.util.*;

public class Matrix {

    public static final int DEFAULT_SIZE = 4;
    protected double[][] m;

    /*===========Constructors================
      Default constructor creates a 4x4 matrix
      Second constructor creates a 4xN matrix
    */
    public Matrix() {
	m = new double[DEFAULT_SIZE][DEFAULT_SIZE];
    }
    public Matrix(int c) {
	m = new double[DEFAULT_SIZE][c];
    }

    /*===========grow================
      Increase the number of columns in a matrix by 10
      You can change the growth factor as you see fit
      Puts old matrix starting in the upper left corner
    */
    public void grow() {

	double[][] n = new double[m.length][m[0].length + 10];
	for (int r=0; r<m.length; r++)
	    for (int c=0; c<m[r].length; c++)
		n[r][c] = m[r][c];
	
	m = n;
    }

    /*======== public void clear() ==========
      Inputs:  
      Returns: 
      Sets every entry in the matrix to 0
      ====================*/
    public void clear() {

	for (int i=0; i<m.length; i++) 
	    for (int j=0; j<m[i].length; j++) 
		m[i][j] = 0;
    }

    /*===========ident================
      Turns this matrix into the indentity matrix
      You may assume the calling Matrix is square
    */
    public void ident() {
	for (int r = 0; r < m.length; r++)
	    for (int c = 0; c < m[0].length; c++)
		m[r][c] = r == c ? 1 : 0;
    }

    /*===========scalarMult================
      Inputs:  double s
      
      multiply each element of the calling matrix by s
    */
    public void scalarMult( int s ) {
	for (int r = 0; r < m.length; r++)
	    for (int c = 0; c < m[0].length; c++)
		m[r][c] *= s;
    }		

    /*===========matrixMult================
      Multply matrix n by the calling matrix, modify
      the calling matrix to store the result.
      
      eg.
      In the call a.matrixMult(n), n will remain the same
      and a will now be the product of n * a
    */
    public void matrixMult( Matrix n ) {
	if (n.m[0].length != this.m.length){
	    throw new UnsupportedOperationException("the number of columns in left matrix doesn't match the number of rows in the right matrix");
	}
	double[][] r = new double[n.m.length][this.m[0].length];
	for (int rr = 0; rr < r.length; rr++)
	    for (int rc = 0; rc < r[0].length; rc++){
		r[rr][rc] = 0;
		for (int i = 0; i < this.m.length; i++)
		    r[rr][rc] += n.m[rr][i] * this.m[i][rc];
	    }
	this.m = r;
    }
   
    /*===========copy================
      Create and return new matrix that is a duplicate 
      of the calling matrix
    */
    public Matrix copy() {
	Matrix returner = new Matrix(m[0].length);
	for (int r = 0; r < m.length; r++)
	    for (int c = 0; c < m[0].length; c++)
		returner.m[r][c] = this.m[r][c];
	return returner;
    }

    /*===========toString================
      Create a readable String representation of the 
      calling matrix.
    */
    public String toString() {
	StringBuilder sb = new StringBuilder();
	Formatter f = new Formatter (sb, Locale.US);
	for (int r = 0; r < m.length; r++){
	    for (int c = 0; c < m[0].length; c++){
		f.format("%1$12.4g ", m[r][c]);
	    }
	    f.format("%n");
	}
	return sb.toString();
    }
    /*===========MakeTranslate================
      Turns the calling matrix into the appropriate
      translation matrix using x, y, and z as the translation
      offsets.
     */
    public void MakeTranslate(double x, double y, double z) {
	ident();
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
    }
    
    /*===========MakeScale================
      Turns the calling matrix into the appropriate scale
      matrix using x, y and z as the scale factors.
     */
    public void MakeScale(double x, double y, double z) {
	// ident();  // unnecessary because scale factors go on the diagonal, where the 1s would go
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
    }

    /*=========== MakeRotX ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and X
      as the axis of rotation.  RADIANS
    */
    public void MakeRotX(double theta){
	ident();
	m[1][1] = Math.cos(theta);
	m[1][2] = -Math.sin(theta);
	m[2][1] = Math.sin(theta);
	m[2][2] = Math.cos(theta);
    }

    /*=========== MakeRotY ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and Y
      as the axis of rotation.  RADIANS
    */
    public void MakeRotY(double theta) {
	ident();
	m[0][0] = Math.cos(theta);
	m[0][2] = Math.sin(theta);
	m[2][0] = -Math.sin(theta);
	m[2][2] = Math.cos(theta);
    }

    /*=========== MakeRotZ ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and axis
      as the axis of rotation.  RADIANS
    */
    public void MakeRotZ(double theta) {
	ident();
	m[0][0] = Math.cos(theta);
	m[0][1] = -Math.sin(theta);
	m[1][0] = Math.sin(theta);
	m[1][1] = Math.cos(theta);
    }
}
