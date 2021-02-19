import java.io.*;
import java.util.*;

public class Point{
    public int x, y;

    public Point(int x, int y){
	this.x = x;
	this.y = y;
    }

    // returns a positive number if this.x > other.x
    public int compareTo (Point other){
	if (this.x > other.x)
	    return 1;
	if (this.x == other.x)
	    return 0;
	else
	    return -1;
    }

    // returns true if the two points make a horizontal line
    public boolean isHorizontal(Point other){
	return this.y == other.y;
    }

    // returns true if the two points make a vertical line
    public boolean isVertical(Point other){
	return this.x == other.x;
    }

}