package nonMDL;

import java.io.*;
import java.util.*;
import java.lang.Math.*;

public class Vector extends PointMatrix {

    // goes from origin to to
    public Vector(PointMatrix to){
    	super(to.m[0][0], to.m[1][0], to.m[2][0]);
	// this is so not the right way to do this; not very sportsmanlike
    }

    // creates a vector from from to to
    public Vector(PointMatrix from, PointMatrix to){
	super(
	      to.m[0][0] - from.m[0][0],
	      to.m[1][0] - from.m[1][0],
	      to.m[2][0] - from.m[2][0]);
    }

    public double magnitude(){
	return Math.sqrt(m[0][0]*m[0][0] + 
			 m[1][0]*m[1][0] + 
			 m[2][0]*m[2][0]);
    }

    public Vector normalize(){
	return new Vector(new PointMatrix(m[0][0] / magnitude(),
					  m[1][0] / magnitude(),
					  m[2][0] / magnitude()));
    }

    public double dotProduct(Vector rhs){ 
	return m[0][0]*rhs.m[0][0] + m[1][0]*rhs.m[1][0] + m[2][0]*rhs.m[2][0];
    }

    public Vector crossProduct(Vector rhs){
    	return new Vector(new PointMatrix(m[1][0]*rhs.m[2][0] - m[2][0]*rhs.m[1][0],
					  m[2][0]*rhs.m[0][0] - m[0][0]*rhs.m[2][0],
					  m[0][0]*rhs.m[1][0] - m[1][0]*rhs.m[0][0]));
    }

    public Vector normalizedNormalVector (Vector nextCounterClockwise){
	return this.crossProduct(nextCounterClockwise).normalize();
    }

    public Vector scalarMult(double multiplier){
	return new Vector(new PointMatrix(m[0][0]*multiplier,
					  m[1][0]*multiplier,
					  m[2][0]*multiplier));
    }

    public Vector minus(Vector subtrahend){
	return new Vector(new PointMatrix(m[0][0] - subtrahend.m[0][0],
					  m[1][0] - subtrahend.m[1][0],
					  m[2][0] - subtrahend.m[2][0]));
    }

}