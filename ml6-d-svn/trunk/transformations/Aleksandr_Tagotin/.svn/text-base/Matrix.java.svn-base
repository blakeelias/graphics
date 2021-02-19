/*========== Matrix.java ==========
  Matrix will hold a 2-d array of doubles and have a default size of 4x4.
  Handles basic matrix maintenence and math.
  Creates transformation matricies for tralation, scale and rotate
=========================*/

import java.io.*;
import java.util.*;
import java.lang.Math.*;

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
    */
    public void grow() {

    double[][] n = new double[m.length][m[0].length + 1];
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
    for(int i =0; i<m.length; i++)
    {
     for(int j=0; j<m[i].length;j++)
     {
      if(i==j)
      {m[i][j]=1;}
       else {m[i][j]=0;}
     }   
    }

    }

    /*===========scalarMult================
      Inputs:  double x
     
      multiply each element of the calling matrix by x
    */
    public void scalarMult( int s ) {
    for(int i =0; i<m.length; i++)
    {
     for(int j=0; j<m[i].length;i++)
     {
      m[i][j]*= s;
     }   
    }
    }       

    /*===========matrixMult================
      Multply matrix n by the calling matrix, modify
      the calling matrix to store the result.
     
      eg.
      In the call a.matrixMult(n), n will remain the same
      and a will now be the product of n * a
    */
    public void matrixMult( Matrix n ) {
 //borrow code in comment box here
/*	 if (n.m[0].length != this.m.length){
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
*/
	//my code
	int k=0;
	int a=0;
	int b=0;
	int sum=0;
	Matrix na = new Matrix(m[0].length);
	for(int i=0;i < n.m.length;i++)
	{
	 for(int j=0;j<m[0].length;j++)
	 {
	  for(;a<n.m.length;a=a)
	   {
		
		sum+=n.m[i][a]*m[b][j];
		a++;
		b++;
	   }
	    na.m[i][j]=sum;
	    sum=0;
	 }	
	}
	m=na.m;

    }
  
    /*===========copy================
      Create and return new matrix that is a duplicate
      of the calling matrix
    */
    public Matrix copy() {
    Matrix n = new Matrix(m.length);//((int)m.length,(int)m[0].length);
    for(int i =0; i<m.length; i++)
    {for(int j =0; j<m[0].length; j++)
     {n.m[i][j]=m[i][j];
     }
    }
    return n;
    }

    /*===========toString================
      Crate a readable String representation of the
      calling matrix.
    */
    public String toString() {
    String s = new String();
    for(int i =0; i<m.length; i++)
    {for(int j =0; j<m[0].length; j++)//changed +[0]
     {s+=m[i][j]+" ";
      //System.out.println(m[i][j]+" ");
     }
      s+= "\n";
    }
    return s;
/*
//temp borrow code, mine above
StringBuilder sb = new StringBuilder();
        Formatter f = new Formatter (sb, Locale.US);
        for (int r = 0; r < m.length; r++){
            for (int c = 0; c < m[0].length; c++){
                f.format("%1$12.4g ", m[r][c]);
            }
            f.format("%n");
        }
        return sb.toString();
*/
    }

    /*===========MakeTranslate================
      Turns the calling matrix into the appropriate
      translation matrix using x, y, and z as the translation
      offsets.
     */
    public void MakeTranslate(int x, int y, int z) {
	int i=0;
	int j=0;
	int k=0;
	for(;i<m.length;i++)
	{
	 for(;j<m[0].length;j++)
	  {
	    if(i==j)
	    {m[i][j]=1;}
	    if(j==m[0].length)
	    {
               if(i==1){m[i][j]=x;} if(i==2){m[i][j]=y;} if(i==3){m[i][j]=z;}
	    }
	    else {m[i][j]=0;}
	  }	
	}
    }
   
    /*===========MakeScale================
      Turns the calling matrix into the appropriate scale
      matrix using x, y and z as the scale factors.
     */
    public void MakeScale(int x, int y, int z) {
	int i=0;
	int j=0;
	int k=0;
	for(;i<m.length;i++)
	{
	 for(;j<m[0].length;j++)
	  {
	    if(i==j)
	     {if(i==1){m[i][j]=x;} if(i==2){m[i][j]=y;} if(i==3){m[i][j]=z;} 			else{m[i][j]=1;}
	     }
	    else {m[i][j]=0;}
	  }	
	}
    }

    /*=========== MakeRotX ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and X
      as the axis of rotation.
    */
    public void MakeRotX(double theta) { // Matrix elements are hard coded
	int i=0;
	int j=0;
	int k=0;
	this.ident();
	m[1][1] = Math.cos(Math.PI/180*theta);
        m[1][2] = -Math.sin(Math.PI/180*theta);
        m[2][1] = Math.sin(Math.PI/180*theta);
        m[2][2] = Math.cos(Math.PI/180*theta);
//some code substitution at the last minute for debugging, should be equivalent 
	/*or(;i<m.length;i++)
	{
	 for(;j<m[0].length;j++)
	  {
	   if(i==1||i>3)
	    { if(j==i){m[i][j]=1;}else{m[i][j]=0;} 
	    }
	   if(i==2)
	    { if(j==2){m[i][j]=Math.cos(Math.PI/180*theta);}
	      if(j==3){m[i][j]=-1*Math.sin(Math.PI/180*theta);}
else{m[i][j]=0;}
	    }
	   if(i==3)
	    { if(j==2){m[i][j]=Math.sin(Math.PI/180*theta);}
	      if(j==3){m[i][j]=-1*Math.cos(Math.PI/180*theta);}
else{m[i][j]=0;} 
	    }
	   
	    
	  }	
	}*/
    }

    /*=========== MakeRotY ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and Y
      as the axis of rotation.
    */
    public void MakeRotY(double theta) {
int i=0;
	int j=0;
	int k=0;
this.ident();
	m[0][0] = Math.cos(Math.PI/180*theta);
        m[0][2] = Math.sin(Math.PI/180*theta);
        m[3][0] = -Math.sin(Math.PI/180*theta);
        m[3][2] = Math.cos(Math.PI/180*theta);

/*	for(;i<m.length;i++)
	{
	 for(;j<m[0].length;j++)
	  {
	   if(i==2||i>3)
	    { if(j==i){m[i][j]=1;}else{m[i][j]=0;} 
	    }
	   if(i==1)
	    { if(j==1){m[i][j]=Math.cos(Math.PI/180*theta);}
	      if(j==3){m[i][j]=Math.sin(Math.PI/180*theta);}
else{m[i][j]=0;} 
	    }
	   if(i==3)
	    { if(j==1){m[i][j]=-1*Math.sin(Math.PI/180*theta);}
	      if(j==3){m[i][j]=Math.cos(Math.PI/180*theta);}
else{m[i][j]=0;} 
	    }
	   
	    
	  }	
	}*/
	
    }

    /*=========== MakeRotZ ================
      Turns the calling matrix into the appropriate rotation
      matrix using theta as the angle of rotation and axis
      as the axis of rotation.
    */
	public void MakeRotZ(double theta, char axis) {}
    public void MakeRotZ(double theta) {

	int i=0;
	int j=0;
	int k=0;
this.ident();
m[0][0] = Math.cos(Math.PI/180*theta);
        m[0][1] = -Math.sin(Math.PI/180*theta);
        m[1][0] = Math.sin(Math.PI/180*theta);
        m[1][1] = Math.cos(Math.PI/180*theta);

/*	for(;i<m.length;i++)
	{
	 for(;j<m[0].length;j++)
	  {
	   if(i>2)
	    { if(j==i){m[i][j]=1;}else{m[i][j]=0;} 
	    }
	   if(i==1)
	    { if(j==1){m[i][j]=Math.cos(Math.PI/180*theta);}
	      if(j==2){m[i][j]=-1*Math.sin(Math.PI/180*theta);}
else{m[i][j]=0;}
	    }
	   if(i==2)
	    { if(j==1){m[i][j]=Math.sin(Math.PI/180*theta);}
	      if(j==2){m[i][j]=-1*Math.cos(Math.PI/180*theta);}
else{m[i][j]=0;} 
	    }
	   
	   
	  }	
	}
    }*/
}}
