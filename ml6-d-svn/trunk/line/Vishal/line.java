import java.io.*;
import java.util.*;

import javax.swing.*;
import java.awt.*;


public class Frame {

    public static final int XRES = 400;
    public static final int YRES = 400;
    public static final int MAXCOLOR = 255;


    private int width, height, maxcolor;
    private Color[][] screen;

    public Frame() {
	width = XRES; 
	height = YRES; 
	maxcolor = MAXCOLOR;
	screen = new Color[width][height];
	clear_screen();
    }

    public void clear_screen() {
	Color c = new Color(0, 0, 0);
	for (int x=0; x < width; x++) 
	    for (int y=0; y < height; y++){ 
		screen[x][y] = c;
	    }
    }
    
    public void plot(Point p, Color c){
	int newx = x;
	int newy = y;
	screen[newy][newx] = c;
    }		
    
    public void save(String filename) { // filename must end in .ppm

	try {
	    FileOutputStream fstream = new FileOutputStream(filename);
	    PrintWriter f = new PrintWriter(fstream);
	    f.printf("P3\n%d %d\n%d\n", width, height, maxcolor); // standard header for .ppm file

	    for (int y=0; y < height; y++) { 
		for (int x=0; x < width; x++) 
		    f.printf("%d %d %d ",
			     screen[x][y].getRed(), screen[x][y].getGreen(), screen[x][y].getBlue());
		f.printf("\n");
	    }
	    f.close();
	}
	catch (IOException e) {}
	
    }

    public void drawLine(Point a, Point b, Color c){
	Point mainPoint;
	int dy, dx;

	if (a.compareTo(b) > 0){
	    mainPoint = a;
	    start = b;
	    end = mainPoint;
	}

	dy = b.y - a.y;
	dx = a.x - b.x;

	// m = 0 case
	if (a.y == b.y)
	    for (mainPoint = a; mainPoint.x <= b.x; mainPoint.x++)
		plot(mainPoint, c);

	// m = infinity case
	else if (a.x == b.x){
	    for (mainPoint = a; mainPoint.y <= b.y; mainPoint.y++)
		plot(mainPoint, c);
	}

	// m = 1 case
	else if (dx == dy){
	    for (mainPoint = a; mainPoint.x <= b.x; mainPoint.x++){
		plot(mainPoint, c);
		mainPoint.y++;
	    }
	}

	// m = -1 case
	else if (dx == (-dy)){
	    for (mainPoint = a; mainPoint.x <= b.x; mainPoint.x++){
		plot(mainPoint, c);
		mainPoint.y--;
	    }
	}

	// 0 < m < 1 case (line in octants 1 or 5)
	else if (0 < dy && dy < dx){
	    int d;  
	    d = 2*dy - dx;
           
            while (mainPoint.x <= b.x){
  	       plot(mainPoint, c);
  	       if (d < 0){
    		    mainPoint.x++;
		    d += dy;
 		}
 		 else{
  		  mainPoint.y++;
 	 	  mainPoint.x++;
    	          d += dy - dx;
  	        }
	     }
	}

	// 1 < m case (line in octants 2 or 6)
	else if (dx<dy){
	    int d;  
	    d = 2*dy - dx;
           
            while (mainPoint.y <= b.y){
  	       plot(mainPoint, c);
  	       if (d < 0){
    		    mainPoint.x++;
		    d += dx;
 		}
 		 else{
 	 	  mainPoint.x++;
    	          d += dx - dy;
  	        }
	     }
	}


	// -1 < m < 0 case (line in octants 4 or 8)
	else if (-dx < dy && dy < 0){
	    int d;  
	    d = 2*dy - dx;
            while (mainPoint.x <= b.x){
  	       plot(mainPoint, c);
  	       if (d < 0){
    		    mainPoint.x++;
		    d -= dy;
 		}
 		 else{
 	 	  mainPoint.y--;
    	          d += -dy - dx;
  	        }
	     }
	}

	// m < -1 case (line in octants 3 or 7)
	else if (dy <-dx){
	    int d;  
	    d = 2*dy - dx;
           
            while (mainPoint.y <= b.y){
  	       plot(mainPoint, c);
  	       if (d < 0){
		    d -= dx;
 		}
 		 else{
 	 	  mainPoint.x--;
    	          d -= dx + dy;
  	        }
	     }
	}

	}
	
    }
}
