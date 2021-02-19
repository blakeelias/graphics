import java.io.*;
import java.util.*;

import javax.swing.*;
import java.awt.*;


public class Frame 
{
  public static final int XRES = 400;
  public static final int YRES = 400;
  public static final int MAX_COLORS = 255;
  
  
  private int width, height, maxcolor;
  private Color[][] screen;
  
  public Frame() 
  {
    width = XRES; 
    height = YRES; 
    maxcolor = MAX_COLORS;
    screen = new Color[height][width];
    clear_screen();
  }
  
  public void clear_screen() 
  {
    for (int x=0; x < width; x++) 
    {
     for (int y=0; y < height; y++)
     { 
       Color c = new Color(0, 0, 0);
       screen[x][y] = c;
     }
    }
  }
    
  public void plot(int x, int y, Color c) 
  {
    int newx = x;
    int newy = y;
    screen[newx][newy] = c;
  }  
    
  public void save(String filename) 
  {  
    try {
      FileOutputStream fstream = new FileOutputStream(filename);
      PrintWriter f = new PrintWriter(fstream);
      f.printf("P3\n%d %d\n%d\n", width, height, maxcolor);
      
      for (int y=0; y < height; y++) 
      { 
        for (int x=0; x < width; x++) 
        {
          f.printf("%d %d %d ", screen[y][x].getRed(), screen[y][x].getGreen(), screen[y][x].getBlue());
        }
        f.printf("\n");
     }
      f.close();
    }
    catch (IOException e) {}
    
  }
  
  public void drawLine(int x0, int y0, int x1, int y1, Color qqq)
  {
    int a, b; // x cor 
    int c, d; // y cor
    if (x0 < x1)
    {
      a = x0; c = y0; // (a, c)   Left Point
      b = x1; d = y1; // (b, d)   Right Point
    }
    else
    {
      a = x1; c = y1; // (a, c)   Left Point
      b = x0; d = y0; // (b, d)   Right Point
    }
    
    int m, psv;
    
    if ((b-a) == 0) // Vertical Line
    {
      while(c < d)
      {
        plot(a, c, qqq);
        c++;
      }
      return;
    }
    
    int dy = d-c;
    int dx = b-a;
    m = dy / dx; // Slope
    
    if (m == 0) // Horizontal Line
    {
      while (a < b)
      {
        plot(a, c, qqq);
        a++;
      }
      return;
    }
    
    if (m == 1) // m = 1
    {
      while (a < b)
      {
        plot(a, c, qqq);
        a++;
        c++;
      }
      return;
    }
    
    if (m == -1) // m == -1
    {
      while (a < b)
      {
        plot(a, c, qqq);
        a++;
        c--;
      }
      return;
    }
    
    /* Octant 1*/
    if (m > 0 && m < 1) // 0 < m < 1
    {
      psv = dy - dx/2;
      while (a < b)
      {
        plot(a, c, qqq);
        if (psv < 0) // Above Line
        {
          a++;
          psv = psv + dy; // A
        }
        else // (psv > 0) Below Line
        {
          a++; c++;
          psv = psv + dy - dx; // A + B
        }
      }
      return;
    }
    
    /* Octant 2*/
    if (m > 1) // 1 < m < 10^4312
    {
      psv = dy/2 - dx;
      while (a < b)
      {
        plot(a, c, qqq);
        if (psv < 0) // To The Right
        {
          c++;
          psv = psv + dx; // -B
        }
        else // (psv > 0) To The Left
        {
          a++; c++;
          psv = psv + dx - dy; // A - B
        }
      }
      return;
    }
    
    /* Octant 7*/
    if (m < -1) // -10^4312 < m < -1
    {
      psv = dy/2 + dx;
      while (a < b)
      {
        plot(a, c, qqq);
        if (psv < 0) // To The Right
        {
          c--;
          psv = psv - dx; // B
        }
        else // (psv > 0) To The Left
        {
          a++; c--;
          psv = psv - dx + dy; // A + B
        }
      }
      return;
    }
    
    /* Octant 8*/
    if (m < 0 && m > -1) // -1 < m < 0
    {
      psv = dy + dx/2;
      while (a < b)
      {
        plot(a, c, qqq);
        if (psv < 0) // Above Line
        {
          a++;
          psv = psv - dy; // -A
        }
        else // (psv > 0) Below Line
        {
          a++; c--;
          psv = psv - dy + dx; // -A - B
        }
      }
      return;
    }
  }
}
