/*========== Matrix.java ==========
  Matrix will hold a 2-d array of doubles and have a default size of 4x4.
  Handles basic matrix maintenence and math.
  Creates transformation matricies for tralation, scale and rotate
=========================*/

/****
  * Sample Matrix (4 rows X 5 columns)
  * 3 5 6 7 5 
  * 4 2 1 3 2
  * 0 9 8 3 2
  * 1 3 5 6 8
  * 
  * m[0][0] m[0][1] m[0][2] m[0][3] m[0][4]
  * m[1][0] m[1][1] m[1][2] m[1][3] m[1][4]
  * m[2][0] m[2][1] m[2][2] m[2][3] m[2][4]
  * m[3][0] m[3][1] m[3][2] m[3][3] m[3][4]
  * 
  * */


import java.io.*;
import java.util.*;


public class Matrix
{
  protected double[][] m;
  public static final int DEFAULT_SIZE = 4;
  
  /*===========Constructors================
      Default constructor creates a 4x4 matrix
      Second constructor creates a 4xN matrix
      */
  public Matrix() 
  {
    m = new double[DEFAULT_SIZE][DEFAULT_SIZE];
  }
  
  public Matrix(int c) 
  {
    m = new double[DEFAULT_SIZE][c];
  }
  
  public double[][] getMatrix()
  {
    return m;
  }
  
  public void setMatrix(double[][] matrix)
  {
    m = matrix;
  }


  /*===========grow================
      Increase the number of columns in a matrix by 10
      You can change the growth factor as you see fit
    */
  public void grow() 
  {
    double[][] n = new double[m.length][m[0].length + 10];
    for (int r=0; r<m.length; r++)
    {
      for (int c=0; c<m[r].length; c++)
      {
        n[r][c] = m[r][c];
      }
    }
    m = n;
  }

  /*======== public void clear() ==========
   Inputs:  
   Returns: 
   Sets every entry in the matrix to 0
   ====================*/
  public void clear() 
  {
    for (int i=0; i<m.length; i++) 
    {
      for (int j=0; j<m[i].length; j++) 
      {
        m[i][j] = 0;
      }
    }
  }

  /*===========ident================
   Turns this matrix into the indentity matrix
   You may assume the calling Matrix is square
   */
  public void makeIdentity() 
  {
    this.clear();
    int row = m.length;
    int col = m[row].length;
    for (int i = 0; i < row; i++)
    {
      m[i][i] = 1;
    }
  }

  /*===========scalarMult================
   Inputs:  double x
   
   multiply each element of the calling matrix by x
   */
  public void scalarMult( int s ) 
  {
    int psv = s;
    for (int i = 0; i < m.length; i++)
    {
      for (int j = 0; j < m[0].length; j++)
      {
        m[i][j] = psv * m[i][j];
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
  public void matrixMult( Matrix n ) 
  {
    double[][] q = n.getMatrix();
    double[][] psv = new double[m.length][q[0].length];
    
    for (int i = 0; i < m.length; i++) // for each row in M
    {
      for (int j = 0; j < q[0].length; j++) // for each column in N
      {
        for (int a = 0; a < m[0].length; a++) // for each column in M = for each row in N
        {
          psv[i][j] += m[i][a] * q[a][j];
        }
      }
    }
    
    this.setMatrix(psv);
  }
   
  /*===========copy================
   Create and return new matrix that is a duplicate 
   of the calling matrix
   */
  public Matrix copy() 
  {
    Matrix q = new Matrix(m[0].length);
    double[][] psv = m;
    
   /* for (int i = 0; i < m.length; i++)
    {
      for (int j = 0; j < m[0].length; j++)
      {
        psv[i][j] = m[i][j];
      }
    }*/
    
    q.setMatrix(psv);
    return q;
  }

  /*===========toString================
   Crate a readable String representation of the 
   calling matrix.
   */
  public String toString() 
  {
    String s = "";
    
    for (int i = 0; i < m.length; i++)
    {
      for (int j = 0; j < m[0].length; j++)
      {
        s = s + m[i][j] + " ";
      }
      s = s + "\n";
    }
    
    return s;
  }
  
}
