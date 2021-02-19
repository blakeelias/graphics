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
	int newy = YRES - 1 - p.y;
	// checks if the point is valid
	if ( p.x >= 0 && p.x < XRES && newy >= 0 && newy < YRES )
	    screen[p.x][newy] = c;
	/*
	  someday, throw an exception
	else
	    throw (new Exception e);
	*/
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

    public void drawLine(Point start, Point end, Color c){
	Point p;
	int deltay, deltax;
	// makes sure that start is to the left of end
	if (start.compareTo(end) > 0){
	    p = start;
	    start = end;
	    end = p;
	}
	deltay = end.y - start.y;
	deltax = end.x - start.x;

	// horizotnal
	if (start.isHorizontal(end))
	    for (p = start; p.x <= end.x; p.x++)
		plot(p, c);

	// vertical
	else if (start.isVertical(end)){
	    if (start.y > end.y){
		p = start;
		start = end;
		end = p;
	    }
	    for (p = start; p.y <= end.y; p.y++)
		plot(p, c);
	}

	// slope == 1
	else if (deltax == deltay){
	    for (p = start; p.x <= end.x; p.x++){
		plot(p,c);
		p.y++;
	    }
	}

	// slope == -1
	else if (deltax == -deltay){
	    for (p = start; p.x <= end.x; p.x++){
		plot(p,c);
		p.y--;
	    }
	}

	// octants 1 and 5 (0 < slope < 1)
	else if (0 < deltay && deltay < deltax){
	    int d;  // d is a scaled version of the vertical distance fom the ideal line's height at x+1 down to the midpoint of y and y+1 (a negative value means that the point is above the line, so the pixel below the line (y) is to be lit up; a positive value means that the point is below the line, so the pixel above the line (y+1) is to be lit up).  The scale factor is deltax.

	    d = deltay - deltax/2;
	    for (p = start; p.x <= end.x; p.x++){
		plot(p, c);
		if (d < 0) // next time through will light up east pixel
		    d += deltay;
		else{ // next time through will light up northeast pixel
		    p.y++;
		    d += deltay - deltax;
		}
	    }
	}

	// octants 2 and 6 (1 < slope)
	else if (deltax < deltay){
	    int d;  // d is a scaled version of the horizontal distance fom the ideal line's x-position at y+1 left to the midpoint of x and x+1 (a negative value means that the point is to the right of the line, so the pixel to the left of the line (x) is to be lit up; a positive value means that the point is to the left of the line, so the pixel to the right of the line (x+1) is to be lit up).  The scale factor is deltay.

	    d = deltax - deltay/2;
	    for (p = start; p.y <= end.y; p.y++){
		plot(p, c);
		if (d < 0) // next time through will light up north pixel
		    d += deltax;
		else{ // next time through will light up northeast pixel
		    p.x++;
		    d += deltax - deltay;
		}
	    }
	}

	// octants 4 and 8 (-1 < slope < 0)
	else if (-deltax < deltay && deltay < 0){
	    int d;  // d is a scaled version of the vertical distance fom the ideal line's y-position at x+1 up to the midpoint of y and y-1 (a negative value means that the point is below the line, so the pixel above the line (y) is to be lit up; a positive value means that the point is above the line, so the pixel below the line (y-1) is to be lit up).  The scale factor is deltax.

	    d = -deltay - deltax/2;
	    for (p = start; p.x <= end.x; p.x++){
		plot(p, c);
		if (d < 0)  // next time through light up east pixel)
		    d += -deltay;  // this can only make d bigger (more + or less -)
		else{  // next time through light up southeast pixel
		    p.y--;
		    d += -deltay - deltax;  // this can only make d smaller (less + or more -)
		}
	    }

	}

	// octants 3 and 7 (slope < -1)
	else if (deltay < -deltax){
	    // flips so that start has a lower y value than end
	    p = start;
	    start = end;
	    end = p;
	    deltax = -deltax;
	    deltay = -deltay;

	    int d;  // d is a scaled version of the horizontal distance fom the ideal line's x-position at y+1 right to the midpoint of x and x-1 (a negative value means that the point is to the left of the line, so the pixel to the right of the line (x) is to be lit up; a positive value means that the point is to the right of the line, so the pixel to the left the line (x-1) is to be lit up).  The scale factor is deltay.

	    d = -deltax - deltay/2;
	    for (p = start; p.y <= end.y; p.y++){
		plot(p, c);
		if (d < 0)  // next time through light up east pixel)
		    d += -deltax;  // this can only make d bigger (more + or less -)
		else{  // next time through light up southeast pixel
		    p.x--;
		    d += -deltax - deltay;  // this can only make d smaller (less + or more -)
		}
	    }

	}
	
    }
}