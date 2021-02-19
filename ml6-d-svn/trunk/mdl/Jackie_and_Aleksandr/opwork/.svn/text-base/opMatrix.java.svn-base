/*========== opMatrix.java ==========
  opMatrix will hold a 2-d array of doubles and have a default size of 4x4.
  Handles basic matrix maintenence and math.
  Creates transformation matricies for tralation, scale and rotate
=========================*/
package opwork;
import java.io.*;
import java.util.*;

public class opMatrix {

    public static final int DEFAULT_SIZE = 4;
    protected double[][] m;

    /*===========Constructors================
      Default constructor creates a 4x4 matrix
      Second constructor creates a 4xN matrix
    */
    public opMatrix() {
	m = new double[DEFAULT_SIZE][DEFAULT_SIZE];
    }
    public opMatrix(int c) {
	m = new double[DEFAULT_SIZE][c];
    }

    /*===========grow================
      Increase the number of columns in a matrix by 10
      You can change the growth factor as you see fit
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
      You may assume the calling opMatrix is square
    */
    public void ident() {
	
	for (int i=0; i<m.length; i++) {
	    for (int j=0; j<m[i].length; j++) {
		
		if (i==j)
		    m[i][j] = 1;
		else
		    m[i][j] = 0;
	    }
	}
    }

    /*===========scalarMult================
      Inputs:  double x
      
      multiply each element of the calling matrix by x
    */
    public void scalarMult( int s ) {

	for (int i=0; i<m.length; i++) 
	    for (int j=0; j<m[i].length; j++) 
		m[i][j] = m[i][j] * s;
    }		

    /*===========matrixMult================
      Multply matrix n by the calling matrix, modify
      the calling matrix to store the result.
      
      eg.
      In the call a.matrixMult(n), n will remain the same
      and a will now be the product of n * a
    */
    public void matrixMult( opMatrix n ) {

	double[][] tmp = new double[4][1];

	for (int c=0; c<m[0].length; c++) {
	    for (int r=0; r<4; r++) 
		tmp[r][0] = m[r][c];

	    for (int r=0; r<4; r++)
		m[r][c] = n.m[r][0] * tmp[0][0] +
		    n.m[r][1] * tmp[1][0] +
		    n.m[r][2] * tmp[2][0] +
		    n.m[r][3] * tmp[3][0];
	}
    }
   
    /*===========copy================
      Create and return new matrix that is a duplicate 
      of the calling matrix
    */
    public opMatrix copy() {

	opMatrix n = new opMatrix( m[0].length );
	for (int r=0; r<m.length; r++)
	    for (int c=0; c<m[r].length; c++)
		n.m[r][c] = m[r][c];

	return n;
    }

    /*===========toString================
      Crate a readable String representation of the 
      calling matrix.
    */
    public String toString() {

	String s = "";
	for (int i=0; i<m.length; i++) {
	    for (int j=0; j<m[i].length; j++)
		s = s + m[i][j] + " ";
	    s = s + "\n";
	}
	return s;
    }

    /*===========MakeTranslate================
      Turns the calling matrix into the appropriate
      translation matrix using x, y, and z as the translation
      offsets.
     */
    public void makeTranslate(double x, double y, double z) {

	ident();
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
    }
    
    /*===========MakeScale================
      Turns the calling matrix into the appropriate scale
      matrix using x, y and z as the scale factors.
     */
    public void makeScale(double x, double y, double z) {

	ident();
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
    }

    /*=========== MakeRotX ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and X
      as the axis of rotation.
    */
    public void makeRotX(double theta) {
	
	ident();
	m[1][1] = Math.cos( theta );
	m[1][2] = -1 * Math.sin( theta );
	m[2][1] = Math.sin( theta );
	m[2][2] = Math.cos( theta );
    }

    /*=========== MakeRotY ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and Y
      as the axis of rotation.
    */
    public void makeRotY(double theta) {

	ident();
	m[0][0] = Math.cos( theta );
	m[0][2] = Math.sin( theta );
	m[2][0] = -1 * Math.sin( theta );
	m[2][2] = Math.cos( theta );
    }

    /*=========== MakeRotZ ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and axis
      as the axis of rotation.
    */
    public void makeRotZ(double theta) {

	ident();
	m[0][0] = Math.cos( theta );
	m[0][1] = -1 * Math.sin( theta );
	m[1][0] = Math.sin( theta );
	m[1][1] = Math.cos( theta );
    }
}
