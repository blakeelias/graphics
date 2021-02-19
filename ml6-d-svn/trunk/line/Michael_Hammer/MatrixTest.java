import java.io.*;
import java.util.*;

import javax.swing.*;
import java.awt.*;

public class MatrixTest 
{
  public static void main(String[] args) 
  {    
    String s;
    Matrix m = new Matrix();
    
    m.makeIdentity();
    s = m.toString();
    System.out.println(s);
    
    m.scalarMult(5);
    s = m.toString();
    System.out.println(s);
    
    Matrix q = m.copy();
    s = q.toString();
    System.out.println(s);
    
    m.matrixMult(q);
    s = m.toString();
    System.out.println(s);
  }
}
