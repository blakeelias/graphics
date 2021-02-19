import java.io.*;
import java.util.*;

public class PointMatrix extends Matrix
{
  private int lastCol;
  
  public PointMatrix()
  {
    super();
    lastCol = 0;
  }

  public PointMatrix(int c)
  {
    super(c);
    lastCol = 0;
  }
  
  /*======== accessors ==========
      ====================*/
  public int getLastCol()
  {
    return lastCol;
  }
  public int getX(int c)
  {
    return (int)m[0][c];
  }
  public int getY(int c)
  {
    return (int)m[1][c];
  }
  public int getZ(int c)
  {
    return (int)m[2][c];
  }
  public void clear()
  {
    super.clear();
    lastCol = 0;
  }
  
  public PointMatrix copy()
  {   
    PointMatrix n = new PointMatrix(m[0].length);
    for (int r=0; r<m.length; r++)
    {
      for (int c=0; c<m[r].length; c++)
      {
        n.m[r][c] = m[r][c];
      }
    }
    n.lastCol = lastCol;
    return n;
  }
  
  /*======== public void addPoint() ==========
   Inputs:  
   int x
   int y
   int z
   Returns:
   adds (x, y, z) to the calling object
   if lastcol is the maxmium value for this current matrix,
   call grow
   ====================*/
  public void addPoint(int x, int y, int z)
  {
    if (lastCol == m[0].length)
    {
      this.grow();
    }
    lastCol += 1;
    this.setval(0, lastCol, x);
    this.setval(1, lastCol, y);
    this.setval(2, lastCol, z);
  }
  
  public void addPoint(int x, int y, int z, int column)
  {
    if (lastCol == m[0].length)
    {
      this.grow();
    }
    lastCol += 1;
    this.setval(0, column, x);
    this.setval(1, column, y);
    this.setval(2, column, z);
  }
  
  /*======== public void addEdge() ==========
   Inputs:  
   int x0
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
  public void addEdge(int x0, int y0, int z0, int x1, int y1, int z1)
  {
    this.addPoint(x0, y0, z0);
    this.addPoint(x1, y1, z1);
  }
  
  public void addEdge(int x0, int y0, int z0, int x1, int y1, int z1, int column)
  {
    this.addPoint(x0, y0, z0, column);
    this.addPoint(x1, y1, z1, column + 1);
  }
}