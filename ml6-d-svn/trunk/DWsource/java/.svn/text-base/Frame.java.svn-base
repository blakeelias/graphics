import java.io.*;
import java.util.*;

import javax.swing.*;
import java.awt.*;


public class Frame {

    public static final int XRES = 400;
    public static final int YRES = 400;
    public static final int MAX_COLORS = 255;


    private int width, height, maxcolor;
    private Color[][] screen;

    public Frame() {
	width = XRES; 
	height = YRES; 
	maxcolor = MAX_COLORS;
	screen = new Color[height][width];
	clear_screen();
    }

    public void clear_screen() {

	for (int x=0; x < width; x++) 
	    for (int y=0; y < height; y++){ 
		Color c = new Color(0, 0, 0);
		screen[y][x] = c;
	    }
    }
    
    public void plot(int x, int y, Color c) {

	int newx = x;
	int newy = y;
	screen[newy][newx] = c;
    }		
    
    public void save(String filename) {

	try {
	    FileOutputStream fstream = new FileOutputStream(filename);
	    PrintWriter f = new PrintWriter(fstream);
	    f.printf("P3\n%d %d\n%d\n", width, height, maxcolor);

	    for (int y=0; y < height; y++) { 
		for (int x=0; x < width; x++) 
		    f.printf("%d %d %d ",
			     screen[y][x].getRed(), screen[y][x].getGreen(), screen[y][x].getBlue());
		f.printf("\n");
	    }
	    f.close();
	}
	catch (IOException e) {}
	
    }
}